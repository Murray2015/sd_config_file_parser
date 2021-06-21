/*
 * SD card configuration file reading library
 *
 * Copyright (c) 2014 Bradford Needham
 * (@bneedhamia, https://www.needhamia.com )
 * Licensed under LGPL version 2.1
 * a version of which should have been supplied with this file.
 */

#define SDCONFIGFILE_DEBUG

#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <stack>
#include <vector>
#include <fstream>
#include <cstring>
#include "SDConfigFile.h"

using namespace std;

/*
 * Opens the given file on the SD card.
 * Returns true if successful, false if not.
 *
 * configFileName = the name of the configuration file on the SD card.
 *
 * NOTE: SD.begin() must be called before calling our begin().
 */
bool SDConfigFile::begin(const char *configFileName, uint8_t maxLineLength)
{
    cout << "In begin \n";
    _lineLength = 0;
    _lineSize = 0;
    _valueIdx = -1;
    _atEnd = true;

    /*
   * Allocate a buffer for the current line.
   */
    _lineSize = maxLineLength + 1;
    _line = (char *)malloc(_lineSize);
    if (_line == 0)
    {
#ifdef SDCONFIGFILE_DEBUG
        cout << "out of memory";
#endif
        _atEnd = true;
        return false;
    }

    /*
   * To avoid stale references to configFileName
   * we don't save it. To minimize memory use, we don't copy it.
   */

    // _file = SD.open(configFileName, FILE_READ);
    // _file.open(configFileName);
    cout << "Config filename = " << configFileName << "\n";
    _file.open(configFileName);
    if (!_file.is_open())
    {
#ifdef SDCONFIGFILE_DEBUG
        cout << "Could not open SD file: ";
        cout << configFileName;
#endif
        _atEnd = true;
        return false;
    }

    // Initialize our reader
    _atEnd = false;

    cout << "Exiting begin \n";

    return true;
}

/*
 * Cleans up our SDCOnfigFile object.
 */
void SDConfigFile::end()
{
    if (_file)
    {
        _file.close();
    }

    if (_line != 0)
    {
        free(_line);
        _line = 0;
    }
    _atEnd = true;
}

/*
 * Reads the next name=value setting from the file.
 * Returns true if the setting was successfully read,
 * false if an error occurred or end-of-file occurred.
 */
bool SDConfigFile::readNextSetting()
{
    char bint = 0;
    cout << "In readNextSetting \n";

    if (_atEnd)
    {
        cout << "In _atEnd or error\n";
        return false; // already at end of file (or error).
    }

    _lineLength = 0;
    _valueIdx = -1;

    /*
   * Assume beginning of line.
   * Skip blank and comment lines
   * until we read the first character of the key
   * or get to the end of file.
   */
    while (true)
    {
        // bint = _file.read();
        // _file >> noskipws >> bint;
        // _file.get(&bint, 1);
        if (!_file.is_open())
        {
            cout << "file not open";
        }

        cout << "132 bint = " << bint << "\n";
        if (bint < 0)
        {
            cout << "In _atEnd or error\n";
            _atEnd = true;
            return false;
        }

        if ((char)bint == '#')
        {
            // Comment line.  Read until end of line or end of file.
            while (true)
            {
                cout << "In comment line\n";
                // bint = _file.read();
                _file >> noskipws >> bint;
                if (bint < 0)
                {
                    _atEnd = true;
                    return false;
                }
                if ((char)bint == '\r' || (char)bint == '\n')
                {
                    break;
                }
            }
            continue; // look for the next line.
        }

        // Ignore line ends and blank text
        if ((char)bint == '\r' || (char)bint == '\n' || (char)bint == ' ' || (char)bint == '\t')
        {
            cout << "In continue\n";
            continue;
        }

        break; // bint contains the first character of the name
    }

    // Copy from this first character to the end of the line.

    while (bint >= 0 && (char)bint != '\r' && (char)bint != '\n')
    {
        cout << "in while for copy \n ";
        cout << "177 bint = " << bint << "\n";
        if (_lineLength >= _lineSize - 1)
        { // -1 for a terminating null.
            _line[_lineLength] = '\0';
#ifdef SDCONFIGFILE_DEBUG
            cout << "Line too long: ";
            cout << _line;
            cout << bint;
#endif
            _atEnd = true;
            return false;
        }

        if ((char)bint == '=')
        {
            // End of Name; the next character starts the value.
            _line[_lineLength++] = '\0';
            _valueIdx = _lineLength;
            cout << "In =\n";
        }
        else
        {
            cout << "199 bint = " << bint << "\n";
            _line[_lineLength++] = bint;
            cout << "_line = " << _line << "_lineLength = " << _lineLength << "\n";
            // cout << "In else\n";
            // cout << "Line = " << _line << "\n";
            // cout << "bint = " << bint << "\n";
            // cout << "char bint = " << (char)bint << "\n";
        }

        // bint = _file.read();
        // _file >> noskipws >> bint;
        // _file.get(&bint, 1);
        bint = _file.get();
    }

    if (bint < 0)
    {
        cout << "In bint < 0 end of file thing\n";
        _atEnd = true;
        // Don't exit. This is a normal situation:
        // the last line doesn't end in newline.
    }
    _line[_lineLength] = '\0';

    /*
   * Sanity checks of the line:
   *   No =
   *   No name
   * It's OK to have a null value (nothing after the '=')
   */
    if (_valueIdx < 0)
    {
#ifdef SDCONFIGFILE_DEBUG
        cout << "Missing '=' in line: ";
        cout << _line;
#endif
        _atEnd = true;
        return false;
    }
    if (_valueIdx == 1)
    {
#ifdef SDCONFIGFILE_DEBUG
        cout << "Missing Name in line: =";
        cout << _line[_valueIdx];
#endif
        _atEnd = true;
        return false;
    }

    // Name starts at _line[0]; Value starts at _line[_valueIdx].
    return true;
}

/*
 * Returns true if the most-recently-read setting name
 * matches the given name, false otherwise.
 */
bool SDConfigFile::nameIs(const char *name)
{
    if (strcmp(name, _line) == 0)
    {
        return true;
    }
    return false;
}

/*
 * Returns the name part of the most-recently-read setting.
 * or null if an error occurred.
 * WARNING: calling this when an error has occurred can crash your sketch.
 */
const char *SDConfigFile::getName()
{
    cout << " IN get name " << _lineLength << " | " << _valueIdx << " | " << &_line[0] << "\n";
    if (_lineLength <= 0 || _valueIdx <= 1)
    {
        return 0;
    }
    return &_line[0];
}

/*
 * Returns the value part of the most-recently-read setting,
 * or null if there was an error.
 * WARNING: calling this when an error has occurred can crash your sketch.
 */
const char *SDConfigFile::getValue()
{
    if (_lineLength <= 0 || _valueIdx <= 1)
    {
        return 0;
    }
    return &_line[_valueIdx];
}

/*
 * Returns a persistent, dynamically-allocated copy of the value part
 * of the most-recently-read setting, or null if a failure occurred.
 * 
 * Unlike getValue(), the return value of this function
 * persists after readNextSetting() is called or end() is called.
 */
char *SDConfigFile::copyValue()
{
    char *result = 0;
    int length;

    if (_lineLength <= 0 || _valueIdx <= 1)
    {
        return 0; // begin() wasn't called, or failed.
    }

    length = strlen(&_line[_valueIdx]);
    result = (char *)malloc(length + 1);
    if (result == 0)
    {
        return 0; // out of memory
    }

    strcpy(result, &_line[_valueIdx]);

    return result;
}

/*
 * Returns the value part of the most-recently-read setting
 * as an integer, or 0 if an error occurred.
 */
int SDConfigFile::getIntValue()
{
    const char *str = getValue();
    if (!str)
    {
        return 0;
    }
    return atoi(str);
}

/*
 * Returns the value part of the most-recently-read setting
 * as a bool.
 * The value "true" corresponds to true;
 * all other values correspond to false.
 */
bool SDConfigFile::getBooleanValue()
{
    if (strcmp("true", getValue()) == 0)
    {
        return true;
    }
    return false;
}