#ifndef USBPORT_H
#define USBPORT_H

#include "./communications/serialCommunications/serialport.h"

class USBPort: public SerialPort{

public:
    USBPort();
    ~USBPort();
};

#endif // USBPORT_H
