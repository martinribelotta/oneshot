#ifndef _iglu_QPixmap_h
#define _iglu_QPixmap_h

#include <iglu/tview.h>

class QPixmap: public TView {
  const char *palette;
  const char *pixmap;
  int background;
public:
  QPixmap (TRect& r, const char *pal, const char *pix, int bg);
  virtual void Draw ();
};

#endif
