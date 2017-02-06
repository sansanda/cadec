#ifndef KEITHLEYK24XX_H
#define KEITHLEYK24XX_H

#include "./instrument/instrument.h"
#include "./setup/keithleyK24xxSetup.h"
#include "./K24xxConfigurationParameters.h"
#include "./communications/parallelCommunications/gpib/gpibPort.h"
#include "./maths/converters/numericalDataFormatConverter.h"
#include "./instrument/keithley/keithleyTools.h"
#include "./genericTools/bufferTools.h"

class KeithleyK24XX: public Instrument{

public:
    KeithleyK24XX(     QString* _name,
                       QString* _idn,
                       QString* _reference,
                       QString* _manufacturer):Instrument(_name,_idn,_reference,_manufacturer)
    {
        actualSetup = new KeithleyK24XXSetup();
        setInSweepVoltageOperationMode();
        internalDataBuffer = new InternalDataBuffer();
        triggerCountBuffer = new TriggerCountBuffer();

    }
    KeithleyK24XX():Instrument()
    {
        actualSetup = new KeithleyK24XXSetup();
        setInSweepVoltageOperationMode();
        internalDataBuffer = new InternalDataBuffer();
        triggerCountBuffer = new TriggerCountBuffer();
    }
    ~KeithleyK24XX(){}


    int reset();

    virtual double getMaxVoltageSourceAtVoltageRange(double _vr);
    virtual double getMaxVoltageMeasureAtVoltageRange(double _vr);
    virtual double getVoltageComplianceAtVoltageRange(double _vr);

    virtual double getMaxCurrentSourceAtCurrentRange(double _cr);
    virtual double getMaxCurrentMeasureAtCurrentRange(double _cr);
    virtual double getCurrentComplianceAtCurrentRange(double _cr);

    virtual double getAbsoluteMaxVoltage();
    virtual double getAbsoluteMaxPower();

    int executeMeasure();
    int stopMeasure();

    int goToInitialConditions();
    int goToFinalConditions();


    int openConnection();
    int checkPresence();

    int enableOutput();
    int disableOutput();
    int redirectOutputToFront();
    int redirectOutputToRear();

    int setNPLC(double nplc);
    int initTrigger();
    int setTriggerCount(int triggerCount);


    QString getIDN();
    int clearBufferOfReadings();
    int clearTriggerCountBuffer();
    int setBufferOfReadingsSize(int _size);
    int enableBufferOfReadings();
    int disableBufferOfReadings();

    int turnOffConcurrentFunctions();

    int smuOffMode( int smuOffModeIndex );
    int smuAutoZero( int smuAutoZeroIndex );


    //Operation modes
    int setSourceMode( int sourceModeIndex );
    int setInVoltageSourceMode();
    int setInCurrentSourceMode();
    int setFixedVoltageSourceMode();
    int setFixedCurrentSourceMode();
    int setInVoltageMeasureMode();
    int setInCurrentMeasureMode();

    int setInSweepVoltageOperationMode();
    int setInSweepCurrentOperationMode();
    int setInStepVoltageOperationMode();
    int setInStepCurrentOperationMode();
    int setInBiasVoltageOperationMode();
    int setInBiasCurrentOperationMode();
    int setInPulsedSweepVoltageOperationMode();
    int setInPulsedSweepCurrentOperationMode();
    int setInVoltmeterOperationMode();
    int setInAmmeterOperationMode();


    //Operation ranges
    int sourceRange(int sourceModeIndex, double sourceRange);
    int setVoltageSourceRange(double _range);
    int setCurrentSourceRange(double _range);

    int formatElements( bool voltageSource,
                         bool readbackSource,
                         bool readMeasure,
                         bool collectTimestamps );

    int setFormatCurrentReadingOnly();
    int setFormatVoltageReadingOnly();
    int setDataFormatAsSinglePrecision();
    int setDataFormatAsASCII();

    int disableAllMeasurementFunctions();
    int fourWiresMeasure( bool status );

    int measureRange( int sourceModeIndex, double sourceRange );
    int setVoltageMeasureRange(double sourceRange );
    int setCurrentMeasureRange(double sourceRange );

    int measureCompliance( int sourceModeIndex, double measureCompliance );
    int setCurrentMeasureCompliance(double measureCompliance);
    int setVoltageMeasureCompliance(double measureCompliance);

    int measureDelay( double measureDelay );

    int beeper( bool status );
    int beeperTone( double frequency, double time );

    int sourceLevel( int sourceModeIndex, double sourceLevel);
    int setVoltageSourceLevel(double sourceLevel);
    int setCurrentSourceLevel(double sourceLevel);


    int resetTimestamp();

    int enableMeasurementFunctions( int sourceModeIndex,
                                     bool enableVoltage = false,
                                     bool enableCurrent = false,
                                     bool enableResitence = false );

    int enablePulseMode( bool enablePulseMode );

    int setSweepStart( const int sourceModeIndex, const double sweepStart );
    int setSweepStop( const int sourceModeIndex, const double sweepStop );
    int setSweepStep( const int sourceModeIndex, const double sweepStep );
    int setSweepMode( const int sourceModeIndex );

    double readVoltage();
    double readMeanVoltage(int mean);

    //Communications
    int getGPIBAddress();
    int setGPIBAddress(int newAddress);

    //Others
    int testCommand(QString comm);
    QString getElements();
    int getNumberOfElementsToRead();
    QString getDataFormat();

    //Test
    int test1();
    int test2();

    void print()
    {

        Instrument::print();

        std::cout<<"*******************************************"<<std::endl;
        std::cout<<"************KEITHLEY 2400 DATA*************"<<std::endl;
        std::cout<<"*******************************************"<<std::endl;

    }

private:

    bool voltageMeasureType( int sourceModeIndex );
    bool currentMeasureType( int sourceModeIndex );

    double MAX_VOLTAGE;
    double MAX_POWER;

    //Buffers
    TriggerCountBuffer* triggerCountBuffer;
    InternalDataBuffer* internalDataBuffer;


public:



protected:


};


#endif // KEITHLEYK24XX_H
