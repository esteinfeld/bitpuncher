# bitpuncher
A simplistic bitmap editor for monochrome, small canvases, supporting animations.

## Why
This tool has been used for the Archimedes Exhibitions GmbH POV (persistance of vision)
gadget, in order to create the patterns to be loaded to the gadget's microcontroller.

## Building
The project has been created with QtCreator 5.6 (4.8 compatible).
Open the file src/bitpuncher.pro as project.

Alternatively, use the following recipe:

    mkdir build && cd build
	qmake ../src/bitpuncher.pro
	make

