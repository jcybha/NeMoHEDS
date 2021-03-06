# There can be multiple blocks of configuration data, chosen by
# compiler flags (using the compiler_args key to chose which block
# should be activated.  This can be useful for multilib builds.  See the
# multilib page at:
#    https://svn.open-mpi.org/trac/ompi/wiki/compilerwrapper3264 
# for more information.

project=Open MPI
project_short=OMPI
version=@OMPI_VERSION_STRING@
language=Fortran 77
compiler_env=F77
compiler_flags_env=FFLAGS
compiler=@F77@
extra_includes=
preprocessor_flags=
compiler_flags=@OMPI_WRAPPER_EXTRA_FFLAGS@
linker_flags=@OMPI_WRAPPER_EXTRA_LDFLAGS@
libs=libmpi.lib libopen-rte.lib libopen-pal.lib @OMPI_WRAPPER_EXTRA_LIBS@
required_file=@OMPI_WRAPPER_F77_REQUIRED_FILE@
includedir=${includedir}
libdir=${libdir}
