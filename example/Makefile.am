# Makefile for libcsdbg
# (c) 2017

AM_CFLAGS=-Wall -g 

AM_LDFLAGS=-L/usr/local/lib 

AM_CPPFLAGS=-I/usr/local/include -I./src

bin_PROGRAMS=hello

hello_SOURCES= src/hello.cpp

AM_CXXFLAGS=-g -fPIC -finstrument-functions -finstrument-functions-exclude-file-list=/usr/include -finstrument-functions-exclude-file-list=iostream -finstrument-functions-exclude-file-list=ios -finstrument-functions-exclude-file-list=istream -finstrument-functions-exclude-file-list=ostream -finstrument-functions-exclude-file-list=/usr/local/include/csdbg   
