#include <qnode.h>
#include <iglu/screen.h>
#include <string.h>
#include <errno.h>

QNode::QNode(): state(0), points(NULL), next(NULL), prev(NULL), id(-1)
{
	head = NULL;
}

QNode::QNode( int x, int y ): state(0), points(NULL), head(NULL)
{
	next=prev=NULL;
	addPoint( new QNodePoint( QPoint( x, y ) ) );
}

QNode::~QNode()
{
	while (points) {
		QNodePoint *p = points;
		points=points->next;
		delete p;
	}
}

inline int dist (int x) { return ((x<0)? -x:x); }
inline int Max (int a, int b) { return (a>b)? a:b; }
inline int Min (int a, int b) { return (a<b)? a:b; }

void draw_line (int cl, int xo, int yo, int x, int y)
{
	int dx, dy;
	dx = dist (xo-x);
	dy = dist (yo-y);
	if ((dx == 0) || (dy == 0))
		gui_drawline (xo, yo, x, y, cl);
	else if (dy>dx) {
		int cy = Min (yo, y) + dy/2;
		gui_drawline (xo, yo, xo, cy, cl);
		gui_drawline (xo, cy, x, cy, cl);
		gui_drawline (x, cy, x, y, cl);
	} else {
		int cx = Min(xo, x) + dx/2;
		gui_drawline (xo, yo, cx, yo, cl);
		gui_drawline (cx, yo, cx, y, cl);
		gui_drawline (cx, y, x, y, cl);
	}

}

void QNode::draw()
{
    int x, y, xo, yo;
    QNodePoint *pu = points;
    while (pu) {
	xo = x = pu->pos().x;
	yo = y = pu->pos().y;
	if (pu->back) {
		xo = pu->back->pos().x;
		yo = pu->back->pos().y;
	}
	int color = EGA_GREEN;
	extern bool simOn;
	if (simOn)
	  color = state? EGA_LIGHTRED:EGA_BLUE;
	draw_line (color, xo, yo, x, y);
	QRect rt( pu->rect() );
	gui_drawrect (rt, color);//EGA_CYAN);
	pu = pu->next;
    };
}

void QNode::addPoint( QNodePoint *p )
{
	if ( !points && !head )
	  points = head = p;
	else {
	  head->next = p;
	  p->prev = head;
	  head = p;
	}
}

void QNode::detachPoint( QNodePoint *p )
{
	if (p->prev)
		p->prev->next = p->next;
	if (p->next)
		p->next->prev = p->prev;
	if (p==points)
		points=points->next;
	p->next=p->prev=NULL;
}

void QNode::delPoint( QNodePoint *p )
{
	detachPoint( p );
	QNodePoint *x=points;
	while (x) {
	  if (x->back == p)
	    x->back = NULL;
	  if (x->isniple) {
	    QNodeNiple *t = (QNodeNiple*)x;
	    if (t->yo == p) {
	      x=x->next;
	      delPoint (t);
	      delete t;
	      continue;
	    }
	  }
	  x=x->next;
	}
}

void QNode::join( QNode* n )
{
	while (n->points) {
		QNodePoint *p = n->points;
		n->detachPoint(p);
		this->addPoint(p);
	}
}

QNodePoint *QNode::inPoint( int x, int y )
{
	QNodePoint *p;
	for (p=points; p; p=p->next)
		if (p->inPoint( QPoint( x, y ) ))
			return p;
	return NULL;
}

QNodePoint *QNode::getPoint( int pid )
{
  QNodePoint *p;
  for (p=points; p; p=p->next)
      if ( p->id == pid )
	return p;
  return NULL;
}

/** Formato del nodo:
node <id>
nipple/point <id> [si point: <x> <y>, si niple <idyo>] <idback>
...
endnode
 */
bool QNode::save( FILE *f )
{
  QNodePoint *p;

  int idp = 0;
  for( p=points; p; p=p->next )
    p->id = idp++;

  fprintf( f, "node %d\n", id );

  for( p=points; p; p=p->next ) {
    if ( p->isniple )
      fprintf( f, "\tniple %d %d ", p->id, ((QNodeNiple*)p)->yo->id );
    else
      fprintf( f, "\tpoint %d %d %d ", p->id, p->pos().x, p->pos().y );
    fprintf( f, "%d\n", (p->back)? p->back->id:-1 );
  }

  fprintf( f, "endnode\n\n" );
  return true;
}

bool QNode::pointPreload( FILE *f )
{
  int i, x, y, b;
  if ( fscanf( f, "%d%d%d%d", &i, &x, &y, &b ) != 4 )
    return false;
  QNodePoint  *np;
  addPoint( np = new QNodePoint( QPoint( x, y ), NULL ) );
  np->id = i;
  return true;
}

bool QNode::niplePreload( FILE *f )
{
  int i, yo, b;
  if ( fscanf( f, "%d%d%d", &i, &yo, &b ) != 3 )
    return false;
  QNodeNiple *n;
  addPoint( n = new QNodeNiple( NULL, NULL ) );
  n->id = i;
  return true;
}

bool QNode::pointLoad( QNodePoint *p, FILE *f )
{
  int i, x, y, back;
  if ( fscanf( f, "%d%d%d%d", &i, &x, &y, &back ) != 4 )
    return false;
  if ( p->id != i )
    return false;
  QNodePoint *pback = getPoint( back );
  if ( !pback && (back!=-1) )
    return false;
  p->back = pback;
  return true;
}

bool QNode::nipleLoad( QNodeNiple *p, FILE *f )
{
  if ( !p->isniple ) return false;
  int i, yo, back;
  if ( fscanf( f, "%d%d%d", &i, &yo, &back ) != 3 )
    return false;
  if ( p->id != i )
    return false;
  QNodePoint *pback = getPoint( back );
  QNodePoint *pyo = getPoint( yo );
  if ( ( !pback && (back!=-1) ) || !pyo )
    return false;
  p->back = pback;
  p->yo = pyo;
  return true;
}

/** El parser llama a esta funcion luego de leer el token "node" */
bool QNode::load( FILE *f )
{
  char b[32];
  if ( fscanf( f, "%d", &id ) != 1 )
    return false;

  long fpos = ftell( f ); // Tomar la posicicon de inicio de los puntos

  while (!feof(f)) {
    if ( fscanf( f, "%s", b ) != 1 )
      return false;
    if ( strcmp( b, "point" ) == 0 ) {  // Es un punto
      if ( !pointPreload( f ) )
	return false;
    } else if ( strcmp( b, "niple" ) == 0 ) { // Es un niple
      if ( !niplePreload( f ) )
	return false;
    } else if (strcmp(b,"endnode")==0) // Terminan las declaraciones
      break;
    else
      return false;
  }

  fseek( f, fpos, SEEK_SET );
  // Releemos las declaraciones de puntos para completar los datos.
  QNodePoint *p = points;
  while (!feof(f)) {
    if ( fscanf( f, "%s", b ) != 1 )
      return false;
    if ( strcmp( b, "point" ) == 0 ) {  // Es un punto
      if ( !pointLoad( p, f ) )
	return false;
    } else if ( strcmp( b, "niple" ) == 0 ) { // Es un niple
      if ( !nipleLoad( (QNodeNiple*)p, f ) )
	return false;
    } else if (strcmp(b,"endnode")==0) // Terminan las declaraciones
      return true;
    else
      return false;
    p = p->next;
  }
  return false; // Por aca se sale cuando hay un EOF sin "endnode"
}
