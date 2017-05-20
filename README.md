# csdbg-automake
automake for libcsdbg (for library and application)

# installation
To install libcsdbg in a standard linux system just:

make

sudo make install

ldconfig

# documentation
make doxygen-doc will produce html docs by default under /doxygen folder.
see ./configure --help for alternative types of docs

# development
Requirements: libtool and autotools

To set up the project:

Checkout the code, and then in the top directory:

libtoolize

aclocal

autoconf

automake --add-missing

This will overwrite the configure and Makefile scripts in the repository, so it is necessary for development that involves changes or additions to the project structure (eg. adding new source files).

To configure the project for a new target or a different configuration:

./configure

To see available configuration options:
./configure --help

# example linkage of an application with csdbg using autotools:

cd example

aclocal

autoconf

automake --add-missing

./configure

make

./hello



