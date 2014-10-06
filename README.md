ZMQ samples
===========

A single appliction built using various ZMQ lirbaries for C and C++ to show how
the different libraries provides the building blocks etc.

Building
--------

Install [libzmq and czmq](https://github.com/zeromq/czmq) in order to build.
Then do

    mkdir build
    cd build
    cmake ..
    make

After you can run the examples like so:

    bin/proto-libzmq

and

    bin/proto-czmq
