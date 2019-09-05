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
CC=mipsel-openwrt-linux-gcc
CCC=mipsel-openwrt-linux-g++
CXX=mipsel-openwrt-linux-g++
FC=gfortran
AS=mipsel-openwrt-linux-as

# Macros
CND_PLATFORM=GNU_Omega-Linux
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/actuators/asyncAOUT.o \
	${OBJECTDIR}/actuators/asyncDisplay.o \
	${OBJECTDIR}/actuators/asyncLED.o \
	${OBJECTDIR}/actuators/asyncMOTOR.o \
	${OBJECTDIR}/actuators/asyncPWM.o \
	${OBJECTDIR}/actuators/asyncSERVO.o \
	${OBJECTDIR}/actuators/asyncSTEPPER.o \
	${OBJECTDIR}/actuators/asyncTools.o \
	${OBJECTDIR}/actuators/gfx_xbm_pics.o \
	${OBJECTDIR}/config/deviceMapping.o \
	${OBJECTDIR}/config/kehopsConfig.o \
	${OBJECTDIR}/configManager.o \
	${OBJECTDIR}/fileIO.o \
	${OBJECTDIR}/hwControl/device_drivers/ads101x.o \
	${OBJECTDIR}/hwControl/device_drivers/ads111x.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/U8g2lib.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_bitmap.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_box.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_buffer.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_circle.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_cleardisplay.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_memory.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_setup.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_font.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_fonts.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_hvline.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_input_value.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_intersection.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_kerning.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_line.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_ll_hvline.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_message.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_polygon.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_selection_list.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_setup.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8g2.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8x8.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_8x8.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_byte.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_cad.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_a2printer.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_il3820_296x128.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ist3020.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ks0108.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_lc7981.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ld7032_60x32.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ls013b7dh03.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_max7219.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcd8544_84x48.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8812.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8814_hx1230.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sbn1661.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sed1330.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_64x32.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_72x40.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1107.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1108.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1122.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1305.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x32.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x64_noname.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_48x64.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x32.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x48.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_96x16.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1309.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1317.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1318.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1322.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1325.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1326.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1327.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1329.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1606_172x72.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1607_200x200.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7511.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st75256.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7565.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7567.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_erc240160.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_s028hn118a.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7588.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7920.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_stdio.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_t6963.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1601.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1604.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1608.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1610.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1611.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1617.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1638.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_dogs102.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_mini12864.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_debounce.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_display.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_fonts.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_gpio.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_input_value.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_message.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_selection_list.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_setup.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_string.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u16toa.o \
	${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u8toa.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_calibration.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_core.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_ranging.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_strings.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_i2c_platform.o \
	${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_platform.o \
	${OBJECTDIR}/hwControl/device_drivers/bh1745.o \
	${OBJECTDIR}/hwControl/device_drivers/display_mono.o \
	${OBJECTDIR}/hwControl/device_drivers/efm8_mcu_kehops.o \
	${OBJECTDIR}/hwControl/device_drivers/k_vl53l0x.o \
	${OBJECTDIR}/hwControl/device_drivers/mcp230xx.o \
	${OBJECTDIR}/hwControl/device_drivers/mcp4725.o \
	${OBJECTDIR}/hwControl/device_drivers/mcp4728.o \
	${OBJECTDIR}/hwControl/device_drivers/pca9629.o \
	${OBJECTDIR}/hwControl/device_drivers/pca9685.o \
	${OBJECTDIR}/hwControl/device_drivers/tca9548a.o \
	${OBJECTDIR}/hwControl/hardwareDrivers.o \
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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.c} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/kehops ${OBJECTFILES} ${LDLIBSOPTIONS} -pthread -lm

${OBJECTDIR}/actuators/asyncAOUT.o: actuators/asyncAOUT.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncAOUT.o actuators/asyncAOUT.c

${OBJECTDIR}/actuators/asyncDisplay.o: actuators/asyncDisplay.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncDisplay.o actuators/asyncDisplay.c

${OBJECTDIR}/actuators/asyncLED.o: actuators/asyncLED.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncLED.o actuators/asyncLED.c

${OBJECTDIR}/actuators/asyncMOTOR.o: actuators/asyncMOTOR.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncMOTOR.o actuators/asyncMOTOR.c

${OBJECTDIR}/actuators/asyncPWM.o: actuators/asyncPWM.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncPWM.o actuators/asyncPWM.c

${OBJECTDIR}/actuators/asyncSERVO.o: actuators/asyncSERVO.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncSERVO.o actuators/asyncSERVO.c

${OBJECTDIR}/actuators/asyncSTEPPER.o: actuators/asyncSTEPPER.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncSTEPPER.o actuators/asyncSTEPPER.c

${OBJECTDIR}/actuators/asyncTools.o: actuators/asyncTools.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/asyncTools.o actuators/asyncTools.c

${OBJECTDIR}/actuators/gfx_xbm_pics.o: actuators/gfx_xbm_pics.c
	${MKDIR} -p ${OBJECTDIR}/actuators
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/actuators/gfx_xbm_pics.o actuators/gfx_xbm_pics.c

${OBJECTDIR}/config/deviceMapping.o: config/deviceMapping.c
	${MKDIR} -p ${OBJECTDIR}/config
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config/deviceMapping.o config/deviceMapping.c

${OBJECTDIR}/config/kehopsConfig.o: config/kehopsConfig.c
	${MKDIR} -p ${OBJECTDIR}/config
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/config/kehopsConfig.o config/kehopsConfig.c

${OBJECTDIR}/configManager.o: configManager.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/configManager.o configManager.c

${OBJECTDIR}/fileIO.o: fileIO.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/fileIO.o fileIO.c

${OBJECTDIR}/hwControl/device_drivers/ads101x.o: hwControl/device_drivers/ads101x.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/ads101x.o hwControl/device_drivers/ads101x.c

${OBJECTDIR}/hwControl/device_drivers/ads111x.o: hwControl/device_drivers/ads111x.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/ads111x.o hwControl/device_drivers/ads111x.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/U8g2lib.o: hwControl/device_drivers/api/gfx_u8g/U8g2lib.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/U8g2lib.o hwControl/device_drivers/api/gfx_u8g/U8g2lib.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_bitmap.o: hwControl/device_drivers/api/gfx_u8g/u8g2_bitmap.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_bitmap.o hwControl/device_drivers/api/gfx_u8g/u8g2_bitmap.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_box.o: hwControl/device_drivers/api/gfx_u8g/u8g2_box.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_box.o hwControl/device_drivers/api/gfx_u8g/u8g2_box.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_buffer.o: hwControl/device_drivers/api/gfx_u8g/u8g2_buffer.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_buffer.o hwControl/device_drivers/api/gfx_u8g/u8g2_buffer.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_circle.o: hwControl/device_drivers/api/gfx_u8g/u8g2_circle.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_circle.o hwControl/device_drivers/api/gfx_u8g/u8g2_circle.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_cleardisplay.o: hwControl/device_drivers/api/gfx_u8g/u8g2_cleardisplay.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_cleardisplay.o hwControl/device_drivers/api/gfx_u8g/u8g2_cleardisplay.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_memory.o: hwControl/device_drivers/api/gfx_u8g/u8g2_d_memory.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_memory.o hwControl/device_drivers/api/gfx_u8g/u8g2_d_memory.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_setup.o: hwControl/device_drivers/api/gfx_u8g/u8g2_d_setup.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_d_setup.o hwControl/device_drivers/api/gfx_u8g/u8g2_d_setup.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_font.o: hwControl/device_drivers/api/gfx_u8g/u8g2_font.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_font.o hwControl/device_drivers/api/gfx_u8g/u8g2_font.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_fonts.o: hwControl/device_drivers/api/gfx_u8g/u8g2_fonts.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_fonts.o hwControl/device_drivers/api/gfx_u8g/u8g2_fonts.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_hvline.o: hwControl/device_drivers/api/gfx_u8g/u8g2_hvline.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_hvline.o hwControl/device_drivers/api/gfx_u8g/u8g2_hvline.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_input_value.o: hwControl/device_drivers/api/gfx_u8g/u8g2_input_value.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_input_value.o hwControl/device_drivers/api/gfx_u8g/u8g2_input_value.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_intersection.o: hwControl/device_drivers/api/gfx_u8g/u8g2_intersection.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_intersection.o hwControl/device_drivers/api/gfx_u8g/u8g2_intersection.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_kerning.o: hwControl/device_drivers/api/gfx_u8g/u8g2_kerning.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_kerning.o hwControl/device_drivers/api/gfx_u8g/u8g2_kerning.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_line.o: hwControl/device_drivers/api/gfx_u8g/u8g2_line.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_line.o hwControl/device_drivers/api/gfx_u8g/u8g2_line.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_ll_hvline.o: hwControl/device_drivers/api/gfx_u8g/u8g2_ll_hvline.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_ll_hvline.o hwControl/device_drivers/api/gfx_u8g/u8g2_ll_hvline.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_message.o: hwControl/device_drivers/api/gfx_u8g/u8g2_message.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_message.o hwControl/device_drivers/api/gfx_u8g/u8g2_message.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_polygon.o: hwControl/device_drivers/api/gfx_u8g/u8g2_polygon.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_polygon.o hwControl/device_drivers/api/gfx_u8g/u8g2_polygon.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_selection_list.o: hwControl/device_drivers/api/gfx_u8g/u8g2_selection_list.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_selection_list.o hwControl/device_drivers/api/gfx_u8g/u8g2_selection_list.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_setup.o: hwControl/device_drivers/api/gfx_u8g/u8g2_setup.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8g2_setup.o hwControl/device_drivers/api/gfx_u8g/u8g2_setup.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log.o: hwControl/device_drivers/api/gfx_u8g/u8log.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log.o hwControl/device_drivers/api/gfx_u8g/u8log.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8g2.o: hwControl/device_drivers/api/gfx_u8g/u8log_u8g2.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8g2.o hwControl/device_drivers/api/gfx_u8g/u8log_u8g2.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8x8.o: hwControl/device_drivers/api/gfx_u8g/u8log_u8x8.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8log_u8x8.o hwControl/device_drivers/api/gfx_u8g/u8log_u8x8.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_8x8.o: hwControl/device_drivers/api/gfx_u8g/u8x8_8x8.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_8x8.o hwControl/device_drivers/api/gfx_u8g/u8x8_8x8.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_byte.o: hwControl/device_drivers/api/gfx_u8g/u8x8_byte.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_byte.o hwControl/device_drivers/api/gfx_u8g/u8x8_byte.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_cad.o: hwControl/device_drivers/api/gfx_u8g/u8x8_cad.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_cad.o hwControl/device_drivers/api/gfx_u8g/u8x8_cad.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_a2printer.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_a2printer.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_a2printer.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_a2printer.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_il3820_296x128.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_il3820_296x128.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_il3820_296x128.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_il3820_296x128.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ist3020.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ist3020.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ist3020.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ist3020.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ks0108.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ks0108.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ks0108.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ks0108.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_lc7981.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_lc7981.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_lc7981.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_lc7981.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ld7032_60x32.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ld7032_60x32.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ld7032_60x32.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ld7032_60x32.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ls013b7dh03.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ls013b7dh03.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ls013b7dh03.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ls013b7dh03.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_max7219.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_max7219.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_max7219.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_max7219.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcd8544_84x48.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcd8544_84x48.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcd8544_84x48.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcd8544_84x48.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8812.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8812.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8812.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8812.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8814_hx1230.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8814_hx1230.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8814_hx1230.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_pcf8814_hx1230.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sbn1661.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sbn1661.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sbn1661.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sbn1661.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sed1330.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sed1330.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sed1330.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sed1330.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_64x32.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_64x32.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_64x32.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_64x32.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_72x40.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_72x40.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_72x40.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1106_72x40.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1107.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1107.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1107.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1107.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1108.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1108.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1108.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1108.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1122.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1122.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1122.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_sh1122.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1305.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1305.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1305.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1305.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x32.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x32.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x32.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x32.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x64_noname.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x64_noname.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x64_noname.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_128x64_noname.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_48x64.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_48x64.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_48x64.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_48x64.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x32.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x32.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x32.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x32.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x48.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x48.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x48.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_64x48.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_96x16.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_96x16.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_96x16.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1306_96x16.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1309.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1309.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1309.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1309.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1317.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1317.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1317.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1317.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1318.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1318.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1318.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1318.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1322.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1322.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1322.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1322.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1325.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1325.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1325.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1325.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1326.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1326.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1326.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1326.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1327.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1327.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1327.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1327.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1329.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1329.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1329.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1329.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1606_172x72.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1606_172x72.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1606_172x72.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1606_172x72.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1607_200x200.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1607_200x200.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1607_200x200.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_ssd1607_200x200.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7511.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7511.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7511.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7511.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st75256.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st75256.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st75256.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st75256.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7565.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7565.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7565.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7565.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7567.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7567.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7567.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7567.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_erc240160.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_erc240160.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_erc240160.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_erc240160.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_s028hn118a.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_s028hn118a.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_s028hn118a.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7586s_s028hn118a.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7588.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7588.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7588.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7588.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7920.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7920.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7920.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_st7920.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_stdio.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_stdio.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_stdio.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_stdio.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_t6963.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_t6963.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_t6963.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_t6963.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1601.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1601.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1601.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1601.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1604.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1604.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1604.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1604.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1608.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1608.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1608.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1608.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1610.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1610.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1610.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1610.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1611.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1611.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1611.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1611.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1617.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1617.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1617.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1617.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1638.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1638.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1638.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1638.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_dogs102.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_dogs102.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_dogs102.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_dogs102.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_mini12864.o: hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_mini12864.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_mini12864.o hwControl/device_drivers/api/gfx_u8g/u8x8_d_uc1701_mini12864.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_debounce.o: hwControl/device_drivers/api/gfx_u8g/u8x8_debounce.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_debounce.o hwControl/device_drivers/api/gfx_u8g/u8x8_debounce.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_display.o: hwControl/device_drivers/api/gfx_u8g/u8x8_display.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_display.o hwControl/device_drivers/api/gfx_u8g/u8x8_display.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_fonts.o: hwControl/device_drivers/api/gfx_u8g/u8x8_fonts.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_fonts.o hwControl/device_drivers/api/gfx_u8g/u8x8_fonts.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_gpio.o: hwControl/device_drivers/api/gfx_u8g/u8x8_gpio.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_gpio.o hwControl/device_drivers/api/gfx_u8g/u8x8_gpio.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_input_value.o: hwControl/device_drivers/api/gfx_u8g/u8x8_input_value.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_input_value.o hwControl/device_drivers/api/gfx_u8g/u8x8_input_value.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_message.o: hwControl/device_drivers/api/gfx_u8g/u8x8_message.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_message.o hwControl/device_drivers/api/gfx_u8g/u8x8_message.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_selection_list.o: hwControl/device_drivers/api/gfx_u8g/u8x8_selection_list.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_selection_list.o hwControl/device_drivers/api/gfx_u8g/u8x8_selection_list.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_setup.o: hwControl/device_drivers/api/gfx_u8g/u8x8_setup.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_setup.o hwControl/device_drivers/api/gfx_u8g/u8x8_setup.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_string.o: hwControl/device_drivers/api/gfx_u8g/u8x8_string.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_string.o hwControl/device_drivers/api/gfx_u8g/u8x8_string.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u16toa.o: hwControl/device_drivers/api/gfx_u8g/u8x8_u16toa.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u16toa.o hwControl/device_drivers/api/gfx_u8g/u8x8_u16toa.c

${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u8toa.o: hwControl/device_drivers/api/gfx_u8g/u8x8_u8toa.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/gfx_u8g/u8x8_u8toa.o hwControl/device_drivers/api/gfx_u8g/u8x8_u8toa.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_api.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api.o hwControl/device_drivers/api/vl53l0x/vl53l0x_api.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_calibration.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_api_calibration.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_calibration.o hwControl/device_drivers/api/vl53l0x/vl53l0x_api_calibration.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_core.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_api_core.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_core.o hwControl/device_drivers/api/vl53l0x/vl53l0x_api_core.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_ranging.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_api_ranging.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_ranging.o hwControl/device_drivers/api/vl53l0x/vl53l0x_api_ranging.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_strings.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_api_strings.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_api_strings.o hwControl/device_drivers/api/vl53l0x/vl53l0x_api_strings.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_i2c_platform.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_i2c_platform.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_i2c_platform.o hwControl/device_drivers/api/vl53l0x/vl53l0x_i2c_platform.c

${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_platform.o: hwControl/device_drivers/api/vl53l0x/vl53l0x_platform.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/api/vl53l0x/vl53l0x_platform.o hwControl/device_drivers/api/vl53l0x/vl53l0x_platform.c

${OBJECTDIR}/hwControl/device_drivers/bh1745.o: hwControl/device_drivers/bh1745.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/bh1745.o hwControl/device_drivers/bh1745.c

${OBJECTDIR}/hwControl/device_drivers/display_mono.o: hwControl/device_drivers/display_mono.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/display_mono.o hwControl/device_drivers/display_mono.c

${OBJECTDIR}/hwControl/device_drivers/efm8_mcu_kehops.o: hwControl/device_drivers/efm8_mcu_kehops.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/efm8_mcu_kehops.o hwControl/device_drivers/efm8_mcu_kehops.c

${OBJECTDIR}/hwControl/device_drivers/k_vl53l0x.o: hwControl/device_drivers/k_vl53l0x.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/k_vl53l0x.o hwControl/device_drivers/k_vl53l0x.c

${OBJECTDIR}/hwControl/device_drivers/mcp230xx.o: hwControl/device_drivers/mcp230xx.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/mcp230xx.o hwControl/device_drivers/mcp230xx.c

${OBJECTDIR}/hwControl/device_drivers/mcp4725.o: hwControl/device_drivers/mcp4725.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/mcp4725.o hwControl/device_drivers/mcp4725.c

${OBJECTDIR}/hwControl/device_drivers/mcp4728.o: hwControl/device_drivers/mcp4728.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/mcp4728.o hwControl/device_drivers/mcp4728.c

${OBJECTDIR}/hwControl/device_drivers/pca9629.o: hwControl/device_drivers/pca9629.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/pca9629.o hwControl/device_drivers/pca9629.c

${OBJECTDIR}/hwControl/device_drivers/pca9685.o: hwControl/device_drivers/pca9685.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/pca9685.o hwControl/device_drivers/pca9685.c

${OBJECTDIR}/hwControl/device_drivers/tca9548a.o: hwControl/device_drivers/tca9548a.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/device_drivers
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/device_drivers/tca9548a.o hwControl/device_drivers/tca9548a.c

${OBJECTDIR}/hwControl/hardwareDrivers.o: hwControl/hardwareDrivers.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/hardwareDrivers.o hwControl/hardwareDrivers.c

${OBJECTDIR}/hwControl/hwManager.o: hwControl/hwManager.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/hwManager.o hwControl/hwManager.c

${OBJECTDIR}/hwControl/libs/i2c/onion-i2c.o: hwControl/libs/i2c/onion-i2c.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/libs/i2c
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/libs/i2c/onion-i2c.o hwControl/libs/i2c/onion-i2c.c

${OBJECTDIR}/hwControl/libs/onion-debug/onion-debug.o: hwControl/libs/onion-debug/onion-debug.c
	${MKDIR} -p ${OBJECTDIR}/hwControl/libs/onion-debug
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/libs/onion-debug/onion-debug.o hwControl/libs/onion-debug/onion-debug.c

${OBJECTDIR}/hwControl/networkManager.o: hwControl/networkManager.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/networkManager.o hwControl/networkManager.c

${OBJECTDIR}/hwControl/wifi_json.o: hwControl/wifi_json.c
	${MKDIR} -p ${OBJECTDIR}/hwControl
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/hwControl/wifi_json.o hwControl/wifi_json.c

${OBJECTDIR}/kehopsCom/libs/lib_json/jRead.o: kehopsCom/libs/lib_json/jRead.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_json
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_json/jRead.o kehopsCom/libs/lib_json/jRead.c

${OBJECTDIR}/kehopsCom/libs/lib_json/jWrite.o: kehopsCom/libs/lib_json/jWrite.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_json
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_json/jWrite.o kehopsCom/libs/lib_json/jWrite.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Clients.o: kehopsCom/libs/lib_mqtt/Clients.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Clients.o kehopsCom/libs/lib_mqtt/Clients.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Heap.o: kehopsCom/libs/lib_mqtt/Heap.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Heap.o kehopsCom/libs/lib_mqtt/Heap.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/LinkedList.o: kehopsCom/libs/lib_mqtt/LinkedList.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/LinkedList.o kehopsCom/libs/lib_mqtt/LinkedList.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Log.o: kehopsCom/libs/lib_mqtt/Log.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Log.o kehopsCom/libs/lib_mqtt/Log.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTClient.o: kehopsCom/libs/lib_mqtt/MQTTClient.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTClient.o kehopsCom/libs/lib_mqtt/MQTTClient.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacket.o: kehopsCom/libs/lib_mqtt/MQTTPacket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacket.o kehopsCom/libs/lib_mqtt/MQTTPacket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacketOut.o: kehopsCom/libs/lib_mqtt/MQTTPacketOut.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPacketOut.o kehopsCom/libs/lib_mqtt/MQTTPacketOut.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistence.o: kehopsCom/libs/lib_mqtt/MQTTPersistence.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistence.o kehopsCom/libs/lib_mqtt/MQTTPersistence.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.o: kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.o kehopsCom/libs/lib_mqtt/MQTTPersistenceDefault.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolClient.o: kehopsCom/libs/lib_mqtt/MQTTProtocolClient.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolClient.o kehopsCom/libs/lib_mqtt/MQTTProtocolClient.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolOut.o: kehopsCom/libs/lib_mqtt/MQTTProtocolOut.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/MQTTProtocolOut.o kehopsCom/libs/lib_mqtt/MQTTProtocolOut.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Messages.o: kehopsCom/libs/lib_mqtt/Messages.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Messages.o kehopsCom/libs/lib_mqtt/Messages.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SSLSocket.o: kehopsCom/libs/lib_mqtt/SSLSocket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SSLSocket.o kehopsCom/libs/lib_mqtt/SSLSocket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Socket.o: kehopsCom/libs/lib_mqtt/Socket.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Socket.o kehopsCom/libs/lib_mqtt/Socket.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SocketBuffer.o: kehopsCom/libs/lib_mqtt/SocketBuffer.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/SocketBuffer.o kehopsCom/libs/lib_mqtt/SocketBuffer.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/StackTrace.o: kehopsCom/libs/lib_mqtt/StackTrace.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/StackTrace.o kehopsCom/libs/lib_mqtt/StackTrace.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Thread.o: kehopsCom/libs/lib_mqtt/Thread.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Thread.o kehopsCom/libs/lib_mqtt/Thread.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Tree.o: kehopsCom/libs/lib_mqtt/Tree.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/Tree.o kehopsCom/libs/lib_mqtt/Tree.c

${OBJECTDIR}/kehopsCom/libs/lib_mqtt/utf-8.o: kehopsCom/libs/lib_mqtt/utf-8.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom/libs/lib_mqtt
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/libs/lib_mqtt/utf-8.o kehopsCom/libs/lib_mqtt/utf-8.c

${OBJECTDIR}/kehopsCom/linux_JSON.o: kehopsCom/linux_JSON.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/linux_JSON.o kehopsCom/linux_JSON.c

${OBJECTDIR}/kehopsCom/messagesManager.o: kehopsCom/messagesManager.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/messagesManager.o kehopsCom/messagesManager.c

${OBJECTDIR}/kehopsCom/mqttProtocol.o: kehopsCom/mqttProtocol.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/mqttProtocol.o kehopsCom/mqttProtocol.c

${OBJECTDIR}/kehopsCom/udpPublish.o: kehopsCom/udpPublish.c
	${MKDIR} -p ${OBJECTDIR}/kehopsCom
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehopsCom/udpPublish.o kehopsCom/udpPublish.c

${OBJECTDIR}/kehops_main.o: kehops_main.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/kehops_main.o kehops_main.c

${OBJECTDIR}/timerManager.o: timerManager.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/timerManager.o timerManager.c

${OBJECTDIR}/tools.o: tools.c
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -IhwControl/libs/i2c -IhwControl/libs/onion-debug -IhwControl -Iactuators -IkehopsCom -IkehopsCom/libs/lib_json -IkehopsCom/libs/lib_mqtt -IhwControl/device_drivers -include buildNumber.h -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/tools.o tools.c

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
