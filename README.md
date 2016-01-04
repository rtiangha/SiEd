# SiEd
This is the original SiEd text editor for Palm OS devices developed by Benjamin Roe. This project was originally developed by Ben Roe and was hosted at [benroe.com](https://web.archive.org/web/20070323092635/http://benroe.com/sied/index.php) which shut down some time in mid-2007.

The final stable version released publically was 0.9.11 released on March 5, 2005 and the final beta version was 0.10-beta3 released on April 27, 2005.

## What Is It?
SiEd is a free simple text editor for Palm OS® based handhelds. Its purpose is to provide an easy way to create and edit large text documents on Palm OS devices, without the limitations of the built-in Memopad program. It's designed mainly for use with an external keyboard of some sort, although of course works fine without. The program is distributed under the GPL.

## Instructions
To install SiEd, just download the latest PRC file and use your favourite Palm desktop sofware to copy the file to your Palm. If you want to hack around with the source or build your own PRC you'll need the prc-tools package and a PalmOS SDK installed.

Using the editor is pretty self explanatory. All commands have a keyboard equivalent (listed in the menus). Documents auto-save on exiting the application. There is a simple User Guide if you need it.

## Features

* Support for plain-text files on VFS volumes
* DOC format support (uncompressed only at present)
* Edit ~600Kb files on most PalmOS 5 devices, ~100Kb files on earlier devices
* Search and replace
* Word count
* Large undo history
* Encrypted file support using 128-bit AES encryption
* Split view - view/edit two files at once Emacs style
* Macro Recording
* Support for text/plain files through Exchange Manager (beaming, inter-application transfer etc)
* 12 display fonts (4 Hires, 4 standard Palm, 4 normal-resolution)
* GPL licensed

## Requirements
* PalmOS v.3.5 or greater

## Development Environment
Compiles using PRC-Tools and PiLRC.

The original 2005 release as published by Benjamin Roe was slightly modified in order to compile using more modern Palm SDKs released after 2005 (mainly, the addition of a few more library header includes in the editor.cc file). Has tested as successfully compiling using either Palm OS 5 SDK R3 or R4 combined with Palm Desktop SDK 5.4. It might work with other combinations of the Palm/Garnet SDKs as well, but for future development, it'd be wise to standardize on these versions of the SDKs. With the inclusion of the new library includes in editor.cc, SiEd may no longer compile successfully using older SDK versions without reverting the changes first.

## How to Build?

Building a PalmOS executable from this source code requires a complete install of the prc-tools package, available from:

http://prc-tools.sourceforge.net

as well as Palm OS 5 SDK R3 or R4 along with Palm Desktop SDK 5.4.

When creating your Palm SDK directory by combining the OS and the Desktop SDKs, ensure that the 68K and Common directories of the Desktop SDK appear inside the root include folder of the OS SDK. Depending on where you got your SDKs, they may be formatted for Windows machines, which may give warnings when compiling under a Linux environment. If so, you'll want to run all of the text files through a utility such as dos2unix to convert them to a Unix-friendly format. 

The targets (i.e. type make target) available for the make process are:

all: builds the English language full version

portuguese,norwegian,dutch,italian,french,german,spanish,catalan: builds appropriate language

Copyright Notice: This software is licensed under the terms of the GPL, included in the COPYING file in the source code directory.

The icons are (C) Stefan Smith and Tankut Enric, and the copyright for the translations is attributed in the relevant file. Everything else is (C) Benjamin Roe.
