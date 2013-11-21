# Makefile for pnm tools.
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

TIFFINC =       -I../libtiff
TIFFBINARIES =  tifftopnm$(EXE) pnmtotiff$(EXE)
TIFFOBJECTS =   tifftopnm$(OBJ) pnmtotiff$(OBJ)

PBMDIR =			../pbm
INCLUDEPBM =	-I$(PBMDIR)
DEFPBM =			$(PBMDIR)/pbm.h ../pbmplus.h
DEFLIBPBM =		$(PBMDIR)/libpbm.h

PGMDIR =			../pgm
INCLUDEPGM =	-I$(PGMDIR)
DEFPGM =			$(PGMDIR)/pgm.h
DEFLIBPGM =		$(PGMDIR)/libpgm.h

PPMDIR =			../ppm
INCLUDEPPM =	-I$(PPMDIR)
DEFPPM =			$(PPMDIR)/ppm.h
DEFLIBPPM =		$(PPMDIR)/libppm.h

DEFPNM =			pnm.h $(DEFPBM) $(DEFPGM) $(DEFPPM)
INCL =			-I.. $(INCLUDEPBM) $(INCLUDEPGM) $(INCLUDEPPM) $(TIFFINC)
ALLCFLAGS =		$(CFLAGS) $(INCL) $(TIFFDEF)
LIBPNM =			libpnm$(LIBEXT)
LIBPNMOBJS =	libpnm1$(OBJ) libpnm2$(OBJ) libpnm3$(OBJ) libpnm4$(OBJ)

.c.obj:
	$(CC) $(ALLCFLAGS) -c $*.c

.obj.exe:
	link386 $(LDFLAGS) $*,,, $(LIBS), pnm

PORTBINARIES =	pnmarith$(EXE) pnmcat$(EXE) pnmconvol$(EXE) pnmcrop$(EXE) \
					pnmcut$(EXE) pnmdepth$(EXE) pnmenlarge$(EXE) pnmfile$(EXE) \
					pnmflip$(EXE) pnminvert$(EXE) pnmnoraw$(EXE) pnmpaste$(EXE) \
					pnmscale$(EXE) pnmtile$(EXE) pnmtops$(EXE) pnmtorast$(EXE) \
					pnmtoxwd$(EXE) rasttopnm$(EXE) xwdtopnm$(EXE)

MATHBINARIES =	pnmgamma$(EXE) pnmrotate$(EXE) pnmshear$(EXE)

BINARIES =		$(PORTBINARIES) $(MATHBINARIES) $(TIFFBINARIES)

PORTOBJECTS =	pnmarith$(OBJ) pnmcat$(OBJ) pnmconvol$(OBJ) pnmcrop$(OBJ) \
					pnmcut$(OBJ) pnmdepth$(OBJ) pnmenlarge$(OBJ) pnmfile$(OBJ) \
					pnmflip$(OBJ) pnminvert$(OBJ) pnmnoraw$(OBJ) pnmpaste$(OBJ) \
					pnmscale$(OBJ) pnmtile$(OBJ) pnmtops$(OBJ) pnmtorast$(OBJ) \
					pnmtoxwd$(OBJ) rasttopnm$(OBJ) xwdtopnm$(OBJ) pnmgamma$(OBJ) \
					pnmrotate$(OBJ) pnmshear$(OBJ)

OBJECTS =		$(PORTOBJECTS) $(TIFFOBJECTS)

all:				lib binaries

binaries:		$(BINARIES)

$(BINARIES):	pnm.def

$(OBJECTS):		$(DEFPNM)

pnmcat$(EXE):	pnmcat$(OBJ)
	link386 $(LDFLAGS) $* setargv,,, /noe $(LIBS) os2386, pnm

tifftopnm$(EXE):	tifftopnm$(OBJ)
	link386 $(LDFLAGS) $*,,, $(LIBS), pnmtiff

pnmtotiff$(EXE):	pnmtotiff$(OBJ)
	link386 $(LDFLAGS) $*,,, $(LIBS), pnmtiff

lib:				$(LIBPNM)

$(LIBPNM):		$(LIBPNMOBJS) libpnm.def
	link386 $(LDFLAGS) $(LIBPNMOBJS), $@,, $(LIBS), libpnm

$(LIBPNMOBJS):	$(DEFPNM)
	$(CC) $(ALLCFLAGS) -Ge- -c $*.c

libpnm2$(OBJ):	$(DEFLIBPBM) $(DEFLIBPGM) $(DEFLIBPPM)

libpnm3$(OBJ):	$(DEFLIBPBM) $(DEFLIBPGM) $(DEFLIBPPM)

libpnm4$(OBJ):	rast.h

pnmtorast$(OBJ):	rast.h
pnmtoxwd$(OBJ):	x11wd.h
rasttopnm$(OBJ):	rast.h
xwdtopnm$(OBJ):	x10wd.h x11wd.h
pnmtotiff$(OBJ):	$(PPMDIR)/ppmcmap.h
