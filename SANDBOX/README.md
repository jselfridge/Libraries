
Libraries
=========

This repository contains various libraries that are useful
for a wide variety of coding projects.  Some are for general 
purpose programs, and others are specific to the BBB platform.

The primary intention is to keep these as static libraries 
which can be referenced throughout multiple projects. The command:

        ar -cvq libmat.a *.o

is run in each <code>makefile</code>, which generates the static 
library that can be included in other projects.

The libraries need to be compiled natively on whatever platform 
they will be used.  So, many libraries that run natively on Mac 
OS X, need to be recompiled on the BBB to be used on that system.


bbbLib
------
The <code>bbbLib</code> library contains the collection of 
functions used to add functionality to the BeagleBone Black
processor.


matLib
------
The <code>matLib</code> library implements a variety of linear 
algebra functions in the C language so it is particularly 
applicable to embedded system architecture.


rotLib
------
The <code>rotLib</code> library contains functions that are needed 
to perform various types of roational transformations.  It is built 
upon the <code>matLib</code> library, and is useful for both 
simulations and hardware applications.


optLib
------
The <code>optLib</code> library performs optimization 
routines.  Currently, it only supports a gradient method 
type of optimization, but others may be added in the 
future.


ctrlLib
-------
The <code>ctrlLib</code> library is an extrension of the 
<code>MatLib</code> library, and performs functions that are 
focused on controls analysis, design, and simulation.



