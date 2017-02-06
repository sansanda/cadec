#ifndef PARALLELPORT_H
#define PARALLELPORT_H

#include "./communications/communicationPort.h"

class ParallelPort: public CommunicationsPort
{
public:
    ParallelPort():CommunicationsPort(){}
    ~ParallelPort(){}
};

#endif // PARALLELPORT_H
