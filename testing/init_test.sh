#!/bin/bash

mkdir "$1"
cd "$1"
cp ../GNUmakefile_cxx_dis.mk GNUmakefile
#echo "$1""_debug" >> "$1"/.gitignore
printf "$1"'\n'"$1"'_debug\n' >> .gitignore
mkdir -p src
cd src
ln -s ../../../src liborangepower_src
cp ../../../examples/example_misc_includes/misc_includes.hpp .
