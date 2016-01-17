AC_INIT([meta-heuristics], [1.0], [hoai@cse.hcmut.edu.vn])
AM_INIT_AUTOMAKE([-Wall no-dependencies dist-bzip2])

AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_RANLIB

AC_CONFIG_FILES([Makefile])

AC_ARG_ENABLE(debug,
              [  --enable-debug=debuglevel   Enable debug output in library ],
              [ if test "$enableval" = "no"; then
                  debuglevel=0
                else
                  debuglevel=$enableval
                fi
              ],
              [debuglevel=0])

AC_SUBST(debuglevel)

mysubdirs=""
AC_ARG_ENABLE([mpi],
              [AS_HELP_STRING([--enable-mpi],
                              [create MPI-based metasearch library (default is yes)])],
              [lib=$enableval],
              [lib=no])
if [ test "$lib" = "yes" ]; then
  AC_CHECK_PROG(MPICXX, [mpicxx],[mpicxx], [mpicxx not found])
  if [ test "$MPICXX" != "mpicxx" ]; then
    AS_EXIT([])
  fi
  AC_CONFIG_FILES([lib/Makefile tsp/Makefile])
  mysubdirs+=" lib tsp"
fi

AC_ARG_ENABLE([popc],
              [AS_HELP_STRING([--enable-popc],
                              [create POPC-based metasearch library (default is no)])],
              [popclib=$enableval],
              [popclib=no])

if [ test "$popclib" = "yes" ]; then
  AC_CHECK_PROG(PAROCC, [parocc], [parocc], [parocc not found])
  if [ test "$PAROCC" != "parocc" ]; then
    AS_EXIT([])
  fi
  AC_CONFIG_FILES([lib/Makefile test/Makefile])
  mysubdirs+=" lib test"
fi
mysubdirs+=" sample_data tools"
AC_SUBST(mybuilddir, ["$mysubdirs"])

AC_CONFIG_FILES([sample_data/Makefile tools/Makefile])

AC_OUTPUT
