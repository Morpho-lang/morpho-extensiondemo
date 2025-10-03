# morpho-extensiondemo

This repository contains a minimal morpho extension for demonstration purposes, illustrating how to create and package a C-based extension. The repository contains C source code for the extension, CMake files to enable convenient building and an example of a help file. 

## Installation

Clone this repository onto your computer in any convenient place:

    git clone https://github.com/morpho-lang/morpho-extensiondemo.git

then add the location of this repository to your .morphopackages file.

    echo PACKAGEPATH >> ~/.morphopackages 
    where PACKAGEPATH is the location of the git repository.

You need to compile the extension, which you can do by cd'ing to the repository's base folder and typing

    mkdir build
    cd build
    cmake .. 
    make install

The package can then be loaded into morpho using the `import` keyword.

    import extensiondemo

## Use

The `extensiondemo` package includes a toy function `foo()` and a toy class `Foo` that inherits from `Object` and implements a single additional method `wibble`. 

Examine the help using morpho in interactive mode by typing

    ? extensiondemo
