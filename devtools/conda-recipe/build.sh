#!/bin/bash

mkdir build && cd build
cmake \
    -DCMAKE_INSTALL_PREFIX:PATH=$PREFIX \
    -DCMAKE_PREFIX_PATH:PATH=$PREFIX \
    -DCMAKE_INCLUDE_PATH:PATH="$PREFIX/include" \
    -DCMAKE_LIBRARY_PATH:PATH="$PREFIX/lib" \
    -DBUILD_SHARED_LIBS=ON \
    -DENABLE_PBAM_APBS=ON \
    -DENABLE_PBSAM_APBS=ON \
    -DENABLE_OPENMP=ON \
    ..
make
make install

mkdir -p "$PREFIX/include/pb_solvers"
cp -r $SRC_DIR/pb_shared/src/*.h $PREFIX/include/pb_solvers/
cp -r $SRC_DIR/pb_wrap/src/*.h $PREFIX/include/pb_solvers/
cp -r $SRC_DIR/pbam/src/*.h $PREFIX/include/pb_solvers/
cp -r $SRC_DIR/pbsam/src/*.h $PREFIX/include/pb_solvers/
