#ifndef Oneshot_QComponent_h
#define Oneshot_QComponent_h

#include <iglu/structs.h>
#include <stdio.h>

class QNode;
class QNodePoint;

#define pinIn	1
#define pinOut  0
#define pinDelta 16

class QPin {
	char *_name;
public:
	QPin *next;
	int io;
	QNode *indicen;
	QNodePoint *indicem;

	QPin( int d, QNode *nd, QNodePoint *ndp, char *s );
	// x(a), y(b), io(c)
	QPin( int a, int b, int c, char *s );
	~QPin();

	void draw();
	char *name() { return _name; }
};

// Separacion entre pines.
#define pinSpace 16

class QComponent {
public:
	char *name;
	int cpi, cpo, id;
	QPin *pins;
	QComponent *next, *prev;
	QRect r;

	QComponent();
	QComponent( int x, int y );
	~QComponent();

	virtual void draw();
	virtual void sim()
	  { /* Reimplementado en los derivados */ }
	virtual void simTick()
	  { /* Reimplementado en los derivados */ }
	virtual bool doDialog()
	  { return false; /* Reimplementado en los derivados */ }
	bool save( FILE *f );
	bool load( FILE *f );

	// Reimplementado en los derivados. Se llama para guardar
	// parametors extra de los derivados.
	virtual bool extraSave( FILE * ) { return true; }

	// Reimplementado en los derivados. Se llama para cargar
	// parametors extra de los derivados.
	virtual bool extraLoad( FILE * ) { return true; }

	void do_moverel( int dx, int dy, int movepins=0 );
	void moverel( int dx, int dy ) { do_moverel( dx, dy, 0 ); }
	void moveto( int dx, int dy ) { do_moverel( dx, dy, 1 ); }

        void setName( char *s );
	void insertPin( QPin *p );
	QPin *getPin( char *s );
};

#endif /* Oneshot_QComponent_h */
