#ifndef KEITHLEYK2440_H
#define KEITHLEYK2440_H

#include "./instrument/keithley/keithleyK24xx.h"

class KeithleyK2440: public KeithleyK24XX{

public:
    KeithleyK2440(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer)
    {
    }
    KeithleyK2440():KeithleyK24XX()
    {
    }
    ~KeithleyK2440(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2440_H
