MODULE_TOPDIR = ../..

PGM = r.carve

LIBES = $(VECTORLIB) $(BITMAPLIB) $(DIG2LIB) $(RASTERLIB) $(GISLIB)
DEPENDENCIES = $(VECTORDEP) $(BITMAPDEP) $(DIG2DEP) $(RASTERDEP) $(GISDEP)

EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
