MODULE_TOPDIR = ../../..

PGM=test.raster3d.lib

LIBES = $(GISLIB) $(RASTER3DLIB) $(RASTERLIB)
DEPENDENCIES = $(GISDEP) $(RASTER3DDEP) $(RASTERDEP)
EXTRA_INC = $(VECT_INC)
EXTRA_CFLAGS = $(VECT_CFLAGS)

include $(MODULE_TOPDIR)/include/Make/Module.make

default: cmd
