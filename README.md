# Mario Kart Wii Lan through brainslug
Basically, this github combines a few projects in order to play Mario Kart Wii (MKW) Custom Distributions in LAN mode. 
This allows up to 12 players (2 per wii) to play together, no disc required!\

Only tested on PAL!
      

## Background
I discovered MKW custom distributions in april 2017 and have played a lot of them since then. Somewhere in early 2021, during the Covid-19 pandemic, I was looking for a possibility to play my favorite game in a LAN setup, so I could play with 11 of my friends and have a major LAN party when the lockdowns would end.

### Custom WFC
At first, I found the possibility to host my own WFC server through this post: https://mariokartwii.com/showthread.php?tid=885. I had some nice lan parties using this setup, but at random times the consoles would disconnect.

### Brainslug LAN module
I knew there was a LAN mod that makes the Wiis talk to each other directly (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) without the need for a server. This is a BrainSlug module, and BrainSlug is a disc patcher. Using the BrainSlug channel comes with a multitude of problems:
- No way to load cheats
- No support for custom distributions.
- No way to USB load the game

While I was willing to buy 6 MKW discs, the first 2 problems are a major issue for me. The cheats are needed because by default, the character/vehicle & track selection menus have a timer of 30 seconds. If you want to take a break between races, this is not possible, since the wii's will automatically select a character/vehicle and a track and the next race will load. Another example is that by default, 30 seconds after the first player crosses the finish line, the game will end. In a large LAN setup,  there might be some skill differences and 

### Solution Part 1
Then I discovered this post https://mariokartwii.com/showthread.php?tid=1891. In this post, Yuri explains the same problems as I had, but finds a solution that enables us to load a game from USB through the brainslug main.dol. Basically, you can tell USB loader GX to load an alternate dol file (other than the main.dol from the game).
If you rename the boot.dol from BrainSlug to RCMX01.dol and place it on the root of your SD card, it will load BrainSlug and its modules and then the game. Unfortunately, loading cheats through USB Loader GX does not work this way. However, luckily InvoxiPlayGames made him a Gecko Code Handler BrainSlug Module (gct.mod).
So, now 2 of the 3 problems indicated above are solved. 

### Solution Part 2
For the custom distribution part, Yuri already points is in the right direction. You see, 
The problem with Emvolution is that it does not support patched main.dol files. Custom distributions often patch main.dol to load le-code.bin. 
This is where the KamekLoader comes in. KamekLoader (Loader.bin) loads E/J/P/K.bin, taken from variety pack, which makes the game load le-code.bin 
In variety pack, E/J/P/K.bin also adds other functionality to the game.
Custom Distributions also often patch main.dol files to include cheat codes into their games. These cheats can be loaded by using the gct.mod Brainslug module.


## Instructions:
- Create a riivolution version of Wiimms Mario Kart Fun 2022-11 and place the files from riiv-sd-card\MKW-Fun-2022-11 inside root_SD/wiimms_mkw_fun 
- Create your .gct file (you can use this https://mariokartwii.com/gct/) and rename it to GAMEID.gct (e.g. RMCP01.gct for PAL) and place it in root_SD/codes 
- place the files in /root_SD on the root of your SD card 
- Load a vanilla mario kart wii through USB-loader GX 
- Select options and set alternate dol to "load from USB/SD" 


## Details
- The KameKLoader looks for Loader.bin inside sd_Card:/varietypack/boot/loader.bin. This is hardcoded becaused the loader was originally made for Variety Pack V3.
- For the same reason, Loader.bin looks for E/J/P/K.bin inside varietypack/ on the iso. Therefore, the replacements that Emvolution does should place these binaries there.

## Module Descriptions
Inside the bslug folder you will find 8 brainslug modules. Here is a short description:


| **Module**        | **Description**                                                                                                                                                                                                    |
|-------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| libfat.mod        | default module. needed for Emvolution                                                                                                                                                                              |
| libsd.mod         | default module. needed for Emvolution                                                                                                                                                                              |
| libfat-sd.mod     | default module. needed for Emvolution                                                                                                                                                                              |
| Emvolution.mod    | File replacements, like Riivolution. Does not support patched main.dol (e.g. to load le-code)                                                                                                                      |
| KamekLoader.mod   | Module to load the kamek loader (loader.bin).   |
| rmc-local-net.mod | LAN Mod from Chadderz & MrBean35000vr                                                                                                                                                                              |
| console-sd.mod    | creates a log file on root of sd.                                                                                                                                                                                  |
| gct.mod           | To load cheat codes  


## Credits
Shoutouts: 
- MrBean35000vr & Chadderz for their LAN Multiplayer brainslug mod (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) 
- Chadderz again for the work on Brainslug (https://github.com/Chadderz121/brainslug-wii) 
- InvoxiPlayGames for his/her work on Emvolution (https://github.com/InvoxiPlayGames/emvolution) 
- Yuri Bacon for this post on mariokartwii.com (https://mariokartwii.com/showthread.php?tid=1891) 
- Lami for his KamekLoader brainslug module (https://github.com/Lami-Lemmy/brainslug-wii/tree/vp3Loader/modules/vpKamekLoader) 
- BrawlBoxGaming for the KamekLoader itself (https://github.com/Brawlboxgaming/VP-Source)
- Wiimm for his awesome work on Wiimms Mario Kart Fun (https://wiki.tockdom.com/wiki/Wiimms_Mario_Kart_Fun_2022-11) (and Wiimmfi and much more ofcourse)

