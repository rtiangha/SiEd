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

## How to Build?

Building a PalmOS executable from this source code requires a complete install of the prc-tools package, available from:

http://prc-tools.sourceforge.net

The targets (i.e. type make target) available for the make process are:

all: builds the English language full version

portuguese,norwegian,dutch,italian,french,german,spanish,catalan: builds appropriate language

Copyright Notice: This software is licensed under the terms of the GPL, included in the COPYING file in the source code directory.

The icons are (C) Stefan Smith and Tankut Enric, and the copyright for the translations is attributed in the relevant file. Everything else is (C) Benjamin Roe.
