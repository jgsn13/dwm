# dwm - dynamic window manager
# See LICENSE file for copyright and license details.

include config.mk

SRC = drw.c dwm.c util.c
OBJ = ${SRC:.c=.o}

all: options dwm

options:
	@echo dwm build options:
	@echo "CFLAGS   = ${CFLAGS}"
	@echo "LDFLAGS  = ${LDFLAGS}"
	@echo "CC       = ${CC}"

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.h config.mk

config.h:
	cp config.def.h $@

dwm: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f dwm ${OBJ} dwm-${VERSION}.tar.gz

dist: clean
	mkdir -p dwm-${VERSION}
	cp -R LICENSE Makefile README config.def.h config.mk\
		dwm.1 drw.h util.h ${SRC} dwm.png transient.c dwm-${VERSION}
	tar -cf dwm-${VERSION}.tar dwm-${VERSION}
	gzip dwm-${VERSION}.tar
	rm -rf dwm-${VERSION}

install: all
	mkdir -p ${DESTDIR}${PREFIX}/bin
	mkdir -pv /home/${SUDO_USER}/Pictures/Screenshots
	mkdir -pv /home/${SUDO_USER}/.local/share/dwm_utils
	cp -f dwm scripts/dwm_status_bar scripts/print_fullscreen scripts/print_select scripts/print_window scripts/dmenuunicode scripts/copygittoken ${DESTDIR}${PREFIX}/bin
	cp -f utils/emoji /home/${SUDO_USER}/.local/share/dwm_utils 
	cp -f dwm ${DESTDIR}${PREFIX}/bin
	chmod 755 ${DESTDIR}${PREFIX}/bin/dwm
	mkdir -p ${DESTDIR}${MANPREFIX}/man1
	sed "s/VERSION/${VERSION}/g" < dwm.1 > ${DESTDIR}${MANPREFIX}/man1/dwm.1
	chmod 644 ${DESTDIR}${MANPREFIX}/man1/dwm.1
	rm -rf config.h

uninstall:
	rm -f ${DESTDIR}${PREFIX}/bin/dwm\
		${DESTDIR}${PREFIX}/bin/dwm_status_bar\
		${DESTDIR}${PREFIX}/bin/print_fullscreen\
		${DESTDIR}${PREFIX}/bin/print_select\
		${DESTDIR}${PREFIX}/bin/print_window\
		${DESTDIR}${PREFIX}/bin/copygittoken\
		${DESTDIR}${PREFIX}/bin/dmenuunicode\
		/home/${SUDO_USER}/.local/share/dwm_utils/emoji\
		${DESTDIR}${MANPREFIX}/man1/dwm.1

.PHONY: all options clean dist install uninstall
