#include "wentworthSXXXSetup.h"

WentworthSXXXSetup::WentworthSXXXSetup(QString* _name, QString* _obs):InstrumentSetup(_name,_obs)
{
    localMode        = true;//
    remoteMode       = !localMode;//
}

WentworthSXXXSetup::WentworthSXXXSetup():InstrumentSetup()
{
    localMode        = true;//
    remoteMode       = !localMode;//
}

WentworthSXXXSetup::~WentworthSXXXSetup(){}
Setup* WentworthSXXXSetup:: getActualMeasureSetup(){return actualSetup;}

QDomElement WentworthSXXXSetup::toQDomElement(){

    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("WentworthSXXXSetup");
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

bool WentworthSXXXSetup::getLocalMode() const
{
    return localMode;
}

void WentworthSXXXSetup::setLocalMode(bool value)
{
    remoteMode = !value;
    localMode = value;
}
bool WentworthSXXXSetup::getRemoteMode() const
{
    return remoteMode;
}

void WentworthSXXXSetup::setRemoteMode(bool value)
{
    localMode = !value;
    remoteMode = value;
}
