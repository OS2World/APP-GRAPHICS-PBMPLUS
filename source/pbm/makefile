# Makefile for pbm tools.
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

DEFPBM =			pbm.h ../pbmplus.h
INCL =			-I..
ALLCFLAGS =		$(CFLAGS) $(RGBDEF) $(TIFFDEF) $(INCL)
LIBPBM =			libpbm$(LIBEXT)
LIBPBMOBJS =	libpbm1$(OBJ) libpbm2$(OBJ) libpbm3$(OBJ) libpbm4$(OBJ) \
					libpbm5$(OBJ)

.c.obj:
	$(CC) $(ALLCFLAGS) -c $*.c

.obj.exe:
	link386 $(LDFLAGS) $*,,, $(LIBS), pbm

BINARIES = atktopbm$(EXE) brushtopbm$(EXE) cmuwmtopbm$(EXE) g3topbm$(EXE) \
		icontopbm$(EXE) gemtopbm$(EXE) macptopbm$(EXE) mgrtopbm$(EXE) \
		pbmlife$(EXE) pbmmake$(EXE) pbmmask$(EXE) pbmreduce$(EXE) \
		pbmtext$(EXE) pbmto10x$(EXE) pbmtoascii$(EXE) pbmtoatk$(EXE) \
		pbmtobbnbg$(EXE) pbmtocmuwm$(EXE) pbmtoepson$(EXE) pbmtog3$(EXE) \
		pbmtogem$(EXE) pbmtogo$(EXE) pbmtoicon$(EXE) pbmtolj$(EXE) \
		pbmtomacp$(EXE) pbmtomgr$(EXE) pbmtopi3$(EXE) pbmtoplot$(EXE) \
		pbmtoptx$(EXE) pbmtox10bm$(EXE) pbmtoxbm$(EXE) pbmtoybm$(EXE) \
		pbmtozinc$(EXE) pbmupc$(EXE) pi3topbm$(EXE) xbmtopbm$(EXE) ybmtopbm$(EXE)

OBJECTS = atktopbm$(OBJ) brushtopbm$(OBJ) cmuwmtopbm$(OBJ) g3topbm$(OBJ) \
		icontopbm$(OBJ) gemtopbm$(OBJ) macptopbm$(OBJ) mgrtopbm$(OBJ) \
		pbmlife$(OBJ) pbmmake$(OBJ) pbmmask$(OBJ) pbmreduce$(OBJ) \
		pbmtext$(OBJ) pbmto10x$(OBJ) pbmtoascii$(OBJ) pbmtoatk$(OBJ) \
		pbmtobbnbg$(OBJ) pbmtocmuwm$(OBJ) pbmtoepson$(OBJ) pbmtog3$(OBJ) \
		pbmtogem$(OBJ) pbmtogo$(OBJ) pbmtoicon$(OBJ) pbmtolj$(OBJ) \
		pbmtomacp$(OBJ) pbmtomgr$(OBJ) pbmtopi3$(OBJ) pbmtoplot$(OBJ) \
		pbmtoptx$(OBJ) pbmtox10bm$(OBJ) pbmtoxbm$(OBJ) pbmtoybm$(OBJ) \
		pbmtozinc$(OBJ) pbmupc$(OBJ) pi3topbm$(OBJ) xbmtopbm$(OBJ) ybmtopbm$(OBJ)


all:				lib binaries

binaries:		$(BINARIES)

$(BINARIES):	pbm.def

$(OBJECTS):		$(DEFPBM)

lib:				$(LIBPBM)

$(LIBPBM):		$(LIBPBMOBJS) libpbm.def
	link386 $(LDFLAGS) $(LIBPBMOBJS), $@,, $(LIBS), libpbm

$(LIBPBMOBJS):	$(DEFPBM)
	$(CC) $(ALLCFLAGS) -Ge- -c $*.c

libpbm1$(OBJ):	libpbm.h ../version.h

libpbm2$(OBJ):	libpbm.h

libpbm3$(OBJ):	libpbm.h

libpbm4$(OBJ):	libpbm.h

libpbm5$(OBJ):	pbmfont.h

cmuwmtopbm$(OBJ):	cmuwm.h
g3topbm$(OBJ):		g3.h
macptopbm$(OBJ):	macp.h
mgrtopbm$(OBJ):	mgr.h
pbmtext$(OBJ):		pbmfont.h
pbmtocmuwm$(OBJ):	cmuwm.h
pbmtog3$(OBJ):		g3.h
pbmtomacp$(OBJ):	macp.h
pbmtomgr$(OBJ):	mgr.h
