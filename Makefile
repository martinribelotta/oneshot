# Makefile.x11 for One-SHOT

LDOPT=-L/usr/X11R6/lib -lX11
COMPILE_CPP=g++ -Wwrite-strings -c -Os -DONX11 -ggdb3 -o $@ -I./include $<
OBJECTS=\
obj/about.o obj/document.o obj/fontm.o obj/icons.o obj/main.o obj/mouse.o obj/mousehdl.o \
obj/msgbox.o obj/qcomps.o obj/qnode.o obj/qpixmap.o obj/screen.o obj/structs.o obj/tbutton.o \
obj/tcanvas.o obj/tcheck.o obj/tctainer.o obj/tevent.o obj/tevmng.o obj/tfdialog.o obj/tflist.o \
obj/tinput.o obj/tlabel.o obj/tless.o obj/tlistbox.o obj/tlist.o obj/tmenu.o obj/tprogram.o \
obj/tscroll.o obj/tshape.o obj/tview.o obj/twindow.o obj/vcomps.o

oneshot: $(OBJECTS)
	g++ -o$@ $(OBJECTS) $(LDOPT)

obj/about.o:src/about.cpp
	$(COMPILE_CPP)

obj/document.o:src/document.cpp
	$(COMPILE_CPP)

obj/fontm.o:src/x11/fontm.cpp
	$(COMPILE_CPP)

obj/icons.o:src/icons.cpp
	$(COMPILE_CPP)

obj/main.o:src/main.cpp
	$(COMPILE_CPP)

obj/mouse.o:src/x11/mouse.cpp
	$(COMPILE_CPP)

obj/mousehdl.o:src/mousehdl.cpp
	$(COMPILE_CPP)

obj/msgbox.o:src/msgbox.cpp
	$(COMPILE_CPP)

obj/qcomps.o:src/qcomps.cpp
	$(COMPILE_CPP)

obj/qnode.o:src/qnode.cpp
	$(COMPILE_CPP)

obj/qpixmap.o:src/qpixmap.cpp
	$(COMPILE_CPP)

obj/screen.o:src/x11/screen.cpp
	$(COMPILE_CPP)

obj/structs.o:src/structs.cpp
	$(COMPILE_CPP)

obj/tbutton.o:src/tbutton.cpp
	$(COMPILE_CPP)

obj/tcanvas.o:src/tcanvas.cpp
	$(COMPILE_CPP)

obj/tcheck.o:src/tcheck.cpp
	$(COMPILE_CPP)

obj/tctainer.o:src/tctainer.cpp
	$(COMPILE_CPP)

obj/tevent.o:src/x11/tevent.cpp
	$(COMPILE_CPP)

obj/tevmng.o:src/tevmng.cpp
	$(COMPILE_CPP)

obj/tfdialog.o:src/tfdialog.cpp
	$(COMPILE_CPP)

obj/tflist.o:src/tflist.cpp
	$(COMPILE_CPP)

obj/tinput.o:src/tinput.cpp
	$(COMPILE_CPP)

obj/tlabel.o:src/tlabel.cpp
	$(COMPILE_CPP)

obj/tless.o:src/tless.cpp
	$(COMPILE_CPP)

obj/tlistbox.o:src/tlistbox.cpp
	$(COMPILE_CPP)

obj/tlist.o:src/tlist.cpp
	$(COMPILE_CPP)

obj/tmenu.o:src/tmenu.cpp
	$(COMPILE_CPP)

obj/tprogram.o:src/tprogram.cpp
	$(COMPILE_CPP)

obj/tscroll.o:src/tscroll.cpp
	$(COMPILE_CPP)

obj/tshape.o:src/tshape.cpp
	$(COMPILE_CPP)

obj/tview.o:src/tview.cpp
	$(COMPILE_CPP)

obj/twindow.o:src/twindow.cpp
	$(COMPILE_CPP)

obj/vcomps.o:src/vcomps.cpp
	$(COMPILE_CPP)

clean:
	rm oneshot obj/*.o
