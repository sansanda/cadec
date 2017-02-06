#include "setup/keithleyK24xxSetup.h"

KeithleyK24XXSetup::KeithleyK24XXSetup(QString* _name, QString* _obs):InstrumentSetup(_name,_obs)
{
    sweepVoltageSetup = new SweepVoltageSetup(_name);
    actualMeasureSetup = sweepVoltageSetup;
    rearMode        = false;//
    guardMode       = false;//
}

KeithleyK24XXSetup::KeithleyK24XXSetup():InstrumentSetup()
{
    sweepVoltageSetup = new SweepVoltageSetup();
    actualMeasureSetup = sweepVoltageSetup;
    rearMode        = false;//
    guardMode       = false;//
}

KeithleyK24XXSetup::~KeithleyK24XXSetup(){}
Setup* KeithleyK24XXSetup:: getActualMeasureSetup(){return actualMeasureSetup;}

QDomElement KeithleyK24XXSetup::toQDomElement(){

    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("KeithleyK24XXSetup");
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
