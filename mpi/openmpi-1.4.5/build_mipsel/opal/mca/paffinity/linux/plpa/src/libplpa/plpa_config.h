/* opal/mca/paffinity/linux/plpa/src/libplpa/plpa_config.h.  Generated from plpa_config.h.in by configure.  */
/* ./src/libplpa/plpa_config.h.in.  Generated from configure.ac by autoheader.  */

/* -*- c -*-
 *
 * Copyright (c) 2004-2005 The Trustees of Indiana University.
 *                         All rights reserved.
 * Copyright (c) 2004-2005 The Regents of the University of California.
 *                         All rights reserved.
 * Copyright (c) 2006-2008 Cisco Systems, Inc.  All rights reserved.
 * $COPYRIGHT$
 * 
 * Additional copyrights may follow
 * 
 * $HEADER$
 */

#ifndef PLPA_CONFIG_H
#define PLPA_CONFIG_H


/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the <valgrind/valgrind.h> header file. */
/* #undef HAVE_VALGRIND_VALGRIND_H */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Define to 1 if your C compiler doesn't accept -c and -o together. */
/* #undef NO_MINUS_C_MINUS_O */

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "http://www.open-mpi.org/community/help/"

/* Define to the full name of this package. */
#define PACKAGE_NAME "Open MPI"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "Open MPI 1.4.5"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "openmpi"

/* Define to the version of this package. */
#define PACKAGE_VERSION "1.4.5"

/* Whether we are in debugging more or not */
#define PLPA_DEBUG 0

/* Major version of PLPA */
/* #undef PLPA_MAJOR_VERSION */

/* Minor version of PLPA */
/* #undef PLPA_MINOR_VERSION */

/* Release version of PLPA */
/* #undef PLPA_RELEASE_VERSION */

/* The PLPA symbol prefix */
#define PLPA_SYM_PREFIX opal_paffinity_linux_plpa_

/* The PLPA symbol prefix in all caps */
#define PLPA_SYM_PREFIX_CAPS OPAL_PAFFINITY_LINUX_PLPA_

/* Whether we want Valgrind support or not */
#define PLPA_WANT_VALGRIND_SUPPORT 0

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
/* #undef YYTEXT_POINTER */

/* Emulated value */
/* #undef __NR_sched_getaffinity */

/* Emulated value */
/* #undef __NR_sched_setaffinity */

/* Define to `__inline__' or `__inline' if that's what the C compiler
   calls it, or to nothing if 'inline' is not supported under any name.  */
#ifndef __cplusplus
#define inline __inline__
#endif


#endif /* PLPA_CONFIG_H */

