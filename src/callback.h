#ifndef __CALLBACK_H__
#define __CALLBACK_H__

char * printTimer ( void * arg );
void  onMessage ( char *topic, char * msg, void * data );

#endif