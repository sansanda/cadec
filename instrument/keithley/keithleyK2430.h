#ifndef KEITHLEYK2430_H
#define KEITHLEYK2430_H

#include "./instrument/keithley/keithleyK24xx.h"

class KeithleyK2430: public KeithleyK24XX{

public:
    KeithleyK2430(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer)
    {
    }
    KeithleyK2430():KeithleyK24XX()
    {
    }
    ~KeithleyK2430(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2430_H
