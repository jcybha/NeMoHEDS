#!/bin/sh
#
# ompi_get_version is created from ompi_get_version.m4 and ompi_get_version.m4sh.
#
# Copyright (c) 2004-2006 The Trustees of Indiana University and Indiana
#                         University Research and Technology
#                         Corporation.  All rights reserved.
# Copyright (c) 2004-2005 The University of Tennessee and The University
#                         of Tennessee Research Foundation.  All rights
#                         reserved.
# Copyright (c) 2004-2005 High Performance Computing Center Stuttgart,
#                         University of Stuttgart.  All rights reserved.
# Copyright (c) 2004-2005 The Regents of the University of California.
#                         All rights reserved.
# Copyright (c) 2008      Cisco Systems, Inc.  All rights reserved.
# $COPYRIGHT$
#
# Additional copyrights may follow
#
# $HEADER$
#



# OMPI_GET_VERSION(version_file, variable_prefix)
# -----------------------------------------------
# parse version_file for version information, setting
# the following shell variables:
#
#  prefix_VERSION
#  prefix_BASE_VERSION
#  prefix_MAJOR_VERSION
#  prefix_MINOR_VERSION
#  prefix_RELEASE_VERSION
#  prefix_GREEK_VERSION
#  prefix_WANT_SVN
#  prefix_SVN_R
#  prefix_RELEASE_DATE



srcfile="$1"
option="$2"

case "$option" in
    # svnversion can take a while to run.  If we don't need it, don't run it.
    --major|--minor|--release|--greek|--base|--help)
        ompi_ver_need_svn=0
        ;;
    *)
        ompi_ver_need_svn=1
esac


if test -z "$srcfile"; then
    option="--help"
else

    : ${ompi_ver_need_svn=1}
    : ${srcdir=.}
    : ${svnversion_result=-1}

        if test -f "$srcfile"; then
        ompi_vers=`sed -n "
	t clear
	: clear
	s/^major/OMPI_MAJOR_VERSION/
	s/^minor/OMPI_MINOR_VERSION/
	s/^release/OMPI_RELEASE_VERSION/
	s/^greek/OMPI_GREEK_VERSION/
	s/^want_svn/OMPI_WANT_SVN/
	s/^svn_r/OMPI_SVN_R/
	s/^date/OMPI_RELEASE_DATE/
	t print
	b
	: print
	p" < "$srcfile"`
	eval "$ompi_vers"

        # Only print release version if it isn't 0
        if test $OMPI_RELEASE_VERSION -ne 0 ; then
            OMPI_VERSION="$OMPI_MAJOR_VERSION.$OMPI_MINOR_VERSION.$OMPI_RELEASE_VERSION"
        else
            OMPI_VERSION="$OMPI_MAJOR_VERSION.$OMPI_MINOR_VERSION"
        fi
        OMPI_VERSION="${OMPI_VERSION}${OMPI_GREEK_VERSION}"
        OMPI_BASE_VERSION=$OMPI_VERSION

        if test $OMPI_WANT_SVN -eq 1 && test $ompi_ver_need_svn -eq 1 ; then
            if test "$svnversion_result" != "-1" ; then
                OMPI_SVN_R=$svnversion_result
            fi
            if test "$OMPI_SVN_R" = "-1" ; then

                if test -d "$srcdir/.svn" ; then
                    OMPI_SVN_R=r`svnversion "$srcdir"`
                elif test -d "$srcdir/.hg" ; then
                    OMPI_SVN_R=hg`hg -v -R "$srcdir" tip | grep changeset | cut -d: -f3`
                fi
                if test "OMPI_SVN_R" = ""; then
                    OMPI_SVN_R=svn`date '+%m%d%Y'`
                fi

            fi
            OMPI_VERSION="${OMPI_VERSION}${OMPI_SVN_R}"
        fi
    fi


    if test "$option" = ""; then
	option="--full"
    fi
fi

case "$option" in
    --full|-v|--version)
	echo $OMPI_VERSION
	;;
    --major)
	echo $OMPI_MAJOR_VERSION
	;;
    --minor)
	echo $OMPI_MINOR_VERSION
	;;
    --release)
	echo $OMPI_RELEASE_VERSION
	;;
    --greek)
	echo $OMPI_GREEK_VERSION
	;;
    --svn)
	echo $OMPI_SVN_R
	;;
    --base)
        echo $OMPI_BASE_VERSION
        ;;
    --release-date)
        echo $OMPI_RELEASE_DATE
        ;;
    --all)
        echo ${OMPI_VERSION} ${OMPI_MAJOR_VERSION} ${OMPI_MINOR_VERSION} ${OMPI_RELEASE_VERSION} ${OMPI_GREEK_VERSION} ${OMPI_SVN_R}
        ;;
    -h|--help)
	cat <<EOF
$0 <srcfile> <option>

<srcfile> - Text version file
<option>  - One of:
    --full         - Full version number
    --major        - Major version number
    --minor        - Minor version number
    --release      - Release version number
    --greek        - Greek (alpha, beta, etc) version number
    --svn          - Subversion repository number
    --all          - Show all version numbers, separated by :
    --base         - Show base version number (no svn number)
    --release-date - Show the release date
    --help         - This message
EOF
        ;;
    *)
        echo "Unrecognized option $option.  Run $0 --help for options"
        ;;
esac

# All done

exit 0
