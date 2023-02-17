# Mario Kart Wii Lan through brainslug
Basically, this github combines a few projects in order to play Mario Kart Wii (MKW) in LAN mode. 
This allows up to 12 players (2 per wii) to play together, no disc required!
Also, with some modding it supports different custom distributions
Only tested on PAL!

Shoutouts: 
- MrBean35000vr & Chadderz for their LAN Multiplayer brainslug mod (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) 
- Chadderz again for the work on Brainslug (https://github.com/Chadderz121/brainslug-wii) 
- InvokiPlayGames for his/her work on Emvolution (https://github.com/InvoxiPlayGames/emvolution) 
- Yuri Bacon for this post on mariokartwii.com (https://mariokartwii.com/showthread.php?tid=1891) 
- Lami for his KamekLoader brainslug module (https://github.com/Lami-Lemmy/brainslug-wii/tree/vp3Loader/modules/vpKamekLoader) 
- BrawlBoxGaming for the KamekLoader itself (https://github.com/Brawlboxgaming/VP-Source)
- Wiimm for his awesome work on Wiimms Mario Kart Fun (https://wiki.tockdom.com/wiki/Wiimms_Mario_Kart_Fun_2022-11) (and Wiimmfi and much more ofcourse)

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

## Background
### Custom WFC
I have played custom distributions since april 2017 and I can't go back to vanilla ever since. I wanted to play Mario Kart Wii in a LAN setup since early 2020. 
At first, I found the possibility to host my own WFC server through this post: https://mariokartwii.com/showthread.php?tid=885. I had some nice lan parties using this setup, but at random times the consoles would disconnect.  \

### Brainslug LAN module
I knew there was a LAN mod that makes the Wiis talk to each other directly (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) without the need for a server. This is a BrainSlug module, and BrainSlug is a disc patcher. Using the BrainSlug channel comes with a multitude of problems:
- No way to load cheats
- No support for custom distributions.
- A need for 6 mario kart wii discs

While I was willing to buy 6 MKW discs, the first 2 problems are a major issue for me. The cheats are needed because by default, the character/vehicle & track selection menus have a timer of 30 seconds. If you want to take a break between races, this is not possible, since the wii's will automatically select a character/vehicle and a track and the next race will load. Another example is that by default, 30 seconds after the first player crosses the finish line, the game will end. In a large LAN setup,  there might be some skill differences and 

### Solution
Then I discovered this post https://mariokartwii.com/showthread.php?tid=1891

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

