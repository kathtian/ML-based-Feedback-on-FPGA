#!./bin/linux-x86_64/ML

epicsThreadSleep 1

epicsEnvSet("EPICS_CA_MAX_ARRAY_BYTES","300000000")

< envPaths

dbLoadDatabase("./dbd/ML.dbd",0,0)
ML_registerRecordDeviceDriver(pdbbase)

dbLoadRecords("./db/Command.db","PriSys=ML,DEV=Unit1")
dbLoadRecords("./db/CommandReg.db","PriSys=ML,DEV=Unit1")
dbLoadRecords("./db/ADC.db","PriSys=ML,DEV=Unit1")
dbLoadRecords("./db/User.db","PriSys=ML,DEV=Unit1")
dbLoadRecords("./db/MatrixCoef.db","PriSys=ML,DEV=Unit1")

createPSC("CmdPort_Unit1", "192.168.86.10", 7,0)
setPSCSendBlockSize("CmdPort_Unit1", 80, 256)
iocInit()

