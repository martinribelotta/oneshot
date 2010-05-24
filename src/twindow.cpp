/*
 * IGLU Iterfaz Grafica Libre del Usuario. (libre de usuarios) (Graphics user interface "free of users")
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
#include <iglu/twindow.h>
#include <iglu/screen.h>
#include <iglu/tshape.h>
#include <iglu/mousehdl.h>

#define DragColor EGA_WHITE

extern char resize_pal[];
extern char* resize_icon;

void do_resize_move (TGroup *Owner, TEvent& e, int resize_move) {
      TRect g, r(Owner->Bounds);
      int dx, dy, changed=0;
      if (resize_move)
	dx = r.b.x-e.pos.x,   dy = r.b.y-e.pos.y;
      else
	dx = e.pos.x-r.a.x,   dy = e.pos.y-r.a.y;
      gui_getclip(g);
      if (Owner->Owner)
	gui_setclip(Owner->Owner->Bounds);
      gui_wmode(XOR_PUT);
      gui_drawrect(r, DragColor);
      do {
	e.GetEvent();
	if (e.type&evMouseMove) {
	  TPoint pos(e.pos);
	  MouseHide ();
	  gui_drawrect(r, DragColor);
	  if (resize_move)
	    r.b = TPoint (pos.x+dx, pos.y+dy);
	  else
	    r.move(pos.x-dx, pos.y-dy);
	  gui_drawrect(r, DragColor);
	  MouseShow ();
	  changed=1;
	}
      } while (!(e.type&evMouseUp));
      MouseHide ();
      gui_drawrect(r, DragColor);
      gui_wmode(COPY_PUT);
      if (changed) {
	((TWindow*)Owner)->Hide();
	if (resize_move)
	  Owner->resize (
	    e.pos.x+dx-Owner->Bounds.a.x, e.pos.y+dy-Owner->Bounds.a.y);
	else
	  Owner->move(e.pos.x-dx, e.pos.y-dy);
	((TWindow*)Owner)->Show();
      }
      gui_setclip(g);
      MouseShow ();
}

/*************************************************************/

class TTitleBar: public TView {
  TCharButton *x;
  char **title;
public:
  TTitleBar (TRect& r, char **s): TView(r), title(s) {
    r.a.x = r.b.x-WinTitleH;
    r.Grow( 1, 1 );
    x = new TCharButton( r, 'X', cmCancel );
    x->State &=~stFocusheable;
    State &=~stFocusheable;
  }
  virtual void moverel( int dx, int dy ) {
    TView::moverel( dx, dy );
    x->moverel( dx, dy );
  }
  virtual void RecuestAlign( TRect& a, TRect& b ) {
    TView::RecuestAlign( a, b );
    TRect r( Bounds );
    r.a.x = r.b.x-WinTitleH;
    r.Grow( 1, 1 );
    x->Bounds = r;
  }
  virtual void Draw() {
    int titlecolor = EGA_BLUE, textcolor = EGA_WHITE;
    TRect r(Bounds);
    if (!(Owner->State&stFocus))
      (titlecolor=EGA_LIGHTGRAY, textcolor=EGA_BLACK);
    TShape tb(r, shpDownBox, 1);
    tb.bg = titlecolor;
    tb.doDraw();
    gui_outtextxy(tb.Bounds.a.x+tb.Bounds.deltax()/2,
      tb.Bounds.a.y+tb.Bounds.deltay()/2, *title, 1, textcolor, -1);
    x->Draw();
  }
  virtual void HandleEvent(TEvent&e) {
    TView::HandleEvent (e);
    x->HandleEvent( e );
    if (!(Owner->State&stNoMoveable))
      if ((e.type&evMouseDown) && Bounds.contain(e.pos))
	do_resize_move (Owner, e, 0);
  }
};

/**********************************************************************/

class TResizeArea: public TView {
public:
  TResizeArea (TRect& r): TView(r) { State &=~stFocusheable; }
  virtual void HandleEvent(TEvent&e) {
//    TView::HandleEvent (e);
    if ((Owner->Align&vaFixedSize)==vaFixedSize)
      return;
    if ((e.type&evMouseDown) && Bounds.contain(e.pos))
      do_resize_move (Owner, e, 1);
  }
  virtual void Draw () {
    if ((Owner->Align&vaFixedSize)==vaFixedSize)
      return;
    gui_drawpixmap (Bounds.a.x, Bounds.a.y, 10, 10, resize_icon, resize_pal);
  }
};

/**********************************************************************/

TWindow::TWindow (TRect& r, char *s):
  TContainer(r, shpUpBox), title(s), menu(NULL)
{
  TRect rb (0,0, WinTitleH, WinTitleH);
  getClientArea(r);
  rb.moverel(r.deltax()-rb.deltax(), -rb.deltay()-1);

  TRect r1 (0, 0, r.deltax(),WinTitleH);
  r1.moverel( 0, -WinTitleH-1 );
  insert(titleBar = new TTitleBar(r1, &title));
  titleBar->Align = vaRight+vaLeft+vaPreservH;
  titleBar->State = stAbsoluteClipped;

  r1 = TRect (0,0,10,10);
  r1.moverel (r.deltax()-r1.deltay(),
	      r.deltay()-r1.deltay());
  resizearea = new TResizeArea(r1);
  insert(resizearea);
  resizearea->Align = vaBottom+vaRight+vaFixedSize;

  SetState(stVisible+stExpose, 1);

  minimumSize = TPoint(
    (WinTitleH+WinBorder)*2+gui_textw( title ), (WinTitleH+WinBorder)*2 );
}

void TWindow::GotFocus()
{
  if (State&stFocus) return;
  TContainer::GotFocus();
  if (next)
    Show();
  else
    DrawDecorate();
}

void TWindow::LostFocus()
{
  if (State&stFocus) {
    TContainer::LostFocus();
    DrawDecorate();
  }
}

void TWindow::Hide()
{
  SetState(stVisible,0);
  if (Owner)
    Owner->RedrawRect(Bounds);
}

void TWindow::Show()
{
  if (Owner)
    Owner->moveTop(this);
  SetState(stVisible,1);
  doDraw();
}

void TWindow::setMenuWindow (TMenuBar *m)
{
   int h = m->Bounds.deltay();
   getClientArea(m->Bounds);
   m->Bounds.b.y = m->Bounds.a.y + h;
   m->Align = vaLeft+vaTop+vaRight+vaPreservH;
   insert(menu=m);
}

void TWindow::insert (TView *q)
{
  q->moverel(WinBorder, WinBorder+WinTitleH+1);
  TContainer::insert(q);
}

void TWindow::detach (TView *q)
{
  TContainer::detach(q);
  q->moverel(-(WinBorder), -(WinBorder+WinTitleH+1));
}

void TWindow::DrawDecorate()
{
  titleBar->doDraw();
}

void TWindow::Draw()
{
  if (State&stVisible) {
    if ((Align&vaFixedSize)==vaFixedSize)
      resizearea = 0l;
    if (resizearea)
      moveTop(resizearea);
    TContainer::Draw();
//    DrawDecorate();
  }
}

void TWindow::getClientArea (TRect& r, int rel)
{
  r = Bounds;
  r.a.x += WinBorder;//+1;
  r.a.y += WinBorder+WinTitleH+1;
  r.b.x -= WinBorder;//+1;
  r.b.y -= WinBorder;//+1;
  if (rel)
    r.moverel (-r.a.x, -r.a.y);
}

void TWindow::HandleEvent(TEvent& e)
{
  if (State&(stFocus|stVisible)) {
//    xb->HandleEvent(e);
    TContainer::HandleEvent(e);
    if ((State&stModal) && (e.type&evBroadcast) && (e.msg.message==cmCancel))
      SetState(stModal,0);
  }
}

void TWindow::resize( int w, int h )
{
  if ( w<minimumSize.x )
    w=minimumSize.x;
  if ( h<minimumSize.y )
    h=minimumSize.y;
  TContainer::resize( w, h );
}
