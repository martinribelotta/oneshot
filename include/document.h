#ifndef Oneshot_QDocument_h
#define Oneshot_QDocument_h

#include <iglu/structs.h>
#include <iglu/tcanvas.h>

class QNode;
class QNodePoint;
class QComponent;

class QDocument {
public:
	char *fileName;
	QComponent *comps;
	QNode *nodes;
	bool modified;

	QDocument();
	~QDocument();

	void newDoc();
	bool save (char *name);	// Para "Guardar"
	bool load (char *name);	// Para "Abrir"

	void addComponent( QComponent *c );
	void delComponent( QComponent *c );
	void addNode( QNode *n );
	void delNode( QNode *n );

	int inNode( int x, int y, QNode **n=NULL, QNodePoint **p=NULL );
	QNode *getNode( int idn );
	QComponent *inComponent( int x, int y );

	void joinNodes( QNode *n1, QNode *n2 );
	void purgeNodes();
};

#endif /* Oneshot_Document_h */
