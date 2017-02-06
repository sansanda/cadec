#ifndef FLOATINGPOINTTOOLS_H
#define FLOATINGPOINTTOOLS_H

#include "math.h"
#include "debug.h"

class FloatingPointTools {

public:
    FloatingPointTools(){}
    ~FloatingPointTools(){}

    static int getSign(char* measureInSPFloatingPointFormat){
        int sign = getBit(measureInSPFloatingPointFormat,31);
        #ifndef DEBUG
            if (sign == 1) qDebug() <<  " Sign = -";
            else qDebug() <<  " Sign = +";
        #endif
        return sign;
    }

    static double getExponent(char* measureInSPFloatingPointFormat){
        double result = 0;
        for (int i=23;i<31;i++)
        {
            result = result + getBit(measureInSPFloatingPointFormat,i)*pow(2,i-23);
            #ifndef DEBUG
                qDebug() <<  " Exponent[" << i << "] = "<<getBit(measureInSPFloatingPointFormat,i);
            #endif
        }
        result = pow(2,result-127);
        #ifndef DEBUG
            qDebug() <<  " Exponent = " << result;
        #endif
        return result;
    }

    static double getFraction(char* measureInSPFloatingPointFormat){
        double result = 1;
        for (int i=22;i>=0;i--)
        {
            result = result + getBit(measureInSPFloatingPointFormat,i)*pow(2,-(23-i));
            #ifndef DEBUG
                qDebug() <<  " Fraction[" << i << "] = "<<getBit(measureInSPFloatingPointFormat,i);
            #endif
        }
        #ifndef DEBUG
            qDebug() <<  " Fraction = " << result;
        #endif

        return result;
    }

private:
    static int getBit(char* measureInSPFloatingPointFormat, int index){
        if ((index>=0) & (index<8)){return getBit(measureInSPFloatingPointFormat[0],index);}
        else if ((index>=8) & (index<16)){return getBit(measureInSPFloatingPointFormat[1],(index-8));}
        else if ((index>=16) & (index<24)){return getBit(measureInSPFloatingPointFormat[2],(index-16));}
        else if ((index>=24) & (index<32)){return getBit(measureInSPFloatingPointFormat[3],(index-24));}
        else return -1;
    }
    static int getBit(char c, int index){
        return ((c>>index)& 1);
    }


protected:


};


#endif // FLOATINGPOINTTOOLS_H
