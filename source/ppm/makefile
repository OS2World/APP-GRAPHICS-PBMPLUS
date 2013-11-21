# Makefile for ppm tools.
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

DEFPPM =			ppm.h $(DEFPBM) $(DEFPGM)
INCL =			-I.. $(INCLUDEPBM) $(INCLUDEPGM)
ALLCFLAGS =		$(CFLAGS) $(INCL) $(RGBDEF)
LIBPPM =			libppm$(LIBEXT)
LIBPPMOBJS =	libppm1$(OBJ) libppm2$(OBJ) libppm3$(OBJ) libppm4$(OBJ) \
					libppm5$(OBJ)
.c.obj:
	$(CC) $(ALLCFLAGS) -c $*.c

.obj.exe:
	link386 $(LDFLAGS) $*,,, $(LIBS), ppm

PORTBINARIES =	giftoppm$(EXE) gouldtoppm$(EXE) ilbmtoppm$(EXE) imgtoppm$(EXE) \
					mtvtoppm$(EXE) pcxtoppm$(EXE) pgmtoppm$(EXE) pi1toppm$(EXE) \
					picttoppm$(EXE) pjtoppm$(EXE) ppmdither$(EXE) ppmhist$(EXE) \
					ppmmake$(EXE) ppmquant$(EXE) ppmrelief$(EXE) ppmtoacad$(EXE) \
					ppmtogif$(EXE) ppmtoicr$(EXE) ppmtoilbm$(EXE) ppmtopcx$(EXE) \
					ppmtopgm$(EXE) ppmtopi1$(EXE) ppmtopict$(EXE) ppmtopj$(EXE) \
					ppmtopuzz$(EXE) ppmtorgb3$(EXE) ppmtosixel$(EXE) \
					ppmtotga$(EXE) ppmtouil$(EXE) ppmtoxpm$(EXE) ppmtoyuv$(EXE) \
					qrttoppm$(EXE) rawtoppm$(EXE) rgb3toppm$(EXE) sldtoppm$(EXE) \
					spctoppm$(EXE) sputoppm$(EXE) tgatoppm$(EXE) ximtoppm$(EXE) \
					xpmtoppm$(EXE) yuvtoppm$(EXE)

MATHBINARIES =	ppmforge$(EXE) ppmpat$(EXE)

BINARIES =		$(PORTBINARIES) $(MATHBINARIES)

OBJECTS =		giftoppm$(OBJ) gouldtoppm$(OBJ) ilbmtoppm$(OBJ) imgtoppm$(OBJ) \
					mtvtoppm$(OBJ) pcxtoppm$(OBJ) pgmtoppm$(OBJ) pi1toppm$(OBJ) \
					picttoppm$(OBJ) pjtoppm$(OBJ) ppmdither$(OBJ) ppmhist$(OBJ) \
					ppmmake$(OBJ) ppmquant$(OBJ) ppmrelief$(OBJ) ppmtoacad$(OBJ) \
					ppmtogif$(OBJ) ppmtoicr$(OBJ) ppmtoilbm$(OBJ) ppmtopcx$(OBJ) \
					ppmtopgm$(OBJ) ppmtopi1$(OBJ) ppmtopict$(OBJ) ppmtopj$(OBJ) \
					ppmtopuzz$(OBJ) ppmtorgb3$(OBJ) ppmtosixel$(OBJ) \
					ppmtotga$(OBJ) ppmtouil$(OBJ) ppmtoxpm$(OBJ) ppmtoyuv$(OBJ) \
					qrttoppm$(OBJ) rawtoppm$(OBJ) rgb3toppm$(OBJ) sldtoppm$(OBJ) \
					spctoppm$(OBJ) sputoppm$(OBJ) tgatoppm$(OBJ) ximtoppm$(OBJ) \
					xpmtoppm$(OBJ) yuvtoppm$(OBJ) ppmforge$(OBJ) ppmpat$(OBJ)

all:				lib binaries

binaries:		$(BINARIES)

$(BINARIES):	ppm.def

$(OBJECTS):		$(DEFPPM)

lib:				$(LIBPPM)

$(LIBPPM):		$(LIBPPMOBJS) libppm.def
	link386 $(LDFLAGS) $(LIBPPMOBJS), $@,, $(LIBS), libppm

$(LIBPPMOBJS):	libppm.h $(DEFPPM)
	$(CC) $(ALLCFLAGS) -Ge- -c $*.c

libppm2$(OBJ):	$(DEFLIBPGM) $(DEFLIBPBM)

libppm3$(OBJ):	ppmcmap.h

libppm5$(OBJ):	ppmdraw.h

ilbmtoppm$(OBJ):		ilbm.h
ppmhist$(OBJ):			ppmcmap.h
ppmpat$(OBJ):			ppmdraw.h
ppmquant$(OBJ):		$(PGMDIR)/dithers.h ppmcmap.h
ppmtoacad$(OBJ):		ppmcmap.h autocad.h
ppmtogif$(OBJ):		ppmcmap.h
ppmtoicr$(OBJ):		ppmcmap.h
ppmtoilbm$(OBJ):		ilbm.h ppmcmap.h
ppmtopcx$(OBJ):		ppmcmap.h
ppmtopi1$(OBJ):		ppmcmap.h
ppmtopict$(OBJ):		ppmcmap.h
ppmtopuzz$(OBJ):		ppmcmap.h
ppmtosixel$(OBJ):		ppmcmap.h
ppmtotga$(OBJ):		ppmcmap.h
ppmtouil$(OBJ):		ppmcmap.h
ppmtoxpm$(OBJ):		ppmcmap.h
sldtoppm$(OBJ):		ppmdraw.h autocad.h
tgatoppm$(OBJ):		tga.h
ximtoppm$(OBJ):		xim.h
