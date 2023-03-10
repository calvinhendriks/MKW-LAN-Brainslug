@echo off
SETLOCAL EnableDelayedExpansion

cls

:: Make build folder
mkdir build

::Hardcoded because yes
mkdir build\tileset

:: CPP compilation settings
SET CC="../../cw/mwcceppc.exe"
SET CFLAGS=-I- -i ../../libraries/ -i ../CommonCodes -Cpp_exceptions off -enum int -O4,s -use_lmw_stmw on -fp hard -rostr -sdata 0 -sdata2 0 -maxerrors 1
SET DEFINES=-d CHANGECOMBO=1 -d LECODE=1
REM SET CPPFILES=
REM for %%f in (*.cpp) do SET "CPPFILES=%%~nf !CPPFILES!"
SET COMMONCPPFILES=
for %%f in (../CommonCodes/*.cpp) do SET "COMMONCPPFILES=%%~nf !COMMONCPPFILES!"

:: Compile CPP
REM SET OBJECTS=
REM FOR %%H IN (%CPPFILES%) DO (
    REM echo "Compiling %%H.cpp..."
    REM %CC% %CFLAGS% %DEFINES% -c -o build/%%H.o %%H.cpp
    REM SET "OBJECTS=build/%%H.o !OBJECTS!"
REM )

SET COMMONOBJECTS=
FOR %%H IN (%COMMONCPPFILES%) DO (
    echo "Compiling %%H.cpp..."
    %CC% %CFLAGS% %DEFINES% -c -o build/%%H.o "../CommonCodes/%%H.cpp"
    SET "COMMONOBJECTS=build/%%H.o !COMMONOBJECTS!"
)

::C:/devkitPro/devkitPPC/bin/powerpc-eabi-readelf -s build/%%H.o

:: Link
echo Linking...
"../../Kamek/bin/Debug/Kamek.exe" %COMMONOBJECTS% -dynamic -externals=../../symbols.txt -versions=../../versions.txt -output-kamek=../vp/build/$KV$.bin
if %ErrorLevel% equ 0 (
	copy /y "..\vp\build\*.bin" "..\vp\"
    REM copy /y "..\vp\build\*.bin" "files\Uploaded Packs\varietypack\boot\"

)

REM rmdir /Q /S build

:end
ENDLOCAL