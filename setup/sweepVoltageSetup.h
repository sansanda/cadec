#ifndef SWEEPVOLTAGESETUP_H
#define SWEEPVOLTAGESETUP_H

#include "setup.h"
#include "K24xxConfigurationParameters.h"

class SweepVoltageSetup: public Setup{
    Q_OBJECT

public:
    SweepVoltageSetup(QString* _name);
    SweepVoltageSetup();
    ~SweepVoltageSetup();


    QDomElement toQDomElement();


    double getStepVoltage() const
    {
        double range = abs(startVoltage - stopVoltage);
        //std::cout<<(range/numberOfPoints);
        return range/(numberOfPoints-1);
    }

    int getStopVoltage() const
    {
        return stopVoltage;
    }

    void setStopVoltage(int value)
    {
        stopVoltage = value;
    }
    int getNumberOfPoints() const
    {
        return numberOfPoints;
    }

    void setNumberOfPoints(int value)
    {
        numberOfPoints = value;
    }
    int getSweepType() const
    {
        return sweepType;
    }

    void setSweepType(int value)
    {
        sweepType = value;
    }
    double getCompliance() const
    {
        return compliance;
    }

    void setCompliance(double value)
    {
        compliance = value;
    }
    int getSweepDelay() const
    {
        return sweepDelay;
    }

    void setSweepDelay(int value)
    {
        sweepDelay = value;
    }
    bool getReadBackVoltage() const
    {
        return readBackVoltage;
    }

    void setReadBackVoltage(bool value)
    {
        readBackVoltage = value;
    }
    bool getMeasureCurrent() const
    {
        return measureCurrent;
    }

    void setMeasureCurrent(bool value)
    {
        measureCurrent = value;
    }
    bool getCollectTimeStamps() const
    {
        return collectTimeStamps;
    }

    void setCollectTimeStamps(bool value)
    {
        collectTimeStamps = value;
    }
    QString getVoltageName() const
    {
        return voltageName;
    }

    void setVoltageName(const QString &value)
    {
        voltageName = value;
    }
    QString getCurrentName() const
    {
        return currentName;
    }

    void setCurrentName(const QString &value)
    {
        currentName = value;
    }
    int getMeasurementRange() const
    {
        return measurementRange;
    }

    void setMeasurementRange(int value)
    {
        measurementRange = value;
    }
    double getNplc() const
    {
        return nplc;
    }

    void setNplc(double value)
    {
        nplc = value;
    }
    int getFilterType() const
    {
        return filterType;
    }

    void setFilterType(int value)
    {
        filterType = value;
    }
    int getFilterCount() const
    {
        return filterCount;
    }

    void setFilterCount(int value)
    {
        filterCount = value;
    }
    bool getFourWireMeasurementMode() const
    {
        return fourWireMeasurementMode;
    }

    void setFourWireMeasurementMode(bool value)
    {
        fourWireMeasurementMode = value;
    }
    int getSmuAutoZero() const
    {
        return smuAutoZeroMode;
    }

    void setSmuAutoZero(int value)
    {
        smuAutoZeroMode = value;
    }
    int getSmuOffMode() const
    {
        return smuOffMode;
    }

    void setSmuOffMode(int value)
    {
        smuOffMode = value;
    }
    int getStartVoltage() const
    {
        return startVoltage;
    }

    void setStartVoltage(int value)
    {
        startVoltage = value;
    }

    int resetSetup();

    virtual void print()
    {

        std::cout<<"******************************************************"<<std::endl;
        std::cout<<"**************MEASURE SETUP DATA**********************"<<std::endl;
        std::cout<<"******************************************************"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"******************************************************"<<std::endl;
        std::cout<<"**************SWEEP VOLTAGE SETUP DATA****************"<<std::endl;
        std::cout<<"******************************************************"<<std::endl;
        std::cout<<std::endl;
        std::cout<<"*******************SOURCE*****************************"<<std::endl;
        std::cout<<"      Start Voltage: "<<getStartVoltage()<<" volts."<<std::endl;
        std::cout<<"       Stop Voltage: "<<getStopVoltage()<<" volts."<<std::endl;
        std::cout<<"       Step Voltage: "<<getStepVoltage()<<" volts."<<std::endl;
        std::cout<<"   Number of Points: "<<getNumberOfPoints()<<" points."<<std::endl;
        if (getSweepType()==0) {
            std::cout<<"         Sweep Type: Linear."<<std::endl;
        }else {
            std::cout<<"         Sweep Type: Logarithmic."<<std::endl;
        }
        std::cout<<"         Compliance: "<<getCompliance()<<" Amps."<<std::endl;
        std::cout<<"        Sweep Delay: "<<getSweepDelay()<<" milliseconds."<<std::endl;
        std::cout<<std::endl;
        std::cout<<"*******************MEASURE****************************"<<std::endl;
        std::cout<<" Read Back Voltage?: "<<getReadBackVoltage()<<std::endl;
        std::cout<<"   Measure Current?: "<<getMeasureCurrent()<<std::endl;
        std::cout<<"Collect Timestamps?: "<<getCollectTimeStamps()<<std::endl;
        std::cout<<"       Voltage Name: "<<getVoltageName().toStdString()<<std::endl;
        std::cout<<"       Current Name: "<<getCurrentName().toStdString()<<std::endl;
        std::cout<<"  Measurement Range: "<<getMeasurementRange()<<std::endl;
        std::cout<<"               NPLC: "<<getNplc()<<std::endl;
        std::cout<<"        Filter Type: "<<getFilterType()<<std::endl;
        std::cout<<"       Filter Count: "<<getFilterCount()<<std::endl;
        std::cout<<std::endl;
        std::cout<<"*******************ADVANCED***************************"<<std::endl;
        std::cout<<"        Four Wires?: "<<getFourWireMeasurementMode()<<std::endl;
        std::cout<<"SMU Auto Zero Mode?: "<<getSmuAutoZero()<<std::endl;
        std::cout<<"      SMU Off Mode?: "<<getSmuOffMode()<<std::endl;
        std::cout<<std::endl;
    }

protected:

private:

    //Source

    int startVoltage;   //In volts
    int stopVoltage;    //In volts
    int stepVoltage;
    int numberOfPoints; //
    int sweepType;      //0 --> linear, 1 --> logarithmic
    double compliance;  //In Amps
    int sweepDelay;     //In ms

    //Measure

    bool readBackVoltage;
    bool measureCurrent;
    bool collectTimeStamps;
    QString voltageName;
    QString currentName;
    int measurementRange; //0 --> auto, 1 --> 1A, 2 --> 100mA, 3 --> 10mA, 4 --> 1mA, 5 --> 100uA, 6 --> 10uA, 7 --> 1uA
    double nplc;          //0 --> 0.01, 1 --> 0.1, 2 --> 1, 3 --> 10
    int filterType;       //0 --> No Filter, 1 --> Repeat
    int filterCount;      //

    //Advanced
    bool fourWireMeasurementMode;   //
    int  smuAutoZeroMode;           //0 --> off, 1 --> once, 2 --> always
    int  smuOffMode;                //0 --> normal, 1 --> highZ, 2 --> zero, 3 --> guard



};

#endif // SWEEPVOLTAGESETUP_H
