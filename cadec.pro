#-------------------------------------------------
#
# Project created by QtCreator 2015-05-08T02:38:00
#
#-------------------------------------------------

QT       += core

QT       -= gui
QT       += xml
QT       += testlib

TARGET = cadec
CONFIG   += console
CONFIG   -= app_bundle

# GPIB driver selection
# Uncomment proper driver selection
# Comment both for test mode only
CONFIG += adlink_usb
# CONFIG += ni_pci

TEMPLATE = app


SOURCES += main.cpp \
    cadec.cpp \
    gpib/gpib.cpp \
    gpib/scpi.cpp \
    setup/instrumentSetup.cpp \
    setup/setup.cpp \
    setup/sweepVoltageSetup.cpp\
    instrument/instrument.cpp\
    instrument/keithley/keithleyK24xx.cpp \
    setup/keithleyK24xxSetup.cpp \
    instrument/keithley/keithleyK2400.cpp \
    instrument/keithley/keithleyK2410.cpp \
    instrument/keithley/keithleyK2420.cpp \
    instrument/keithley/keithleyK2425.cpp \
    instrument/keithley/keithleyK2430.cpp \
    instrument/keithley/keithleyK2440.cpp \
    communications/serialCommunications/lan/lanport.cpp \
    communications/parallelCommunications/gpib/gpibPort.cpp \
    communications/serialCommunications/usb/usbport.cpp \
    communications/serialCommunications/rs232/rs232.cpp \
    gpib/SCPICommandFactory.cpp \
    instrument/quadTech/Q7600.cpp \
    instrument/wentworth/wentworthS200.cpp \
    setup/wentworthInstrumentsSetups/wentworthSXXXSetup.cpp


HEADERS += \
    cadec.h \
    gpib/gpib_user.h \
    gpib/gpib.h \
    gpib/Adgpib.h \
    gpib/scpi.h \
    gpib/ni488.h \
    setup/instrumentSetup.h \
    setup/setup.h \
    setup/sweepVoltageSetup.h\
    instrument/gpibInstrument.h\
    instrument/instrument.h\
    instrument/usbInstrument.h \
    K24xxConfigurationParameters.h \
    instrument/keithley/keithleyK24xx.h \
    setup/keithleyK24xxSetup.h \
    instrument/keithley/keithleyK2400.h \
    instrument/keithley/keithleyK2410.h \
    instrument/keithley/keithleyK2420.h \
    instrument/keithley/keithleyK2425.h \
    instrument/keithley/keithleyK2430.h \
    instrument/keithley/keithleyK2440.h \
    communications/communicationPort.h \
    communications/parallelCommunications/gpib/gpibPort.h \
    communications/serialCommunications/lan/lanport.h \
    communications/serialCommunications/usb/usbport.h \
    communications/serialCommunications/serialport.h \
    communications/parallelCommunications/parallelport.h \
    communications/serialCommunications/rs232/rs232.h \
    cadecCommands.h \
    commandExecutionResult_Codes.h \
    gpib/SCPICommandFactory.h \
    maths/converters/numericalDataFormatConverter.h \
    instrument/keithley/keithleyTools.h \
    genericTools/bufferTools.h \
    maths/dataFormat/floatingPointTools.h \
    debug.h \
    instrument/quadTech/Q7600.h \
    instrument/wentworth/wentworthS200.h \
    setup/wentworthInstrumentsSetups/wentworthSXXXSetup.h \
    wentworthS200ConfigurationParameters.h


OTHER_FILES += \ gpib/gpib-32.obj

adlink_usb{
    # Driver's library setting
    CONFIG += ADLINK_USB_GPIB
    # Driver's includes
    DEFINES += AD_GPIB
}

win32:ADLINK_USB_GPIB {
    LIBS += $$quote(C:/ADLINK/ADL-GPIB/Lib/gpib-32.dll)
    LIBS += $$quote(C:/ADLINK/ADL-GPIB/Lib/gpib-32.lib)
}

win32:NI_PCI_GPIB {
    LIBS += gpib/gpib-32.obj
}

