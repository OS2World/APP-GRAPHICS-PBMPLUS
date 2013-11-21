# Makefile for pgm tools.
#
# Copyright (C) 1989, 1991 by Jef Poskanzer.
#
# Permission to use, copy, modify, and distribute this software and its
# documentation for any purpose and without fee is hereby granted, provided
# that the above copyright notice appear in all copies and that both that
# copyright notice and this permission notice appear in supporting
# documentation.  This software is provided "as is" without express or
# implied warranty.

# Default values, usually overridden by top-level Makefile.
CC =				icc
CFLAGS =			-Sm -D__STDC__ -Q -Ti -Gd
RGBDEF =
TIFFDEF =		-DLIBTIFF
LDFLAGS =		/pm:vio
OBJ =				.obj
EXE =				.exe
LIBEXT =			.dll
LIBS =			/nod dde4sbso

PBMDIR =			../pbm
INCLUDEPBM =	-I$(PBMDIR)
DEFPBM =			$(PBMDIR)/pbm.h ../pbmplus.h
DEFLIBPBM =		$(PBMDIR)/libpbm.h

DEFPGM =			pgm.h $(DEFPBM)
INCL =			-I.. $(INCLUDEPBM)
ALLCFLAGS =		$(CFLAGS) $(INCL)
LIBPGM =			libpgm$(LIBEXT)
LIBPGMOBJS =	libpgm1$(OBJ) libpgm2$(OBJ)

.c.obj:
	$(CC) $(ALLCFLAGS) -c $*.c

.obj.exe:
	link386 $(LDFLAGS) $*,,, $(LIBS), pgm

PORTBINARIES =	fitstopgm$(EXE) fstopgm$(EXE) hipstopgm$(EXE) lispmtopgm$(EXE) \
					pgmbentley$(EXE) pgmenhance$(EXE) pgmhist$(EXE) pgmnorm$(EXE) \
					pgmoil$(EXE) pgmramp$(EXE) pgmtofits$(EXE) pgmtofs$(EXE) \
					pgmtolispm$(EXE) pgmtopbm$(EXE) psidtopgm$(EXE) rawtopgm$(EXE)

MATHBINARIES =	pgmcrater$(EXE) pgmedge$(EXE) pgmtexture$(EXE)

BINARIES =		$(PORTBINARIES) $(MATHBINARIES)

OBJECTS =		fitstopgm$(OBJ) fstopgm$(OBJ) hipstopgm$(OBJ) lispmtopgm$(OBJ) \
					pgmbentley$(OBJ) pgmenhance$(OBJ) pgmhist$(OBJ) pgmnorm$(OBJ) \
					pgmoil$(OBJ) pgmramp$(OBJ) pgmtofits$(OBJ) pgmtofs$(OBJ) \
					pgmtolispm$(OBJ) pgmtopbm$(OBJ) psidtopgm$(OBJ) rawtopgm$(OBJ) \
					pgmcrater$(OBJ) pgmedge$(OBJ) pgmtexture$(OBJ)

all:				lib binaries

binaries:		$(BINARIES)

$(BINARIES):	pgm.def

$(OBJECTS):		$(DEFPGM)

lib:				$(LIBPGM)

$(LIBPGM):		$(LIBPGMOBJS) libpgm.def
	link386 $(LDFLAGS) $(LIBPGMOBJS), $@,, $(LIBS), libpgm

$(LIBPGMOBJS):	libpgm.h $(DEFPGM)
	$(CC) $(ALLCFLAGS) -Ge- -c $*.c

libpgm2$(OBJ):	$(DEFLIBPBM)

pgmtopbm$(OBJ):	dithers.h
