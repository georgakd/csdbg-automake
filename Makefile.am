# Makefile for csdbg
# (c) 2017

#SUBDIRS = src tst

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
DOPTS				=		_REENTRANT

if DEBUG
DOPTS               += CSDBG_WITH_DEBUG
endif

if COLOR
DOPTS               += CSDBG_WITH_COLOR_TERM
endif


# -f options
FOPTS                =     PIC
FOPTS                +=    no-enforce-eh-specs
FOPTS                +=    strict-aliasing

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


lib_LTLIBRARIES=libcsdbg.la

libcsdbg_la_SOURCES= $(MODS:=.cpp)

libcsdbg_la_LDFLAGS = -version-info 1:29:0

libcsdbg_la_includedir = $(includedir)/csdbg

libcsdbg_la_include_HEADERS = include/*.hpp

# Compiler flag setup
AM_CXXFLAGS            =     $(GOPTS:%=-%) #$(foreach o, $(GOPTS),-$(o))
AM_CXXFLAGS            +=    $(WOPTS:%=-W%) 
AM_CXXFLAGS            +=    $(FOPTS:%=-f%) 
AM_CXXFLAGS            +=    $(DOPTS:%=-D%)
AM_CXXFLAGS            +=    $(IPATHS:%=-I%)

echo:
		@echo $(AM_CXXFLAGS)

