#############################################################################
# Makefile for building: qwatch
# Generated by qmake (2.01a) (Qt 4.5.1) on: Mon May 25 17:54:10 2009
# Project:  qwatch.pro
# Template: subdirs
# Command: /opt/qtsdk-2009.02/qt/bin/qmake -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qwatch.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /opt/qtsdk-2009.02/qt/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-src-app \
		sub-src-tests

src-app/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src-app/ || $(MKDIR) src-app/ 
	cd src-app/ && $(QMAKE) src-app.pro -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o $(MAKEFILE)
sub-src-app-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src-app/ || $(MKDIR) src-app/ 
	cd src-app/ && $(QMAKE) src-app.pro -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o $(MAKEFILE)
sub-src-app: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE)
sub-src-app-make_default-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) 
sub-src-app-make_default: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) 
sub-src-app-make_first-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) first
sub-src-app-make_first: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) first
sub-src-app-all-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) all
sub-src-app-all: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) all
sub-src-app-clean-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-app-clean: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-app-distclean-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-app-distclean: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-app-install_subtargets-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) install
sub-src-app-install_subtargets: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) install
sub-src-app-uninstall_subtargets-ordered: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-src-app-uninstall_subtargets: src-app/$(MAKEFILE) FORCE
	cd src-app/ && $(MAKE) -f $(MAKEFILE) uninstall
src-tests/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) src-tests/ || $(MKDIR) src-tests/ 
	cd src-tests/ && $(QMAKE) src-tests.pro -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o $(MAKEFILE)
sub-src-tests-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) src-tests/ || $(MKDIR) src-tests/ 
	cd src-tests/ && $(QMAKE) src-tests.pro -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o $(MAKEFILE)
sub-src-tests: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE)
sub-src-tests-make_default-ordered: src-tests/$(MAKEFILE) sub-src-app-make_default-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) 
sub-src-tests-make_default: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) 
sub-src-tests-make_first-ordered: src-tests/$(MAKEFILE) sub-src-app-make_first-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) first
sub-src-tests-make_first: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) first
sub-src-tests-all-ordered: src-tests/$(MAKEFILE) sub-src-app-all-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) all
sub-src-tests-all: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) all
sub-src-tests-clean-ordered: src-tests/$(MAKEFILE) sub-src-app-clean-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-tests-clean: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) clean
sub-src-tests-distclean-ordered: src-tests/$(MAKEFILE) sub-src-app-distclean-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-tests-distclean: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) distclean
sub-src-tests-install_subtargets-ordered: src-tests/$(MAKEFILE) sub-src-app-install_subtargets-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) install
sub-src-tests-install_subtargets: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) install
sub-src-tests-uninstall_subtargets-ordered: src-tests/$(MAKEFILE) sub-src-app-uninstall_subtargets-ordered  FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) uninstall
sub-src-tests-uninstall_subtargets: src-tests/$(MAKEFILE) FORCE
	cd src-tests/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: qwatch.pro  /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64/qmake.conf /opt/qtsdk-2009.02/qt/mkspecs/common/g++.conf \
		/opt/qtsdk-2009.02/qt/mkspecs/common/unix.conf \
		/opt/qtsdk-2009.02/qt/mkspecs/common/linux.conf \
		/opt/qtsdk-2009.02/qt/mkspecs/qconfig.pri \
		/opt/qtsdk-2009.02/qt/mkspecs/features/qt_functions.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/qt_config.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/exclusive_builds.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/default_pre.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/debug.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/default_post.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/warn_on.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/qt.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/unix/thread.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/moc.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/resources.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/uic.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/yacc.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/lex.prf \
		/opt/qtsdk-2009.02/qt/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qwatch.pro
/opt/qtsdk-2009.02/qt/mkspecs/common/g++.conf:
/opt/qtsdk-2009.02/qt/mkspecs/common/unix.conf:
/opt/qtsdk-2009.02/qt/mkspecs/common/linux.conf:
/opt/qtsdk-2009.02/qt/mkspecs/qconfig.pri:
/opt/qtsdk-2009.02/qt/mkspecs/features/qt_functions.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/qt_config.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/exclusive_builds.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/default_pre.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/debug.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/default_post.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/warn_on.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/qt.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/unix/thread.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/moc.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/resources.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/uic.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/yacc.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/lex.prf:
/opt/qtsdk-2009.02/qt/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /opt/qtsdk-2009.02/qt/mkspecs/linux-g++-64 -unix CONFIG+=debug -o Makefile qwatch.pro

qmake_all: sub-src-app-qmake_all sub-src-tests-qmake_all FORCE

make_default: sub-src-app-make_default-ordered sub-src-tests-make_default-ordered FORCE
make_first: sub-src-app-make_first-ordered sub-src-tests-make_first-ordered FORCE
all: sub-src-app-all-ordered sub-src-tests-all-ordered FORCE
clean: sub-src-app-clean-ordered sub-src-tests-clean-ordered FORCE
distclean: sub-src-app-distclean-ordered sub-src-tests-distclean-ordered FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-src-app-install_subtargets-ordered sub-src-tests-install_subtargets-ordered FORCE
uninstall_subtargets: sub-src-app-uninstall_subtargets-ordered sub-src-tests-uninstall_subtargets-ordered FORCE

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

