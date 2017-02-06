#ifndef KEITHLEYK24XXSETUP_H
#define KEITHLEYK24XXSETUP_H

#include "instrumentSetup.h"
#include "sweepVoltageSetup.h"
#include "./K24xxConfigurationParameters.h"

class KeithleyK24XXSetup: public InstrumentSetup{
    Q_OBJECT

public:
    KeithleyK24XXSetup(QString* _name, QString* _obs);
    KeithleyK24XXSetup();
    ~KeithleyK24XXSetup();

    Setup* getActualMeasureSetup();

    bool getGuardMode() const
    {
        return guardMode;
    }

    void setGuardMode(bool value)
    {
        guardMode = value;
    }
    bool getRearMode() const
    {
        return rearMode;
    }

    void setRearMode(bool value)
    {
        rearMode = value;
    }
    QDomElement toQDomElement();

    virtual void print()
    {
        InstrumentSetup::print();

        std::cout<<"         Rear Mode?: "<<getRearMode()<<std::endl;
        std::cout<<"        Guard Mode?: "<<getGuardMode()<<std::endl;

        actualMeasureSetup->print();
    }


protected:

private:

    bool rearMode;      //
    bool guardMode;     //

    SweepVoltageSetup* sweepVoltageSetup;
    Setup* actualMeasureSetup;


};

#endif // KEITHLEYK24XXSETUP_H
