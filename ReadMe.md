# ZScope
ZaidaTek ZScope



Use your PC and Arduino as an Oscilloscope!



![ZScope](https://github.com/ZaidaTek/ZScope/blob/master/ZScope-v20200706.png "ZScope-v20200706")



Features

1) 1-100 kHz combined measuring rate (75-80 kHz for 2+ channels)

2) Up to eight channels simultaneously

3) Basic trigger and cursor functions.



Quick Install Guide

1) Download https://github.com/ZaidaTek/ZScope/raw/master/ZScope-v20200706.zip

2) Extract to folder of your choice.

3) Upload included at328p.ino file to your Arduino Uno/Nano or similiar AT328P.

4) Execute ZScope.exe, choose your COM-Port, channel config and measuring rate, and click connect.

Note: If your Arduino uses an FTDI USB/Serial Chip, you need to adjust its latency from the default 16 ms to 1 ms for best performance.

To do this, go to Device Manager, open COM port, go to "Port Settings", click "Advanced" and adjust latency to 1 ms.

USB/Serial chip CH340 does not have this issue, but has many COM communication errors at higher measuring rates.



Requirements

1) Windows 7 or newer operating system (Tested on Windows 7 and Windows 10 systems)

2) Arduino Uno/Nano/other AT328P systems



Copyright (C) 2019-2020 ZaidaTek and Andreas Riebesehl

This work is licensed under: Creative Commons Attribution-NoDerivatives 4.0 International Public License

For full license text, please visit: https://creativecommons.org/licenses/by-nd/4.0/legalcode
