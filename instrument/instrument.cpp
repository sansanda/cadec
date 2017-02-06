#include "./instrument/instrument.h"

Instrument::Instrument(         QString* _name,
                                QString* _idn,
                                QString* _reference,
                                QString* _manufacturer);

Instrument::Instrument();

Instrument::~Instrument();


Setup *Instrument::getActualSetup() const
{
    return actualSetup;
}

void Instrument::setActualSetup(Setup *value)
{
    actualSetup = value;
}
