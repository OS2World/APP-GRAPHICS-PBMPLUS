#	$Header: /usr/people/sam/tiff/libtiff/RCS/Makefile.sun,v 1.27 91/08/23 17:09:22 sam Exp $
#
# Tag Image File Format Library
#
# Copyright (c) 1988, 1989, 1990, 1991 Sam Leffler
# Copyright (c) 1991 Silicon Graphics, Inc.
#
# Permission to use, copy, modify, distribute, and sell this software and
# its documentation for any purpose is hereby granted without fee, provided
# that (i) the above copyright notices and this permission notice appear in
# all copies of the software and related documentation, and (ii) the names of
# Sam Leffler and Silicon Graphics may not be used in any advertising or
# publicity relating to the software without the specific, prior written
# permission of Stanford and Silicon Graphics.
#
# THE SOFTWARE IS PROVIDED "AS-IS" AND WITHOUT WARRANTY OF ANY KIND,
# EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
# WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
#
# IN NO EVENT SHALL SAM LEFFLER OR SILICON GRAPHICS BE LIABLE FOR
# ANY SPECIAL, INCIDENTAL, INDIRECT OR CONSEQUENTIAL DAMAGES OF ANY KIND,
# OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
# WHETHER OR NOT ADVISED OF THE POSSIBILITY OF DAMAGE, AND ON ANY THEORY OF
# LIABILITY, ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE
# OF THIS SOFTWARE.
#
# Library-wide configuration defines:
#	SUBFILE_COMPAT	include compat code for bad SubFileType tag
#	JPEG_SUPPORT	add support for C-Cube JPEG tags & JPEG algorithm
#
# Compression configuration defines:
#	CCITT_SUPPORT	add support for CCITT Group 3 & 4 algorithms
#	PACKBITS_SUPPORT	add support for Macintosh PackBits algorithm
#	LZW_SUPPORT	add support for LZW algorithm
#	THUNDER_SUPPORT	add support for ThunderScan 4-bit RLE algorithm
#	NEXT_SUPPORT	add support for NeXT 2-bit RLE algorithm
#	JPEG_SUPPORT	add support for C-Cube JPEG tags & JPEG algorithm
#
# Note that if you change the library-wide configuration, you'll
# need to manual force a full rebuild.  Changing the configuration
# of which compression algorithms are included in the library is
# automatically handled (i.e. compress.o has a dependency on
# the Makefile).
#

CC =		icc
DEFS = -D__STDC__ -DBSDTYPES -DMSDOS -DJPEG_SUPPORT -DSUBFILE_COMPAT
CFLAGS = -Sm -Q -Ti -Gde- $(DEFS)

CONF_COMPRESSION = \
	-DPACKBITS_SUPPORT \
	-DLZW_SUPPORT \
	-DCCITT_SUPPORT \
	-DTHUNDER_SUPPORT  \
	-DNEXT_SUPPORT

INCS =	tiff.h tiffiop.h tiffcompat.h machdep.h

OBJS =	tif_ccittrle.obj \
			tif_close.obj \
			tif_compat.obj \
			tif_compress.obj \
			tif_dir.obj \
			tif_dumpmode.obj \
			tif_error.obj \
			tif_jpeg.obj \
			tif_flush.obj \
			tif_lzw.obj \
			tif_open.obj \
			tif_packbits.obj \
			tif_print.obj \
			tif_read.obj \
			tif_strip.obj \
			tif_swab.obj \
			tif_thunder.obj \
			tif_tile.obj \
			tif_warning.obj \
			tif_write.obj \
			tif_next.obj \
			tif_fax3.obj \
			tif_fax4.obj

libtiff.dll:	$(OBJS) libtiff.def
	link386 $(LDFLAGS) @libtiff.lnk

$(OBJS):			$(INCS)

tif_compress.obj:	makefile
	$(CC) $(CFLAGS) $(CONF_COMPRESSION) -c tif_compress.c

tif_fax3.obj:	g3states.h tif_fax3.h

g3states.h:		mkg3states.c t4.h
	$(CC) -Q -c mkg3states.c
	link386 /pm:vio mkg3states;
	mkg3states > g3states.h
