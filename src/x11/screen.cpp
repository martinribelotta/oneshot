/*
 * IGLU Iterfaz Grafica Libre del Usuario.
 * Copyright (C) 2005 Martin Alejandro Ribelotta
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */
#include <iglu/screen.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>

#define RGB(r,g,b)    ((unsigned long)(r<<16)|(g<<8)|b)
#define GETR(c)       ((c>>16)&0xFF)
#define GETG(c)       ((c>>8)&0xFF)
#define GETB(c)       ((c)&0xFF)

int Wt, Ht, MaxX = 640, MaxY = 480;

static Colormap clmap;

unsigned long egacolors[32];

static TRect actual_clip;

static bool needFlush=false;

Display *dis;
int screen;
Window win;
GC gc;
XGCValues gs;
XFontStruct *fonts;

static void CreateStdColors () {
	egacolors[0]=RGB(0,   0,   0  );	/* black */
	egacolors[1]=RGB(0,   0,   170);	/* blue */
	egacolors[2]=RGB(0,   170, 0  );	/* green */
	egacolors[3]=RGB(0,   170, 170);	/* cyan */
	egacolors[4]=RGB(170, 0,   0  );	/* red */
	egacolors[5]=RGB(170, 0,   170);	/* magenta */
	egacolors[6]=RGB(170, 85,  0  );	/* brown */
	egacolors[7]=RGB(170, 170, 170);	/* light gray */
	egacolors[8]=RGB(85,  85,  85 );	/* dark gray */
	egacolors[9]=RGB(85,  85,  255);	/* light blue */
	egacolors[10]=RGB(85,  255, 85 );	/* light green */
	egacolors[11]=RGB(85,  255, 255);	/* light cyan */
	egacolors[12]=RGB(255, 85,  85 );	/* light red */
	egacolors[13]=RGB(255, 85,  255);	/* light magenta */
	egacolors[14]=RGB(255, 255, 85 );	/* yellow */
	egacolors[15]=RGB(255, 255, 255);	/* white */
	int i;
	XColor c;
	clmap = DefaultColormap(dis, screen);
	for (i=0; i<16; i++) {
		c.red = GETR(egacolors[i])<<8;
		c.green = GETG(egacolors[i])<<8;
		c.blue = GETB(egacolors[i])<<8;
		XAllocColor (dis, clmap, &c);
		egacolors[i] = c.pixel;
	}
}

void initGUI (void)
{
  unsigned long bg;
  dis=XOpenDisplay((char *)0);
  screen=DefaultScreen(dis);
  bg = BlackPixel (dis,screen);
  CreateStdColors ();
/*  if (Application)
    bg = Application->bg;*/
  win=XCreateSimpleWindow(dis,DefaultRootWindow(dis),0,0,
			MaxX, MaxY, 5,
			WhitePixel(dis,screen),
			bg);

  XSelectInput (dis, win,
  	ExposureMask|
	ButtonPressMask|
	ButtonReleaseMask|
	PointerMotionMask|
	KeyPressMask|
	StructureNotifyMask
  );

  Wt=gui_textw("_");
  Ht=gui_texth("$");
  XSetStandardProperties(dis,win,"IGLU","IGLU",None,NULL,0,NULL);

  initMouseHandle();

  gc=XCreateGC(dis, win, 0, &gs);
  XSetBackground(dis,gc,WhitePixel(dis,screen));
  XSetForeground(dis,gc,BlackPixel(dis,screen));
  XSetLineAttributes(dis, gc, 1, LineSolid, CapButt, JoinRound);
  actual_clip = TRect(0,0,MaxX,MaxY);
  gui_setclip (actual_clip);
  XClearWindow(dis, win);
  XMapRaised(dis, win);
}

void doneGUI ()
{
  doneMouseHandle();
  XFreeGC(dis, gc);
  XDestroyWindow(dis,win);
  XCloseDisplay(dis);
}

//////////////////////////////////////////////////////////////////////

void gui_drawpixel(int x, int y, int color) {
  XSetForeground(dis,gc,egacolors[color]);
  XDrawPoint(dis,win,gc, x, y);
  needFlush = true;
}

int gui_getpixel(int x, int y)
  { return 0; } // Not supòrted Mierda!

void gui_drawline(int xa, int ya, int xb, int yb, int cl) {
  XSetForeground(dis,gc,egacolors[cl]);
  XDrawLine(dis,win,gc,xa,ya,xb,yb);
  needFlush = true;
}

void gui_drawvline(int x, int y, int dy, int cl) {
  gui_drawline (x,y,x,dy,cl);
  needFlush = true;
}

void gui_drawhline(int x, int y, int dx, int cl) {
  gui_drawline (x,y,dx,y,cl);
  needFlush = true;
}

void gui_drawpolyline(int n, int *points, int color) {
  XPoint *pts = new XPoint[n];
  int i, j;
  for (i=0, j=0; i<n; i++) {
  	pts[i].x = points[j++];
  	pts[i].y = points[j++];
  }
  XSetForeground(dis,gc,egacolors[color]);
  XDrawPoints(dis,win,gc,pts,n,0);
  delete pts;
  needFlush = true;
}

void gui_drawrect(TRect& r, int color) {
  XSetForeground(dis,gc,egacolors[color]);
  XDrawRectangle (dis,win,gc, r.a.x, r.a.y, r.deltax(), r.deltay());
  needFlush = true;
}

void gui_drawrectfill(TRect& r, int color) {
  XSetForeground(dis,gc,egacolors[color]);
  XFillRectangle(dis,win,gc, r.a.x, r.a.y, r.deltax(), r.deltay());
  needFlush = true;
}

void gui_drawcircle(int x, int y, int radius, int color) {
  x-=radius;
  y-=radius;
  radius*=2;
  XSetForeground(dis,gc,egacolors[color]);
  XDrawArc(dis,win,gc, x,y, radius, radius, 0, 360*64);
  needFlush = true;
}

void gui_drawcirclefill(int x, int y, int radius, int color) {
  x-=radius;
  y-=radius;
  radius*=2;
  XSetForeground(dis,gc,egacolors[color]);
  XFillArc(dis,win,gc, x,y, radius, radius, 0, 360*64);
  needFlush = true;
}

extern void writechar (int x, int y, char c, int cl);

void gui_outtextxy(int x, int y, char *s, int center, int fg, int bg)
{
  if (center) (y-=Ht/2, x-=gui_textw(s)>>1);
  TRect r (x, y, x+gui_textw(s), y+gui_texth(s));
  if (bg!=-1)
    gui_drawrectfill(r, bg);
  while (*s)
    writechar (x, y, *(s++), fg), x+=8;
  needFlush = true;
}

int gui_textw(char *s)
{
//  return XTextWidth (fonts, s, strlen(s));
  int l, i;
  for (l=i=0; s[i]; i++, l+=8);
  return l;
}

int gui_texth(char *s)
{
//  return fonts->ascent+fonts->descent;
  return 8;
}

void gui_setclip(TRect& r)
{
  XRectangle rects[1];
  rects[0].x = r.a.x;
  rects[0].y = r.a.y;
  rects[0].width = r.deltax()+1;
  rects[0].height = r.deltay()+1;
  actual_clip = r;
  XSetClipRectangles(dis,gc,0,0, rects, 1, 0);
}

void gui_getclip(TRect& r)
{
  r = actual_clip;
}

void *gui_getimage(TRect& r)
{
  (void) r;
/*  GrContext *bmp = GrCreateContext(r.deltax()+1, r.deltay()+1, NULL, NULL);
  GrBitBlt(bmp, 0, 0,
           GrCurrentContext(), r.a.x, r.a.y, r.b.x+1, r.b.y+1, GrIMAGE);
  return (void*)bmp;*/
  return NULL;
}

void gui_putimage (void *bmp, int x, int y, int freshed)
{
  (void)bmp; (void)x; (void)y; (void)freshed;
/*  GrContext *bmp2 = (GrContext*)bmp;
  GrBitBlt(GrCurrentContext(), x, y,
           bmp2, 0, 0, bmp2->gc_xmax+1, bmp2->gc_ymax+1, GrWRITE);
  if (freshed)
    free(bmp);*/
}

void gui_wmode(int mode) {
  static int ops[4] = {
    GXcopy,     /* C_WRITE */
    GXxor,      /* C_XOR */
    GXor,       /* C_OR */
    GXand       /* C_AND */
  };
  XSetFunction (dis,gc,ops[mode&0x03]);
}

void gui_drawelipse (int ax, int ay, int bx, int by, int cl)
{
  XSetForeground(dis,gc,egacolors[cl]);
  XDrawArc(dis,win,gc, ax, ay, bx-ax, by-ay, 0, 360*64);
  needFlush = true;
}

void gui_drawfillelipse (int ax, int ay, int bx, int by, int cl)
{
  XSetForeground(dis,gc,egacolors[cl]);
  XFillArc(dis,win,gc, ax, ay, bx-ax, by-ay, 0, 360*64);
  needFlush = true;
}

void gui_drawpixmap (int x, int y, int w, int h, char *b, char *p)
{
  int i,j,k;
  for (j=0, k=0; j<h; j++)
    for (i=0; i<w; i++, k++)
      if (p[b[k]-'0']!=-1)
        gui_drawpixel(x+i, y+j, p[b[k]-'0']);
  needFlush = true;
}

void gui_flush() {
	if ( needFlush )
		XFlush( dis );
}
