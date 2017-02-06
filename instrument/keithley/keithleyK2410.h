#ifndef KEITHLEYK2410_H
#define KEITHLEYK2410_H

#include "./instrument/keithley/keithleyK24xx.h"

class KeithleyK2410: public KeithleyK24XX{

public:
    KeithleyK2410(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer)
    {
    }
    KeithleyK2410():KeithleyK24XX()
    {
    }
    ~KeithleyK2410(){}

    double getAbsoluteMaxVoltage();

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2410_H
