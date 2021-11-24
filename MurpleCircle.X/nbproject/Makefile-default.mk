#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS

else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/RC_Servo.c C:/ECE118/src/pwm.c C:/ECE118/src/serial.c EventCheckers.c FindNewCornerSub.c OrientBotSub.c robot.c TopLevel.c ScanForBeaconSub.c timers.c PingService.c TemplateES_Main.c TapeService.c BumperService.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/EventCheckers.o ${OBJECTDIR}/FindNewCornerSub.o ${OBJECTDIR}/OrientBotSub.o ${OBJECTDIR}/robot.o ${OBJECTDIR}/TopLevel.o ${OBJECTDIR}/ScanForBeaconSub.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/PingService.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/TapeService.o ${OBJECTDIR}/BumperService.o
POSSIBLE_DEPFILES=${OBJECTDIR}/_ext/1975241074/AD.o.d ${OBJECTDIR}/_ext/1975241074/BOARD.o.d ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d ${OBJECTDIR}/_ext/1975241074/LED.o.d ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d ${OBJECTDIR}/_ext/1975241074/pwm.o.d ${OBJECTDIR}/_ext/1975241074/serial.o.d ${OBJECTDIR}/EventCheckers.o.d ${OBJECTDIR}/FindNewCornerSub.o.d ${OBJECTDIR}/OrientBotSub.o.d ${OBJECTDIR}/robot.o.d ${OBJECTDIR}/TopLevel.o.d ${OBJECTDIR}/ScanForBeaconSub.o.d ${OBJECTDIR}/timers.o.d ${OBJECTDIR}/PingService.o.d ${OBJECTDIR}/TemplateES_Main.o.d ${OBJECTDIR}/TapeService.o.d ${OBJECTDIR}/BumperService.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/_ext/1975241074/AD.o ${OBJECTDIR}/_ext/1975241074/BOARD.o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o ${OBJECTDIR}/_ext/1975241074/LED.o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o ${OBJECTDIR}/_ext/1975241074/pwm.o ${OBJECTDIR}/_ext/1975241074/serial.o ${OBJECTDIR}/EventCheckers.o ${OBJECTDIR}/FindNewCornerSub.o ${OBJECTDIR}/OrientBotSub.o ${OBJECTDIR}/robot.o ${OBJECTDIR}/TopLevel.o ${OBJECTDIR}/ScanForBeaconSub.o ${OBJECTDIR}/timers.o ${OBJECTDIR}/PingService.o ${OBJECTDIR}/TemplateES_Main.o ${OBJECTDIR}/TapeService.o ${OBJECTDIR}/BumperService.o

# Source Files
SOURCEFILES=C:/ECE118/src/AD.c C:/ECE118/src/BOARD.c C:/ECE118/src/ES_CheckEvents.c C:/ECE118/src/ES_Framework.c C:/ECE118/src/ES_KeyboardInput.c C:/ECE118/src/ES_PostList.c C:/ECE118/src/ES_Queue.c C:/ECE118/src/ES_TattleTale.c C:/ECE118/src/ES_Timers.c C:/ECE118/src/IO_Ports.c C:/ECE118/src/LED.c C:/ECE118/src/RC_Servo.c C:/ECE118/src/pwm.c C:/ECE118/src/serial.c EventCheckers.c FindNewCornerSub.c OrientBotSub.c robot.c TopLevel.c ScanForBeaconSub.c timers.c PingService.c TemplateES_Main.c TapeService.c BumperService.c



CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=32MX320F128H
MP_LINKER_FILE_OPTION=,--script="C:\ECE118\bootloader320.ld"
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assembleWithPreprocess
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/8612ecf44b39b7ba1875a9183bc98789d5f2608b .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/dc3f4d7d6fb85b350b30ecbcba0b569d989133c6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/aa112750621593ee67ee7af9bd8900de4c4ccf37 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/d3a536bd84445f5d20a5ecb904c8334e95fa95a3 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/f5babe262a8ef2065224bfe89b39d8dab964f7e2 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/36e44c246d84f67390ad30f8290443cdb15670ce .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/414c3c19cfe2621189ceea97c274b722922097a7 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/d32ffca56bd40e283011003dbfba9804a8a86af4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/df976be49e0652f77c7f0d36bd0851542f6dc2ff .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/682f6cbd87afc70e5cf03fb8d5b82f9eb65e10a4 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/1a4f0c37cb71c2226e59e11f46a95a675b8e0656 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/RC_Servo.o: C:/ECE118/src/RC_Servo.c  .generated_files/flags/default/4fd3ab235149e4fcf01d4aea8ea9d9a5da9225f6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o C:/ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/32ee17762f262550904c7e46cf3ed5cc4d1b4c9a .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/3fd607cb2ba4af8f7484965295202be1f89496c .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EventCheckers.o: EventCheckers.c  .generated_files/flags/default/abc33dd37808930c1e131674a8756bd19b0771e2 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/EventCheckers.o.d" -o ${OBJECTDIR}/EventCheckers.o EventCheckers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FindNewCornerSub.o: FindNewCornerSub.c  .generated_files/flags/default/e24107409e1f8673ef93f6848788441c0c764146 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindNewCornerSub.o.d 
	@${RM} ${OBJECTDIR}/FindNewCornerSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/FindNewCornerSub.o.d" -o ${OBJECTDIR}/FindNewCornerSub.o FindNewCornerSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OrientBotSub.o: OrientBotSub.c  .generated_files/flags/default/43c1925aaa98418ac8ef8f3cd57c1546378a74b1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OrientBotSub.o.d 
	@${RM} ${OBJECTDIR}/OrientBotSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/OrientBotSub.o.d" -o ${OBJECTDIR}/OrientBotSub.o OrientBotSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/robot.o: robot.c  .generated_files/flags/default/e5830f87fd917a57d6097f49fbd2b822145f786e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robot.o.d 
	@${RM} ${OBJECTDIR}/robot.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/robot.o.d" -o ${OBJECTDIR}/robot.o robot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TopLevel.o: TopLevel.c  .generated_files/flags/default/b7236258bf05f6f9b4edc622a3ec6cd769506962 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopLevel.o.d 
	@${RM} ${OBJECTDIR}/TopLevel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TopLevel.o.d" -o ${OBJECTDIR}/TopLevel.o TopLevel.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ScanForBeaconSub.o: ScanForBeaconSub.c  .generated_files/flags/default/708dc804cc269c095bc21b425da9785d82eb8bba .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ScanForBeaconSub.o.d 
	@${RM} ${OBJECTDIR}/ScanForBeaconSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/ScanForBeaconSub.o.d" -o ${OBJECTDIR}/ScanForBeaconSub.o ScanForBeaconSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timers.o: timers.c  .generated_files/flags/default/c688298c2c00ceac822436f5f7cd7b4f18a3ce4d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${RM} ${OBJECTDIR}/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PingService.o: PingService.c  .generated_files/flags/default/98854206a282b94ea174f4b49ec964cc04a53ae9 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PingService.o.d 
	@${RM} ${OBJECTDIR}/PingService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/PingService.o.d" -o ${OBJECTDIR}/PingService.o PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  .generated_files/flags/default/5b38d4c01c9c9648db35b66b7e5d423df42dbda6 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeService.o: TapeService.c  .generated_files/flags/default/4a9cd6291a840588bf864cf12b122dd63cedd013 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeService.o.d 
	@${RM} ${OBJECTDIR}/TapeService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeService.o.d" -o ${OBJECTDIR}/TapeService.o TapeService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BumperService.o: BumperService.c  .generated_files/flags/default/c7ce4e495da16b764fd2f61f035449f215984400 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE) -g -D__DEBUG   -fframe-base-loclist  -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
else
${OBJECTDIR}/_ext/1975241074/AD.o: C:/ECE118/src/AD.c  .generated_files/flags/default/e57974dcc2db2aa35623870ed6983d1114da392d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/AD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/AD.o.d" -o ${OBJECTDIR}/_ext/1975241074/AD.o C:/ECE118/src/AD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/BOARD.o: C:/ECE118/src/BOARD.c  .generated_files/flags/default/9a5ed5238a2159b6b73c73ac30f9a436f52653a5 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/BOARD.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/BOARD.o.d" -o ${OBJECTDIR}/_ext/1975241074/BOARD.o C:/ECE118/src/BOARD.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o: C:/ECE118/src/ES_CheckEvents.c  .generated_files/flags/default/c20ecbb4889ee883d9a487aafe5f230410e3ed7d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_CheckEvents.o C:/ECE118/src/ES_CheckEvents.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Framework.o: C:/ECE118/src/ES_Framework.c  .generated_files/flags/default/86a6c7ac99148ef83fd8c02baaf734382bd8fccb .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Framework.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Framework.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Framework.o C:/ECE118/src/ES_Framework.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o: C:/ECE118/src/ES_KeyboardInput.c  .generated_files/flags/default/fca474eab80c3f20f984af23a1e7e01c4b26da68 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_KeyboardInput.o C:/ECE118/src/ES_KeyboardInput.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_PostList.o: C:/ECE118/src/ES_PostList.c  .generated_files/flags/default/b8e45022e393418c91d6a49f769781f9f169651d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_PostList.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_PostList.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_PostList.o C:/ECE118/src/ES_PostList.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Queue.o: C:/ECE118/src/ES_Queue.c  .generated_files/flags/default/bb4b51642433fa362edb7a6fc5802fbf5536c5d2 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Queue.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Queue.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Queue.o C:/ECE118/src/ES_Queue.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o: C:/ECE118/src/ES_TattleTale.c  .generated_files/flags/default/936f7fbd74f3a89fb14ec135b1c57f07cc677897 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_TattleTale.o C:/ECE118/src/ES_TattleTale.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/ES_Timers.o: C:/ECE118/src/ES_Timers.c  .generated_files/flags/default/a7f4b6d312b00c4d7a46766add67cead235316b0 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/ES_Timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/ES_Timers.o.d" -o ${OBJECTDIR}/_ext/1975241074/ES_Timers.o C:/ECE118/src/ES_Timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/IO_Ports.o: C:/ECE118/src/IO_Ports.c  .generated_files/flags/default/a2a56a400a1ef857a9a02beb0fa01ee419165544 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/IO_Ports.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/IO_Ports.o.d" -o ${OBJECTDIR}/_ext/1975241074/IO_Ports.o C:/ECE118/src/IO_Ports.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/LED.o: C:/ECE118/src/LED.c  .generated_files/flags/default/5459bf344632011c89eaf810d611f7e274938f59 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/LED.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/LED.o.d" -o ${OBJECTDIR}/_ext/1975241074/LED.o C:/ECE118/src/LED.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/RC_Servo.o: C:/ECE118/src/RC_Servo.c  .generated_files/flags/default/844fb747a2c543ca610fe0062f9f0ec359b9ea45 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/RC_Servo.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/RC_Servo.o.d" -o ${OBJECTDIR}/_ext/1975241074/RC_Servo.o C:/ECE118/src/RC_Servo.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/pwm.o: C:/ECE118/src/pwm.c  .generated_files/flags/default/c29afc6abe6c1e6fbc70e7ac4b4b4b0092bfbe29 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/pwm.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/pwm.o.d" -o ${OBJECTDIR}/_ext/1975241074/pwm.o C:/ECE118/src/pwm.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/_ext/1975241074/serial.o: C:/ECE118/src/serial.c  .generated_files/flags/default/340789a9f169035b5696d0976f21681cbdb487cb .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}/_ext/1975241074" 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o.d 
	@${RM} ${OBJECTDIR}/_ext/1975241074/serial.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/_ext/1975241074/serial.o.d" -o ${OBJECTDIR}/_ext/1975241074/serial.o C:/ECE118/src/serial.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/EventCheckers.o: EventCheckers.c  .generated_files/flags/default/9e263a8d304a8ea9a3ebf743616dbea0a8b807e1 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/EventCheckers.o.d 
	@${RM} ${OBJECTDIR}/EventCheckers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/EventCheckers.o.d" -o ${OBJECTDIR}/EventCheckers.o EventCheckers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/FindNewCornerSub.o: FindNewCornerSub.c  .generated_files/flags/default/cf6b602b430f8a68bc985ceabb5d385b87bcafed .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/FindNewCornerSub.o.d 
	@${RM} ${OBJECTDIR}/FindNewCornerSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/FindNewCornerSub.o.d" -o ${OBJECTDIR}/FindNewCornerSub.o FindNewCornerSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/OrientBotSub.o: OrientBotSub.c  .generated_files/flags/default/d87112de413e68cb7daa6b5e839dbde5698405a7 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/OrientBotSub.o.d 
	@${RM} ${OBJECTDIR}/OrientBotSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/OrientBotSub.o.d" -o ${OBJECTDIR}/OrientBotSub.o OrientBotSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/robot.o: robot.c  .generated_files/flags/default/21ef51d23517b83a04432eaae5a190ee0da68319 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/robot.o.d 
	@${RM} ${OBJECTDIR}/robot.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/robot.o.d" -o ${OBJECTDIR}/robot.o robot.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TopLevel.o: TopLevel.c  .generated_files/flags/default/1d480aa40c930e40720f7fd9491bba7285f9124 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TopLevel.o.d 
	@${RM} ${OBJECTDIR}/TopLevel.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TopLevel.o.d" -o ${OBJECTDIR}/TopLevel.o TopLevel.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/ScanForBeaconSub.o: ScanForBeaconSub.c  .generated_files/flags/default/4caacdbcb5079e2613575526a936b23bd3d1fa9d .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/ScanForBeaconSub.o.d 
	@${RM} ${OBJECTDIR}/ScanForBeaconSub.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/ScanForBeaconSub.o.d" -o ${OBJECTDIR}/ScanForBeaconSub.o ScanForBeaconSub.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/timers.o: timers.c  .generated_files/flags/default/698b065c84497a2b070377b6f566deb3c937177e .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/timers.o.d 
	@${RM} ${OBJECTDIR}/timers.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/timers.o.d" -o ${OBJECTDIR}/timers.o timers.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/PingService.o: PingService.c  .generated_files/flags/default/36f553ca6aa75ee21066fd3eaff0574133ed9f17 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/PingService.o.d 
	@${RM} ${OBJECTDIR}/PingService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/PingService.o.d" -o ${OBJECTDIR}/PingService.o PingService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TemplateES_Main.o: TemplateES_Main.c  .generated_files/flags/default/f9b6451dc0fb66f1d3aa6976235f49c5a6d59f .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o.d 
	@${RM} ${OBJECTDIR}/TemplateES_Main.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TemplateES_Main.o.d" -o ${OBJECTDIR}/TemplateES_Main.o TemplateES_Main.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/TapeService.o: TapeService.c  .generated_files/flags/default/ccf1712a2a69d110420841344c4ba55da9e9fc56 .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/TapeService.o.d 
	@${RM} ${OBJECTDIR}/TapeService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/TapeService.o.d" -o ${OBJECTDIR}/TapeService.o TapeService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
${OBJECTDIR}/BumperService.o: BumperService.c  .generated_files/flags/default/50a4e4ca50821f8a12c3b9bbc360736d6d4e11cc .generated_files/flags/default/25cf332145e109ecc94cb8c88ed46e464b66686
	@${MKDIR} "${OBJECTDIR}" 
	@${RM} ${OBJECTDIR}/BumperService.o.d 
	@${RM} ${OBJECTDIR}/BumperService.o 
	${MP_CC}  $(MP_EXTRA_CC_PRE)  -g -x c -c -mprocessor=$(MP_PROCESSOR_OPTION)  -fno-common -I"." -I"C:/ECE118/include" -MP -MMD -MF "${OBJECTDIR}/BumperService.o.d" -o ${OBJECTDIR}/BumperService.o BumperService.c    -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -mdfp="${DFP_DIR}"  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compileCPP
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    C:/ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) -g   -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)      -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,-D=__DEBUG_D,--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   C:/ECE118/bootloader320.ld
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -mprocessor=$(MP_PROCESSOR_OPTION)  -o dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} ${OBJECTFILES_QUOTED_IF_SPACED}          -DXPRJ_default=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,--defsym=__MPLAB_BUILD=1$(MP_EXTRA_LD_POST)$(MP_LINKER_FILE_OPTION),--no-code-in-dinit,--no-dinit-in-serial-mem,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -mdfp="${DFP_DIR}"
	${MP_CC_DIR}\\xc32-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/MurpleCircle.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} 
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
