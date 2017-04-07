# csdbg-automake
automake for libcsdbg (for library and application)

example linkage of an application with csdbg using autotools:

cd example
aclocal
autoconf
automake --add-missing
./configure
make
./hello


