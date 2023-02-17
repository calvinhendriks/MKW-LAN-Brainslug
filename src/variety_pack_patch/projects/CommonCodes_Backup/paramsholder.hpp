
#pragma once
#include <Kamek/kamek.hpp>
#include <System/system.hpp>
#include <egg/egg.hpp>
#define customButtons 1
#define curVersion 1

class Settings0{
    //empty just exists to pass it in the ctor lol
};

class Settings1{ 
public:
    Settings1(){
        magic[0] = 'V';
        magic[1] = 'P';
        version = curVersion;
        settingsRadioCount = 3;
    };
    Settings1(Settings0 *oldSettings) //in case a new file needs to get built
    {
        magic[0] = 'V';
        magic[1] = 'P';
        version = curVersion;
        settingsRadioCount = 3;
    }
    char magic[2]; //"VP"
    //padding 2
    u32 version; //just in case more than 255 versions
    u8 settingsRadioCount;
    u8 radioSetting[6];
    u8 scrollSetting[6];
};

class ParamsHolder {
public:
    ParamsHolder();
    void SaveSettings();
    Settings1 settings;
    static ParamsHolder *sInstance;
    //any global var can go here I guess
};

