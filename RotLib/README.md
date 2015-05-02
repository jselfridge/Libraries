
RotLib
======

This directory is C code for a static library that contains fuctions 
which pertain to rotations, such as Euler angles and Quaternions. 


<!--

The functions are 
grouped in the following categories:

    RotConv   - Used to convert scales and units
    RotEuler  - Performs Euler rotations and transformations
    RotQuat   - Contains functions pertaining to quaternions

The primary intention is to keep this as a static 
library that can be referenced throughout multiple
projects.  The command:

    ar -cvq libRot.a *.o

is used to generate the static library.  It is
included in the 'makefile' and places the 
library in the appropriate folder.



-->