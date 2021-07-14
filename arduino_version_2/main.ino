#include <iostream>
#include <stdio.h>
#include <iomanip>
#include <stack>
#include <vector>
#include <fstream>
#include "SDConfigFile.h"
using namespace std;

const char *configFileName = "/fs/config.cfg";
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
String asdf;

void setup()
{
    Serial.begin(9600);
    if (cfg.begin("./config.cfg", 20))
    {
        while (cfg.readNextSetting())
        {
            if (cfg.nameIs("INFO"))
            {
                INFO = cfg.getIntValue();
                Serial.print("value INFO is ");
                Serial.println(INFO);
            }
            else if (cfg.nameIs("USB_SERIAL"))
            {
                USB_SERIAL = cfg.getIntValue();
                Serial.print("value of USB_SERIAL is ");
                Serial.println(USB_SERIAL);
            }
            else if (cfg.nameIs("SD_INCLUDE"))
            {
                SD_INCLUDE = cfg.getIntValue();
                Serial.print("value of SD_INCLUDE is ");
                Serial.println(SD_INCLUDE);
            }
            else if (cfg.nameIs("PIX_INCLUDE"))
            {
                PIX_INCLUDE = cfg.getIntValue();
                Serial.print("value of PIX_INCLUDE is ");
                Serial.println(PIX_INCLUDE);
            }
            else if (cfg.nameIs("SHT_INCLUDE"))
            {
                SHT_INCLUDE = cfg.getIntValue();
                Serial.print("value of SHT_INCLUDE is ");
                Serial.println(SHT_INCLUDE);
            }
            else if (cfg.nameIs("FTBOARD_INCLUDE"))
            {
                FTBOARD_INCLUDE = cfg.getIntValue();
                Serial.print("value of USE_SERDATA FTBOARD_INCLUDE");
                Serial.println(FTBOARD_INCLUDE);
            }
            else if (cfg.nameIs("VALVES_INCLUDE"))
            {
                VALVES_INCLUDE = cfg.getIntValue();
                Serial.print("value of USE_SERDATA VALVES_INCLUDE");
                Serial.println(VALVES_INCLUDE);
            }
            else if (cfg.nameIs("PUMP_INCLUDE"))
            {
                PUMP_INCLUDE = cfg.getIntValue();
                Serial.print("value of PUMP_INCLUDE is ");
                Serial.println(PUMP_INCLUDE);
            }
            else if (cfg.nameIs("WDT_INCLUDE"))
            {
                WDT_INCLUDE = cfg.getIntValue();
                Serial.print("value of WDT_INCLUDE is ");
                Serial.println(WDT_INCLUDE);
            }
            else if (cfg.nameIs("DIGI_INCLUDE"))
            {
                DIGI_INCLUDE = cfg.getIntValue();
                Serial.print("value of DIGI_INCLUDE is ");
                Serial.println(DIGI_INCLUDE);
            }
            else if (cfg.nameIs("GSS_INCLUDE"))
            {
                GSS_INCLUDE = cfg.getIntValue();
                Serial.print("value of GSS_INCLUDE is ");
                Serial.println(GSS_INCLUDE);
            }
            else if (cfg.nameIs("PART_INCLUDE"))
            {
                PART_INCLUDE = cfg.getIntValue();
                Serial.print("value of PART_INCLUDE is ");
                Serial.println(PART_INCLUDE);
            }
            else if (cfg.nameIs("DATA_CACHING"))
            {
                DATA_CACHING = cfg.getIntValue();
                Serial.print("value of DATA_CACHING is ");
                Serial.println(DATA_CACHING);
            }
            else if (cfg.nameIs("DO_TIMING"))
            {
                DO_TIMING = cfg.getIntValue();
                Serial.print("value of DO_TIMING is ");
                Serial.println(DO_TIMING);
            }
            else if (cfg.nameIs("USE_SERMON"))
            {
                USE_SERMON = cfg.getIntValue();
                Serial.print("value of USE_SERMON is ");
                Serial.println(USE_SERMON);
            }
            else if (cfg.nameIs("USE_SERDATA"))
            {
                USE_SERDATA = cfg.getIntValue();
                Serial.print("value of USE_SERDATA is ");
                Serial.println(USE_SERDATA);
            }
            else if (cfg.nameIs("asdf"))
            {
                asdf = cfg.getValue();
                Serial.print("value of asdf is ");
                Serial.println(asdf);
            }
            else
            {
                Serial.print("The name of this setting is:");
                Serial.println(cfg.getName());
            }
        }
        cfg.end();
    }
}

void loop()
{
    Serial.println("Start of loop");
    Serial.println(INFO);
    Serial.println(USB_SERIAL);
    Serial.println(SD_INCLUDE);
    Serial.println(PIX_INCLUDE);
    Serial.println(SHT_INCLUDE);
    Serial.println(FTBOARD_INCLUDE);
    Serial.println(VALVES_INCLUDE);
    Serial.println(PUMP_INCLUDE);
    Serial.println(WDT_INCLUDE);
    Serial.println(DIGI_INCLUDE);
    Serial.println(GSS_INCLUDE);
    Serial.println(PART_INCLUDE);
    Serial.println(DATA_CACHING);
    Serial.println(DO_TIMING);
    Serial.println(USE_SERMON);
    Serial.println(USE_SERDATA);
    //     digitalWrite(LED_BUILTIN, HIGH); // turn the LED on (HIGH is the voltage level)
    //     delay(1000);                     // wait for a second
    //     digitalWrite(LED_BUILTIN, LOW);  // turn the LED off by making the voltage LOW
    //     delay(1000);
}
