#include "./instrument/keithley/keithleyK24xx.h"

const int timeBetweenSteps = 200;

KeithleyK24XX::KeithleyK24XX(QString* _name,
                     QString* _idn,
                     QString* _reference,
                     QString* _manufacturer);

KeithleyK24XX::KeithleyK24XX();

KeithleyK24XX::~KeithleyK24XX();

int KeithleyK24XX::reset()
{
    QString inst = scpiCommandFactory->reset();
    return gpibPort->write(inst);
}

double KeithleyK24XX::getMaxVoltageSourceAtVoltageRange(double _vr){return 0.0;}
double KeithleyK24XX::getMaxVoltageMeasureAtVoltageRange(double _vr){return 0.0;}
double KeithleyK24XX::getVoltageComplianceAtVoltageRange(double _vr){return 0.0;}

double KeithleyK24XX::getMaxCurrentSourceAtCurrentRange(double _cr){return 0.0;}
double KeithleyK24XX::getMaxCurrentMeasureAtCurrentRange(double _cr){return 0.0;}
double KeithleyK24XX::getCurrentComplianceAtCurrentRange(double _cr){return 0.0;}

double KeithleyK24XX::getAbsoluteMaxVoltage(){return 0.0;}
double KeithleyK24XX::getAbsoluteMaxPower(){return 0.0;}


int KeithleyK24XX::getGPIBAddress() {return gpibPort->getAddress();}
int KeithleyK24XX::setGPIBAddress(int newAddress){gpibPort->setAddress(newAddress);}

int KeithleyK24XX::executeMeasure(){
    int result = 0;
    int delay = 100;
    goToInitialConditions();
    gpibPort->setTimeout(TIMEOUT_3s);

    //return test2();




    if (getOperationMode()==SWEEP_VOLTAGE)
    {


        beeper(false);
        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"*****CONFIGURING THE SWEEP VOLTAGE*********"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"\n"<<std::endl;

        //Ejemplo extraido de las fuentes de información

        //send (device,":*rst",&status);
        //send (device,":TRAC:CLE",&status);
        //send (device,":TRAC:POIN 11",&status);
        //send (device,":SENS:FUNC:CONC OFF",&status);
        //send (device,":SOUR:FUNC VOLT",&status);
        //send (device,":SOUR:CLE:AUTO ON",&status);
        //send (device,":SENS:FUNC 'CURR:DC'",&status);
        //send (device,":SENS:CURR:PROT 0.1",&status);
        //send (device,":SOUR:VOLT:START 1",&status);
        //send (device,":SOUR:VOLT:STOP 2",&status);
        //send (device,":SOUR:VOLT:STEP 0.1",&status);
        //send (device,":SOUR:VOLT:MODE SWE",&status);
        //send (device,":TRIG:COUN 11",&status);
        //send (device,":FORM:ELEM VOLT,CURR",&status);
        //send (device,":TRAC:FEED:CONT NEXT",&status);
        //send (device,":OUTP:STAT ON",&status);

        //send (device,":INIT",&status);
        //wait(2);	//# of seconds delay to allow data to be stored
        //send (device,":TRAC:DATA?",&status);
        //enter (sout,1000,&l,device,&status);

        //Fin ejemplo

        int delay = 100;
        reset();                    //"*RST"
        Sleep(delay*10);
        disableBufferOfReadings();
        Sleep(delay);
        clearBufferOfReadings();    //":TRAC:CLE"
        Sleep(delay);
        setBufferOfReadingsSize(((SweepVoltageSetup*)getActualSetup())->getNumberOfPoints()); //":TRAC:POIN NumberOfPoints"
        Sleep(delay);
        turnOffConcurrentFunctions(); //":SENS:FUNC:CONC OFF"
        Sleep(delay);
        setInVoltageSourceMode();   //":SOUR:FUNC VOLT"
        Sleep(delay);
        smuAutoZero(((SweepVoltageSetup*)getActualSetup())->getSmuAutoZero());
        Sleep(delay);
        setInCurrentMeasureMode();  //":SENS:FUNC 'CURR:DC'"
        Sleep(delay);
        setCurrentMeasureCompliance(((SweepVoltageSetup*)getActualSetup())->getCompliance()); //":SENS:CURR:PROT ....."
        Sleep(delay);
        setSweepStart(SWEEP_VOLTAGE,((SweepVoltageSetup*)getActualSetup())->getStartVoltage()); //":SOUR:VOLT:START ...."
        Sleep(delay);
        setSweepStop(SWEEP_VOLTAGE,((SweepVoltageSetup*)getActualSetup())->getStopVoltage());   //":SOUR:VOLT:STOP ...."
        Sleep(delay);
        setSweepStep(SWEEP_VOLTAGE,((SweepVoltageSetup*)getActualSetup())->getStepVoltage());   //":SOUR:VOLT:STEP ...."
        Sleep(delay);
        setSweepMode(SWEEP_VOLTAGE);
        Sleep(delay);
        setNPLC(((SweepVoltageSetup*)getActualSetup())->getNplc());
        Sleep(delay);
        setTriggerCount(((SweepVoltageSetup*)getActualSetup())->getNumberOfPoints()); //":TRIG:COUN Number of points"
        Sleep(delay);
        formatElements(true,
                       ((SweepVoltageSetup*)getActualSetup())->getReadBackVoltage(),
                       ((SweepVoltageSetup*)getActualSetup())->getMeasureCurrent(),
                       ((SweepVoltageSetup*)getActualSetup())->getCollectTimeStamps());
        Sleep(delay);
        enableBufferOfReadings();
        Sleep(delay);
        setDataFormatAsSinglePrecision();


        if (((KeithleyK24XXSetup*)getActualSetup())->getRearMode()) redirectOutputToRear(); else redirectOutputToFront();

        Sleep(delay);
        enableOutput();
        Sleep(delay);

        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"******PERFORMING THE SWEEP VOLTAGE*********"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"\n"<<std::endl;

        initTrigger();

        Sleep(70*((SweepVoltageSetup*)getActualSetup())->getNumberOfPoints());    //# of mseconds delay to allow data to be stored

        int nBytesToRead = ((SweepVoltageSetup*)getActualSetup())->getNumberOfPoints() * getNumberOfElementsToRead() * SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR;
        qDebug() <<  " nBytesToRead = " <<nBytesToRead;


        QString inst = scpiCommandFactory->dataQuery();
        result = gpibPort->write(inst);


        //Read the bytes of the results buffer
        gpibPort->read(triggerCountBuffer->buffer,nBytesToRead + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR+SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER);



        Sleep(2000);
        //triggerCountBuffer->printBufferContent(nBytesToRead + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR+SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER);

        //El test debe dar como resultado 0.15625 (fraction = 1.25, Exponent = 0.125, Sign = +)
        //char measureForTest[4] = {0,0,32,62};
        //qDebug() <<  " measure for test = " <<NumericalDataFormatConverter::singlePrecisionDataFormatToDouble(measureForTest);

        triggerCountBuffer->printAllMeasures(((SweepVoltageSetup*)getActualSetup())->getNumberOfPoints() * getNumberOfElementsToRead());
    }
    goToFinalConditions();
    return result;
}

int KeithleyK24XX::test1(){
    int result = 0;
    int delay = 100;
    goToInitialConditions();

    //Test que permita aplicar una tensión y medir cada un tiempo determinado haciendo uno del delay en la medida

    beeper(false);
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST1*****************"<<std::endl;
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


    gpibPort->testInstrunction("*RST");
    Sleep(delay*10);
    gpibPort->testInstrunction(":SOUR:VOLT 10");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRAC:FEED SENS");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRAC:POIN 10");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRAC:FEED:CONT NEXT");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRIG:COUN 10");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRIG:SOUR IMM");
    Sleep(delay*10);
    gpibPort->testInstrunction(":TRIG:DEL 1");
    Sleep(delay*10);
    setNPLC(0.01);
    Sleep(delay*10);
    gpibPort->testInstrunction(":SENS:AVER OFF");
    Sleep(delay*10);
    gpibPort->testInstrunction(":OUTP ON");
    Sleep(delay*10);
    formatElements(true,true,true,true);
    Sleep(delay*10);
    setDataFormatAsSinglePrecision();
    Sleep(delay*10);
    gpibPort->testInstrunction(":INIT");
    Sleep(delay*100);


    QString inst = scpiCommandFactory->dataQuery();
    result = gpibPort->write(inst);



    int nBytesToRead = (10 * 3 * SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR);
    qDebug()  <<  " nBytesToRead = " <<nBytesToRead;

    //Read the bytes of the results buffer
    gpibPort->read(triggerCountBuffer->buffer,nBytesToRead + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR+SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER);

    triggerCountBuffer->printAllMeasures(10 * 3);


    goToFinalConditions();
    return result;

}

int KeithleyK24XX::test2(){

    int result = 0;
    int delayBetweenCommands = 10;
    int numberOfPoints = 11;
    int numberOfElementsToRead = 3;


    double desiredMeasureDelay = 1; //In seconds
    double triggerLatency = 0.0001; //100us
    double nplc = 0.01;
    double lineFreq = 50; // In Hertz
    double adcMeasureTime = nplc / lineFreq;
    double measureDelay = desiredMeasureDelay; //desiredMeasureDelay-triggerLatency-adcMeasureTime*10;

    int delayBeforeReadingMeasureResult = 1000*desiredMeasureDelay*numberOfPoints*1.1;

    QString aux = "";

    goToInitialConditions();


    //Test que permita aplicar una tensión y medir cada un tiempo determinado haciendo uno del delay en la medida

    beeper(false);
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****CONFIGURING THE TEST2*****************"<<std::endl;
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


    gpibPort->testInstrunction("*RST");
    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":SOUR:VOLT 10");
    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":TRAC:FEED SENS");
    Sleep(delayBetweenCommands*10);

    aux.append(":TRAC:POIN ");
    aux.append(QString::number(numberOfPoints));
    gpibPort->testInstrunction(aux);
    aux = "";

    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":TRAC:FEED:CONT NEXT");
    Sleep(delayBetweenCommands*10);

    aux.append(":TRIG:COUN ");
    aux.append(QString::number(numberOfPoints));
    gpibPort->testInstrunction(aux);
    aux = "";

    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":TRIG:SOUR IMM");
    Sleep(delayBetweenCommands*10);

    setCurrentMeasureCompliance(0.001);

    aux.append(":TRIG:DEL ");
    aux.append(QString::number(measureDelay));
    gpibPort->testInstrunction(aux);
    aux = "";

    Sleep(delayBetweenCommands*10);
    setNPLC(nplc);
    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":SENS:AVER OFF");
    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":OUTP ON");
    Sleep(delayBetweenCommands*10);
    formatElements(true,true,true,true);
    Sleep(delayBetweenCommands*10);
    setDataFormatAsSinglePrecision();
    Sleep(delayBetweenCommands*10);
    gpibPort->testInstrunction(":INIT");
    Sleep(delayBeforeReadingMeasureResult);


    QString inst = scpiCommandFactory->dataQuery();
    result = gpibPort->write(inst);



    int nBytesToRead = (numberOfPoints * numberOfElementsToRead * SINGLEPRECISION_DATA_FORMAT_BYTES_PER_ELEMENT + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR);
    qDebug()  <<  " nBytesToRead = " <<nBytesToRead;

    //Read the bytes of the results buffer
    gpibPort->read(triggerCountBuffer->buffer,nBytesToRead + SINGLEPRECISION_DATA_FORMAT_BYTES_OF_TERMINATOR+SINGLEPRECISION_DATA_FORMAT_BYTES_OF_HEADER);
    Sleep(delayBetweenCommands*10);
    triggerCountBuffer->printAllMeasures(numberOfPoints * numberOfElementsToRead);


    goToFinalConditions();
    return result;

}

int KeithleyK24XX::stopMeasure(){
    int result = 0;
    return result;
}

int KeithleyK24XX::enableOutput(){
    QString inst = scpiCommandFactory->enableOutput(true);
    return gpibPort->write(inst);
}

int KeithleyK24XX::disableOutput(){
    QString inst = scpiCommandFactory->enableOutput(false);
    return gpibPort->write(inst);
}
int KeithleyK24XX::redirectOutputToRear(){
    QString inst = scpiCommandFactory->terminalsRoute(true);
    return gpibPort->write(inst);
}
int KeithleyK24XX::redirectOutputToFront(){
    QString inst = scpiCommandFactory->terminalsRoute(false);
    return gpibPort->write(inst);
}

int KeithleyK24XX::goToInitialConditions(){


    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****GOING TO INITIAL CONDITIONS***********"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;


    int result = 0;

    gpibPort->openConnection();
    //Sleep(timeBetweenSteps);
    disableOutput();
    //Sleep(timeBetweenSteps);
    return result;

}
int KeithleyK24XX::goToFinalConditions(){


    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"*****GOING TO FINAL CONDITIONS*************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"\n"<<std::endl;

    int result = 0;
    gpibPort->openConnection();
    //Sleep(timeBetweenSteps);
    disableOutput();
    //Sleep(timeBetweenSteps);
    return result;
}

/**
 * @brief check the connection with the instrument sending the IDN query and waiting for an error or not.
 *
 * @param pad is an integer that represents the primary GPIB address where from the Keithley 2400.
 */


int KeithleyK24XX::checkPresence(){
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
int KeithleyK24XX::openConnection()
{  
    return gpibPort->openConnection();
}

/**
 * @brief Disable the Buffer of readings.
 * This action command is used to disable the buffer of readings.
 */

int KeithleyK24XX::disableBufferOfReadings()
{
    QString inst = scpiCommandFactory->disableBufferOfReadings();
    return gpibPort->write(inst);
}

/**
 * @brief Enable the Buffer of readings.
 * This action command is used to enable the buffer of readings.
 */

int KeithleyK24XX::enableBufferOfReadings()
{
    QString inst = scpiCommandFactory->enableBufferOfReadings();
    return gpibPort->write(inst);
}

/**
 * @brief Clear the Buffer of readings.
 * This action command is used to clear the buffer of readings. If you do
 * not clear the buffer, a subsequent store will overwrite the old read-
 * ings.
 */

int KeithleyK24XX::clearBufferOfReadings()
{
    QString inst = scpiCommandFactory->clearBufferOfReadings();
    return gpibPort->write(inst);
}

/**
 * @brief Clear the Trigger Count Buffer.
 * This action command is used to clear the trigger count buffer.
 * More info = http://www.keithley.com/data?asset=3814
 */

int KeithleyK24XX::clearTriggerCountBuffer()
{
    QString inst = scpiCommandFactory->clearTriggerCountBuffer();
    return gpibPort->write(inst);
}

/**
 * @brief Set the size of the Buffer of readings.
 * This command is used to specify the size of the buffer
 */

int KeithleyK24XX::setBufferOfReadingsSize(int _size)
{
    QString inst = scpiCommandFactory->setBufferOfReadingsSize(_size);
    return gpibPort->write(inst);
}

/**
  * @brief Gets the identification string of the instrument
  *
  * @param None
  * @return A QString with the identification of the instrument.
  */

QString KeithleyK24XX::getIDN()
{
    int status = 0;
    QString inst = scpiCommandFactory->idnQuery();
    gpibPort->write(inst);
    QVariant idn;

    status = gpibPort->read(2500,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}

/**
 * @brief Turn off concurrent functions
 *
 */
int  KeithleyK24XX::turnOffConcurrentFunctions()
{
    QString inst = scpiCommandFactory->turnOffConcurrentFunctions();
    return gpibPort->write(inst);
}


/**
  * @brief SMU Output Off Mode configuration
  *
  * @param smuOffModeIndex Is an integer used to decode the type of output mode, from the comboBox
  * index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::smuOffMode(int smuOffModeIndex)
{
    QString inst;
    switch ( smuOffModeIndex ) {
    case NORMAL:
        inst = QString(":OUTP:SMOD NORM");
        break;
    case HIGH_Z:
        inst = QString(":OUTP:SMOD HIMP");
        break;
    case ZERO:
        inst = QString(":OUTP:SMOD ZERO");
        break;
    case GUARD:
        inst = QString(":OUTP:SMOD GUAR");
        break;
    default:
        inst = QString(":OUTP:SMOD NORM");
        break;
    }
    return gpibPort->write(inst);
}

/**
  * @brief SMU Auto Zero configuration
  *
  * @param smuAutoZeroIndex Is an integer used to decode the type of auto zero config, from
  * combo box index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::smuAutoZero(int smuAutoZeroIndex)
{
    QString inst;
    switch ( smuAutoZeroIndex ) {
    case AZERO_ALWAYS:
        inst = QString(":SYST:AZER:STAT ON");
        break;
    case AZERO_ONCE:
        inst = QString(":SYST:AZER:STAT ONCE");
        break;
    case AZERO_OFF:
        inst = QString(":SYST:AZER:STAT OFF");
        break;
    default:
        inst = QString(":SYST:AZER:STAT ON");
        break;
    }

    return gpibPort->write(inst);
}


//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES**************************************************
//**************************************************************************************************************
//**************************************************************************************************************


int KeithleyK24XX::setInSweepVoltageOperationMode(){operationMode = SWEEP_VOLTAGE;}
int KeithleyK24XX::setInSweepCurrentOperationMode(){operationMode = SWEEP_CURRENT;}
int KeithleyK24XX::setInStepVoltageOperationMode(){operationMode = STEP_VOLTAGE;}
int KeithleyK24XX::setInStepCurrentOperationMode(){operationMode = STEP_CURRENT;}
int KeithleyK24XX::setInBiasVoltageOperationMode(){operationMode = BIAS_VOLTAGE;}
int KeithleyK24XX::setInBiasCurrentOperationMode(){operationMode = BIAS_CURRENT;}
int KeithleyK24XX::setInPulsedSweepVoltageOperationMode(){operationMode = PULSED_SWEEP_VOLTAGE;}
int KeithleyK24XX::setInPulsedSweepCurrentOperationMode(){operationMode = PULSED_SWEEP_CURRENT;}
int KeithleyK24XX::setInVoltmeterOperationMode(){operationMode = VOLTMETER;}
int KeithleyK24XX::setInAmmeterOperationMode(){operationMode = AMMETER;}

/**
  * @brief SMU Source Mode configuration
  *
  * @param sourceModeIndex Is an integer used to decode the type of source mode, from the comboBox
  * index(widget) in the KeithleyK24XX config UI.
  */

int KeithleyK24XX::setSourceMode(int sourceModeIndex)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setInVoltageSourceMode();
    else if ( currentMeasureType( sourceModeIndex ) ) return setInCurrentSourceMode();
    return 0;
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Voltage Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setInVoltageSourceMode()
{
    QString inst = scpiCommandFactory->setInVoltageSourceMode();
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setInCurrentSourceMode()
{
    QString inst = scpiCommandFactory->setInCurrentSourceMode();
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Fixed Voltage Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setFixedVoltageSourceMode()
{
    QString inst = scpiCommandFactory->setInFixedVoltageSourceMode();
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Fixed Current Source Mode
  *
  * @param none
  */

int KeithleyK24XX::setFixedCurrentSourceMode()
{
    QString inst = scpiCommandFactory->setInFixedCurrentSourceMode();
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Voltage Measure Mode
  *
  * @param none
  */

int KeithleyK24XX::setInVoltageMeasureMode()
{
    QString inst = scpiCommandFactory->setInVoltageMeasureMode();
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Measure Mode
  *
  * @param none
  */

int KeithleyK24XX::setInCurrentMeasureMode()
{
    QString inst = scpiCommandFactory->setInCurrentMeasureMode();
    return gpibPort->write(inst);
}

/**
  * @brief Select the source Range for measuring.
  *
  * @param sourceModeIndex An int that cointains the source mode index (current or voltage).
  * @param sourceRange A double that holds source range value.
  */



//**************************************************************************************************************
//**************************************************************************************************************
//*********************************************OPERATION MODES END**********************************************
//**************************************************************************************************************
//**************************************************************************************************************


int KeithleyK24XX::sourceRange(int sourceModeIndex, double sourceRange)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setVoltageSourceRange(sourceRange);
    else if ( currentMeasureType( sourceModeIndex ) ) return setCurrentSourceRange(sourceRange);
    return 0;
}


/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley Voltage Source Range
  *
  * @param double with the range
  */

int KeithleyK24XX::setVoltageSourceRange(double _range)
{
    QString inst = scpiCommandFactory->setVoltageSourceRange(_range);
    return gpibPort->write(inst);
}

/**
  * @author David Sánchez Sánchez
  * @brief SMU Sets the Keithley In Current Source Range
  *
  * @param double with the range
  */

int KeithleyK24XX::setCurrentSourceRange(double _range)
{
    QString inst = scpiCommandFactory->setCurrentSourceRange(_range);
    return gpibPort->write(inst);
}

/**
  * @brief Data format selection.
  *
  * @param voltageSource A bool that indicates if we are in voltage or current cource.
  * @param readbackSource A bool that indicates wether or not readback source value.
  * @param readMeasure A bool that indicates wether or not read the measure result.
  * @param collectTimestamps A bool that indicates wether or not retrieves the time stamps.
  */

int KeithleyK24XX::formatElements( bool voltageSource,
                                    bool readbackSource,
                                    bool readMeasure,
                                    bool collectTimestamps)
{

    //QString output = ":FORM:ELEM VOLT, CURR, TIME";
    int i=0;
    QString inst = ":FORM:ELEM ";

    if( voltageSource)
    {
        if (readbackSource){
            inst.append("VOLT");
            i++;
        }
        if (readMeasure){
            if (i>0) inst.append(", CURR");
            else
            {
                inst.append("CURR");
                i++;
            }
        }
        if (collectTimestamps){
            if (i>0) inst.append(", TIME");
            else
            {
                inst.append("TIME");
                i++;
            }
        }
    }
    else
    {
        if (readbackSource){
            inst.append("CURR");
            i++;
        }
        if (readMeasure){
            if (i>0) inst.append(", VOLT");
            else
            {
                inst.append("VOLT");
                i++;
            }
        }
        if (collectTimestamps){
            if (i>0) inst.append(", TIME");
            else
            {
                inst.append("TIME");
                i++;
            }
        }
    }
    return gpibPort->write(inst);
}

/**
  * @brief Data format selection to current reading only.
  */

int KeithleyK24XX::setFormatCurrentReadingOnly()
{
    QString inst = ":FORM:ELEM CURR";
    return gpibPort->write(inst);
}

/**
  * @brief Data format selection to voltage reading only.
  */

int KeithleyK24XX::setFormatVoltageReadingOnly()
{
    QString inst = ":FORM:ELEM VOLT";
    return gpibPort->write(inst);
}

/**
  * @brief Sets the Keithley Data format as Single Precision.
  */

int KeithleyK24XX::setDataFormatAsSinglePrecision()
{
    QString inst = ":FORM:DATA SRE";
    return gpibPort->write(inst);
}

/**
  * @brief Sets the Keithley Data format as ASCII.
  */

int KeithleyK24XX::setDataFormatAsASCII()
{
    QString inst = ":FORM:DATA ASCII";
    return gpibPort->write(inst);
}

/**
  * @brief Disable all measurement functions.
  */

int KeithleyK24XX::disableAllMeasurementFunctions()
{
    QString inst = ":SENS:FUNC:OFF:ALL";
    return gpibPort->write(inst);
}

/**
  * @brief Enable or disable 4 wires measure.
  *
  * @param status Is a bool that eneables or disables 4 wires measure
  */

int KeithleyK24XX::fourWiresMeasure(bool status)
{
    QString inst;
    if( status )
        inst = ":SYST:RSEN ON";
    else
        inst = ":SYST:RSEN OFF";

    return gpibPort->write(inst);
}

/**
  * @brief Measure range selection.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sourceRangeIndex And int that contains the source range index from the keithley ui's
  * combobox.
  */
int KeithleyK24XX::measureRange( int sourceModeIndex, double sourceRange )
{
    if( voltageMeasureType( sourceModeIndex ) ) return setCurrentMeasureRange(sourceRange);
    else if ( currentMeasureType( sourceModeIndex ) ) return setVoltageMeasureRange(sourceRange);
    return 0;
}

/**
  * @brief Set Voltage Measure Range.
  *
  * @param sourceRangeIndex And int that contains the voltage measure range
  */
int KeithleyK24XX::setVoltageMeasureRange(double sourceRange )
{
    if ( sourceRange == AUTO_MEASURE_RANGE_FLAG )
    {
        QString inst = scpiCommandFactory->setVoltageMeasureRangeInAuto( true );
        return gpibPort->write(inst);
    }
    else return setVoltageMeasureRange( sourceRange );
}


/**
  * @brief Set Current Measure Range.
  *
  * @param sourceRangeIndex And int that contains the current measure range
  */
int KeithleyK24XX::setCurrentMeasureRange(double sourceRange )
{
    if ( sourceRange == AUTO_MEASURE_RANGE_FLAG )
    {
        QString inst = scpiCommandFactory->setCurrentMeasureRangeInAuto( true );
        return gpibPort->write(inst);
    }
    else return setCurrentMeasureRange( sourceRange );
}

/**
  * @brief Set measure compliance.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::measureCompliance(int sourceModeIndex, double measureCompliance)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setCurrentMeasureCompliance( measureCompliance );
    else if ( currentMeasureType( sourceModeIndex ) ) return setVoltageMeasureCompliance( measureCompliance );
    return 0;
}

/**
  * @brief Set the current measure compliance.
  *
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::setCurrentMeasureCompliance(double measureCompliance)
{
    QString inst = scpiCommandFactory->setCurrentCompliance(measureCompliance);
    return gpibPort->write(inst);
}

/**
  * @brief Set the voltage measure compliance.
  *
  * @param measureCompliance A double that contains the complaince value desired.
  */

int KeithleyK24XX::setVoltageMeasureCompliance(double measureCompliance)
{
    QString inst = scpiCommandFactory->setVoltageCompliance(measureCompliance);
    return gpibPort->write(inst);
}

/**
  * @brief set delay time (settling time)
  *
  * @param measureDelay Is a double that holds settling measure time (delay) between 0 and 999.99s.
  */

int KeithleyK24XX::measureDelay( double measureDelay )
{
    QString inst = QString( ":SOUR:DEL %1" ).arg( measureDelay );
    return gpibPort->write(inst);
}

/**
  * @brief Enable or disable beeper (sound)
  *
  * @param status A bool that defines wether or not enable or disable the beeper.
  */

int KeithleyK24XX::beeper( bool status )
{
    QString inst;
    if( status )
        inst = ":SYST:BEEP:STAT ON";
    else
        inst = ":SYST:BEEP:STAT OFF";

    return gpibPort->write(inst);
}

/**
  * @brief Executes and set ups a beep tone.
  *
  * @param frequency An int that contains the beep frequency (65 to 2e6 Hz).
  * @param time A double that holds the beep duration (0 to 7.9 seconds).
  */

int KeithleyK24XX::beeperTone( double frequency, double time )
{
    QString inst = QString( ":SYST:BEEP %1,%2" ).arg( frequency ).arg( time / 1000 );
    return gpibPort->write(inst);
    QTest::qSleep(time);
}

/**
  * @brief Sets source level.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::sourceLevel(int sourceModeIndex, double sourceLevel)
{
    if ( voltageMeasureType( sourceModeIndex ) ) return setVoltageSourceLevel(sourceLevel);
    else if ( currentMeasureType( sourceModeIndex ) ) return setCurrentSourceLevel(sourceLevel);
    return 0;
}

/**
  * @brief Sets voltage source level.
  *
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::setVoltageSourceLevel(double sourceLevel)
{
    QString inst = scpiCommandFactory->setVoltageSourceLevel(sourceLevel);
    return gpibPort->write(inst);
}

/**
  * @brief Sets current source level.
  *
  * @param sourceLevel A double that holds desired source level.
  */
int KeithleyK24XX::setCurrentSourceLevel(double sourceLevel)
{
    QString inst = scpiCommandFactory->setCurrentSourceLevel(sourceLevel);
    return gpibPort->write(inst);
}

/**
  * @brief Reset timestamp to zero.
  */

int KeithleyK24XX::resetTimestamp()
{
    QString inst = scpiCommandFactory->resetTimeStamps();
    return gpibPort->write(inst);
}

/**
  * @brief Enable the desired measure functions( V, C , R).
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param enableSource A bool indicates whether or not to enable source measurement.
  * @param enableMeasure A bool indicates whether or not to enable measure measurement.
  * @param enableResistance A bool indicates wether or not to enable resistance measurement.
  *
  * @todo Add resistence capabilities to the rest of the program.
  * @todo Instead of using a dirty if-else method to choose, create a list with the enabled params.
  */

int KeithleyK24XX::enableMeasurementFunctions(int sourceModeIndex,
                                              bool enableSource,
                                              bool enableMeasure,
                                              bool enableResitence)
{
    if( voltageMeasureType( sourceModeIndex ) )
    {
        if      (enableSource & enableMeasure & enableResitence){QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\",\"RES\"");return gpibPort->write(inst);}
        else if (enableSource & enableMeasure)                  {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\"");return gpibPort->write(inst);}
        else if (enableSource)                                  {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\"");return gpibPort->write(inst);}
        else if (enableMeasure)                                 {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\"");return gpibPort->write(inst);}
        else if (enableResitence)                               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"RES\"");return gpibPort->write(inst);}
        else if (enableSource & enableResitence)                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"RES\"");return gpibPort->write(inst);}
        else if (enableMeasure & enableResitence)               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\",\"RES\"");return gpibPort->write(inst);}
        else                                                    {return -1;}
    }
    else if ( currentMeasureType( sourceModeIndex ))
    {
        if( enableSource & enableMeasure & enableResitence )    {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\",\"RES\"");return gpibPort->write(inst);}
        else if ( enableSource & enableMeasure )                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"CURR\"");return gpibPort->write(inst);}
        else if ( enableSource )                                {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\"");return gpibPort->write(inst);}
        else if ( enableMeasure )                               {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\"");return gpibPort->write(inst);}
        else if ( enableResitence )                             {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"RES\"");return gpibPort->write(inst);}
        else if ( enableSource & enableResitence )              {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"CURR\",\"RES\"");return gpibPort->write(inst);}
        else if ( enableMeasure & enableResitence)              {QString inst = scpiCommandFactory->enableMeasureFunctionsSCPI("\"VOLT\",\"RES\"");return gpibPort->write(inst);}
        else                                                    {return -1;}
    }
    else    {return -1;}
}


/**
  * @brief Enable or disable the pulse mode for keithley 2430.
  *
  * @param enablePulseMode Is a bool that eneables or disables the pulse mode.
  */

int KeithleyK24XX::enablePulseMode( bool enablePulseMode )
{
    QString inst;
    if( enablePulseMode )   inst = ":SOUR:FUNC:SHAP PULS";
    else                    inst = ":SOUR:FUNC:SHAP DC";

    return gpibPort->write(inst);
}

/**
  * @brief Sets sweep starting point
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStart A double holding the sweep starting point value.
  */
int KeithleyK24XX::setSweepStart( const int sourceModeIndex, const double sweepStart)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStart(sweepStart);
        return gpibPort->write(inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStart(sweepStart);
        return gpibPort->write(inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep lasts point
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStop A double holding the sweep last point.
  */
int KeithleyK24XX::setSweepStop(const int sourceModeIndex, const double sweepStop)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStop(sweepStop);
        return gpibPort->write(inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStop(sweepStop);
        return gpibPort->write(inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep step value
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  * @param sweepStep A double holding the sweep step value.
  */
int KeithleyK24XX::setSweepStep(const int sourceModeIndex, const double sweepStep)
{
    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepStep(sweepStep);
        return gpibPort->write(inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepStep(sweepStep);
        return gpibPort->write(inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Sets sweep mode
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  */
int KeithleyK24XX::setSweepMode( const int sourceModeIndex )
{

    QString inst;

    switch( sourceModeIndex ){
    case VOLTAGE_PULSED_SWEEP:
    case VOLTAGE_SWEEP :
        inst = scpiCommandFactory->setVoltageSweepMode();
        return gpibPort->write(inst);
        break;
    case CURRENT_PULSED_SWEEP:
    case CURRENT_SWEEP:
        inst = scpiCommandFactory->setCurrentSweepMode();
        return gpibPort->write(inst);
        break;
    default:
        //nothing todo
        return -1;
        break;
    }
}

/**
  * @brief Method to know if a of measure is voltage type.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  *
  * @return A bool that indicates wether the measure is voltage type or not.
  */

bool KeithleyK24XX::voltageMeasureType(int sourceModeIndex)
{
    bool status;
    switch( sourceModeIndex ){
    case VOLTAGE_SWEEP:
        status = true;
        break;
    case VOLTAGE_STEP:
        status = true;
        break;
    case VOLTAGE_MEASURE:
        status = true;
        break;
    case VOLTAGE_PULSED_SWEEP:
        status = true;
        break;
    case VOLTAGE_PULSED_NO_MEAS:
        status = true;
        break;
    case CURRENT_SWEEP:
        status = false;
        break;
    case CURRENT_STEP:
        status = false;
        break;
    case CURRENT_MEASURE:
        status = false;
        break;
    case CURRENT_PULSED_SWEEP:
        status = false;
        break;
    case CURRENT_PULSED_NO_MEAS:
        status = false;
        break;
    }
    return status;
}

/**
  * @brief Method to know if a of measure is current type.
  *
  * @param sourceModeIndex An int that contains the source mode index from the keithley
  * ui's combobox( voltage or current ).
  *
  * @return A bool that indicates wether the measure is current type or not.
  */

bool KeithleyK24XX::currentMeasureType(int sourceModeIndex)
{
    bool status;
    switch( sourceModeIndex ){
    case VOLTAGE_SWEEP:
        status = false;
        break;
    case VOLTAGE_STEP:
        status = false;
        break;
    case VOLTAGE_MEASURE:
        status = false;
        break;
    case VOLTAGE_PULSED_SWEEP:
        status = false;
        break;
    case VOLTAGE_PULSED_NO_MEAS:
        status = false;
        break;
    case CURRENT_SWEEP:
        status = true;
        break;
    case CURRENT_STEP:
        status = true;
        break;
    case CURRENT_MEASURE:
        status = true;
        break;
    case CURRENT_PULSED_SWEEP:
        status = true;
        break;
    case CURRENT_PULSED_NO_MEAS:
        status = true;
        break;
    }
    return status;    
}
double KeithleyK24XX::readVoltage(){
    setInVoltageMeasureMode();
    fourWiresMeasure(true);
    setNPLC(1);
    setFormatVoltageReadingOnly();
    enableOutput();
    initTrigger();

    QVariant res;
    gpibPort->read(200,res);
    QString resString;
    resString = res.toString();
    qDebug() << resString;
    int nToRemove = resString.length()-resString.indexOf("E");
    resString = resString.remove(resString.indexOf("E")+4,nToRemove);
    qDebug() << resString;

    return resString.toDouble();

}

double KeithleyK24XX::readMeanVoltage(int mean){

    double acumValue = 0;

    int i=0;
    bool fi = false;

    while (!fi){

        acumValue = acumValue + readVoltage();
        i++;
        fi = (i>=mean);
    }

    qDebug() << (acumValue/(double)mean);


    return (acumValue/(double)mean);

}

int KeithleyK24XX::setNPLC(double nplc)
{
    if (nplc==0.01 || nplc==0.1 || nplc==1 || nplc==10)
    {
        QString inst = scpiCommandFactory->setNplc(QString::number(nplc));
        return gpibPort->write(inst);
    }else return -1;

}
int KeithleyK24XX::initTrigger()
{
    QString inst = scpiCommandFactory->initTrigger();
    return gpibPort->write(inst);
}
int KeithleyK24XX::setTriggerCount(int triggerCount)
{
    QString inst = scpiCommandFactory->setTriggerCount(triggerCount);
    return gpibPort->write(inst);
}
QString KeithleyK24XX::getElements()
{
    int status = 0;
    QString inst = ":FORM:ELEM?";
    gpibPort->write(inst);
    QVariant idn;

    status = gpibPort->read(2500,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}
int KeithleyK24XX::getNumberOfElementsToRead()
{
    int nElements = 0;
    QString elements = getElements();
    if (elements == NULL) nElements = -1;
    else
    {
        QStringList l = elements.split(",");
        nElements = l.size();
    }
    return nElements;
}
QString KeithleyK24XX::getDataFormat()
{
    int status = 0;
    QString inst = ":FORM:DATA?";
    gpibPort->write(inst);
    QVariant idn;

    status = gpibPort->read(2500,idn);

    if (status!=0) return NULL; else return idn.toString().toLocal8Bit();
}

int KeithleyK24XX::testCommand(QString comm)
{
    return gpibPort->testInstrunction(comm);
}
