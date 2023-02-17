# Mario Kart Wii Lan through brainslug
Basically, this github combines a few projects in order to play Mario Kart Wii (MKW) in LAN mode. 
This allows up to 12 players (2 per wii) to play together, no disc required!
Also, with some modding it supports different custom distributions
Only tested on PAL!

Shoutouts:
MrBean35000vr & Chadderz for their LAN Multiplayer brainslug mod (https://www.chadsoft.co.uk/downloads/LAN_MKW_v0.9.zip) \
Chadderz again for the work on Brainslug (https://github.com/Chadderz121/brainslug-wii) \
InvokiPlayGames for his/her work on Emvolution (https://github.com/InvoxiPlayGames/emvolution) \
Yuri Bacon for this post on mariokartwii.com (https://mariokartwii.com/showthread.php?tid=1891) \
Lami for his KamekLoader brainslug module (https://github.com/Lami-Lemmy/brainslug-wii/tree/vp3Loader/modules/vpKamekLoader) \
BrawlBoxGaming for the KamekLoader itself (https://github.com/Brawlboxgaming/VP-Source)\

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

The problem with Emvolution is that it does not support patched main.dol files. Custom distributions often
patch main.dol to load le-code.bin. This is where the KamekLoader comes in. 
KamekLoader (Loader.bin) loads E/J/P/K.bin, taken from variety pack, which makes the game load le-code.bin 
In variety pack, E/J/P/K.bin also adds other functionality to the game


## Instructions:
Create a riivolution version of Wiimms Mario Kart Fun 2022-11 and place the files from riiv-sd-card\MKW-Fun-2022-11 inside root_SD/wiimms_mkw_fun
Create your .gct file (you can use this https://mariokartwii.com/gct/) and rename it to GAMEID.gct (e.g. RMCP01.gct for PAL) and place it in root_SD/codes
place the files in /root_SD on the root of your SD card
Load a vanilla mario kart wii through USB-loader GX
Select options and set alternate dol to "load from USB/SD"

# Compiling the KamekLoader

http://web.archive.org/web/20160602205749/http://www.nxp.com/products/software-and-tools/software-development-tools/codewarrior-development-tools/downloads/special-edition-software:CW_SPECIALEDITIONS
# Compiling the KamekLoader Brainslug Module

# Compiling Emvolution
