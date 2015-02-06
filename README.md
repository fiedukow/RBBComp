# RBBComp
Unofficial R bindings for bbcomp (the Black Box Optimialization Competition - http://bbcomp.ini.rub.de/).

# Dependencies

 * R
 * libbbcomp

# Installation

To use those bindigs just follow 2 simple steps:

 1. Run this code to build Shared Libary for R.

    $ make -f Makefile-Linux

 2. Put RProxy.so, libbbcomp.so (download binary for your own architecture from http://bbcomp.ini.rub.de) and RBBComp.r in your LD_LIBRARY_PATH.
 3. Use RRBComp.r API in a way described in bbcomp official documentation for C. Note, that you can pass matrices containing more then one point to evaluate multiple points with one call (you will get vector of values in return).

# Issue tracking, patches

Patches, suggestions and bug reports are kindly welcome. Please use github tools for all of those :)

# Differences between C API and R API.

 * Function names in R API starts with capital letter.
 * The first call from bbcomp in R API should always be Configure - its OBLIGATORY now.
 * There is additional function Logout which acctually only unloads DLL. It's not really usefull unless you are one of those people who keep they R session for years.
 * Whenever there is a place to put point into API you can put there two things:
    * Vector representing point with Dimension() length. You will get single double value (value of point) in return.
    * Matrix representing multiple points with Dimension() columns and 1 or more rows. Each row represents single point. You will get vector of double values (values of consecutive points) in return.

Note, that if C API will return error for some of points only - you will get warning. You can then check which of returned values are equal 1e100 to determine what exacly wasnt calculated properly. Keep in mind that the 1e100 is also value returned by C API if you will try to calculate value for point outside of [0,1]^D range.
