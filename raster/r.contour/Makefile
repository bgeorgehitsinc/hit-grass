
MODULE_TOPDIR = ../..

PGM=r.contour

LIBES = $(VECTORLIB) $(DBMILIB) $(RASTERLIB) $(GISLIB) $(MATHLIB)
DEPENDENCIES = $(VECTORDEP) $(DBMIDEP) $(RASTERDEP) $(GISDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
