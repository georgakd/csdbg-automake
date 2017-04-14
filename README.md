# csdbg-automake
automake for libcsdbg (for library and application)

# installation
To install libcsdbg:

./configure

make

sudo make install

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

This will overwrite the configure and Makefile scripts in the repository.

# example linkage of an application with csdbg using autotools:

cd example

aclocal

autoconf

automake --add-missing

./configure

make

./hello



