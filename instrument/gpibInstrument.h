#ifndef GPIBINSTRUMENT_H
#define GPIBINSTRUMENT_H

#include "./instrument/instrument.h"
#include "./gpib/scpi.h"

class GPIBInstrument: public Instrument, public Scpi {

public:
    GPIBInstrument(     QString* _name,
                        QString* _idn,
                        QString* _reference,
                        QString* _manufacturer,
                        int      _gpibAddress):Instrument(_name,_idn,_reference,_manufacturer)
    {
        setGPIBAddress(_gpibAddress);
    }
    GPIBInstrument():Instrument() {setGPIBAddress(24);}

    ~GPIBInstrument(){}

    int         getGPIBAddress()                                {return gpibAddress;}
    void        setGPIBAddress(int _gpibAddress)                {gpibAddress = _gpibAddress;}
    void        writeToGPIB(QString _message){write(_message);}

    void print()
    {
        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"************GPIB INSTRUMENT DATA***********"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

        Instrument::print();
        std::cout<<"GPIB Address = "   <<getGPIBAddress()<<std::endl;
    }


protected:


private:

    int         gpibAddress;

};



#endif // GPIBINSTRUMENT_H
