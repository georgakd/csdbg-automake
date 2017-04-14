# csdbg-automake
automake for libcsdbg (for library and application)

# installation
To install libcsdbg:

./configure

make

sudo make install

ldconfig

To see available configuration options:
./configure --help

# development
Requirements: libtool and autotools

To set up the project:

Checkout the code, and then in the top directory:

libtoolize

aclocal

autoconf

automake --add-missing

This will overwrite the configure and Makefile scripts in the repository, so it is necessary for development that involves changes or additions to the project structure (eg. adding new source files).

# example linkage of an application with csdbg using autotools:

cd example

aclocal

autoconf

automake --add-missing

./configure

make

./hello



