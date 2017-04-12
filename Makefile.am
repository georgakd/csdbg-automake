# Makefile for hello world
# (c) 2017



AM_LDFLAGS=#-L/usr/local/lib 

AM_CPPFLAGS=#-I/usr/local/include -I./src

lib_LTLIBRARIES=libcsdbg.la

# Library modules
MODS                =     object
MODS                +=    util
MODS                +=    exception
MODS                +=    string
MODS                +=    symbol
MODS                +=    call
MODS                +=    node
MODS                +=    chain
MODS                +=    stack
MODS                +=    symtab
MODS                +=    thread
MODS                +=    process
MODS                +=    tracer

libcsdbg_la_SOURCES= $(foreach o, $(MODS), src/$(o).cpp)

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

 # Compiler flag setup
AM_CXXFLAGS            =     $(foreach o, $(GOPTS), -$(o))
AM_CXXFLAGS            +=    $(foreach w, $(WOPTS), -W$(w))
AM_CXXFLAGS            +=    $(foreach f, $(FOPTS), -f$(f))
AM_CXXFLAGS            +=    $(foreach d, $(DOPTS), -D$(d))
AM_CXXFLAGS            +=    $(foreach p, $(IPATHS), -I$(p))






