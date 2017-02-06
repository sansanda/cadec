#ifndef WENTWORTHS200_H
#define WENTWORTHS200_H

#include "./instrument/instrument.h"
#include "./setup/wentworthInstrumentsSetups/wentworthSXXXSetup.h"
#include "../../wentworthS200ConfigurationParameters.h"
#include "./maths/converters/numericalDataFormatConverter.h"
#include "./genericTools/bufferTools.h"

class WentworthS200: public Instrument{

public:
    WentworthS200(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):Instrument(_name,_idn,_reference,_manufacturer)
    {
        wentworthSXXXSetup = new WentworthSXXXSetup();

    }
    WentworthS200():Instrument()
    {
        wentworthSXXXSetup = new WentworthSXXXSetup();
    }
    ~WentworthS200(){}

    WentworthSXXXSetup* getSetup() {return wentworthSXXXSetup;}


    int reset();

    int executeMeasure();
    int stopMeasure();

    int goToInitialConditions();
    int goToFinalConditions();


    int openConnection();
    int checkPresence();




    QString getIDN();

    //Operation modes



    //Communications
    int getGPIBAddress();
    int setGPIBAddress(int newAddress);

    //Others
    int testCommand(QString comm);


    //Test
    int test1();
    int test2();

    void print()
    {

        Instrument::print();

        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"************PEGASUS S200 DATA**************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

    }

private:


    WentworthSXXXSetup* wentworthSXXXSetup;

public:


protected:


};

#endif // WENTWORTHS200_H
