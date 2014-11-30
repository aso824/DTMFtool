DTMF Tool
=========

This is a simple tool for DTMF ([Wikipedia](http://en.wikipedia.org/wiki/DTMF)). Written in modern C++ with Qt 5.3. License is GPL (more details in `LICENSE.txt` file), so feel free to use and share.

Features
--------

* Keyboard like cellphone - just press for tone. All tones from DTMF standard: from 0 to 9 and from A to D. You can set tone length (single-press mode) or emit tone by holding the button.
* Generator - enter number (very handy for *Echolink*), set parameters - tone length and interval between tones - and click play. 
* Decoder - select audio input and see tones. Also you have spectrum monitor hidden in menu.
* UI styling - you can use light or dark colors.

**Note**: some features may not be accessible due to still development stage. Final, stable version (*v1.0*) will have all features listed above.

Requirements
------------
- Modern Linux 
- Graphical desktop
- Qt 5 libraries installed
- Qt Multimedia library 
- More than 512MB RAM and 2 GHz CPU

Qt packets can be downloaded from your distribution repository.

How to build
------------

Easiest way: you need *Qt Creator* 3.0 or newer. Just open `.pro` file in creator and compile. Of course you must have compiler and Qt development packages installed.