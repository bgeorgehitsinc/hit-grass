
MODULE_TOPDIR = ../..

SUBDIRS1 = \
	i.ortho.camera \
	i.ortho.elev \
	i.ortho.init \
	i.ortho.photo \
	i.ortho.rectify \
	i.ortho.target \
	i.ortho.transform

SUBDIRS = lib $(SUBDIRS1)

include $(MODULE_TOPDIR)/include/Make/Dir.make

$(SUBDIRS1): lib

default: parsubdirs
