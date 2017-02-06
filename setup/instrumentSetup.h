#ifndef INSTRUMENTSETUP_H
#define INSTRUMENTSETUP_H

#include "setup.h"

class InstrumentSetup: public Setup{
    Q_OBJECT

public:
    InstrumentSetup(QString* _name, QString* _obs);
    InstrumentSetup();
    ~InstrumentSetup();

    QString* getObs(){return obs;}
    void setObs(QString* _obs){obs = _obs;}

    QDomElement toQDomElement();

    virtual void print()
    {


        std::cout<<"******************************************************"<<std::endl;
        std::cout<<"**************INSTRUMENT SETUP DATA*******************"<<std::endl;
        std::cout<<"******************************************************"<<std::endl;

        Setup::print();

        std::cout<<"Obsertations = "<<getObs()->toStdString()<<std::endl;

        std::cout<<std::endl;
    }


protected:

private:

    QString*    obs;

};

#endif // INSTRUMENTSETUP_H
