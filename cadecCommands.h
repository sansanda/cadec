#ifndef CADECCOMMANDS_H
#define CADECCOMMANDS_H

#include "QCoreApplication"


//Help and info
const QString PRINTSETUP_CMD = "printsetup";

//Keithley k24xx series operation modes
const QString SWEEPVOLTAGE_CMD = "sweepvoltage";
const QString SWEEPCURRENT_CMD = "sweepcurrent";
const QString PULSEDSWEEPVOLTAGE_CMD = "pulsedsweepvoltage";
const QString PULSEDSWEEPCURRENT_CMD = "pulsedsweepcurrent";
const QString STEPCURRENT_CMD = "stepcurrent";
const QString STEPVOLTAGE_CMD = "stepvoltage";
const QString BIASCURRENT_CMD = "biascurrent";
const QString BIASVOLTAGE_CMD = "biasvoltage";
const QString VOLTMETER_CMD   = "voltmeter";
const QString AMMETER_CMD     = "ammeter";

//SweepVoltage, PulsedSweepVoltage, StepVoltage Setup configuration
const QString STARTVOLTAGE_CMD = "startvoltage";
const QString STOPVOLTAGE_CMD = "stopvoltage";
const QString NUMBEROFPOINTS_CMD = "numberofpoints";



//Measure procress
const QString STARTMEASURE_CMD =    "startmeasure";
const QString STOPMEASURE_CMD =     "stopmeasure";
const QString ENABLEREARMODE_CMD =  "rear";
const QString ENABLEGUARD_CMD =     "guard";
const QString ENABLEFRONTMODE_CMD = "front";
const QString DISABLEGUARD_CMD =    "noguard";


//Measurement speed
const QString SETNPLC_CMD =    "setnplc";




//Instrument selection
const QString cd2400_CMD = "2400";
const QString cd2410_CMD = "2410";
const QString cd2420_CMD = "2420";
const QString cd2425_CMD = "2425";
const QString cd2430_CMD = "2430";
const QString cd2440_CMD = "2440";
const QString cdS200_CMD = "S200";
const QString cdAWP1050_CMD = "AWP1050";

//GPIB Configuration
const QString CONFIGGPIB = "configGPIB";
const QString SETGPIBADDRESS = "setGPIBAddr";




//Debug
const QString try_CMD = "try";
const QString send_CMD = "send";


#endif // CADECCOMMANDS_H
