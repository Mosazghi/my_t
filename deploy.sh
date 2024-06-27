#!/bin/bash

echo "Making build directory"

if [ -d $PWD/build/ ]; then
	echo "build directory exists"
	rm -rf build
	echo "build directory deleted"
fi

mkdir build
cd build

# build
/home/mosa/Qt/Tools/CMake/bin/cmake \
	-S ../ \
	-B ./ \
	-DCMAKE_BUILD_TYPE:STRING=Release \
	-DCMAKE_PREFIX_PATH:PATH=/home/mosa/Qt/6.7.2/gcc_64

make -j16

# deploy
cqtdeployer -bin my_t -libDir /home/mosa/Qt/6.7.2/gcc_64/lib qif -qmake /home/mosa/Qt/6.7.2/gcc_64/bin/qmake
