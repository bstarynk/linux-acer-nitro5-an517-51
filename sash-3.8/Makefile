#
# Makefile for sash
#
# The HAVE_GZIP definition adds the -gzip and -gunzip commands.
# The HAVE_LINUX_ATTR definition adds the -chattr and -lsattr commands.
# The HAVE_LINUX_CHROOT definition adds the -chroot command.
# The HAVE_LINUX_PIVOT definition adds the -pivot_root command.
# The HAVE_LINUX_LOSETUP definition adds the -losetup command.
# The HAVE_LINUX_MOUNT definition makes -mount and -umount work on Linux.
# The HAVE_BSD_MOUNT definition makes -mount and -umount work on BSD.
# The MOUNT_TYPE definition sets the default file system type for -mount.
#
# Note that the linker may show warnings about 'statically linked
# programs' requiring getpwnam, getpwuid, getgrnam and getgrgid.
# This is unavoidable since those routines use dynamic libraries anyway.
# Sash will still run, but if there are shared library problems then
# the user might have to be be careful when using the -chown, -chgrp,
# and -ls commands.
#

HAVE_GZIP		= 1
HAVE_LINUX_ATTR		= 1
HAVE_LINUX_CHROOT	= 1
HAVE_LINUX_LOSETUP	= 1
HAVE_LINUX_PIVOT	= 1
HAVE_LINUX_MOUNT	= 1
HAVE_BSD_MOUNT		= 0
MOUNT_TYPE		= '"ext4"'

OPT = -O2 -g

CFLAGS = $(OPT) -Wall -Wmissing-prototypes \
	-DHAVE_GZIP=$(HAVE_GZIP) \
	-DHAVE_LINUX_ATTR=$(HAVE_LINUX_ATTR) \
	-DHAVE_LINUX_CHROOT=$(HAVE_LINUX_CHROOT) \
	-DHAVE_LINUX_LOSETUP=$(HAVE_LINUX_LOSETUP) \
	-DHAVE_LINUX_PIVOT=$(HAVE_LINUX_PIVOT) \
	-DHAVE_LINUX_MOUNT=$(HAVE_LINUX_MOUNT) \
	-DHAVE_BSD_MOUNT=$(HAVE_BSD_MOUNT) \
	-DMOUNT_TYPE=$(MOUNT_TYPE)

LDFLAGS = -static
LIBS = -lreadline -lz -lcurl
INDENT= indent
INDENTFLAGS= --gnu-style 
ASTYLE= astyle
ASTYLE_FLAGS= --style=gnu -s2
DESTDIR =
BINDIR = /bin
MANDIR = /usr/man

.PHONY: all sash clean indent

all: sash

OBJS = sash.o cmds.o cmd_dd.o cmd_ed.o cmd_grep.o cmd_ls.o cmd_tar.o \
	cmd_gzip.o cmd_find.o cmd_file.o cmd_chattr.o cmd_basile.o cmd_ar.o utils.o



sash:	$(OBJS)
	$(CXX) $(LDFLAGS) -o sash $(OBJS) $(LIBS)

cmd_basile.o: cmd_basile.cpp
	$(CXX) -c -I . -I /usr/include -I /usr/local/include $^ -o $@

clean:
	rm -vf $(OBJS) sash *.orig

install: sash
	cp sash $(DESTDIR)/$(BINDIR)/sash
	cp sash.1 $(DESTDIR)/$(MANDIR)/man1/sash.1

indent:
	for f in *.c ; do \
	  mv --backup $$f $$f.orig ; \
	  $(INDENT) $(INDENTFLAGS) $$f ; \
	done
	for f in  *.cpp ; do \
	  mv --backup $$f $$f.orig ; \
	  $(ASTYLE) $(ASTYLEFLAGS) $$f ; \
	done

$(OBJS):	sash.h
