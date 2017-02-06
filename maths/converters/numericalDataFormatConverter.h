#ifndef NUMERICALDATAFORMATCONVERTER_H
#define NUMERICALDATAFORMATCONVERTER_H

#include "math.h"
#include "./maths/dataFormat/floatingPointTools.h"

class NumericalDataFormatConverter {

public:
    NumericalDataFormatConverter(){}
    ~NumericalDataFormatConverter(){}

    static double singlePrecisionDataFormatToDouble(char* numberInSPDataFormat){
        return singlePrecisionDataFormatToDouble(
                    FloatingPointTools::getSign(numberInSPDataFormat),
                    FloatingPointTools::getExponent(numberInSPDataFormat),
                    FloatingPointTools::getFraction(numberInSPDataFormat));
    }

private:

    static double singlePrecisionDataFormatToDouble(int sign,double exponent,double fraction){
        double result = 0;
        result = pow(-1,sign);
        result = result * exponent;
        result = result * fraction;
        return result;
    }


public:



protected:


};

#endif // NUMERICALDATAFORMATCONVERTER_H
