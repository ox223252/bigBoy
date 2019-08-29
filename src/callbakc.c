#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

char * printTimer ( void * arg )
{
	static char str[32];
	sprintf ( str, "test %d\r", (*((uint8_t*)arg))++ );
	return ( str );
}

void  onMessage ( char *topic, char * msg, void * data )
{
	if ( !strcmp( topic, "/petit/position"))
	printf ( "topic : %s\n", topic );
	printf ( "message : %s\n", msg );
}