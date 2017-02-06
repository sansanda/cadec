#ifndef KEITHLEYK2425_H
#define KEITHLEYK2425_H

#include "./instrument/keithley/keithleyK24xx.h"

class KeithleyK2425: public KeithleyK24XX{

public:
    KeithleyK2425(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):KeithleyK24XX(      _name,
                                                               _idn,
                                                               _reference,
                                                               _manufacturer)
    {
    }
    KeithleyK2425():KeithleyK24XX()
    {
    }
    ~KeithleyK2425(){}

    void print();
    QDomElement toQDomElement();


private:


protected:


};

#endif // KEITHLEYK2425_H
