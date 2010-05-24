#include <string.h>
#include <iglu/tprogram.h>
#include <iglu/tbutton.h>
#include <iglu/tcanvas.h>
#include <iglu/twindow.h>
#include <iglu/tfdialog.h>
#include <iglu/msgbox.h>
#include <iglu/tlabel.h>
#include <iglu/tmenu.h>
#include <iglu/qpixmap.h>
#include <about.h>
#include <document.h>
#include <vcomps.h>
#include <qnode.h>

TScrollCanvas *canvas;
QDocument *doc;
TListBox *complist;

class QLed;
class QVisualBinding;

class TMyApp: public TProgram {
  QLed *led;
  QVisualBinding *visualBinding;
  TWindow * mainWindow;
  TMenuBar *mainMenu;
public:
  TMyApp(int argc, char **argv);
  ~TMyApp()
    { delete doc; }
  virtual void HandleEvent(TEvent& e);

  void do_draw_nodes();
  void do_draw_comps();
};

#define stateDraggin 1
#define stateConnect 2

QComponent *currc=NULL, *selectc=NULL;
QNode *currn=NULL;
QNodePoint *currp=NULL;
QPoint posold(1200,1200), posori(1200,1200), delta(24,24), size(48,48);
bool simOn = false;
int state = 0;

#define bDrawNodes    1   // 01
#define bDrawComps    2   // 10
#define bDrawAll      3   // 11

class QVisualBinding: public TView {
public:
	int dflags;

	QVisualBinding(): TView( Rect( 0,0,1200,1200 ) )
	  { dflags=bDrawAll; }
	virtual void Draw ();
	virtual void moverel(int dx, int dy);
	virtual void MouseEvent( TEvent& e );

	void do_draw_flags( int f) {
	  int t=dflags;
	  dflags = f;
	  doDraw();
	  dflags = t;
	}
};

void draw_icon  (TPoint p) {
  TRect r (p.x, p.y, p.x+size.x, p.y+size.y);
  r.moverel (-delta.x, -delta.y);
  gui_drawrect (r, EGA_WHITE);
}

void QVisualBinding::Draw()
{
      if ( dflags&bDrawNodes ) {
	QNode *n;
	for (n=doc->nodes; n; n=n->next)
		n->draw();
      }
      if ( dflags&bDrawComps ) {
	QComponent *c;
	for (c=doc->comps; c; c=c->next) {
	  c->draw();
	  if (c==selectc) // Dibujar seleccion
	    gui_drawrect( c->r, EGA_RED );
	}
      }
}

void QVisualBinding::moverel( int dx, int dy )
{
	TView::moverel( dx, dy );
	QNode *n;	QNodePoint *p;
	for (n=doc->nodes; n; n=n->next)
		for (p=n->points; p; p=p->next)
			p->moverel(QPoint(dx, dy));
	QComponent *c;
	for (c=doc->comps; c; c=c->next)
		c->moverel(dx, dy);
}

extern void draw_line (int cl, int xo, int yo, int x, int y);

void QVisualBinding::MouseEvent( TEvent& e )
{
	if (e.type&evMouseDown) {
	  currc=doc->inComponent( e.pos.x, e.pos.y );
	  if (e.btn==1) {
	    if (currc) {
	      state=stateDraggin;
	      gui_wmode( XOR_PUT );
	      posold = e.pos;
	      size = QPoint(currc->r.deltax(), currc->r.deltay());
	      delta = QPoint( e.pos.x-currc->r.a.x, e.pos.y-currc->r.a.y );
	      draw_icon( posold );
	    } else if (doc->inNode( e.pos.x, e.pos.y, &currn, &currp))
	      if (!simOn) {
		state=stateConnect;
		gui_wmode( XOR_PUT );
		posold = posori = currp->pos();
	      } else {
		currn->state = !currn->state;
		do_draw_flags( bDrawNodes );
	      }
	  }
	}
	//////////////////////////////////////////////////////////////////
	if (e.type&evMouseMove) {
	  if (state==stateDraggin) {
	    draw_icon( posold );
	    draw_icon( posold=e.pos );
	  } else if (state==stateConnect) {
	    draw_line( EGA_WHITE, posori.x, posori.y, posold.x, posold.y);
	    posold = e.pos;
	    draw_line( EGA_WHITE, posori.x, posori.y, posold.x, posold.y);
	  }
	}
	//////////////////////////////////////////////////////////////////
	if (e.type&evMouseUp) {
	  if (state==stateDraggin) {
	    draw_icon( posold );
	    gui_wmode( COPY_PUT );
	    state=0;
	    if (currc) // cuando se mueve un componente
	      currc->moveto(
		posold.x-currc->r.a.x-delta.x,
		posold.y-currc->r.a.y-delta.y);
	    else if (canvas->Bounds.contain(e.pos))
		// Cuando se coloca uno nuevo...
		doc->addComponent(
			createComponent(
				posold.x-delta.x, posold.y-delta.y,
				complist->pos
			)
		);
	    currc=NULL;
	    canvas->doDraw();
	  } else if (state==stateConnect) {
	    draw_line( EGA_WHITE, posori.x, posori.y, posold.x, posold.y);
	    state = 0;
	    gui_wmode( COPY_PUT );
	    if (currn && currp) {
	      QNode *n;
	      QNodePoint *p;
	      if (doc->inNode(posold.x, posold.y, &n, &p) && (n!=currn)) {
		doc->joinNodes( currn, n );
		currn->addPoint(new QNodeNiple(currp, p));
	      } else
		currn->addPoint(new QNodePoint(posold, currp));
	    }
	    currn = NULL;
	    currp = NULL;
	    canvas->doDraw();
	  } else
	     if (e.btn==2) {
		QComponent *c=doc->inComponent( e.pos.x, e.pos.y );
		if (c!=selectc) {
			selectc=c;
			do_draw_flags( bDrawComps );
		}
	  }
	}
}

class QLed: public TView {
public:
	bool ison;

	QLed(QPoint pos):
		TView(QRect(pos, pos+QPoint(20,20))), ison(false) { }
	virtual void HandleEvent(TEvent& ) { }
	virtual void Draw () {
	  gui_drawfillelipse(
		Bounds.a.x, Bounds.a.y, Bounds.b.x, Bounds.b.y,
		(ison)? EGA_LIGHTGREEN:EGA_BLACK);
	  gui_drawelipse( Bounds.a.x, Bounds.a.y, Bounds.b.x, Bounds.b.y,
		EGA_BLACK );
	}
	inline void On () { ison=true; doDraw(); }
	inline void Off () { ison=false; doDraw(); }
	inline void Toggle () { ison=(bool)!ison; doDraw(); }
};

enum {
   cmNuevo = 1000,
   cmAbrir,
   cmGuardar,
   cmSalir,
   cmCortar,
   cmCopiar,
   cmPegar,
   cmBorrar,
   cmPropiedades,
   cmSimOn,
   cmSimOff,
   cmAcerca_de
};

void onSelectComp (TPoint& po, TListBox *sender) {
  sender->SetState (stSelect, 0);
  canvas->SetState (stFocus, 1);
  gui_wmode( XOR_PUT );
  state=stateDraggin;
  currn = NULL;
  delta = QPoint( 24, 24 );
  size = QPoint( 48, 48 );
  draw_icon( posold = po );
}

TMyApp::TMyApp(int argc, char **argv): TProgram(argc, argv, EGA_CYAN)
{
  int i, _MaxX, _MaxY;
  TRect r ( Bounds );
  r.Grow( 10, 10 );
  doc = new QDocument();
  mainWindow = new TWindow( r,
	"One-Shot: Digital circuit simulator" );
//  mainWindow->State |= stNoMoveable;
//  mainWindow->Align |= vaFixedSize;
  insert( mainWindow );
  mainWindow->GotFocus();

  mainWindow->getClientArea( r );
  _MaxX = r.deltax();
  _MaxY = r.deltay();
  r.b.y = r.a.y + Ht*2;

  mainMenu = new TMenuBar (r,
    new TSubMenu("File",
      new TMenuItem("New",  cmNuevo,
      new TMenuItem("Open",  cmAbrir,
      new TMenuItem("Save", cmGuardar,
      new TMenuItem(mnuSeparatorLine, 0,
      new TMenuItem("Quit", cmSalir,
      NULL))))),
    new TSubMenu("Edit",
      new TMenuItem("Properties", cmPropiedades,
      new TMenuItem(mnuSeparatorLine, 0,
      new TMenuItem("Delete", cmBorrar,
      NULL))),
    new TSubMenu("Simulate",
      new TMenuItem("Start", cmSimOn,
      new TMenuItem("Stop", cmSimOff,
    NULL)),
    new TSubMenu("Help",
      new TMenuItem("About...", cmAcerca_de, NULL),
    NULL))))
  );

  mainWindow->insert( led = new QLed( QPoint( _MaxX-32, r.b.y+1 ) ) );
  led->Align = vaFixedSize+vaRight;

  r = TRect (2, mainMenu->Bounds.b.y, 3*_MaxX/4, _MaxY-12);
  mainWindow->insert (canvas = new TScrollCanvas (r, 1200, 1200));
  canvas->Align = vaClient+vaPropW+vaPropH;
  canvas->shpbg = EGA_BLACK;
  canvas->insert( visualBinding = new QVisualBinding() );

  r = TRect (r.b.x+2, r.a.y+24, _MaxX-2, r.b.y);
  mainWindow->insert (complist = new TListBox (r));
  complist->Align = vaPreservW+vaRight+vaTop+vaBottom+vaPropW+vaPropH;
  complist->height_item = 32;

  extern char *compList[];
  for (i=0; compList[i]; i++)
    complist->additem( compList[i] );
  complist->onSelect = onSelectComp;

  mainWindow->setMenuWindow( mainMenu );
}

void TMyApp::do_draw_nodes()
{
  visualBinding->do_draw_flags( bDrawNodes );
}

void TMyApp::do_draw_comps()
{
  visualBinding->do_draw_flags( bDrawComps );
}

void TMyApp::HandleEvent(TEvent& e)
{
  TProgram::HandleEvent(e);
  if (e.type&evMessage) {
    TMessage m(e.msg);
    switch (m.message) {
       case cmNuevo:
	 doc->newDoc();
	 canvas->doDraw();
       break;
       case cmAbrir: {
	 TFileDialog *d = new TFileDialog ("Open file", ".ggg");
	 TRect r (d->Bounds);
	 r.centeron (Application->Bounds);
	 d->move (r.a.x, r.a.y);
	 d->doDraw();
	 ExecView (d);
	 if (d->isok) {
	   char s1[256];
	   sprintf( s1, "%s", d->filelist->getabsolute() );
	   if ( !doc->load( s1 ) ) {
	     doc->newDoc();
	     canvas->doDraw();
	     MessageBox( "Error reading file %s",
	       d->filename->text );
	   } else {
	     canvas->moveall( canvas->Bounds.a.x, canvas->Bounds.a.y );
	     canvas->doDraw();
	   }
	 }
	 delete d;
	 mainWindow->GotFocus();
       } break;
       case cmGuardar: {
	 TFileDialog *d = new TFileDialog ("Save file", ".ggg");
	 TRect r (d->Bounds);
	 r.centeron (Application->Bounds);
	 d->move (r.a.x, r.a.y);
	 d->doDraw();
	 ExecView (d);
	 if (d->isok) {
	   canvas->moveall( -canvas->Bounds.a.x, -canvas->Bounds.a.y );
	   if ( !doc->save( d->filename->text ) )
	     MessageBox( "Can not save file %s\n",
	       d->filename->text);
	   canvas->moveall( canvas->Bounds.a.x, canvas->Bounds.a.y );
	 }
	 delete d;
	 mainWindow->GotFocus();
       } break;
       case cmSalir:
	 SetState( stModal, 0 ); break;
       case cmBorrar:
	 if (selectc) {
	   doc->delComponent( selectc );
	   doc->purgeNodes();
	   canvas->doDraw();
	   selectc = NULL;
	 }
       break;
       case cmPropiedades:
	 if (selectc) {
	   if (selectc->doDialog())
	     do_draw_comps();
	   mainWindow->GotFocus();
	 }
       break;
       case cmSimOn:
	 simOn = true;
	 led->On();
	 do_draw_nodes();
       break;
       case cmSimOff:
	 simOn = false;
	 led->Off();
	 do_draw_nodes();
       break;
       case cmAcerca_de: {
	 TWindow *w = new AboutOneSHOT();
	 w->Show();
	 ExecView (w);
	 delete w;
	 mainWindow->GotFocus();
       } break;
    }
  }
  if (simOn) {
    QComponent *c;
    for (c=doc->comps; c; c=c->next)
	c->sim();
    if (e.type&evTimerOut)
      for (c=doc->comps; c; c=c->next)
	c->simTick();
    if (doc->modified) {
      do_draw_nodes();
      doc->modified = false;
    }
  }
}

int main (int argc, char **argv)
{
  TMyApp *MyApp = new TMyApp(argc, argv);
  MyApp->mainLoop();
  delete MyApp;
  return 0;
}
