#include "instrumentSetup.h"

InstrumentSetup::InstrumentSetup(QString* _name,
                                 QString* _obs):Setup(_name)
{
    setObs(_obs);
}

InstrumentSetup::InstrumentSetup():Setup()
{
    setObs(new QString("default obs"));
}

InstrumentSetup::~InstrumentSetup(){}

QDomElement InstrumentSetup::toQDomElement(){

    QDomDocument doc("MyML");

    QDomElement root = doc.createElement("InstrumentSetup");
    doc.appendChild(root);

    QDomElement nameTag = doc.createElement("name");
    root.appendChild(nameTag);

    QDomText nameText = doc.createTextNode(*getName());
    nameTag.appendChild(nameText);

    QDomElement obsTag = doc.createElement("obsevations");
    root.appendChild(obsTag);

    QDomText obsText = doc.createTextNode(*getObs());
    obsTag.appendChild(obsText);

    return root;
}
