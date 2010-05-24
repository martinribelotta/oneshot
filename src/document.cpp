#include <document.h>
#include <qcomp.h>
#include <qnode.h>
#include <vcomps.h>
#include <stdio.h>
#include <string.h>

QDocument::QDocument(): fileName(NULL), comps(NULL), nodes(NULL)
{
	modified = false;
}

QDocument::~QDocument()
{
	newDoc();
}

void QDocument::newDoc ()
{
	while (comps)
	  delComponent(comps);
	purgeNodes();
}

bool QDocument::save (char *name)
{
	FILE *f = fopen( name, "wt" );
	if ( f ) {
	  // Numerar componentes y nodos.
	  int idc=0, idn=0, idp;
	  QComponent *c;
	  for (c=comps; c; c=c->next)
	    c->id = idc++;
	  QNode *n;
	  for (n=nodes; n; n=n->next) {
	    n->id = idn++;
	    QNodePoint *ndp;
	    for ( idp=0, ndp = n->points; ndp; ndp=ndp->next, idp++ )
	      if ( !ndp->isniple )
		ndp->id = idp;
	  }

	  // Guardar los nodos.
	  for (n=nodes; n; n=n->next)
	    if ( !n->save( f ) )
	      return false;

	  // Guardar los componentes.
	  for (c=comps; c; c=c->next)
	    if ( !c->save( f ) )
	      return false;

	  fclose( f );
	  return true;
	}
	return false;
}

bool QDocument::load (char *name)
{
	newDoc();
	FILE *f = fopen( name, "rt" );
	if ( f ) {
	  char b[32];
	  while ( !feof( f ) ) {
	    fscanf( f, "%s", b );
	    if ( strcmp( b, "node" ) == 0 ) {
	      QNode *n = new QNode();
	      if ( n->load( f ) )
		addNode( n );
	      else
		{ delete n; return false; }
	    } else if ( strcmp( b, "comp" ) == 0 ) {
	      extern bool getString( FILE *f, char *b );
	      if ( !getString( f, b ) )
		return false;
	      QComponent *c = createComponentByName( b );
	      if ( !c || !c->load( f ) )
		return false;
	      extern QPoint *origin;
	      addComponent( c );
	    } else if ( feof( f ) )
	      break;
	    else
	      return false;
	  }
	  fclose( f );
	  return true;
	}
	return false;
}

void QDocument::addComponent( QComponent *c )
{
	if (c) {
		c->next = comps;
		if (comps)
			comps->prev = c;
		comps = c;
	}
}

void QDocument::addNode( QNode *n )
{
	if (n) {
	  n->next = nodes;
	  if (nodes)
		nodes->prev = n;
	  nodes = n;
	}
}

int QDocument::inNode( int x, int y, QNode **n, QNodePoint **p )
{
	QNode *nd;
	for (nd=nodes; nd; nd=nd->next) {
		QNodePoint *px = nd->inPoint( x, y );
		if (px) {
		   if (p) *p = px;
		   if (n) *n = nd;
		   return 1;
		}
	}
	return 0;
}

QNode *QDocument::getNode( int idn ) {
  QNode *nd;
  for (nd=nodes; nd; nd=nd->next)
    if ( nd->id == idn )
      return nd;
  return NULL;
}

QComponent *QDocument::inComponent( int x, int y )
{
	QComponent *c;
	for (c=comps; c; c=c->next)
		if (c->r.contain( x, y ))
			return c;
	return NULL;
}

void QDocument::delNode( QNode *n )
{
	if (n->prev) n->prev->next = n->next;
	if (n->next) n->next->prev = n->prev;
	if (n==nodes) nodes=nodes->next;
	n->prev = n->next = NULL;
	delete n;
}

void QDocument::delComponent (QComponent *c)
{
	if (c->prev) c->prev->next = c->next;
	if (c->next) c->next->prev = c->prev;
	if (c==comps) comps=comps->next;
	c->next = c->prev = NULL;
	delete c;
}

void QDocument::joinNodes( QNode *n1, QNode *n2 )
{
	n1->join(n2);
	QComponent *c;	QPin *p;
	for (c=comps; c; c=c->next)
		for (p=c->pins; p; p=p->next)
			if (p->indicen == n2)
				p->indicen = n1;
	delNode (n2);
}

void QDocument::purgeNodes()
{
	QNode *n;	QComponent *c;	QPin *p;
	n=nodes;
	while (n) {
		bool inUses = false;
		for (c=comps; c; c=c->next)
			for (p=c->pins; p; p=p->next)
				if (p->indicen==n)
					inUses = true;
		QNode *t = n;
		n=n->next;
		if (inUses==false) // detach an delete
			delNode (t);
	}
}
