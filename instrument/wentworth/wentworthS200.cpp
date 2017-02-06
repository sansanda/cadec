#include "wentworthS200.h"

const int timeBetweenSteps = 200;

WentworthS200::WentworthS200(QString* _name,
                     QString* _idn,
                     QString* _reference,
                     QString* _manufacturer);

WentworthS200::WentworthS200();

WentworthS200::~WentworthS200();

int WentworthS200::reset()
{
    QString inst = scpiCommandFactory->reset();
    return gpibPort->write(inst);
}

int WentworthS200::getGPIBAddress() {return gpibPort->getAddress();}
int WentworthS200::setGPIBAddress(int newAddress){gpibPort->setAddress(newAddress);}

int WentworthS200::executeMeasure(){
    int result = 0;
    int delay = 100;
    goToInitialConditions();
    gpibPort->setTimeout(TIMEOUT_3s);

    //return test2();

    goToFinalConditions();
    return result;
}

int WentworthS200::test1(){
    int result = 0;
    int delay = 100;
    goToInitialConditions();

    //Test que permita aplicar una tensión y medir cada un tiempo determinado haciendo uno del delay en la medida

    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST1*****************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;


    //gpibPort->testInstrunction("*RST");
    //Sleep(delay*10);

    goToFinalConditions();
    return result;

}

int WentworthS200::test2(){

    int result = 0;
    int delayBetweenCommands = 10;

    goToInitialConditions();


    //Test que permita aplicar una tensión y medir cada un tiempo determinado haciendo uno del delay en la medida


    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST2*****************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;

    //Data store example



    //gpibPort->testInstrunction("*RST");
    //Sleep(delayBetweenCommands*10);

    goToFinalConditions();
    return result;

}

int WentworthS200::stopMeasure(){
    int result = 0;
    return result;
}

int WentworthS200::goToInitialConditions(){

    int result = 0;

    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****GOING TO INITIAL CONDITIONS***********"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;




    gpibPort->openConnection();
    //Sleep(timeBetweenSteps);
    return result;

}
int WentworthS200::goToFinalConditions(){

    int result = 0;

    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****GOING TO FINAL CONDITIONS*************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;


    gpibPort->openConnection();
    //Sleep(timeBetweenSteps);
    return result;
}

/**
 * @brief check the connection with the instrument sending the IDN query and waiting for an error or not.
 *
 * @param pad is an integer that represents the primary GPIB address where from the Keithley 2400.
 */


int WentworthS200::checkPresence(){
    int status = EXIT_SUCCESS;

#ifndef TEST
    QString inst = scpiCommandFactory->idnQuery();
    QVariant result;

    status = gpibPort->write(inst);

    if (status != EXIT_SUCCESS) return status;

    status = gpibPort->read(200,result);
#endif
    return status;
}


/**
 * @brief Open conection that set up the connection with the PAD device.
 *
 * @param pad is an integer that represents the primary GPIB address where from the Keithley 2400.
 */
int WentworthS200::openConnection()
{
    return gpibPort->openConnection();
}

/**
  * @brief Gets the identification string of the instrument
  *
  * @param None
  * @return A QString with the identification of the instrument.
  */

QString WentworthS200::getIDN()
{
    int status = 0;
    QString inst = scpiCommandFactory->idnQuery();
    gpibPort->write(inst);
    QVariant idn;

    status = gpibPort->read(2500,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}




//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES**************************************************
//**************************************************************************************************************
//**************************************************************************************************************






//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES END**********************************************
//**************************************************************************************************************
//**************************************************************************************************************


int WentworthS200::testCommand(QString comm)
{
    return gpibPort->testInstrunction(comm);
}

