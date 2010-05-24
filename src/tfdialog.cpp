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
#include <iglu/tfdialog.h>

class CBOnChangeSelect: public TCallBack { public:
  virtual void do_callback (TView *v) {
    TFileDialog *d = (TFileDialog*)v->Owner;
    d->filename->setText (d->filelist->getfilename ());
  }
};

TFileDialog::TFileDialog (const char *title, const char *ext):
  TWindow (Rect (0,0,320,200), title)
{
  TRect a, r;
  getClientArea (a);
//  Align = vaFixedSize;
  r.assign (2,32,a.deltax()-2,a.deltay()-32);
  insert (filelist = new TFileList (r, ext));
  filelist->OnSelectFile = cb1 = new CBOnChangeSelect ();
  filelist->Align = vaLeft+vaRight+vaBottom+vaPreservGapB;

  r.assign (2,4,a.deltax()-2, 24);
  insert (filename = new TInputLine (r, 38));
  filename->Align = vaLeft+vaRight;
  r.assign (0,0,60,25);
  r.moverel (a.deltax()-r.deltax()-16, a.deltay()-r.deltay()-2);
  insert (bCancel = new TTextButton (r, "Cancel", 0));
  r.moverel (-r.deltax()-8, 0);
  insert (bOk = new TTextButton (r, "Ok", 0));

  bCancel->Align = bOk->Align =
    vaFixedSize+vaBottom+vaRight+vaPreservGapR+vaPreservGapB;
}

TFileDialog::~TFileDialog () { delete cb1; }

void TFileDialog::MessageEvent (TEvent& e)
{
  TWindow::MessageEvent (e);
  if (!e.msg.message) {
    if (e.msg.sender==bOk)
      isok=1;
    else if (e.msg.sender==bCancel)
      isok=0;
    else
      return;
    SetState (stModal, 0);
  }
}
