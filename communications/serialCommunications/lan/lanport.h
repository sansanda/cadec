#ifndef LANPORT_H
#define LANPORT_H

#include "./communications/serialCommunications/serialport.h"

class LANPort: public SerialPort{

public:
    LANPort();
    ~LANPort();
};

#endif // LANPORT_H
