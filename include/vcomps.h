#ifndef Oneshot_VirtualComponents_h
#define Oneshot_VirtualComponents_h

#include <qcomp.h>

extern QComponent *createComponent( int x, int y, int index, int forLoad=0 );
extern QComponent *createComponentByName( const char *name );

#endif /* Oneshot_VirtualComponents_h */
