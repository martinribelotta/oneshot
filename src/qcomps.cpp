#include <string.h>
#include <ctype.h>
#include <iglu/screen.h>
#include <iglu/tshape.h>
#include <qcomp.h>
#include <qnode.h>
#include <document.h>

extern QDocument *doc;

QPin::QPin( int d, QNode *nd, QNodePoint *ndp, const char *s ):
  io(d), indicen(nd), indicem(ndp), _name(strdup(s))
{
}

QPin::QPin( int a, int b, int c, const char *s ):
	io(c), indicen(NULL), indicem(NULL)
{
	_name = strdup( s );
	next=NULL;
	a += (c==pinOut)? pinDelta:-pinDelta;
	indicen = new QNode( a, b );
	doc->addNode( indicen );
	indicem = indicen->points;
}

QPin::~QPin()
{
	delete _name;
	indicen->delPoint( indicem );
	if (indicen->points==NULL)
		doc->delNode(indicen);
}

void QPin::draw()
{
	int x=indicem->pos().x, y=indicem->pos().y, xo;
	xo = x;
	if (io==pinIn) xo+= pinDelta;
	else xo-= pinDelta;
	gui_drawhline( x, y+1, xo, EGA_DARKGRAY );
	gui_drawhline( x, y+0, xo, EGA_WHITE );
	gui_drawhline( x, y-1, xo, EGA_LIGHTGRAY );
	int tx, ty, l=gui_textw( name() );
	ty = y-gui_texth( name() );
	tx = x;
	if (io==pinOut)	tx+=8;
	else tx-=l+8;
	gui_outtextxy( tx, ty, name(), 0, EGA_GREEN, -1);
}

QComponent::QComponent():
  name(NULL), id(0), pins(NULL), next(NULL), prev(NULL)
{
}

QComponent::QComponent( int x, int y ):
  next(NULL), prev(NULL), pins(NULL), name(NULL)
{
	r = QRect(x,y, x+48,y+48);
	setName( "????" );
}

QComponent::~QComponent()
{
  if ( name ) delete name;
  while (pins) {
    QPin *t = pins;
    pins= pins->next;
    delete t;
  }
}

void QComponent::setName( const char *s )
{
  if ( name )
    delete name;
  name = strdup( s );
}

/** Guarda los pines basicos, la geometria y el tipo de componente.
 * Formato de texto plano:
comp "nombre" [x] [y] [w] [h]
...parametros de los derivados... (o nada)
pin "nombre" in/out [idn] [idm]
...
endcomo
 */
bool QComponent::save( FILE *f )
{
  fprintf( f, "comp \"%s\" %d %d %d %d\n",
    name, r.a.x, r.a.y, r.deltax(), r.deltay() );

  if ( !extraSave( f ) )
    return false;

  QPin *p;
  for ( p=pins; p; p=p->next )
    fprintf( f, "\tpin \"%s\" %s %d %d\n",
      p->name(),
      (p->io==pinIn)? "in":"out",
      p->indicen->id,
      p->indicem->id
    );

  fprintf( f, "endcomp\n\n" );
  return true;
}

bool getString( FILE *f, char *b )
{
  int c;
  while (!feof(f) && isspace( c=fgetc( f ) ) )
    ;
  if ( (c!='"') || feof( f ) )
    return false;

  while (!feof( f )) {
    c = fgetc( f );
    if ( c=='"' ) return true;
    *b = c;
    b++;
    *b = 0;
  }
  return false;
}

/** Carga el componente. El parser llama a esta funcion una vez de
 * haver leido el token "comp" y su nombre
 * Formato de texto plano:
comp "nombre" [x] [y] [w] [h]
...parametros de los derivados... (o nada)
pin "nombre" in/out [idn] [idm]
...
endcomo
 */
bool QComponent::load( FILE *f )
{
  if ( fscanf( f, "%d%d%d%d", &r.a.x, &r.a.y, &r.b.x, &r.b.y ) != 4 )
    return false;
  r.b.x += r.a.x;
  r.b.y += r.a.y;

  if ( !extraLoad( f ) )
    return false;

  char b[32];
  while ( !feof( f ) ) {
    char pinName[32];
    int pio, idn, idm;
    bool pointIsNiple;
    if ( fscanf( f, "%s", b ) != 1 )
      return false;
    if ( strcmp( b, "pin" ) == 0 ) {
      if ( !getString( f, pinName ) )
	return false;
      if ( fscanf( f, "%s%d%d", b, &idn, &idm ) != 3 )
	return false;

      if ( strcmp( b, "in" ) == 0 )
	pio = pinIn;
      else if ( strcmp( b, "out" ) == 0 )
	pio = pinOut;
      else
	return false;

      QNode *pn = doc->getNode( idn );
      if ( !pn )
	return false;
      QNodePoint *pm = pn->getPoint( idm );
      if ( !pm )
	return false;
      insertPin( new QPin( pio, pn, pm, pinName ) );
    } else if ( strcmp( b, "endcomp" ) == 0 )
      return true;
    else
      return false;
  }
  return false; // Unexpected EOF
}

void QComponent::do_moverel( int dx, int dy, int movepins )
{
	QPin *p;
	r.moverel( dx, dy );
	if (movepins)
		for (p=pins; p; p=p->next)
			p->indicem->moverel( QPoint( dx, dy ) );
}

void QComponent::draw()
{
	TShape shp (r, shpUpBox, 3, EGA_DARKGRAY);
	shp.Draw ();
	int tx, ty;
	tx = r.a.x+(r.b.x-r.a.x)/2;
	ty = r.a.y+(r.b.y-r.a.y)/2;
	gui_outtextxy( tx, ty, name, 1, EGA_BLUE, -1);
	QPin *p;
	for (p=pins; p; p=p->next)
	   p->draw();
}

void QComponent::insertPin( QPin *p )
{
	p->next = pins;
	pins = p;
}

QPin *QComponent::getPin( char *s )
{
	QPin *p;
	for (p=pins; p; p=p->next)
	   if (strcmp(p->name(),s)==0)
	     return p;
	return NULL;
}
