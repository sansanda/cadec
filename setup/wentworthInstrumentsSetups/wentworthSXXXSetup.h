#ifndef WENTWORTHSXXXSETUP_H
#define WENTWORTHSXXXSETUP_H

#include "../instrumentSetup.h"
#include "./wentworthS200ConfigurationParameters.h"

class WentworthSXXXSetup: public InstrumentSetup{
    Q_OBJECT

public:
    WentworthSXXXSetup(QString* _name, QString* _obs);
    WentworthSXXXSetup();
    ~WentworthSXXXSetup();

    Setup* getActualMeasureSetup();

    QDomElement toQDomElement();

    virtual void print()
    {
        InstrumentSetup::print();

        std::cout<<"         Local Mode?: "<<getLocalMode()<<std::endl;
        std::cout<<"         Remote Mode?: "<<getRemoteMode()<<std::endl;

        actualSetup->print();
    }


    bool getLocalMode() const;
    void setLocalMode(bool value);

    bool getRemoteMode() const;
    void setRemoteMode(bool value);

protected:

private:

    bool localMode;      //
    bool remoteMode;     //

    Setup* actualSetup;


};

#endif // WENTWORTHSXXXSETUP_H


