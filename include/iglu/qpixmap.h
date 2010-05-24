#ifndef _iglu_QPixmap_h
#define _iglu_QPixmap_h

#include <iglu/tview.h>

class QPixmap: public TView {
  char *palette, *pixmap;
  int background;
public:
  QPixmap (TRect& r, char *pal, char *pix, int bg);
  virtual void Draw ();
};

#endif
