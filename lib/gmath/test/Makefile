MODULE_TOPDIR = ../../..

PGM=test.gmath.lib

LIBES = $(GISLIB) $(GMATHLIB) $(OPENMP_LIBPATH) $(OPENMP_LIB)
DEPENDENCIES = $(GISDEP) $(GMATHDEP) $(OMPDEP)
EXTRA_CFLAGS = $(OPENMP_CFLAGS)
EXTRA_INC = $(OPENMP_INCPATH)

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
