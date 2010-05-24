#ifndef Oneshot_QNode_h
#define Oneshot_QNode_h

#include <iglu/structs.h>
#include <stdio.h>

#define nodePointz 8

class QNodePoint {
	QPoint _pos;
public:
	QNodePoint *back, *next, *prev;
	int isniple, id;

	QNodePoint(QPoint p, QNodePoint *b=NULL):
		_pos(p), back(b), next(NULL), prev(NULL)
		{ isniple=0; }
	inline QRect rect() {
		return QRect(
			pos().x-nodePointz/2, pos().y-nodePointz/2,
			pos().x+nodePointz/2, pos().y+nodePointz/2
		);
	}
	inline int inPoint( QPoint p ) { return rect().contain( p ); }
	virtual QPoint pos() { return _pos; }
	void moverel( QPoint rel ) { _pos += rel; }
};

class QNodeNiple: public QNodePoint {
public:
	QNodePoint *yo;

	QNodeNiple(QNodePoint *y, QNodePoint *b=NULL):
		QNodePoint(QPoint(0,0),b), yo(y) { isniple=1; }
	virtual QPoint pos() { return yo->pos(); }
};

class QNode {
	bool pointPreload( FILE *f );
	bool niplePreload( FILE *f );
	bool pointLoad( QNodePoint *p, FILE *f );
	bool nipleLoad( QNodeNiple *p, FILE *f );

	QNodePoint *head;
public:
	int state;
	QNodePoint *points;
	QNode *next, *prev;
	int id;

        QNode();
	QNode( int x, int y );
	~QNode();

	void draw();

	void addPoint( QNodePoint *p );
	void delPoint( QNodePoint *p );
	void detachPoint( QNodePoint *p );
	void join( QNode *n );
	bool save( FILE *f );
	bool load( FILE *f );
	QNodePoint *inPoint( int x, int y );
	QNodePoint *getPoint( int pid );
};

#endif /* Oneshot_QNode_h */
