#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug-GNU-LINUX
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/actuators/asyncLED.o \
	${OBJECTDIR}/actuators/asyncMOTOR.o \
	${OBJECTDIR}/actuators/asyncPWM.o \
	${OBJECTDIR}/actuators/asyncSERVO.o \
	${OBJECTDIR}/actuators/asyncSTEPPER.o \
	${OBJECTDIR}/actuators/asyncTools.o \
	${OBJECTDIR}/configManager.o \
	${OBJECTDIR}/deviceMapping.o \
	${OBJECTDIR}/hwControl/boardHWctrl.o \
	${OBJECTDIR}/hwControl/boardHWsimu.o \
	${OBJECTDIR}/hwControl/device_drivers/pca9685.o \
	${OBJECTDIR}/hwControl/hwManager.o \
	${OBJECTDIR}/hwControl/libs/i2c/onion-i2c.o \
	${OBJECTDIR}/hwControl/libs/onion-debug/onion-debug.o \
	${OBJECTDIR}/hwControl/networkManager.o \
	${OBJECTDIR}/hwControl/wifi_json.o \
	${OBJECTDIR}/kehopsCom/libs/lib_json/jRead.o \
	${OBJECTDIR}/kehopsCom/libs/lib_json/jWrite.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Clients.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Heap.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/LinkedList.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Log.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTClient.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacket.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacketOut.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistence.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolClient.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolOut.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Messages.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SSLSocket.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Socket.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SocketBuffer.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/StackTrace.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Thread.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Tree.o \
	${OBJECTDIR}/kehopsCom/libs/lib_mqtt/utf-8.o \
	${OBJECTDIR}/kehopsCom/linux_JSON.o \
	${OBJECTDIR}/kehopsCom/messagesManager.o \
	${OBJECTDIR}/kehopsCom/mqttProtocol.o \
	${OBJECTDIR}/kehopsCom/udpPublish.o \
	${OBJECTDIR}/kehops_main.o \
	${OBJECTDIR}/timerManager.o \
	${OBJECTDIR}/tools.o


# C Compiler Flags
CFLAGS=-pthread -lm

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops_x64

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops_x64: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops_x64 ${OBJECTFILES} ${LDLIBSOPTIONS} -pthread -lm

${OBJECTDIR}/actuators/asyncLED.o: actuators/asyncLED.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncLED.o actuators/asyncLED.c

${OBJECTDIR}/actuators/asyncMOTOR.o: actuators/asyncMOTOR.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncMOTOR.o actuators/asyncMOTOR.c

${OBJECTDIR}/actuators/asyncPWM.o: actuators/asyncPWM.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncPWM.o actuators/asyncPWM.c

${OBJECTDIR}/actuators/asyncSERVO.o: actuators/asyncSERVO.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncSERVO.o actuators/asyncSERVO.c

${OBJECTDIR}/actuators/asyncSTEPPER.o: actuators/asyncSTEPPER.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncSTEPPER.o actuators/asyncSTEPPER.c

${OBJECTDIR}/actuators/asyncTools.o: actuators/asyncTools.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncTools.o actuators/asyncTools.c

${OBJECTDIR}/configManager.o: configManager.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/configManager.o configManager.c

${OBJECTDIR}/deviceMapping.o: deviceMapping.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/deviceMapping.o deviceMapping.c

${OBJECTDIR}/hwControl/boardHWctrl.o: hwControl/boardHWctrl.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/boardHWctrl.o hwControl/boardHWctrl.c

${OBJECTDIR}/hwControl/boardHWsimu.o: hwControl/boardHWsimu.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/boardHWsimu.o hwControl/boardHWsimu.c

${OBJECTDIR}/hwControl/device_drivers/pca9685.o: hwControl/device_drivers/pca9685.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/pca9685.o hwControl/device_drivers/pca9685.c

${OBJECTDIR}/hwControl/hwManager.o: hwControl/hwManager.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/hwManager.o hwControl/hwManager.c

${OBJECTDIR}/hwControl/libs/i2c/onion-i2c.o: hwControl/libs/i2c/onion-i2c.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/libs/i2c
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/libs/i2c/onion-i2c.o hwControl/libs/i2c/onion-i2c.c

${OBJECTDIR}/hwControl/libs/onion-debug/onion-debug.o: hwControl/libs/onion-debug/onion-debug.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/libs/onion-debug
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/libs/onion-debug/onion-debug.o hwControl/libs/onion-debug/onion-debug.c

${OBJECTDIR}/hwControl/networkManager.o: hwControl/networkManager.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/networkManager.o hwControl/networkManager.c

${OBJECTDIR}/hwControl/wifi_json.o: hwControl/wifi_json.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/wifi_json.o hwControl/wifi_json.c

${OBJECTDIR}/kehopsCom/libs/lib_json/jRead.o: kehopsCom/libs/lib_json/jRead.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_json
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_json/jRead.o kehopsCom/libs/lib_json/jRead.c

${OBJECTDIR}/kehopsCom/libs/lib_json/jWrite.o: kehopsCom/libs/lib_json/jWrite.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_json
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_json/jWrite.o kehopsCom/libs/lib_json/jWrite.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Clients.o: kehopsCom/libs/lib_mqtt/Clients.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Clients.o kehopsCom/libs/lib_mqtt/Clients.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Heap.o: kehopsCom/libs/lib_mqtt/Heap.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Heap.o kehopsCom/libs/lib_mqtt/Heap.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/LinkedList.o: kehopsCom/libs/lib_mqtt/LinkedList.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/LinkedList.o kehopsCom/libs/lib_mqtt/LinkedList.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Log.o: kehopsCom/libs/lib_mqtt/Log.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Log.o kehopsCom/libs/lib_mqtt/Log.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTClient.o: kehopsCom/libs/lib_mqtt/MQTTClient.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTClient.o kehopsCom/libs/lib_mqtt/MQTTClient.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacket.o: kehopsCom/libs/lib_mqtt/MQTTPacket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacket.o kehopsCom/libs/lib_mqtt/MQTTPacket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacketOut.o: kehopsCom/libs/lib_mqtt/MQTTPacketOut.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacketOut.o kehopsCom/libs/lib_mqtt/MQTTPacketOut.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistence.o: kehopsCom/libs/lib_mqtt/MQTTPersistence.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistence.o kehopsCom/libs/lib_mqtt/MQTTPersistence.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.o: kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.o kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolClient.o: kehopsCom/libs/lib_mqtt/MQTTProtocolClient.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolClient.o kehopsCom/libs/lib_mqtt/MQTTProtocolClient.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolOut.o: kehopsCom/libs/lib_mqtt/MQTTProtocolOut.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolOut.o kehopsCom/libs/lib_mqtt/MQTTProtocolOut.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Messages.o: kehopsCom/libs/lib_mqtt/Messages.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Messages.o kehopsCom/libs/lib_mqtt/Messages.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SSLSocket.o: kehopsCom/libs/lib_mqtt/SSLSocket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SSLSocket.o kehopsCom/libs/lib_mqtt/SSLSocket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Socket.o: kehopsCom/libs/lib_mqtt/Socket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Socket.o kehopsCom/libs/lib_mqtt/Socket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SocketBuffer.o: kehopsCom/libs/lib_mqtt/SocketBuffer.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SocketBuffer.o kehopsCom/libs/lib_mqtt/SocketBuffer.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/StackTrace.o: kehopsCom/libs/lib_mqtt/StackTrace.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/StackTrace.o kehopsCom/libs/lib_mqtt/StackTrace.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Thread.o: kehopsCom/libs/lib_mqtt/Thread.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Thread.o kehopsCom/libs/lib_mqtt/Thread.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Tree.o: kehopsCom/libs/lib_mqtt/Tree.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Tree.o kehopsCom/libs/lib_mqtt/Tree.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/utf-8.o: kehopsCom/libs/lib_mqtt/utf-8.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/utf-8.o kehopsCom/libs/lib_mqtt/utf-8.c

${OBJECTDIR}/kehopsCom/linux_JSON.o: kehopsCom/linux_JSON.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/linux_JSON.o kehopsCom/linux_JSON.c

${OBJECTDIR}/kehopsCom/messagesManager.o: kehopsCom/messagesManager.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/messagesManager.o kehopsCom/messagesManager.c

${OBJECTDIR}/kehopsCom/mqttProtocol.o: kehopsCom/mqttProtocol.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/mqttProtocol.o kehopsCom/mqttProtocol.c

${OBJECTDIR}/kehopsCom/udpPublish.o: kehopsCom/udpPublish.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/udpPublish.o kehopsCom/udpPublish.c

${OBJECTDIR}/kehops_main.o: kehops_main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehops_main.o kehops_main.c

${OBJECTDIR}/timerManager.o: timerManager.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timerManager.o timerManager.c

${OBJECTDIR}/tools.o: tools.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -DI2CSIMU -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools.o tools.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
