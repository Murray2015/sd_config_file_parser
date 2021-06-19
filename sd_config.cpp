#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <stack>
#include <vector>
#include <fstream>
#include "SDConfigFile.h"
using namespace std;

const char *configFileName = "config.cfg";
// const int pinSelect = SDCARD_SS_PIN;
const int maxLineLength = 50;
SDConfigFile cfg;

int INFO;
int USB_SERIAL;
int SD_INCLUDE;
int PIX_INCLUDE;
int SHT_INCLUDE;
int FTBOARD_INCLUDE;
int VALVES_INCLUDE;
int PUMP_INCLUDE;
int WDT_INCLUDE;
int DIGI_INCLUDE;
int GSS_INCLUDE;
int PART_INCLUDE;
int DATA_CACHING;
int DO_TIMING;
int USE_SERMON;
int USE_SERDATA;

void setup()
{
    cout << "In setup";

    if (cfg.begin("config.cfg", 20))
    {
        while (cfg.readNextSetting())
        {
            cout << "Before if statement\n";
            if (cfg.nameIs("INFO"))
            {
                INFO = cfg.getIntValue();
            }
            else if (cfg.nameIs("USB_SERIAL"))
            {
                USB_SERIAL = cfg.getIntValue();
            }
            else if (cfg.nameIs("SD_INCLUDE"))
            {
                SD_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("PIX_INCLUDE"))
            {
                PIX_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("SHT_INCLUDE"))
            {
                SHT_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("FTBOARD_INCLUDE"))
            {
                FTBOARD_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("VALVES_INCLUDE"))
            {
                VALVES_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("PUMP_INCLUDE"))
            {
                PUMP_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("WDT_INCLUDE"))
            {
                WDT_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("DIGI_INCLUDE"))
            {
                DIGI_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("GSS_INCLUDE"))
            {
                GSS_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("PART_INCLUDE"))
            {
                PART_INCLUDE = cfg.getIntValue();
            }
            else if (cfg.nameIs("DATA_CACHING"))
            {
                DATA_CACHING = cfg.getIntValue();
            }
            else if (cfg.nameIs("DO_TIMING"))
            {
                DO_TIMING = cfg.getIntValue();
            }
            else if (cfg.nameIs("USE_SERMON"))
            {
                USE_SERMON = cfg.getIntValue();
            }
            else if (cfg.nameIs("USE_SERDATA"))
            {
                USE_SERDATA = cfg.getIntValue();
            }
            else
            {
                cout << "The name of this setting is:";
                cout << cfg.getName();
            }
        }
        cfg.end();
    }
}

void loop()
{
    cout << "hi";
    cout << INFO;
    cout << USB_SERIAL;
    cout << SD_INCLUDE;
    cout << PIX_INCLUDE;
    cout << SHT_INCLUDE;
    cout << FTBOARD_INCLUDE;
    cout << VALVES_INCLUDE;
    cout << PUMP_INCLUDE;
    cout << WDT_INCLUDE;
    cout << DIGI_INCLUDE;
    cout << GSS_INCLUDE;
    cout << PART_INCLUDE;
    cout << DATA_CACHING;
    cout << DO_TIMING;
    cout << USE_SERMON;
    cout << USE_SERDATA;
    //     digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    //     delay(1000);                     // wait for a second
    //     digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    //     delay(1000);
}

int main(void)
{
    cout << "Running setup";
    setup();
}

// int main(void)
// {
//     cout << "This is a test\n";

//     // char buffer;
//     // ifstream ConfigFile;
//     // ConfigFile.open("./config.cfg");

//     // while (ConfigFile >> noskipws >> buffer)
//     // {
//     //     cout << buffer;
//     // }

//     // ConfigFile.close();
// }