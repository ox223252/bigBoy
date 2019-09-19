#include "draw.h"
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "./lib/log/log.h"

// https://en.wikipedia.org/wiki/BMP_file_format
typedef struct
{
	char type[2];
	uint32_t size;
	uint16_t r[2];
	uint32_t offset;
	uint32_t headerSize;
	uint32_t width;
	uint32_t height;
	uint16_t colorPlans;
	uint16_t bitPerPixels;
} __attribute__((packed))
bmpHeader ;

int drawBmp ( robot_t *r, char* picture )
{
	if ( !picture  )
	{
		return ( __LINE__ );
	}

	int fd = open ( picture, O_RDONLY );

	if ( fd <= 0 )
	{
		return ( __LINE__ );
	}

	bmpHeader bh;
	read ( fd, &bh, sizeof ( bh ) );

	logVerbose ( "TYPE : %c%c\n", bh.type[ 0 ], bh.type[ 1 ] );
	logVerbose ( "size : %u\n", bh.size );
	logVerbose ( "offset : %u\n", bh.offset );
	logVerbose ( "width : %u\n", bh.width );
	logVerbose ( "height : %u\n", bh.height );
	logVerbose ( "bitPerPixels : %u\n", bh.bitPerPixels );

	uint32_t width = ( ( ( bh.width * bh.bitPerPixels + 31 ) / 32 ) * 4 );
	uint32_t size = width * bh.height;

	logDebug ( "width %d\n", width );

	uint8_t table [ bh.height ][ width ];
	lseek ( fd, bh.offset, SEEK_SET );
	read ( fd, table, size );
	close ( fd );

	// file BMP_file_format storage is BGR
	holonomicSet ( r, HOLD, 0, true );
	holonomicWait ( r );

	for ( uint32_t i = bh.height - 1; i < bh.height; i-- )
	{
		for ( uint32_t j = 0; j < bh.width; j++ )
		{

			if ( table[ i ][ j * 3 ] > table[ i ][ j * 3 + 1 ] + table[ i ][ j * 3 + 2 ] )
			{ // BLUE
				printf ( "\e[44m \e[0m" );
			}
			else if ( table[ i ][ j * 3 + 1 ] > table[ i ][ j * 3 ] + table[ i ][ j * 3 + 2 ] )
			{ // GREEN
				printf ( "\e[42m \e[0m" );
			}
			else if ( table[ i ][ j * 3 + 2 ] > table[ i ][ j * 3 ] + table[ i ][ j * 3 + 1 ] )
			{ // RED
				printf ( "\e[41m \e[0m" );
			}
			else if ( table[ i ][ j * 3 ] - table[ i ][ j * 3 + 1 ] == 0 &&
				table[ i ][ j * 3 ] - table[ i ][ j * 3 + 2 ] == 0 )
			{
				if ( table[ i ][ j * 3] == 255 )
				{ // WHITE
					printf ( "\e[47m \e[0m" );
				}
				else
				{
					printf ( " " );
				}
			}
			else
			{
				printf ( "#" );
			}
			holonomicSet ( r, LEFT, 1, true );
			holonomicWait ( r );
		}
		printf ( "\n" );

		holonomicSet ( r, BACK, 1, true );
		holonomicWait ( r );

		holonomicSet ( r, RIGHT, bh.width, true );
		holonomicWait ( r );
	}

	holonomicSet ( r, FREE, 0, true );


	return ( 0 );
}