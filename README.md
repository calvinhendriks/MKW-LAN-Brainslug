# Mario Kart Wii LAN mode through brainslug
Basically, this github combines a few projects in order to play Mario Kart Wii (MKW) Custom Track Distributions in LAN mode. 
This allows up to 12 players (2 per wii) to play together, no disc required! \
\
Only tested on PAL!
      

## 1. Background
I discovered MKW custom track distributions in april 2017 and have played a lot of them since then. Somewhere in early 2021, during the Covid-19 pandemic, I was looking for a possibility to play my favorite game in a LAN setup, so I could play with 11 of my friends and have a major LAN party when the lockdowns would end.

### 1.1 Custom WFC
At first, I found the possibility to host my own WFC server through this post: https://mariokartwii.com/showthread.php?tid=885. I had some nice lan parties using this setup, but at random times the consoles would disconnect.

### 1.2 Brainslug LAN module
I knew there was a LAN mod that makes the Wiis talk to each other directly (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) without the need for a server. This is a BrainSlug module, and BrainSlug is a disc patcher. Using the BrainSlug channel comes with a multitude of problems:
- No way to load cheats
- No support for custom track distributions.
- No way to USB load the game

While I was willing to buy 6 MKW discs, the first 2 problems are a major issue for me. The cheats are needed because by default, the character/vehicle & track selection menus have a timer of 30 seconds. If you want to take a break between races, this is not possible, since the wii's will automatically select a character/vehicle and a track and the next race will load. Another example is that by default, 30 seconds after the first player crosses the finish line, the game will end. In a large LAN setup,  there might be some skill differences and we would like everyone to be able to finish.

## 2. Solution Pt I
Then I discovered this post https://mariokartwii.com/showthread.php?tid=1891. In this post, Yuri explains the same problems as I had, but finds a solution that enables us to load a game from USB through the brainslug main.dol. Basically, you can tell USB loader GX to load an alternate dol file (other than the main.dol from the game).
If you rename the boot.dol from BrainSlug to RCMX01.dol and place it on the root of your SD card, it will load BrainSlug and its modules and then the game. Unfortunately, loading cheats through USB Loader GX does not work this way. However, luckily InvoxiPlayGames made him a Gecko Code Handler BrainSlug Module (gct.mod).
So, now 2 of the 3 problems indicated above are solved. 

## 3. Solution Pt II
Now we only need to solve the custom track distribution issue. 
Custom Track Distributions often come in 2 flavours: 
- An ISO Builder script
- A riivolution folder. \

These roughly do the same thing; The ISO Builder extracts the files from a supplied vanilla MKWII iso and replaces some files. Often, it also patches the main.dol with some cheatcodes and patches it to load LE-CODE. Riivolution also does these file replacements, but on the wii itself (you need the original disc). For riivolution mods, the main.dol that replaces the original is already patched to contain the cheats and load LE-CODE. \

For the custom track distribution part, Yuri already points is in the right direction; Emvolution, also by InvoxiPlayGames. Emvolution is basically a riivolution BrainSlug module. The problem with Emvolution is that it does not support patched main.dol files. However, most custom distributions rely on LE-CODE (for the scrollable cups selection screen for example). \

This is where the KamekLoader comes in. KamekLoader (Loader.bin) loads E/J/P/K.bin, taken from variety pack, which makes the game load lecode-XXX.bin (XXX = USA/JAP/PAL/KOR). In variety pack, E/J/P/K.bin also adds other functionality to the game. \
Finally, we have solved all issues and we are able to play MKWII Custom Track Distribution in LAN Mode without any disc, while also loading our beloved cheat codes.

## 3. Summary
- Load ISO through BrainSlug by selecting alt dol file in USB Loader GX
- LAN functionality from rmc-local-net.mod BrainSlug module(LAN Mod from Cadderz & MrBean35000vr)
- Load cheats by using gct.mod BrainSlug module
- Patch in the Custom Tracks through Emvolution.mod BrainSlug module
- Patch in KamekLoader (Loader.bin) with KamekLoader.mod BrainSlug module. The KamekLoader loads E.bin, which in turn loads 

## 3. Prepping SD card
The SD card needs to be formatted in a proper way, otherwise you will get green error screens.
- First, Run SD Card Formatter from SD Card association (https://www.sdcard.org/downloads/formatter/sd-memory-card-formatter-for-windows-download/) as Administrator. Select the correct SD card and click start.
- Next, if your SD card is larger than 32GB (i.e. 64GB and up) run FAT32 GUI formatter as Administrator. Select your SD card and Set Allocation size unit to 4096 bytes. Make sure Quick Format is checked. Click on start.


## 4. Instructions (Wiimms Mario Kart Fun):
- Create a riivolution version of Wiimms Mario Kart Fun 2022-11 and place the files from riiv-sd-card\MKW-Fun-2022-11 inside root_SD/wiimms_mkw_fun 
- Create your .gct file (you can use this https://mariokartwii.com/gct/) and rename it to GAMEID.gct (e.g. RMCP01.gct for PAL) and place it in root_SD/codes 
- place the files in /root_SD on the root of your SD card 
- Load a vanilla mario kart wii through USB Loader GX 
- Select options and set alternate dol to "load from USB/SD" 


## 5. Instruction (other distros)
- Take a look at the ISO builder script or riivolution .xml file.
- Mimic the replacements done using Emvolution. Edit replacements.h and compile. Replace the emvolution.mod inside root_SD/bslug/modules/
- If you see some cheats being patched into main.dol in the ISO builder, take the .gct file and place it in root_SD/codes/RMCX01.gct

## 6. Details
- The KameKLoader looks for Loader.bin inside sd:/varietypack/boot/loader.bin. This is hardcoded becaused the loader was originally made for Variety Pack V3.
- For the same reason, Loader.bin looks for E/J/P/K.bin inside varietypack/ on the iso. Therefore, the replacements that Emvolution does should place these binaries there.
- E/J/P/K.bin looks for lecode-XXX.bin inside the rel/ folder on the iso. Make sure emvolution puts the lecode-XXX.bin there!

## 7. Module Descriptions
Inside the bslug folder you will find 8 brainslug modules. Here is a short description:


| **Module**        | **Description**                                                                                                                                                                                                                      |
|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| rmc-local-net.mod | LAN Mod from Chadderz & MrBean35000vr                                                                                                                                                                                                |
| gct.mod           | Module to load cheat codes through BrainSlug                                                                                                                                                                                         |
| libfat.mod        | default module. needed for Emvolution                                                                                                                                                                                                |
| libsd.mod         | default module. needed for Emvolution                                                                                                                                                                                                |
| libfat-sd.mod     | default module. needed for Emvolution                                                                                                                                                                                                |
| Emvolution.mod    | File replacements, like Riivolution. Does not support patched main.dol (e.g. to load le-code)                                                                                                                                        |
| KamekLoader.mod   | Module to load the kamek loader (Loader.bin).  Loader.bin loads E/J/P/K.bin, taken from variety pack, which makes the game load lecode-XXX.bin (XXX = region) In variety pack, E/J/P/K.bin also adds other functionality to the game |
| console-sd.mod    | creates a log file on root of sd.                                                                                                                                                                                                    |

## 8. Credits
Shoutouts: 
- MrBean35000vr & Chadderz for their LAN Multiplayer brainslug mod (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) 
- Chadderz again for the work on Brainslug (https://github.com/Chadderz121/brainslug-wii) 
- InvoxiPlayGames for his/her work on Emvolution (https://github.com/InvoxiPlayGames/emvolution) 
- Yuri Bacon for this post on mariokartwii.com (https://mariokartwii.com/showthread.php?tid=1891) 
- Lami for his KamekLoader brainslug module (https://github.com/Lami-Lemmy/brainslug-wii/tree/vp3Loader/modules/vpKamekLoader) 
- BrawlBoxGaming for the KamekLoader itself (https://github.com/Brawlboxgaming/VP-Source)
- Wiimm for his awesome work on Wiimms Mario Kart Fun (https://wiki.tockdom.com/wiki/Wiimms_Mario_Kart_Fun_2022-11) (and Wiimmfi and much more ofcourse)

## 9. FAQ
- Why do i need to format twice?\
The SD/SDHC/SDXC memory cards have a "Protected Area" on the card for the SD standard's security function. The SD Formatter (from SD Associatino) does not format the "Protected Area". \
The Wii is very picky when it comes to SD cards. I got the best results if i first ran this formatter. However, this tool sets the cluster size based on the total size of the SD card. \
According to this page (https://wiibrew.org/wiki/SD/SDHC_card_compatibility_tests), issues can sometimes be fixed by setting cluster size to 4096 bytes. This is where FAT32 GUI Formatter comes in.

- Game does not load (green / black screen) \
Check the RMCX.log on the root of the SD card. This tells you if files can't be found.

- Game loads, but I get "An error has occured. Press the EJECT button, ..." \
This is often when a license has been used before on different server. Please delete it and play from a fresh license.
