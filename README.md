kiwi libc
===============

kiwi libc is an MIT-licensed implementation of the standard C library
targetting the macOS x86_64 ABI.

kiwi libc is derived from musl libc.


Build Prerequisites
-------------------

The only build-time prerequisites for kiwi are GNU Make and Xcode.

Tested with macOS-10.12.4, clang-802.0.42 and ld64-278.4.


Supported Targets
-----------------

kiwi can be built for the following CPU instruction set architectures:

* macOS 10.12 - x86_64


Build and Installation Procedure
--------------------------------

To build and install kiwi:

1. Run "make" to compile.

2. Run "make install" with appropriate privileges to write to the
   target locations.

3. Run "make examples" to build the test programs

By default, make install uses a prefix of "/usr/local/kiwi".

