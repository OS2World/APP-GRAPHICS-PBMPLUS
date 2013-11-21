


		    PBMPLUS FOR OS/2 2.0 icc version
	 brought to you by Michael Caldwell (mcaldwel@netcom.com)
   Also available is the DKB ray tracer with an integrated PM interface.
		      DKBPM is available on EXEC-PC.



I have not been able to use the MSDOS version of pbmplus under OS/2 1.3 or
OS/2 2.0, it causes OS/2 1.3 to hang and it causes an OS/2 2.0 VDM to
trap.  So I have ported pbmplus (10dec91) to OS/2 2.0 using icc.

Notes:

Thanks to John Stone (johns@cs.umr.edu) who identified the stdout problem.

I have modified a few source files and of course the configure items in
'pbmplus.h'.

I created new make files and .def files for the dlls and the exes.

The libraries are dlls with the nonshared data attribute set.

The dlls import functions from other dlls, so you have to have all the
dlls including the tiff library dll and the pbmplus C run time library dll
in your libpath.

The -Ge- option is important for dlls.

The -Gd option is for the dynamically linked C run time library.  This
eliminates the comparison problem with stdout.  This also saves as much
disk space as possible.

In order to use the write and getpid functions I had to specify -Sm option
for the migration libraries.  Then I had to manually define __STDC__
instead of using -Sa so that stdarg.h and not varargs.h is included.

In order to use the O_* identifiers in the tiff library I had to specify
-Sm option for the migration libraries.  Then I had to manually define
__STDC__ instead of using -Sa so that stdarg.h and not varargs.h is
included.

And lastly I did a little trick at the end of the pbmplus.h file where I
open another file handle for stdout in binary mode then replace the
definition for stdout with the new file handle.  I also defined the main
function in the header file which does the file handle substitution and
calls main_continued.  I then define main as main_continued.

Because of the new stdout handle I had to make sure every program closed
the handle before terminating otherwise the data wouldn't get flushed and I
had to change 'printf (' to 'fprintf (stdout,'.

In pnmtotiff I had to change the hard coded '1' for stdout's file handle
to 'fileno (stdout)'.

The program pnmcat is linked with setargv.obj so you can specify wildcards
on the command line.

Michael Caldwell (mcaldwel@netcom.com)
