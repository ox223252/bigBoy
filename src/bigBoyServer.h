#ifndef __BIGBOYSERVER_H__
#define __BIGBOYSERVER_H__

#include <mosquitto.h>

// to install mosquitto :
// apt install libmosquitto-dev
// or
// git clone https://github.com/eclipse/mosquitto.git
// make
// make install
//
// install mosquitto for cross compilation
// need openssl
// git clone https://github.com/openssl/openssl.git
// cd openssl/
// ./Configure linux-armv4 --prefix=/usr/arm-linux-gnueabihf CROSS_COMPILE=arm-linux-gnueabihf-
// make 
// make install
// git clone https://github.com/eclipse/mosquitto.git
// cd mosquitto
// make CROSS_COMPILE=arm-linux-gnueabihf- CC=gcc CXX=g++ AR=ar LD=ld
// cp lib/libmosquitto.so.1 /usr/arm-linux-gnueabihf/lib/libmosquitto.so.1
// ln -s /usr/arm-linux-gnueabihf/lib/libmosquitto.so.1 /usr/arm-linux-gnueabihf/lib/libmosquitto.so
// cp lib/mosquitto.h /usr/arm-linux-gnueabihf/include

#include <pthread.h>
#include <stdint.h>

#include "lib/holonomic/holonomic.h"

typedef struct
{
	char * name;
	char * host;
	int port;

	char * ca;
	char * cert;
	char * key;

	char * lastName;
	char * lastMsg;
}
MQTT_init_t;

int bigBoyMQTT_init ( const MQTT_init_t s, struct mosquitto ** mosq, void (*fnc)(char* topic,char* msg), void * arg);
int bigBoyMQTT_stop ( struct mosquitto ** mosq );
int bigBoyMQTT_sender ( struct mosquitto * mosq, const char* topic, uint8_t * stop, void * data, char *callback( void* arg ), uint32_t time );

#endif