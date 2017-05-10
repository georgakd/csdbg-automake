# Makefile for csdbg
# (c) 2017

#SUBDIRS = src tst

lib_LTLIBRARIES=libcsdbg.la

libcsdbg_la_LDFLAGS = -version-info 1:29:0

# Library modules
MODS                =     src/object
MODS                +=    src/util
MODS                +=    src/exception
MODS                +=    src/string
MODS                +=    src/symbol
MODS                +=    src/call
MODS                +=    src/node
MODS                +=    src/chain
MODS                +=    src/stack
MODS                +=    src/symtab
MODS                +=    src/thread
MODS                +=    src/process
MODS                +=    src/tracer

# Thread safety
DOPTS				= _REENTRANT

# Include debugging code
if DEBUG
DOPTS               += CSDBG_WITH_DEBUG
endif

# Include support for color terminals (VT100)
if COLOR
DOPTS               += CSDBG_WITH_COLOR_TERM
endif

if HIGHLIGHT
DOPTS               += CSDBG_WITH_HIGHLIGHT
MODS                += src/style
MODS                += src/dictionary
MODS                += src/parser
bin_SCRIPTS         = extra/vtcolors
DATAFILES           = extra/*.dict
endif

# Include code for buffered output streams
if STREAMBUF
DOPTS               += CSDBG_WITH_STREAMBUF
DOPTS				+= CSDBG_WITH_STREAMBUF_FILE
DOPTS				+= CSDBG_WITH_STREAMBUF_TCP
DOPTS				+= CSDBG_WITH_STREAMBUF_STTY
MODS                += src/streambuf
MODS                += src/filebuf
MODS                += src/tcpsockbuf
MODS                += src/sttybuf
endif

if PLUGIN
DOPTS               += CSDBG_WITH_PLUGIN
MODS				+= src/plugin
endif

if FILTER
DOPTS               += CSDBG_WITH_FILTER
MODS                += src/filter

endif

# -f options
FOPTS                =  PIC
FOPTS                += no-enforce-eh-specs
FOPTS                += strict-aliasing

# -W options
WOPTS                =     all
WOPTS                +=    abi
WOPTS                +=    ctor-dtor-privacy
WOPTS                +=    non-virtual-dtor
WOPTS                +=    format-security
WOPTS                +=    init-self
WOPTS                +=    missing-include-dirs
WOPTS                +=    switch-enum
WOPTS                +=    cast-align
WOPTS                +=    cast-qual
WOPTS                +=    clobbered
WOPTS                +=    empty-body
WOPTS                +=    sign-compare
WOPTS                +=    logical-op
WOPTS                +=    missing-field-initializers
WOPTS                +=    packed
WOPTS                +=    redundant-decls
WOPTS                +=    overlength-strings
WOPTS                +=    disabled-optimization
WOPTS                +=    missing-noreturn
WOPTS                +=    type-limits
# WOPTS            +=    old-style-cast

# Generic options
GOPTS                =     O2
GOPTS                +=    rdynamic
GOPTS                +=    march=native
GOPTS                +=    std=gnu++0x

libcsdbg_la_SOURCES= $(MODS:=.cpp)

libcsdbg_la_includedir= $(includedir)/csdbg

libcsdbg_la_include_HEADERS= include/*.hpp

libcsdbg_la_DATA= $(DATAFILES)

libcsdbg_ladir= $(prefix)/etc

# Compiler flag setup
AM_CXXFLAGS            =     $(GOPTS:%=-%) 
AM_CXXFLAGS            +=    $(WOPTS:%=-W%) 
AM_CXXFLAGS            +=    $(FOPTS:%=-f%) 
AM_CXXFLAGS            +=    $(DOPTS:%=-D%)
AM_CXXFLAGS            +=    $(IPATHS:%=-I%)

# Doxygen support
include dxinclude.am

EXTRA_DIST = $(DX_CONFIG) doc/html


#for debugging the makefile
echo:
		@echo $(AM_CXXFLAGS)

