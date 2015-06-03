/*
 * magic.h --
 *
 * Global definitions for all MAGIC modules
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
 *
 * rcsid="$Header"
 */

#ifndef _MAGIC_H
#define	_MAGIC_H

/*
 * Note:  System files, such as "stdio.h" and "sys/types.h", should be
 * included before this magic.h file.  This is done automatically below
 * based on the _STDIO_H and _SYS_TYPES_H standard definitions.
 */

#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _SYS_TYPES_H
#include <sys/types.h>
#endif

/* Below is deprecated---magic from 7.2 rev. 56 is 64-bit clean! */
#ifdef ALPHA32BIT
/* must be before any declarations with pointers in them! */
#pragma pointer_size(short)
#ifndef ALPHA
#define	ALPHA
#endif
#endif

/* ------------------- Universal pointer typecast --------------------- */

#define SIZEOF_UNSIGNED_INT 4
#define SIZEOF_UNSIGNED_LONG 8
#define SIZEOF_UNSIGNED_LONG_LONG 8
#define SIZEOF_VOID_P 8

/* Set default value for backwards compatibility with non-autoconf make */
#ifndef SIZEOF_UNSIGNED_INT
#define SIZEOF_UNSIGNED_INT 4
#endif
#ifndef SIZEOF_UNSIGNED_LONG
#define SIZEOF_UNSIGNED_LONG 4
#endif
#ifndef SIZEOF_UNSIGNED_LONG_LONG
#define SIZEOF_UNSIGNED_LONG_LONG 8
#endif
#ifndef SIZEOF_VOID_P
#define SIZEOF_VOID_P SIZEOF_UNSIGNED_INT
#endif

#if SIZEOF_VOID_P == SIZEOF_UNSIGNED_INT
typedef unsigned int pointertype;
typedef signed int spointertype;
#elif SIZEOF_VOID_P == SIZEOF_UNSIGNED_LONG
typedef unsigned long pointertype;
typedef signed long spointertype;
#else
ERROR: Cannot compile without knowing the size of a pointer.  See utils/magic.h
#endif

/*-------------------------------------------------------------------
 * Define a double integer.  This replaces the horrible mess that
 * used to be the "DoubleInt" module.  Use of dlong should
 * improve the portability of magic.
 *
 * This defines "dlong" to be an 8-byte double-precision integer.
 *-------------------------------------------------------------------
 */

#ifdef HAVE_LIMITS_H
#include <limits.h>
#else
  #ifdef HAVE_SYS_PARAM_H
  #include <sys/param.h>
  #endif
#endif

#if defined(LONG_MAX) && defined(INT_MAX) 
  #if LONG_MAX == INT_MAX
  typedef long long dlong;
  #else
  typedef long dlong;
  #endif
#else
typedef long long dlong;
#endif

/* Modified by NP & Tim 7/04 */
// MAX vaule of dlong = 9223372036854775807LL [2^63]
#ifndef DLONG_MAX
  /* Note:  Linux defines LLONG_MAX but not LONG_LONG_MAX */
  #ifdef LLONG_MAX
  #define DLONG_MAX LLONG_MAX
  #else
    #ifdef LONG_LONG_MAX
    #define DLONG_MAX LONG_LONG_MAX
    #else
    #define DLONG_MAX 0x7FFFFFFFFFFFFFFFLL
    #endif
  #endif
#endif

#ifndef DLONG_MIN
  /* Note:  Linux defines LLONG_MIN but not LONG_LONG_MIN */
  #ifdef LLONG_MIN
  #define DLONG_MIN LLONG_MIN
  #else
    #ifdef LONG_LONG_MIN
    #define DLONG_MIN LONG_LONG_MIN
    #else
    #define DLONG_MIN 0x8000000000000000LL
    #endif
  #endif
#endif

/* --------------------- Universal pointer type ----------------------- */

#ifndef _CLIENTDATA
typedef pointertype ClientData;
#endif

/* --------------------------- Booleans ------------------------------- */

typedef unsigned char bool;

#ifndef TRUE
#define	TRUE	((bool)1)
#endif
#ifndef FALSE
#define	FALSE	((bool)0)
#endif

/* --------------------------- Infinities ------------------------------ */

/* maximum representable positive integer */
/* (special case vaxes to avoid compiler bug in ultrix) */
#ifdef vax
#define MAXINT 0x7fffffff
#else
#ifndef MAXINT
#define MAXINT (((unsigned int) ~0) >> 1)
#endif
#endif

/* ----------------------- Simple functions --------------------------- */

#ifndef	MAX
#define MAX(a,b)	(((a) < (b)) ? (b) : (a))
#endif

#ifndef	MIN
#define MIN(a,b)	(((a) > (b)) ? (b) : (a))
#endif

#define	ABS(x)		(((x) >= 0)  ? (x) : -(x))
#define	ABSDIFF(x,y)	(((x) < (y)) ? (y) - (x) : (x) - (y))
#define ODD(i)		(i&1)
#define EVEN(i)		(!(i&1))

/*----------------------------------------------------------------------*/
/* Round to nearest integer---use c99 functions if available from the	*/
/* math library (checked by "configure"), otherwise use the macro	*/
/* definitions below.							*/
/*----------------------------------------------------------------------*/

#ifndef HAVE_ROUND
#define round(a) (((a) < 0) ? (int)((a) - 0.5) : (int)((a) + 0.5))
#endif

#ifndef HAVE_ROUNDF
#define roundf(x) ((float)((int)((float)(x) + ((x < 0) ? -0.5 : 0.5))))
#endif

/* ------------ Function headers of globally used functions ----------- */

#ifndef __STDC__
extern char *strcpy(), *strncpy(), *index(), *rindex();
extern char *strcat(), *strncat();
#endif


/* -------------------------- Search paths ---------------------------- */

extern char *CellLibPath;	/* Path for finding cells. */
extern char *SysLibPath;	/* Path for finding system
				 * files like color maps, styles, etc.
				 */

/* --------------------- Debugging and assertions --------------------- */

/* To enable assertions, undefine NDEBUG in file defs.mak */

#include <assert.h>
#define	ASSERT(p, where) assert(p)	/* "where" is ignored */

/* ------------------------ Malloc/free ------------------------------- */

/*
 * Magic has its own versions of malloc() and free(), called mallocMagic()
 * and freeMagic().  Magic procedures should ONLY use these procedures.
 * Just for the sake of robustness, though, we define malloc and free
 * here to error strings.
 */
#define	malloc	You_should_use_the_Magic_procedure_mallocMagic_instead
#define	free	You_should_use_the_Magic_procedure_freeMagic_instead
#define calloc	You_should_use_the_Magic_procedure_callocMagic_instead

/* ---------- Flag for global variables (for readability) ------------- */

#define	global	/* Nothing */

/* ------------ Globally-used strings. -------------------------------- */

extern char *MagicVersion;
extern char *MagicRevision;
extern char *MagicCompileTime;
extern char AbortMessage[];

/* ---------------- Start of Machine Configuration Section ----------------- */

    /* ------- Configuration:  Handle Missing Routines/Definitions ------- */

/* System V is missing some BSDisms. */
#ifdef SYSV
# ifndef index
#  define index(x,y)		strchr((x),(int)(y))
# endif
# ifndef bcopy
#  define bcopy(a, b, c)	memcpy(b, a, c)
# endif
# ifndef bzero
#  define bzero(a, b)		memset(a, 0, b)
# endif
# ifndef bcmp
#  define bcmp(a, b, c)		memcmp(b, a, c)
# endif
# ifndef rindex
#  define rindex(x,y)  strrchr((x),(int)(y))
# endif
#endif

/* Some machines need vfprintf().  (A temporary MIPS bug?) (see txOutput.c) */
#if 	(defined(MIPSEB) && defined(SYSTYPE_BSD43)) || ibm032
# define	NEED_VFPRINTF
#endif

/* Some machines expect signal handlers to return an "int".  But most machines
 * expect them to return a "void".  If your machine expects an "int", put in
 * an "ifdef" below.
 */

#if 	(defined(MIPSEB) && defined(SYSTYPE_BSD43)) || ibm032
# define	SIG_RETURNS_INT
#endif

/* We have this really fancy abort procedure in utils/niceabort.c.  However,
 * these days only vax's appear to have all the things neccessary to make it
 * work (i.e. /usr/ucb/gcore).
 */

#ifdef	vax
# define	FANCY_ABORT
#endif


/*
 * errno and sys_errlist
 */
#ifdef CYGWIN
#include <errno.h>
#define sys_errlist _sys_errlist
#elif !defined(__FreeBSD__) && !defined(__NetBSD__) && !defined(__DragonFly__) && !defined(__APPLE__)
extern int errno;
/* extern char *sys_errlist[]; */
#elif defined(__APPLE__)
extern int errno;
#endif

/* 
 * Sprintf is a "char *" under BSD, and an "int" under System V. 
 */

#ifndef  __STDC__
#ifndef	SYSV
#if !defined(ALPHA) && !defined(__APPLE__)
    extern char* sprintf();
#endif
#endif
#endif

/*
 * Linux
 */
#ifdef	linux
#define       sigvec          sigaction
#define       sv_handler      sa_handler
#endif

/*
 * Irix 
 */
#ifdef sgi
#define vfork fork
#endif


/*
 * Select system call
 *
 * 	Note:  Errors here may be caused by not including <sys/types.h> 
 *	before "magic.h"
 */
#ifndef FD_SET
#define fd_set int
#define FD_SET(n, p)    ((*(p)) |= (1 << (n)))
#define FD_CLR(n, p)    ((*(p)) &= ~(1 << (n)))
#define FD_ISSET(n, p)  ((*(p)) & (1 << (n)))
#define FD_ZERO(p)      (*(p) = 0)
#endif

/*
 * Handling of VA_COPY.  These variables are set by the configuration
 * script.  Some systems define va_copy, some define __va_copy, and
 * some don't define it at all.  It is assumed that systems which do
 * not define it at all allow arguments to be copied with "=".
 */

#ifndef HAVE_VA_COPY
  #ifdef HAVE___VA_COPY
    #define va_copy(a, b) __va_copy(a, b)
  #else
    #define va_copy(a, b) a = b
  #endif
#endif

/* ------------------ End of Machine Configuration Section ----------------- */

#endif /* _MAGIC_H */
