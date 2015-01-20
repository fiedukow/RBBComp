# RBBComp
Unofficial R bindings for bbcomp (the Black Box Optimialization Competition - http://bbcomp.ini.rub.de/).

# Dependencies

 * R
 * libbbcomp

# Installation

To use those bindigs just follow 2 simple steps:

 1. Run this code to build Shared Libary for R.

    $ make -f Makefile-Linux

 2. Put RProxy.so, libbbcomp.so (download binary for your own architecture from http://bbcomp.ini.rub.de) and RBBComp.r in your working directory.
 3. Use RRBComp.r API in a way described in bbcomp official documentation for C. Note, that you can pass matrices containing more then one point to evaluate multiple points with one call (you will get vector of values in return).
