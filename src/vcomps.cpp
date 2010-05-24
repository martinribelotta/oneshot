#include <iglu/tprogram.h>
#include <iglu/twindow.h>
#include <iglu/tinput.h>
#include <vcomps.h>
#include <document.h>
#include <qnode.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern QDocument *doc;

class QCompAND: public QComponent {
public:
	QCompAND(): QComponent() { setName( "AND" ); }
	QCompAND( QPoint p ): QComponent( p.x, p.y ) {
		r = QRect( p, p+QPoint(48, 48) );
		setName( "AND" );
		insertPin( new QPin( p.x, p.y+16, pinIn, "A" ) );
		insertPin( new QPin( p.x, p.y+32, pinIn, "B" ) );
		insertPin( new QPin( r.b.x, p.y+24, pinOut, "Q" ) );
	}
	virtual void sim () {
		QNode *a, *b, *q;
		int oldq;
		a = getPin("A")->indicen;
		b = getPin("B")->indicen;
		q = getPin("Q")->indicen;
		oldq = q->state;
		q->state = a->state && b->state;
		if (oldq!=q->state)
			doc->modified = true;
	}
};

class QCompOR: public QCompAND { public:
	QCompOR(): QCompAND() { setName( "OR" ); }
	QCompOR( QPoint p ): QCompAND( p ) { setName( "OR" ); }
	virtual void sim () {
		QNode *a, *b, *q;
		int oldq;
		a = getPin("A")->indicen;
		b = getPin("B")->indicen;
		q = getPin("Q")->indicen;
		oldq = q->state;
		q->state = a->state || b->state;
		if (oldq!=q->state)
			doc->modified = true;
	}
};

class QCompXOR: public QComponent { public:
	QCompXOR(): QComponent() { setName( "XOR" ); }
	QCompXOR( QPoint p ): QComponent( p.x, p.y ) {
		r = QRect( p, p+QPoint(48, 48) );
		setName( "XOR" );
		insertPin( new QPin( p.x, p.y+16, pinIn, "A" ) );
		insertPin( new QPin( p.x, p.y+32, pinIn, "B" ) );
		insertPin( new QPin( r.b.x, p.y+24, pinOut, "Q" ) );
	}
	virtual void sim() {
		QNode *a, *b, *q;
		a = getPin("A")->indicen;
		b = getPin("B")->indicen;
		q = getPin("Q")->indicen;
		int oldq = q->state;
		// Funcion XOR segun el pirata morgan...
		q->state=(a->state && !b->state) || (!a->state && b->state);
		if (q->state!=oldq)
			doc->modified = true;
	}
};

class QCompNOT: public QComponent { public:
	QCompNOT(): QComponent() { setName( "NOT" ); }
	QCompNOT( QPoint p ): QComponent( p.x, p.y ) {
		r = QRect( p.x, p.y, p.x+48, p.y+24 );
		setName( "NOT" );
		insertPin( new QPin( p.x, p.y+12, pinIn, "I" ) );
		insertPin( new QPin( r.b.x, p.y+12, pinOut, "Q" ) );
	}
	virtual void sim() {
		QNode *i, *q;
		i = getPin("I")->indicen;
		q = getPin("Q")->indicen;
		int oldq = q->state;
		q->state = !i->state;
		if (q->state!=oldq)
			doc->modified = true;
	}

};

class QCompCount: public QComponent {
	unsigned char count;
	int oldClk;
public:
	QCompCount(): QComponent(), count(0), oldClk(0)
		{ setName( "Count" ); }
	QCompCount( QPoint p ): QComponent( p.x, p.y ) {
		count = 0;
		oldClk = 0;
		r = QRect( p, p+QPoint( 48, 16*9 ) );
		setName( "Count" );
		insertPin( new QPin( r.b.x, p.y+16*1, pinOut, "Q0" ) );
		insertPin( new QPin( r.b.x, p.y+16*2, pinOut, "Q1" ) );
		insertPin( new QPin( r.b.x, p.y+16*3, pinOut, "Q2" ) );
		insertPin( new QPin( r.b.x, p.y+16*4, pinOut, "Q3" ) );
		insertPin( new QPin( r.b.x, p.y+16*5, pinOut, "Q4" ) );
		insertPin( new QPin( r.b.x, p.y+16*6, pinOut, "Q5" ) );
		insertPin( new QPin( r.b.x, p.y+16*7, pinOut, "Q6" ) );
		insertPin( new QPin( r.b.x, p.y+16*8, pinOut, "Q7" ) );

		insertPin( new QPin( p.x, p.y+16, pinIn, "CLK" ) );
		insertPin( new QPin( p.x, p.y+32, pinIn, "RST" ) );
	}
	virtual void sim() {
		QNode *q[8], *clk, *rst;
		int i;
		q[0] = getPin("Q0")->indicen;
		q[1] = getPin("Q1")->indicen;
		q[2] = getPin("Q2")->indicen;
		q[3] = getPin("Q3")->indicen;
		q[4] = getPin("Q4")->indicen;
		q[5] = getPin("Q5")->indicen;
		q[6] = getPin("Q6")->indicen;
		q[7] = getPin("Q7")->indicen;
		clk = getPin("CLK")->indicen;
		rst = getPin("RST")->indicen;
		if ( !oldClk && clk->state ) { // Flanco ascendente
		   count++;
		   doc->modified = true;
		}
		if ( rst->state && count>0 ) { // En reset
		   count = 0;
		   doc->modified = true;
		}
		if ( doc->modified ) {
		  q[0]->state = (count&(1<<0))? 1:0;
		  q[1]->state = (count&(1<<1))? 1:0;
		  q[2]->state = (count&(1<<2))? 1:0;
		  q[3]->state = (count&(1<<3))? 1:0;
		  q[4]->state = (count&(1<<4))? 1:0;
		  q[5]->state = (count&(1<<5))? 1:0;
		  q[6]->state = (count&(1<<6))? 1:0;
		  q[7]->state = (count&(1<<7))? 1:0;
		}
		oldClk = clk->state;
	}
};

class QCompOscDialog: public TWindow {
public:
	bool isOk;
	TInputLine *input;

	QCompOscDialog( QRect& r, int mt ):
	  TWindow(r, "Numero de ticks (0-9)")
	{
	  getClientArea( r );
	  r.Grow( 8, 8 );
	  r.b.y = r.a.y+Ht*2;
	  insert( input = new TInputLine( r, 2 ) );
	  input->text[0] = mt+'0';
	  input->text[1] = 0;
	  input->len = 1;
	  input->Align = vaPropW;
	  getClientArea( r );
	  r.a.x = r.b.x - 80;
	  r.a.y = r.b.y - 20;
	  r.moverel( -12, -4 );
	  TTextButton *b;
	  insert( b = new TTextButton( r, "Aceptar", cmOk ) );
	  b->Align =
	    vaFixedSize+vaPreservGapR+vaPreservGapB+vaRight+vaBottom;
	}
	virtual void MessageEvent( TEvent& e ) {
	  if ( e.msg.message == cmOk )
	    { isOk = true;  SetState( stModal, 0 ); }
	  else if ( e.msg.message == cmCancel )
	    { isOk = false;  SetState( stModal, 0 ); }
	  else
	    TWindow::MessageEvent( e );
	}
};

class QCompOsc: public QComponent {
	int ticks, maxTicks;
public:
	QCompOsc(): QComponent(), ticks(0) { setName("OSC *Tk"); }
	QCompOsc( QPoint p ): QComponent( p.x, p.y ) {
		r = QRect( p, p+QPoint( 64, 48 ) );
		setName("OSC *Tk");
		insertPin( new QPin( r.b.x, p.y+24, pinOut, "OUT" ) );
		ticks = 0;
		maxTicks = 3;
		name[4] = maxTicks+'0';
	}
	virtual void simTick () {
		QNode *q = getPin("OUT")->indicen;
		if ( ++ticks > maxTicks ) {
			ticks = 0;
			q->state = !q->state;
			doc->modified = true;
		}
	}
	virtual bool doDialog() {
	  QRect r( 0, 0, 220, 100 );
	  r.centeron( Application->Bounds, 1 );
	  QCompOscDialog d( r, maxTicks );
	  d.Draw();
	  Application->ExecView( &d );
	  if ( d.isOk ) {
	    maxTicks = atoi( d.input->text );
	    name[4] = maxTicks+'0';
	    return true;
	  }
	  return QComponent::doDialog();
	}
	virtual bool extraSave( FILE *f ) {
	  fprintf( f, "%d\n", maxTicks );
	  return true;
	}
	virtual bool extraLoad( FILE *f ) {
	  if ( fscanf( f, "%d", &maxTicks ) != 1 )
	    return false;
	  name[4] = '0'+maxTicks;
	  return true;
	}
};

class QCompReg: public QComponent {
	int oldClk;
public:
	QCompReg(): QComponent() { setName( "REG" ); }
	QCompReg( QPoint p ): QComponent( p.x, p.y ) {
	  r = QRect( p, p+QPoint( 48, 16*10 ) );
	  setName( "REG" );

	  insertPin( new QPin( p.x, p.y+16*9, pinIn, "CLK" ) );

	  insertPin( new QPin( p.x, p.y+16*1, pinIn, "I0" ) );
	  insertPin( new QPin( p.x, p.y+16*2, pinIn, "I1" ) );
	  insertPin( new QPin( p.x, p.y+16*3, pinIn, "I2" ) );
	  insertPin( new QPin( p.x, p.y+16*4, pinIn, "I3" ) );
	  insertPin( new QPin( p.x, p.y+16*5, pinIn, "I4" ) );
	  insertPin( new QPin( p.x, p.y+16*6, pinIn, "I5" ) );
	  insertPin( new QPin( p.x, p.y+16*7, pinIn, "I6" ) );
	  insertPin( new QPin( p.x, p.y+16*8, pinIn, "I7" ) );

	  insertPin( new QPin( r.b.x, p.y+16*1, pinOut, "Q0" ) );
	  insertPin( new QPin( r.b.x, p.y+16*2, pinOut, "Q1" ) );
	  insertPin( new QPin( r.b.x, p.y+16*3, pinOut, "Q2" ) );
	  insertPin( new QPin( r.b.x, p.y+16*4, pinOut, "Q3" ) );
	  insertPin( new QPin( r.b.x, p.y+16*5, pinOut, "Q4" ) );
	  insertPin( new QPin( r.b.x, p.y+16*6, pinOut, "Q5" ) );
	  insertPin( new QPin( r.b.x, p.y+16*7, pinOut, "Q6" ) );
	  insertPin( new QPin( r.b.x, p.y+16*8, pinOut, "Q7" ) );
	}
	virtual void sim();
};

void QCompReg::sim() {
  QNode *clk = getPin("CLK")->indicen;
  if ( !oldClk && clk->state ) {
    int n;  char bi[3] = { 'I', 0, 0 }, bo[3] = { 'Q', 0, 0 };
    for ( n=0; n<8; n++ ) {
      bi[1] = '0'+n;
      bo[1] = '0'+n;
      getPin( bo )->indicen->state = getPin( bi )->indicen->state;
    }
    doc->modified = true;
  }
  oldClk = clk->state;
}

class QFlipFlopRS: public QComponent {
public:
	QFlipFlopRS(): QComponent() { setName( "FF-RS" ); }
	QFlipFlopRS( QPoint p ): QComponent( p.x, p.y ) {
	  r = QRect( p, p+QPoint( 48, 48 ) );
	  setName( "FF-RS" );

	  insertPin( new QPin( r.b.x, p.y+16, pinOut, "Q" ) );
	  insertPin( new QPin( r.b.x, p.y+32, pinOut, "!Q" ) );

	  insertPin( new QPin( p.x, p.y+16, pinIn, "SET" ) );
	  insertPin( new QPin( p.x, p.y+32, pinIn, "RESET" ) );
	}
	virtual void sim() {
	  QNode *r, *s, *q, *_q;
	  r = getPin( "RESET" )->indicen;
	  s = getPin( "SET" )->indicen;
	  q = getPin( "Q" )->indicen;
	  _q = getPin( "!Q" )->indicen;
	  //	R	S	Q	!Q
	  //	0	0	prev	!prev
	  //	1	0	0	1
	  //    0       1       1	0
	  //	1	1	????	!???!!!$%"$ú$&/(#@# piiii...
	  if ( r->state )
	    { _q->state = ! (q->state = 0);  doc->modified = true; }
	  if ( s->state )
	    { _q->state = ! (q->state = 1);  doc->modified = true; }
	}
};

class QFlipFlopD: public QComponent {
public:
	QFlipFlopD(): QComponent() { setName( "FF-D" ); }
	QFlipFlopD( QPoint p ): QComponent( p.x, p.y ) {
	  r = QRect( p, p+QPoint( 48, 48 ) );
	  setName( "FF-D" );

	  insertPin( new QPin( p.x, p.y+16, pinIn, "D" ) );
	  insertPin( new QPin( p.x, p.y+32, pinIn, "CLK" ) );
	  insertPin( new QPin( r.b.x, p.y+16, pinOut, "Q" ) );
	}
	virtual void sim() {
	  QNode *clk, *d, *q;
	  clk = getPin( "CLK" )->indicen;
	  d = getPin( "D" )->indicen;
	  q = getPin( "Q" )->indicen;
	  if ( clk->state )
	    { q->state = d->state;  doc->modified = true; }
	}
};

QComponent *createComponent( int x, int y, int index, int forLoad )
{
	QPoint p( x, y );
	if ( forLoad )
	  switch (index) {
		case 0: return new QCompAND();
		case 1: return new QCompOR();
		case 2: return new QCompXOR();
		case 3: return new QCompNOT();
		case 4: return new QCompCount();
		case 5: return new QCompOsc();
		case 6: return new QCompReg();
		case 7: return new QFlipFlopRS();
		case 8: return new QFlipFlopD();
		default: return NULL;
	  }

	else
	  switch (index) {
		case 0: return new QCompAND( p );
		case 1: return new QCompOR( p );
		case 2: return new QCompXOR( p );
		case 3: return new QCompNOT( p );
		case 4: return new QCompCount( p );
		case 5: return new QCompOsc( p );
		case 6: return new QCompReg( p );
		case 7: return new QFlipFlopRS( p );
		case 8: return new QFlipFlopD( p );
		default: return NULL;
	  }
}

char *compList [] = {
  "AND Gate",
  "OR Gate",
  "XOR Gate",
  "NOT Gate",
  "Contador",
  "Oscilador",
  "Registro",
  "FF RS",
  "FF D",
  NULL
};

char *nameList[] = {
 "AND"      ,
 "OR"       ,
 "XOR"      ,
 "NOT"      ,
 "Count"    ,
 "OSC *Tk"  ,
 "REG"      ,
 "FF-RS"    ,
 "FF-D"     ,
 NULL
};

QComponent *createComponentByName( const char *C_name )
{
  int i=0;
  char t=0;
  char *name = new char[strlen(C_name+1)];
  strcpy(name, C_name);
  if ( strncmp( name, "OSC ", 4 ) == 0 )
    { t=name[4]; name[4] = '*'; }
  while ( nameList[i] )
    if ( strcmp( nameList[i], name ) == 0 )
      break;
    else
      i++;
  if ( t!=0 )
    name[4] = t;
  delete name;
  return createComponent( 0, 0, i, 1 );
}
