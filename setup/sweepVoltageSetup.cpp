#include "sweepVoltageSetup.h"

SweepVoltageSetup::SweepVoltageSetup(QString* _name):Setup(_name)
{
    resetSetup();
}

SweepVoltageSetup::SweepVoltageSetup():Setup()
{
    resetSetup();
}

SweepVoltageSetup::~SweepVoltageSetup(){}

int SweepVoltageSetup::resetSetup(){
    int result = 0;
    startVoltage    = 0;    //In volts
    stopVoltage     = 10;   //In volts
    numberOfPoints  = NUMBER_OF_POINTS_PER_SWEEP_DEFAULT;    //
    sweepType       = 0;    //0 --> linear, 1 --> logarithmic
    compliance      = 0.001;//In Amps
    sweepDelay      = 100;  //In ms

    //Measure

    readBackVoltage = true;
    measureCurrent  = true;
    collectTimeStamps = false;
    voltageName     = "Voltage";
    currentName     = "Current";
    measurementRange =  4;  //0 --> auto, 1 --> 1A, 2 --> 100mA, 3 --> 10mA, 4 --> 1mA, 5 --> 100uA, 6 --> 10uA, 7 --> 1uA
    nplc            =   NPLC_FOR2430_DEFAULT;  //0.01, 0.1 (default), 1, 10
    filterType      =   0;  //0 --> No Filter, 1 --> Repeat
    filterCount     =   2;  //

    //Advanced

    fourWireMeasurementMode = false;    //

    //SMU Auto Zero Modes
    //AZERO_ALWAYS  0
    //AZERO_ONCE  1
    //AZERO_OFF  2

    smuAutoZeroMode         = AZERO_ALWAYS;        //0 --> off, 1 --> once, 2 --> always
    smuOffMode              = 0;        //0 --> normal, 1 --> highZ, 2 --> zero, 3 --> guard
    return result;
}

QDomElement SweepVoltageSetup::toQDomElement(){

    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("SweepVoltageSetup");
    doc.appendChild(root);

    /*QDomElement nameTag = doc.createElement("name");
    root.appendChild(nameTag);

    QDomText nameText = doc.createTextNode(*getName());
    nameTag.appendChild(nameText);

    QDomElement idnTag = doc.createElement("idn");
    root.appendChild(idnTag);

    QDomText idnText = doc.createTextNode(*getIDN());
    idnTag.appendChild(idnText);

    QDomElement refTag = doc.createElement("reference");
    root.appendChild(refTag);

    QDomText refText = doc.createTextNode(*getReference());
    refTag.appendChild(refText);

    QDomElement manufactTag = doc.createElement("manufacturer");
    root.appendChild(manufactTag);

    QDomText manufactText = doc.createTextNode(*getManufacturer());
    manufactTag.appendChild(manufactText);

    QDomElement obsTag = doc.createElement("obsevations");
    root.appendChild(obsTag);

    QDomText obsText = doc.createTextNode(*getObs());
    obsTag.appendChild(obsText);*/

    return root;
}

