# flags for alls targets
FLAGS= -D'BY_LINUX_MAKEFILE' -D'PCA_WITH_THREAD' -D'MCP_WITH_THREAD' -D'FOE_WITH_THREAD'
LDFLAGS= -lmosquitto

# tools / flags / libs only for native target
CC=gcc
CXX=g++
natif_FLAGS=
natif_LIBS=

# tools / flags / libs only for arm linux target
LABEL=arm-Linux
arm-Linux_CROSS_CC=arm-linux-gnueabihf-gcc
arm-Linux_CROSS_CXX=arm-linux-gnueabihf-g++
arm-Linux_FLAGS=
arm-Linux_LIBS= -L/usr/arm-linux-gnueabihf/lib/
arm-Linux_EXEC_AFTER=

# tools / flags / libs only for arm target
LABEL=arm
arm_CROSS_CC=arm-none-eabi-gcc
arm_CROSS_CXX=arm-none-eabi-g++
arm_FLAGS=-std=gnu99 -g -O2 -Wall -mlittle-endian -mthumb -mthumb-interwork -mcpu=cortex-m0 -fsingle-precision-constant -Wdouble-promotion
arm_LIBS=
arm_EXEC_AFTER=arm-none-eabi-objcopy -O binary ${EXEC} ${EXEC}.bin

# tools / flags / libs only for w64 target
LABEL=w64
w64_CROSS_CC=i686-w64-mingw32-gcc
w64_CROSS_CXX=i686-w64-mingw32-g++
w64_FLAGS=
w64_LIBS=
w64_EXEC_AFTER=
