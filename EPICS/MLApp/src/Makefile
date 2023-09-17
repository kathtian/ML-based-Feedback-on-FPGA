TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

PROD_IOC = ML
# ML.dbd will be created and installed
DBD += ML.dbd

# ML.dbd will be made up from these files:
ML_DBD += base.dbd
ML_DBD += pscCore.dbd
#ML_DBD += pscdrv.dbd
ML_DBD += aSubOperation.dbd

# Add all the support libraries needed by this IOC
#ML_LIBS += xxx

# ML_registerRecordDeviceDriver.cpp derives from ML.dbd
ML_SRCS += ML_registerRecordDeviceDriver.cpp

ML_SRCS += aSubOperation.c

#ML_SRCS += psc.cpp
#ML_SRCS += pscwrap.cpp
#ML_SRCS += devcommon.cpp
#ML_SRCS += devPSCString.cpp
#ML_SRCS += devPSCWf.cpp
#ML_SRCS += devPSCReg.cpp
#ML_SRCS += devPSCCtrl.cpp

ML_SRCS += aSubOperations.c

# Build the main IOC entry point on workstation OSs.
ML_SRCS_DEFAULT += pscMain.cpp
ML_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#ML_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary
ML_LIBS += pscCore

# Finally link to the EPICS Base libraries
ML_LIBS += $(EPICS_BASE_IOC_LIBS)

ML_SYS_LIBS += event_core event_extra

ifeq ($(POSIX),YES)
ML_SYS_LIBS += event_pthreads
endif

ifneq ($(LIBEVENT),)
LDFLAGS += -L$(LIBEVENT)/lib
CPPFLAGS += -I$(LIBEVENT)/include
endif

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

