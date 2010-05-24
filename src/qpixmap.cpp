#include <iglu/qpixmap.h>
#include <iglu/screen.h>

QPixmap::QPixmap (TRect& r, char *pal, char *pix, int bg):
  TView (r), palette(pal), pixmap(pix), background(bg)
{
}

void QPixmap::Draw () {
  TRect r (Bounds);
  gui_drawrectfill (r, background);
  gui_drawpixmap(r.a.x, r.a.y, r.deltax(), r.deltay(), pixmap, palette);
}
