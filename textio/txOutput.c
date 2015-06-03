/*
 * txOutput.c --
 *
 * 	Handles 'stdout' and 'stderr' output.
 *
 *     ********************************************************************* 
 *     * Copyright (C) 1985, 1990 Regents of the University of California. * 
 *     * Permission to use, copy, modify, and distribute this              * 
 *     * software and its documentation for any purpose and without        * 
 *     * fee is hereby granted, provided that the above copyright          * 
 *     * notice appear in all copies.  The University of California        * 
 *     * makes no representations about the suitability of this            * 
 *     * software for any purpose.  It is provided "as is" without         * 
 *     * express or implied warranty.  Export of this software outside     * 
 *     * of the United States of America may require an export license.    * 
 *     *********************************************************************
 */

#ifndef lint
static char rcsid[] __attribute__ ((unused)) = "$Header: /usr/cvsroot/magic-7.5/textio/txOutput.c,v 1.1.1.1 2006/04/10 22:03:13 tim Exp $";
#endif  /* not lint */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifndef	SYSV
#include <sys/wait.h>
#endif /* SYSV */
#include <sys/stat.h>
#include <unistd.h>

#include "../utils/magic.h"
#include "textio.h"
#include "../utils/geometry.h"
#include "../utils/utils.h"
#include "../utils/malloc.h"

/* When a pipe has been opened to "more", the following variables
 * keep track of the file and process.  The "TxMoreFile" variable is
 * public so that routines like vfprintf() can check it to see if it
 * is NULL or not.  It is guaranteed to be NULL if we don't want to send
 * stuff through more.
 */

FILE * TxMoreFile = NULL;
#ifndef MAGIC_WRAPPER


/*
 * ----------------------------------------------------------------------------
 * TxFlush --
 *
 *	Flush the standard out and error out.
 *
 * Results:
 *	None.
 *
 * ----------------------------------------------------------------------------
 */ 

void
TxFlushErr()
{
    (void) fflush(stderr);
}

/*----------------------------------------------------------------------------*/

void
TxFlushOut()
{
    (void) fflush(stdout);
}

/*----------------------------------------------------------------------------*/

void
TxFlush()
{
    TxFlushOut();
    TxFlushErr();
}

#endif


/*
 * ----------------------------------------------------------------------------
 * TxError:
 *
 *	Magic's own version of printf, but it goes to stderr
 *
 * Tricks:
 *	Called with a variable number of arguments -- may not be portable.
 *
 * Results:
 *	None.
 *
 * Side effects:
 *	text appears on stderr on the text terminal
 *
 * Note: 
 *	Many thanks to Paul Chow at Stanford for getting this to run on
 *	a Pyramid machine.
 * ----------------------------------------------------------------------------
 */

void
TxError(char *fmt, ...)
{
    va_list args;
    FILE *f;

    TxFlushOut();
    if (TxMoreFile != NULL) 
	f = TxMoreFile;
    else
	f = stderr;
    va_start(args, fmt);
	Vfprintf(f, fmt, args);
    va_end(args);
    TxFlushErr();
}
