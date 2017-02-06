#include <instrument/quadTech/Q7600.h>


int Q7600::getGPIBAddress() {return gpibPort->getAddress();}
int Q7600::setGPIBAddress(int newAddress){gpibPort->setAddress(newAddress);}
int Q7600::test(){

    int result = 0;
    int delay = 100;

    //Test que permita aplicar una tensión y medir cada un tiempo determinado haciendo uno del delay en la medida


    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST*****************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;

    //Data store example

    //*RST                  Restore GPIB defaults.
    //:SOUR:VOLT 10         Source 10V.
    //:TRAC:FEED SENS       Store raw readings in buffer.
    //:TRAC:POIN 10         Store 10 readings in buffer.
    //:TRAC:FEED:CONT NEXT  Enable buffer.
    //:TRIG:COUN 10         Trigger count = 10.
    //:OUTP ON              Turn on output.
    //:INIT                 Trigger readings.
    //:TRACE:DATA?          Request raw buffer readings.
    //:CALC3:FORM MEAN      Select mean buffer statistic.
    //:CALC3:DATA?          Request buffer mean data.
    //:CALC3:FORM SDEV      Select standard deviation statistic.
    //:CALC3:DATA?          Request standard deviation data.


//    gpibPort->testInstrunction("*RST");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":SOUR:VOLT 10");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRAC:FEED SENS");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRAC:POIN 10");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRAC:FEED:CONT NEXT");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRIG:COUN 10");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRIG:SOUR IMM");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":TRIG:DEL 1");
//    Sleep(delay*10);
//    setNPLC(0.01);
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":SENS:AVER OFF");
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":OUTP ON");
//    Sleep(delay*10);
//    formatElements(true,true,true,true);
//    Sleep(delay*10);
//    setDataFormatAsSinglePrecision();
//    Sleep(delay*10);
//    gpibPort->testInstrunction(":INIT");
//    Sleep(delay*100);


    return result;

}
