cpp-iniparser
=============

A small C++ INI parser library

How to build
------------
cpp-iniparser uses Waf build system (http://code.google.com/p/waf/)

### Building a static library ###
    waf configure
    waf build --static

### Building a shared library ###
    waf configure
    waf build --shared

### Running unit tests ###
cpp-iniparses uses GoogleTest (http://code.google.com/p/googletest/)
    waf build --test

Alternatively, we can also explicitly tell where the gtest header files and libraries are
    waf build --test --gtest_include=/gtest/include --gtest_lib=/gtest/lib
