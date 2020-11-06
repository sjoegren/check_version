SUBDIRS = src

EXTRA_DIST = LICENSE

README: README.md
	sed -e '/http.*\.svg/d' $< > $@
