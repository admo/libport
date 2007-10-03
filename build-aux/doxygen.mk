## To use this module, DOCDIR must be defined.
## Additionnal variable: EXCLUDE_PATTERNS (see the Doxygen manual)

## ----------------------- ##
## Doxygen documentation.  ##
## ----------------------- ##

.PHONY: doc internal-doc user-doc

doc: internal-doc

internal-doc:
	rm -rf $(DOCDIR).tmp $(builddir)/$(DOCDIR)
	$(MAKE) $(AM_MAKEFLAGS) DOC_INTERNAL=YES doc-builder

user-doc:
	rm -rf $(DOCDIR).tmp $(builddir)/$(DOCDIR)
	$(MAKE) $(AM_MAKEFLAGS) DOC_INTERNAL=NO doc-builder

EXTRA_DIST = $(builddir)/$(DOCDIR)

$(builddir)/$(DOCDIR):
	$(mkdir_p) $(builddir)/$(DOCDIR)

doc-builder: $(top_srcdir)/build-aux/Doxyfile.in
	test -w $(builddir)
	rm -rf $(DOCDIR).tmp $(builddir)/$(DOCDIR)
	$(MAKE) $(AM_MAKEFLAGS) Doxyfile
	sed -e 's/@DOC_INTERNAL@/$(DOC_INTERNAL)/g' \
            -e 's,@EXCLUDE_PATTERNS@,$(EXCLUDE_PATTERNS),g' Doxyfile >Doxytmp
	mv -f Doxytmp Doxyfile
	chmod -w Doxyfile
	$(DOXYGEN) Doxyfile
	mv $(DOCDIR).tmp $(builddir)/$(DOCDIR)

maintainer-clean-local:
	rm -rf $(DOCDIR).tmp $(builddir)/$(DOCDIR)

# We install by hand, otherwise Automake produces "install .../srcdoc
# .../srcdoc", which install our dir into the previous one, instead of
# replacing it.
if ENABLE_DOC
install-data-local:
	rm -rf $(DESTDIR)$(htmldir)/$(DOCDIR)
	$(mkdir_p) $(DESTDIR)$(htmldir)
	cp -r $(builddir)/$(DOCDIR) $(DESTDIR)$(htmldir)

uninstall-local:
	(test -d && chmod -R 700 $(DESTDIR)$(htmldir)/$(DOCDIR)) || true
	rm -rf $(DESTDIR)$(htmldir)/$(DOCDIR)
endif
