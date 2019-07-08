// file auto generated

#include "./lib/timer/timer.h"
#include <unistd.h>
#include "./lib/tcpIp/tcpIp.h"
#include <stdlib.h>
#include "./lib/signalHandler/signalHandler.h"
#include "./lib/pca9685/pca9685.h"
#include "./lib/mcp23017/mcp23017.h"
#include "./lib/log/log.h"
#include "./lib/freeOnExit/freeOnExit.h"
#include <stdint.h>
#include "./lib/config/config_arg.h"
#include "./lib/config/config_file.h"
#include <pthread.h>
#include "./lib/holonomic/holonomic.h"
#include <errno.h>
#include <string.h>

// INIT_FUNCTION
void functionExit ( void * arg )
{
 
	printf ( "%s\n", ( char * )arg );
 
	exit ( 0 );
}
 

int main ( int argc, char ** argv )
{
	// INIT_VAR
	char serverAddr[ 32 ] = "172.0.0.1";
	uint16_t serverPort = 6666;
	int serverFd = 0;
	int clientFd = 0;

	char *picture = NULL;

	signalHandling signal =
	{
		.flag =
		{
			.Int = 1,
			.Quit = 1,
			.Term = 1
		},
		.Int =
		{
			.func = functionExit,
			.arg = "Int case\n"
		},
		.Quit =
		{
			.func = functionExit,
			.arg = "Quit case\n"
		},
		.Term =
		{
			.func = functionExit,
			.arg = "Term case\n"
		}
	};
 
	struct
	{
		uint8_t help:1,
			quiet:1,
			verbose:1,
			#ifndef RELEASE_MODE
				color:1, // only available for debug mode
				debug:1, // only available for debug mode
			#else
				unused:2,
			#endif
			term:1,
			file:1;
	}
	flags = { 0 };

	char logFileName[ 512 ] = "";

	pthread_mutex_t i2cMutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;

	int pca9685_fd = 0;
	int pca9685_addr = 0x40;
	char pca9685_i2c[ 512 ] = "";

	int mcp23017_fd = 0;
	int mcp23017_addr = 0x40;
	char mcp23017_i2c[ 512 ] = "";
 
	config_el config[] =
	{
		#ifdef __PCA9685_H__
			{ "PCA9685_ADDR", cT ( int32_t ), &pca9685_addr, "pca9685 address"},
			{ "PCA9685_I2C", cT ( str ), pca9685_i2c, "pca9685 i2c bus name"},
		#endif
		#ifdef __MCP23017_H__
			{ "MCP23017_ADDR", cT ( int32_t ), &mcp23017_addr, "mcp23017 address"},
			{ "MCP23017_I2C", cT ( str ), mcp23017_i2c, "mcp23017 i2c bus name"},
		#endif
		#ifdef __TCPIP_H__
			{ "TCP_PORT", cT ( uint16_t ), &serverPort, "tcp server port"},
			{ "TCP_ADDR", cT ( str ), serverAddr, "tcp server ip address or server name"},
		#endif
		{ NULL }
	};
 
	param_el param[] =
	{
		{ "--help", "-h", 0x01, cT ( bool ), &flags, "help" },
		#ifdef __LOG_H__
			{ "--quiet", "-q", 0x02, cT ( bool ), &flags, "quiet" },
			{ "--verbose", "-v", 0x04, cT ( bool ), &flags, "verbose" },
			#ifndef RELEASE_MODE
				{ "--color", "-c", 0x08, cT ( bool ), &flags, "color" },
				{ "--debug", "-d", 0x10, cT ( bool ), &flags, "debug" },
			#endif
			{ "--term", "-lT", 0x20, cT ( bool ), &flags, "log on term" },
			{ "--file", "-lF", 0x40, cT ( bool ), &flags, "log in file" },
			{ "--logFileName", "-lFN", 1, cT ( str ), logFileName, "log file name" },
		#endif
		#ifdef __PCA9685_H__
			{ "--pca9685_addr", "-pA", 1, cT ( int32_t ), &pca9685_addr, "pca9685 address" },
			{ "--pca9685_i2c", "-pI", 1, cT ( str ), pca9685_i2c, "pca9685 i2c bus name" },
		#endif
		#ifdef __MCP23017_H__
			{ "--mcp23017_addr", "-mA", 1, cT ( int32_t ), &mcp23017_addr, "mcp23017 address" },
			{ "--mcp23017_i2c", "-mI", 1, cT ( str ), mcp23017_i2c, "mcp23017 i2c bus name" },
		#endif
		#ifdef __TCPIP_H__
			{ "--tcp_port", "-tp", 1, cT ( uint16_t ), &serverPort, "tcp server port" },
			{ "--tcp_addr", "-tA", 1, cT ( str ), serverAddr, "tcp server ip address or server name" },
		#endif
		{ "--picture", "-p", 1, cT ( ptrStr ), &picture, "picture need to be draw (only bmp)" },
		{ NULL }
	};
 
	// INIT_CORE
	// INIT_SIGNALHANDLER
	signalHandlerInit ( &signal );
	// END_SIGNALHANDLER
	
	// INIT_FREEONEXIT
	if ( initFreeOnExit ( ) )
	{ // failure case
	}
	// END_FREEONEXIT
	
	// INIT_CONFIG
	if ( readConfigFile ( "config", config ) )
	{ // failure case
	}
	
	if ( readConfigArgs ( argc, argv, config ) )
	{ // failure case
	}
	
	if ( readParamArgs ( argc, argv, param ) )
	{ // failure case
	}
	else if ( flags.help )
	{// configFile read successfully
		printf ( "%s is a program to drive na honomic robot based on mecanum well\n", argv[ 0 ] );
		printf ( "Build date: %s\n", DATE_BUILD );
		printf ( "Author: ox223252\n" );
		printf ( "License: GPLv2\n" );
		helpParamArgs ( param );
		helpConfigArgs ( config );
		return ( 0 );
	}
	// END_CONFIG

	// if ( clientFd = clientInit ( serverAddr, serverPort ), clientFd > 0 )
	// { // client create
	// 	printf ( "connected to server\n" );
	// }
	// else if ( serverFd = serverInit ( serverPort ), serverFd <= 0 )
	// { // failure case
	// }
	// else if ( clientFd = serverListen ( serverFd ), clientFd > 0 )
	// { // client connected
	// 	printf ( "client connected\n" );
	// }
	// else
	// { // failure case
	// }
 
	// // INIT_PCA9685
	// if ( openPCA9685 ( pca9685_i2c, pca9685_addr, &pca9685_fd ) )
	// { // failure case
	// }
	// else if ( setCloseOnExit ( pca9685_fd ) )
	// { // failure case

	// }
	// else
	// {
	// 	setPCA9685BusMutex ( &i2cMutex );
	// }

	// // END_PCA9685
 
	// // INIT_MCP23017
	// if ( openMCP23017 ( mcp23017_i2c, mcp23017_addr, &mcp23017_fd ) )
	// { // failure case
	// }
	// else if ( setCloseOnExit ( mcp23017_fd ) )
	// { // failure case

	// }
	// else
	// {
	// 	setMCP23017BusMutex( &i2cMutex );
	// }
	// // END_MCP23017
 
	// INIT_LOG
	logSetVerbose ( flags.verbose );
	#ifndef RELEASE_MODE
		logSetDebug ( flags.debug );
		logSetColor ( flags.color );
	#endif
	logSetQuiet ( flags.quiet );
	logSetOutput ( flags.term | !flags.file, flags.file );
	logSetFileName ( logFileName );
	// END_LOG
	
	robot_t robot;
	if ( holonomicInit ( &robot, true, &i2cMutex, pca9685_fd  ) )
	{ // failure case
		return ( 0 );
	}
	else
	{
		setThreadCancelOnExit ( robot.thread );
		setThreadJoinOnExit ( robot.thread );

		holonomicSetDelay ( &robot, 100000 );
	}

	if ( picture )
	{
		printf ( "try to draw \n" );
		if ( drawBmp ( &robot, picture ) )
		{
			printf ( "error %s\n", strerror ( errno ) );
		}
	}
	else
	{
		holonomicSet ( &robot, FRONT | LEFT, 100, true );

		holonomicWait ( &robot );
	}

	// END_CORE
	// END_PROGRAM
	if ( clientFd > 0 )
	{
		close ( clientFd );
	}
	if ( serverFd > 0 )
	{
		close ( serverFd );
	}

	unsetThreadCancelOnExit ( robot.thread );
	unsetThreadJoinOnExit ( robot.thread );

	pthread_cancel ( robot.thread );
	pthread_join ( robot.thread, NULL );

	// RELEASE_PCA9685
	unsetCloseOnExit ( pca9685_fd );
	closePCA9685 ( pca9685_fd );
	// RELEASE_MCP23017
	unsetCloseOnExit ( mcp23017_fd );
	closeMCP23017 ( mcp23017_fd );

	return ( 0 );
}

