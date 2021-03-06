/* pnmtops.c - read a portable anymap and produce a PostScript file
**
** Copyright (C) 1989 by Jef Poskanzer.
**
** Permission to use, copy, modify, and distribute this software and its
** documentation for any purpose and without fee is hereby granted, provided
** that the above copyright notice appear in all copies and that both that
** copyright notice and this permission notice appear in supporting
** documentation.  This software is provided "as is" without express or
** implied warranty.
*/

#include "pnm.h"

#define MARGIN 0.95

static void putinit ARGS(( char* name, int cols, int rows, int padright, int bps, float scale, int dpi, int pagewid, int pagehgt, int format, int turnflag, int turnokflag, int rleflag ));
static void putitem ARGS(( void ));
static void putxelval ARGS(( xelval xv ));
static void putrest ARGS(( void ));
static void rleputbuffer ARGS(( void ));
static void rleputitem ARGS(( void ));
static void rleputxelval ARGS(( xelval xv ));
static void rleflush ARGS(( void ));
static void rleputrest ARGS(( void ));

void
main( argc, argv )
    int argc;
    char* argv[];
    {
    FILE* ifp;
    xel* xelrow;
    register xel* xP;
    int argn, turnflag, turnokflag, rleflag;
    int rows, cols, format, bps, padright, row, col;
    xelval maxval, nmaxval;
    float scale, f;
    int dpi, pagewid, pagehgt;
    char name[100];
    char* cp;
    char* usage = "[-scale <x>] [-turn|-noturn] [-rle|-runlength] [-dpi <n>] [-width <n>] [-height <n>] [-rle|-runlength] [pnmfile]";

    pnm_init( &argc, argv );

    argn = 1;
    scale = 1.0;
    turnflag = 0;
    turnokflag = 1;
    rleflag = 0;
    /* LaserWriter defaults. */
    dpi = 300;
    pagewid = 612;
    pagehgt = 762;

    /* Check for flags. */
    while ( argn < argc && argv[argn][0] == '-' && argv[argn][1] != '\0' )
	{
	if ( pm_keymatch( argv[argn], "-scale", 2 ) )
	    {
	    ++argn;
	    if ( argn == argc || sscanf( argv[argn], "%f", &scale ) != 1 )
		pm_usage( usage );
	    }
	else if ( pm_keymatch( argv[argn], "-turn", 2 ) )
	    turnflag = 1;
	else if ( pm_keymatch( argv[argn], "-noturn", 2 ) )
	    turnokflag = 0;
	else if ( pm_keymatch( argv[argn], "-rle", 2 ) ||
	          pm_keymatch( argv[argn], "-runlength", 2 ) )
	    rleflag = 1;
	else if ( pm_keymatch( argv[argn], "-dpi", 2 ) )
	    {
	    ++argn;
	    if ( argn == argc || sscanf( argv[argn], "%d", &dpi ) != 1 )
		pm_usage( usage );
	    }
	else if ( pm_keymatch( argv[argn], "-width", 2 ) )
	    {
	    ++argn;
	    if ( argn == argc || sscanf( argv[argn], "%f", &f ) != 1 )
		pm_usage( usage );
	    pagewid = f * 72.0;
	    }
	else if ( pm_keymatch( argv[argn], "-height", 2 ) )
	    {
	    ++argn;
	    if ( argn == argc || sscanf( argv[argn], "%f", &f ) != 1 )
		pm_usage( usage );
	    pagehgt = f * 72.0;
	    }
	else
	    pm_usage( usage );
	++argn;
	}

    if ( argn < argc )
	{
	ifp = pm_openr( argv[argn] );
	strcpy( name, argv[argn] );
	if ( strcmp( name, "-" ) == 0 )
	    strcpy( name, "noname" );

	if ( ( cp = index( name, '.' ) ) != 0 )
	    *cp = '\0';
	++argn;
	}
    else
	{
	ifp = stdin;
	strcpy( name, "noname" );
	}

    if ( argn != argc )
	pm_usage( usage );

    pnm_readpnminit( ifp, &cols, &rows, &maxval, &format );
    xelrow = pnm_allocrow( cols );

    /* Figure out bps. */
    bps = pm_maxvaltobits( (int) maxval );
    if ( bps > 2 && bps < 4 )
	bps = 4;
    else if ( bps > 4 && bps < 8 )
	bps = 8;
    else if ( bps > 8 )
	pm_error( "maxval of %d is too large for PostScript", maxval );
    nmaxval = pm_bitstomaxval( bps );
    
    /* Compute padding to round cols * bps up to the nearest multiple of 8. */
    padright = ( ( ( cols * bps + 7 ) / 8 ) * 8 - cols * bps ) / bps;

    putinit(
	name, cols, rows, padright, bps, scale, dpi, pagewid, pagehgt, format,
	turnflag, turnokflag, rleflag );
    for ( row = 0; row < rows; ++row )
	{
	pnm_readpnmrow( ifp, xelrow, cols, maxval, format );
	switch ( PNM_FORMAT_TYPE( format ) )
	    {
	    case PPM_TYPE:
	    /* Color. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		if ( maxval != nmaxval )
		    PPM_DEPTH( *xP, *xP, maxval, nmaxval );
	    /* First red. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		if ( rleflag )
		    rleputxelval( PPM_GETR( *xP ) );
		else
		    putxelval( PPM_GETR( *xP ) );
	    for ( col = 0; col < padright; ++col )
		if ( rleflag )
		    rleputxelval( 0 );
		else
		    putxelval( 0 );
	    if ( rleflag )
		rleflush();
	    /* Then green. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		if ( rleflag )
		    rleputxelval( PPM_GETG( *xP ) );
		else
		    putxelval( PPM_GETG( *xP ) );
	    for ( col = 0; col < padright; ++col )
		if ( rleflag )
		    rleputxelval( 0 );
		else
		    putxelval( 0 );
	    if ( rleflag )
		rleflush();
	    /* And blue. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		if ( rleflag )
		    rleputxelval( PPM_GETB( *xP ) );
		else
		    putxelval( PPM_GETB( *xP ) );
	    for ( col = 0; col < padright; ++col )
		if ( rleflag )
		    rleputxelval( 0 );
		else
		    putxelval( 0 );
	    if ( rleflag )
		rleflush();
	    break;
	    default:
	    /* Grayscale. */
	    for ( col = 0, xP = xelrow; col < cols; ++col, ++xP )
		{
		if ( maxval != nmaxval )
		    PNM_ASSIGN1( *xP, (int) PNM_GET1(*xP) * nmaxval / maxval );
		if ( rleflag )
		    rleputxelval( PNM_GET1( *xP ) );
		else
		    putxelval( PNM_GET1( *xP ) );
		}
	    for ( col = 0; col < padright; ++col )
		if ( rleflag )
		    rleputxelval( 0 );
		else
		    putxelval( 0 );
	    if ( rleflag )
		rleflush();
	    break;
	    }
        }

    pm_close( ifp );

    if ( rleflag )
	rleputrest();
    else
	putrest();

	pm_close (stdout);

    exit( 0 );
    }

static int bitspersample, item, bitsperitem, bitshift, itemsperline, items;
static int rleitem, rlebitsperitem, rlebitshift;
static int repeat, itembuf[128], count, repeatitem, repeatcount;

#if __STDC__
static void
putinit( char* name, int cols, int rows, int padright, int bps, float scale,
	 int dpi, int pagewid, int pagehgt, int format, int turnflag,
	 int turnokflag, int rleflag )
#else /*__STDC__*/
static void
putinit( name, cols, rows, padright, bps, scale, dpi, pagewid, pagehgt, format,
	 turnflag, turnokflag, rleflag )
    char* name;
    int cols, rows, padright, bps;
    float scale;
    int dpi, pagewid, pagehgt, format, turnflag, turnokflag, rleflag;
#endif /*__STDC__*/
    {
    int icols, irows, devpix;
    float pixfac, scols, srows, llx, lly;

    /* Turn? */
    icols = cols;
    irows = rows;
    if ( turnflag || ( turnokflag && cols > rows ) )
	{
	turnflag = 1;
	cols = irows;
	rows = icols;
	}

    /* Figure out size. */
    devpix = dpi / 72.0 + 0.5;		/* device pixels per unit, approx. */
    pixfac = 72.0 / dpi * devpix;	/* 1, approx. */
    scols = scale * cols * pixfac;
    srows = scale * rows * pixfac;
    if ( scols > pagewid * MARGIN || srows > pagehgt * MARGIN )
	{
	if ( scols > pagewid * MARGIN )
	    {
	    scale *= pagewid / scols * MARGIN;
	    scols = scale * cols * pixfac;
	    srows = scale * rows * pixfac;
	    }
	if ( srows > pagehgt * MARGIN )
	    {
	    scale *= pagehgt / srows * MARGIN;
	    scols = scale * cols * pixfac;
	    srows = scale * rows * pixfac;
	    }
	pm_message(
	    "warning, image too large for page, rescaling to %g", scale );
	}
    llx = ( pagewid - scols ) / 2;
    lly = ( pagehgt - srows ) / 2;

    fprintf (stdout,  "%%!PS-Adobe-2.0 EPSF-2.0\n" );
    fprintf (stdout,  "%%%%Creator: pnmtops\n" );
    fprintf (stdout,  "%%%%Title: %s.ps\n", name );
    fprintf (stdout,  "%%%%Pages: 1\n" );
    fprintf (stdout, 
	"%%%%BoundingBox: %d %d %d %d\n",
	(int) llx, (int) lly,
	(int) ( llx + scols + 0.5 ), (int) ( lly + srows + 0.5 ) );
    fprintf (stdout,  "%%%%EndComments\n" );
    if ( rleflag )
	{
	fprintf (stdout,  "/rlestr1 1 string def\n" );
	fprintf (stdout,  "/readrlestring {\n" );				/* s -- nr */
	fprintf (stdout,  "  /rlestr exch def\n" );			/* - */
	fprintf (stdout,  "  currentfile rlestr1 readhexstring pop\n" );	/* s1 */
	fprintf (stdout,  "  0 get\n" );					/* c */
	fprintf (stdout,  "  dup 127 le {\n" );				/* c */
	fprintf (stdout,  "    currentfile rlestr 0\n" );			/* c f s 0 */
	fprintf (stdout,  "    4 3 roll\n" );				/* f s 0 c */
	fprintf (stdout,  "    1 add  getinterval\n" );			/* f s */
	fprintf (stdout,  "    readhexstring pop\n" );			/* s */
	fprintf (stdout,  "    length\n" );				/* nr */
	fprintf (stdout,  "  } {\n" );					/* c */
	fprintf (stdout,  "    256 exch sub dup\n" );			/* n n */
	fprintf (stdout,  "    currentfile rlestr1 readhexstring pop\n" );/* n n s1 */
	fprintf (stdout,  "    0 get\n" );				/* n n c */
	fprintf (stdout,  "    exch 0 exch 1 exch 1 sub {\n" );		/* n c 0 1 n-1*/
	fprintf (stdout,  "      rlestr exch 2 index put\n" );
	fprintf (stdout,  "    } for\n" );				/* n c */
	fprintf (stdout,  "    pop\n" );					/* nr */
	fprintf (stdout,  "  } ifelse\n" );				/* nr */
	fprintf (stdout,  "} bind def\n" );
	fprintf (stdout,  "/readstring {\n" );				/* s -- s */
        fprintf (stdout,  "  dup length 0 {\n" );				/* s l 0 */
	fprintf (stdout,  "    3 copy exch\n" );				/* s l n s n l*/
	fprintf (stdout,  "    1 index sub\n" );				/* s l n s n r*/
	fprintf (stdout,  "    getinterval\n" );				/* s l n ss */
	fprintf (stdout,  "    readrlestring\n" );			/* s l n nr */
	fprintf (stdout,  "    add\n" );					/* s l n */
        fprintf (stdout,  "    2 copy le { exit } if\n" );		/* s l n */
        fprintf (stdout,  "  } loop\n" );					/* s l l */
        fprintf (stdout,  "  pop pop\n" );				/* s */
	fprintf (stdout,  "} bind def\n" );
	}
    else
	{
	fprintf (stdout,  "/readstring {\n" );				/* s -- s */
	fprintf (stdout,  "  currentfile exch readhexstring pop\n" );
	fprintf (stdout,  "} bind def\n" );
	}
    if ( PNM_FORMAT_TYPE( format ) == PPM_TYPE )
	{
	fprintf (stdout,  "/rpicstr %d string def\n", ( icols + padright ) * bps / 8 );
	fprintf (stdout,  "/gpicstr %d string def\n", ( icols + padright ) * bps / 8 );
	fprintf (stdout,  "/bpicstr %d string def\n", ( icols + padright ) * bps / 8 );
	}
    else
	fprintf (stdout,  "/picstr %d string def\n", ( icols + padright ) * bps / 8 );
    fprintf (stdout,  "%%%%EndProlog\n" );
    fprintf (stdout,  "%%%%Page: 1 1\n" );
    fprintf (stdout,  "gsave\n" );
    fprintf (stdout,  "%g %g translate\n", llx, lly );
    fprintf (stdout,  "%g %g scale\n", scols, srows );
    if ( turnflag )
	fprintf (stdout,  "0.5 0.5 translate  90 rotate  -0.5 -0.5 translate\n" );
    fprintf (stdout,  "%d %d %d\n", icols, irows, bps );
    fprintf (stdout,  "[ %d 0 0 -%d 0 %d ]\n", icols, irows, irows );
    if ( PNM_FORMAT_TYPE( format ) == PPM_TYPE )
	{
	fprintf (stdout,  "{ rpicstr readstring }\n" );
	fprintf (stdout,  "{ gpicstr readstring }\n" );
	fprintf (stdout,  "{ bpicstr readstring }\n" );
	fprintf (stdout,  "true 3\n" );
	fprintf (stdout,  "colorimage\n" );
	pm_message( "writing color PostScript..." );
	}
    else
	{
	fprintf (stdout,  "{ picstr readstring }\n" );
	fprintf (stdout,  "image\n" );
	}

    bitspersample = bps;
    itemsperline = items = 0;
    if ( rleflag )
	{
	rleitem = 0;
	rlebitsperitem = 0;
	rlebitshift = 8 - bitspersample;
	repeat = 1;
	count = 0;
	}
    else
	{
	item = 0;
	bitsperitem = 0;
	bitshift = 8 - bitspersample;
	}
    }

static void
putitem()
    {
    char* hexits = "0123456789abcdef";

    if ( itemsperline == 30 )
	{
	putchar( '\n' );
	itemsperline = 0;
	}
    putchar( hexits[item >> 4] );
    putchar( hexits[item & 15] );
    ++itemsperline;
    ++items;
    item = 0;
    bitsperitem = 0;
    bitshift = 8 - bitspersample;
    }

#if __STDC__
static void putxelval( xelval xv )
#else /*__STDC__*/
static void
putxelval( xv )
    xelval xv;
#endif /*__STDC__*/
    {
    if ( bitsperitem == 8 )
	putitem();
    item += xv << bitshift;
    bitsperitem += bitspersample;
    bitshift -= bitspersample;
    }

static void
putrest()
    {
    if ( bitsperitem > 0 )
	putitem();
    fprintf (stdout,  "\n" );
    fprintf (stdout,  "grestore\n" );
    fprintf (stdout,  "showpage\n" );
    fprintf (stdout,  "%%%%Trailer\n" );
    }

static void
rleputbuffer()
    {
    int i;

    if ( repeat )
	{
	item = 256 - count;
	putitem();
	item = repeatitem;
	putitem();
	}
    else
	{
	item = count - 1;
	putitem();
	for ( i = 0; i < count; ++i )
	    {
	    item = itembuf[i];
	    putitem();
	    }
	}
    repeat = 1;
    count = 0;
    }

static void
rleputitem()
    {
    int i;

    if ( count == 128 )
	rleputbuffer();

    if ( repeat && count == 0 )
	{ /* Still initializing a repeat buf. */
	itembuf[count] = repeatitem = rleitem;
	++count;
	}
    else if ( repeat )
	{ /* Repeating - watch for end of run. */
	if ( rleitem == repeatitem )
	    { /* Run continues. */
	    itembuf[count] = rleitem;
	    ++count;
	    }
	else
	    { /* Run ended - is it long enough to dump? */
	    if ( count > 2 )
		{ /* Yes, dump a repeat-mode buffer and start a new one. */
		rleputbuffer();
		itembuf[count] = repeatitem = rleitem;
		++count;
		}
	    else
		{ /* Not long enough - convert to non-repeat mode. */
		repeat = 0;
		itembuf[count] = repeatitem = rleitem;
		++count;
		repeatcount = 1;
		}
	    }
	}
    else
	{ /* Not repeating - watch for a run worth repeating. */
	if ( rleitem == repeatitem )
	    { /* Possible run continues. */
	    ++repeatcount;
	    if ( repeatcount > 3 )
		{ /* Long enough - dump non-repeat part and start repeat. */
		count = count - ( repeatcount - 1 );
		rleputbuffer();
		count = repeatcount;
		for ( i = 0; i < count; ++i )
		    itembuf[i] = rleitem;
		}
	    else
		{ /* Not long enough yet - continue as non-repeat buf. */
		itembuf[count] = rleitem;
		++count;
		}
	    }
	else
	    { /* Broken run. */
	    itembuf[count] = repeatitem = rleitem;
	    ++count;
	    repeatcount = 1;
	    }
	}

    rleitem = 0;
    rlebitsperitem = 0;
    rlebitshift = 8 - bitspersample;
    }

#if __STDC__
static void rleputxelval( xelval xv )
#else /*__STDC__*/
static void
rleputxelval( xv )
    xelval xv;
#endif /*__STDC__*/
    {
    if ( rlebitsperitem == 8 )
	rleputitem();
    rleitem += xv << rlebitshift;
    rlebitsperitem += bitspersample;
    rlebitshift -= bitspersample;
    }

static void
rleflush()
    {
    if ( rlebitsperitem > 0 )
	rleputitem();
    if ( count > 0 )
	rleputbuffer();
    }

static void
rleputrest()
    {
    rleflush();
    fprintf (stdout,  "\n" );
    fprintf (stdout,  "grestore\n" );
    fprintf (stdout,  "showpage\n" );
    fprintf (stdout,  "%%%%Trailer\n" );
    }
