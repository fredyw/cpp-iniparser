#!/bin/bash

cd gtest-1.7.0/make
make
cp gtest_main.a libgtest_main.a
cd -
./waf clean
./waf build --test --gtest_include=gtest-1.7.0/include --gtest_lib=gtest-1.7.0/make
