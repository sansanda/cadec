#ifndef BUFFERTOOLS_H
#define BUFFERTOOLS_H

#include <QDebug>

class BufferContents {

public:
    BufferContents(){}
    ~BufferContents(){}

    static void printBufferContent(int size,char *buffer)
    {
        for (int i=0;i<size;i++) {
            qDebug() << (int)buffer[i]<<endl;
        }
    }

private:

public:


protected:


};

#endif // BUFFERTOOLS_H
