#include "cadec.h"



Cadec::Cadec();
Cadec::~Cadec();


int Cadec::executeCommand(QString _cmd)
{
    int result = 0;
    int numberOfParameters = 0;

    QRegExp rx("(\\ )"); //RegEx for ' ' (espace)
    QStringList parameters;

    parameters = _cmd.split(rx);
    numberOfParameters = parameters.size();

    #if DEBUG == 1
        qDebug()<<" Number of Parameters = "<<numberOfParameters;
        qDebug()<<" Parameters at (0) = "<<parameters.at(0);
    #endif

    //Debug
    if (parameters.at(0).compare(try_CMD)==0)
    {
        if (numberOfParameters < 2) return MISSING_PARAMETER;

        //get the command to try
        QString cmd = "send ";
        QListIterator<QString> i (parameters);

        i.next();
        while(i.hasNext()){
            cmd.append(i.next());
            cmd.append(" ");
        }
        cmd.chop(1);

        executeCommand(cmd);
        return RESULT_OK;
    }
    if (parameters.at(0).compare(send_CMD)==0)
    {
        if (numberOfParameters < 2) return MISSING_PARAMETER;

        //get the command to try
        QString cmd = "";
        QListIterator<QString> i (parameters);;
        i.next();
        while(i.hasNext()){
            cmd.append(i.next());
            cmd.append(" ");
        }
        cmd.chop(1);

        //Send the command to the keithley
        //TODO
        #if DEBUG == 1
            qDebug()<<" Sending to the keithley --> "<< cmd;
        #endif
        actualInstrument->gpibPort->testInstrunction(cmd);
        return RESULT_OK;
    }
    //Help and info
    if (parameters.at(0).compare(PRINTSETUP_CMD)==0){
        ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->print();
        return RESULT_OK;
    }

    //Setup configuration
    if (parameters.at(0).compare(ENABLEREARMODE_CMD)==0)
    {
        ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->setRearMode(true);
        return RESULT_OK;
    }
    if (parameters.at(0).compare(ENABLEGUARD_CMD)==0)
    {
        ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->setGuardMode(true);
        return RESULT_OK;
    }
    if (parameters.at(0).compare(ENABLEFRONTMODE_CMD)==0)
    {
        ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->setRearMode(false);
        return RESULT_OK;
    }
    if (parameters.at(0).compare(DISABLEGUARD_CMD)==0)
    {
        ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->setGuardMode(false);
        return RESULT_OK;
    }

    //SweepVoltage, PulsedSweepVoltage, StepVoltage setup configuration

    //START VOLTAGE
    if (parameters.at(0).compare(STARTVOLTAGE_CMD)==0){

        if (numberOfParameters < 2) return MISSING_PARAMETER;
        if (numberOfParameters > 2) return TOOMUCH_PARAMETERS;

        int sv = parameters.at(1).toInt();
        Setup* setup = ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup();

        if (abs(sv) > ((KeithleyK24XX*)actualInstrument)->getAbsoluteMaxVoltage()) return START_VOLTAGE_GREATER_THAN_MAX_VOLTAGE;

        //SweepVoltageSetup case
        if (setup->inherits("SweepVoltageSetup")) ((SweepVoltageSetup*)setup)->setStartVoltage(sv);
        //PulsedSweepVoltage case
        //else if (setup->inherits("PulsedSweepVoltage"))  ((PulsedSweepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setStartVoltage(sv);
        //StepVoltage case
        //else if (setup->inherits("StepVoltage"))  ((StepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setStartVoltage(sv);
        return RESULT_OK;

    }
    //STOP VOLTAGE
    if (parameters.at(0).compare(STOPVOLTAGE_CMD)==0){

        if (numberOfParameters < 2) return MISSING_PARAMETER;
        if (numberOfParameters > 2) return TOOMUCH_PARAMETERS;

        int sv = parameters.at(1).toInt();
        Setup* setup = ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup();
        if (abs(sv) > ((KeithleyK24XX*)actualInstrument)->getAbsoluteMaxVoltage()) return STOP_VOLTAGE_GREATER_THAN_MAX_VOLTAGE;


        //SweepVoltageSetup case
        if (setup->inherits("SweepVoltageSetup")) ((SweepVoltageSetup*)setup)->setStopVoltage(sv);
        //PulsedSweepVoltage case
        //else if (setup->inherits("PulsedSweepVoltage"))  ((PulsedSweepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setStopVoltage(sv);
        //StepVoltage case
        //else if (setup->inherits("StepVoltage"))  ((StepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setStopVoltage(sv);
        return RESULT_OK;

    }
    //NUMBER OF POINTS
    if (parameters.at(0).compare(NUMBEROFPOINTS_CMD)==0){

        if (numberOfParameters < 2) return MISSING_PARAMETER;
        if (numberOfParameters > 2) return TOOMUCH_PARAMETERS;

        int np = parameters.at(1).toInt();
        if (np > NUMBER_OF_POINTS_PER_SWEEP_MAX) return TOOMUCH_NUMBER_OF_POINTS_PER_SWEEP;
        if (np < NUMBER_OF_POINTS_PER_SWEEP_MIN) return NOT_ENOUGH_NUMBER_OF_POINTS_PER_SWEEP;

        Setup* setup = ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup();
        //SweepVoltageSetup case
        if (setup->inherits("SweepVoltageSetup")) ((SweepVoltageSetup*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setNumberOfPoints(np);
        //PulsedSweepVoltage case
        //else if (setup->inherits("PulsedSweepVoltage"))  ((PulsedSweepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setNumberOfPoints(np);
        //StepVoltage case
        //else if (setup->inherits("StepVoltage"))  ((StepVoltage*)((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup())->setNumberOfPoints(np);
        return RESULT_OK;

    }
    //NPLC
    if (parameters.at(0).compare(SETNPLC_CMD)==0){

        if (numberOfParameters < 2) return MISSING_PARAMETER;
        if (numberOfParameters > 2) return TOOMUCH_PARAMETERS;

        double nplc = parameters.at(1).toDouble();

        if (actualInstrument->inherits("KeithleyK2430"))
        {
            if (nplc > NPLC_FOR2430_MAX) return NPLC_GREATER_THAN_MAX_VALUE;
            if (nplc < NPLC_FOR2430_MIN) return NPLC_LOWER_THAN_MIN_VALUE;
        }
        else
        {
            if (nplc > NPLC_MAX) return NPLC_GREATER_THAN_MAX_VALUE;
            if (nplc < NPLC_MIN) return NPLC_LOWER_THAN_MIN_VALUE;
        }

        Setup* setup = ((KeithleyK24XXSetup*)actualInstrument->getActualSetup())->getActualMeasureSetup();
        //SweepVoltageSetup case
        if (setup->inherits("SweepVoltageSetup")) ((SweepVoltageSetup*)setup)->setNplc(nplc);

        return RESULT_OK;

    }

    //Keithley k24xx series operation modes
    if (    parameters.at(0).compare(SWEEPVOLTAGE_CMD)==0 ||
            parameters.at(0).compare(SWEEPCURRENT_CMD)==0 ||
            parameters.at(0).compare(PULSEDSWEEPVOLTAGE_CMD)==0 ||
            parameters.at(0).compare(PULSEDSWEEPCURRENT_CMD)==0 ||
            parameters.at(0).compare(STEPCURRENT_CMD)==0 ||
            parameters.at(0).compare(STEPVOLTAGE_CMD)==0 ||
            parameters.at(0).compare(BIASCURRENT_CMD)==0 ||
            parameters.at(0).compare(BIASVOLTAGE_CMD)==0 ||
            parameters.at(0).compare(VOLTMETER_CMD)==0 ||
            parameters.at(0).compare(AMMETER_CMD)==0

            )
    {
        changeOperationMode(_cmd);
        return RESULT_OK;
    }

    //Instrument selection
    if (    parameters.at(0).compare(cd2400_CMD)==0 ||
            parameters.at(0).compare(cd2410_CMD)==0 ||
            parameters.at(0).compare(cd2420_CMD)==0 ||
            parameters.at(0).compare(cd2425_CMD)==0 ||
            parameters.at(0).compare(cd2430_CMD)==0 ||
            parameters.at(0).compare(cd2440_CMD)==0 ||
            parameters.at(0).compare(cdS200_CMD)==0

            )
    {
        changeActualInstrument(_cmd);
        return RESULT_OK;
    }

    //Measure procress
    if (    parameters.at(0).compare(STARTMEASURE_CMD)==0 )
    {
        ((KeithleyK24XX*)actualInstrument)->executeMeasure();
        return RESULT_OK;
    }
    if (    parameters.at(0).compare(STOPMEASURE_CMD)==0 )
    {
        ((KeithleyK24XX*)actualInstrument)->stopMeasure();
        return RESULT_OK;
    }

    return COMMAND_NOT_FOUND;
}


int Cadec::changeOperationMode(QString _om){

//    if (_om.compare(SWEEPVOLTAGE_CMD)==0) {actualInstrument->setInSweepVoltageOperationMode();}
//    if (_om.compare(SWEEPCURRENT_CMD)==0) {actualInstrument->setInSweepCurrentOperationMode();}
//    if (_om.compare(PULSEDSWEEPVOLTAGE_CMD)==0) {actualInstrument->setInPulsedSweepVoltageOperationMode();}
//    if (_om.compare(PULSEDSWEEPCURRENT_CMD)==0) {actualInstrument->setInPulsedSweepCurrentOperationMode();}
//    if (_om.compare(STEPCURRENT_CMD)==0) {actualInstrument->setInStepCurrentOperationMode();}
//    if (_om.compare(STEPVOLTAGE_CMD)==0) {actualInstrument->setInStepVoltageOperationMode();;}
//    if (_om.compare(BIASCURRENT_CMD)==0) {actualInstrument->setInBiasCurrentOperationMode();}
//    if (_om.compare(BIASVOLTAGE_CMD)==0) {actualInstrument->setInBiasVoltageOperationMode();}
//    if (_om.compare(VOLTMETER_CMD)==0) {actualInstrument->setInVoltmeterOperationMode();}
//    if (_om.compare(AMMETER_CMD)==0){actualInstrument->setInAmmeterOperationMode();}

    return RESULT_OK;
}


int Cadec::changeActualInstrument(QString _ref)
{
    actualInstrument = NULL;
    if (_ref.compare("S200")==0)
    {
        actualInstrument = new WentworthS200();
        actualInstrument->setReference(new QString("S200"));
    }
//    if (_ref.compare("AWP1050")==0)
//    {
//        actualInstrument = new WentworthAWP1050();
//        actualInstrument->setReference(new QString("AWP1050"));
//    }
    if (_ref.compare("2400")==0)
    {
        actualInstrument = new KeithleyK2400();
        actualInstrument->setReference(new QString("2400"));
    }
    if (_ref.compare("2410")==0)
    {
        actualInstrument = new KeithleyK2410();
        actualInstrument->setReference(new QString("2410"));

    }
    if (_ref.compare("2420")==0)
    {
        actualInstrument = new KeithleyK2420();
        actualInstrument->setReference(new QString("2420"));
    }
    if (_ref.compare("2425")==0)
    {
        actualInstrument = new KeithleyK2425();
        actualInstrument->setReference(new QString("2425"));
    }
    if (_ref.compare("2430")==0)
    {
        actualInstrument = new KeithleyK2430();
        actualInstrument->setReference(new QString("2430"));
    }
    if (_ref.compare("2440")==0)
    {
        actualInstrument = new KeithleyK2440();
        actualInstrument->setReference(new QString("2440"));
    }
    return 0.0;
}

QString Cadec::getInfo()
{
    return cadecInfo;
}

QString Cadec::getPromptString()
{
    QString pString = "";
    QString instRef = QString(actualInstrument->getReference()->toUpper());
    pString.append(instRef);
    pString.append(":");

    qDebug()<<(((QMetaClassInfo)actualInstrument->metaObject()->classInfo(0)).value());



    if (instRef=="2400" ||
            instRef=="2410" ||
            instRef=="2420" ||
            instRef=="2425" ||
            instRef=="2430" ||
            instRef=="2440" )
    {

        switch (actualInstrument->getOperationMode()){
            case SWEEP_VOLTAGE:
                pString.append("SWEEPVOLTAGE: ");
                break;
            case SWEEP_CURRENT:
                pString.append("SWEEPCURRENT: ");
                break;
            case STEP_VOLTAGE:
                pString.append("STEPVOLTAGE: ");
                break;
            case STEP_CURRENT:
                pString.append("STEPCURRENT: ");
                break;
            case BIAS_VOLTAGE:
                pString.append("BIASVOLTAGE: ");
                break;
            case BIAS_CURRENT:
                pString.append("BIASCURRENT: ");
                break;
            case PULSED_SWEEP_VOLTAGE:
                pString.append("PULSEDSWEEPVOLTAGE: ");
                break;
            case PULSED_SWEEP_CURRENT:
                pString.append("PULSEDSWEEPCURRENT: ");
                break;
            case VOLTMETER:
                pString.append("VOLTMETER: ");
                break;
            case AMMETER:
                pString.append("AMMETER: ");
                break;
            default:
                //nothing to change
                ;
        }
    }
    if (instRef=="S200")
    {
        switch (actualInstrument->getOperationMode()){
            case LOCALMODE:
                pString.append("LM: ");
                break;
            case REMOTEMODE:
                pString.append("RM: ");
                break;
            default:
                //nothing to change
                ;
        }

    }

    return pString;
}

QString Cadec::getHelp()
{
    return helpString;
}

QStringList Cadec::getSuggestedCommandsList(QString _cmd)
{
    QStringList suggestedCommandsList;

    QStringListIterator i(commandsList);
    while (i.hasNext())
    {
        QString c = i.next();
        if (c.contains(_cmd)){
            suggestedCommandsList.append(c);
        }
        //qDebug() << c.toLocal8Bit().constData() << endl;
    }
    return suggestedCommandsList;

}

int Cadec::printSuggestedCommandsList(QTextStream& out,QString _cmd)
{
    int result = 0;
    QStringList suggestedCommandsList = getSuggestedCommandsList(_cmd);
    QStringListIterator i(suggestedCommandsList);
    int counter = 1;
    int columnWidth = 20;
    while (i.hasNext())
    {
        QString c = i.next();
        out<<c.toUpper()+" ";
        if (c.length()<columnWidth)
        {
            int i=0;
            while(i<columnWidth-c.length()){
                out<<" ";
                i++;
            }

        }
        if ((counter%5)==0 )
        {
            out<<"\n";
        }
        counter++;
    }
    out<<"\n";
    out<<"\n";

    return result;
}


/**
  * @brief Prints the Cadec Information.
  * @param none
  * @return none
  */
void Cadec::print()
{
    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"**************CADEC DATA*******************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;




    std::cout<<"*******************************************"<<std::endl;
    std::cout<<"***********CADEC DATA END *****************"<<std::endl;
    std::cout<<"*******************************************"<<std::endl;

}

void Cadec::printLastCommand_ExecutionResult(int commandExecRes, QString commandLine)
{
    QTextStream out(stdout);

    if (commandExecRes == COMMAND_NOT_FOUND)
    {
        std::cout<<"\n";
        std::cout<<"Command not Found!!!!!!!!!\n";
        std::cout<<"Suggested commands are: \n";
        std::cout<<"\n";
        printSuggestedCommandsList(out,commandLine);
    }
    if (commandExecRes == MISSING_PARAMETER)
    {
        std::cout<<"\n";
        std::cout<<"Missing Parameter!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == TOOMUCH_PARAMETERS)
    {
        std::cout<<"\n";
        std::cout<<"Too Much Parameters!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == TOOMUCH_NUMBER_OF_POINTS_PER_SWEEP)
    {
        std::cout<<"\n";
        std::cout<<"Too Much Number Of Points!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == NOT_ENOUGH_NUMBER_OF_POINTS_PER_SWEEP)
    {
        std::cout<<"\n";
        std::cout<<"Not Enough Number of Points!!!!!!!!!\n";
        std::cout<<"Or....\n";
        std::cout<<"Negative Number!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == START_VOLTAGE_GREATER_THAN_MAX_VOLTAGE)
    {
        std::cout<<"\n";
        std::cout<<"Absolute Start Voltage Greater Than Max Voltage!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == STOP_VOLTAGE_GREATER_THAN_MAX_VOLTAGE)
    {
        std::cout<<"\n";
        std::cout<<"Absolute Stop Voltage Greater Than Max Voltage!!!!!!!!!\n";
        std::cout<<"\n";
    }
    if (commandExecRes == NPLC_GREATER_THAN_MAX_VALUE)
    {
        std::cout<<"\n";
        std::cout<<"NPLC Value Greater Than Max Value!!!!!!!!!\n";
        std::cout<<"\n";
    }

    if (commandExecRes == NPLC_LOWER_THAN_MIN_VALUE)
    {
        std::cout<<"\n";
        std::cout<<"NPLC Value Lower Than min Value!!!!!!!!!\n";
        std::cout<<"\n";
    }

}


void Cadec::fillCommandsList()
{
    commandsList.append(PRINTSETUP_CMD);
    commandsList.append(SWEEPVOLTAGE_CMD);
    commandsList.append(SWEEPCURRENT_CMD);
    commandsList.append(PULSEDSWEEPVOLTAGE_CMD);
    commandsList.append(PULSEDSWEEPCURRENT_CMD);
    commandsList.append(STEPCURRENT_CMD);
    commandsList.append(STEPVOLTAGE_CMD);
    commandsList.append(BIASCURRENT_CMD);
    commandsList.append(BIASVOLTAGE_CMD);
    commandsList.append(VOLTMETER_CMD);
    commandsList.append(AMMETER_CMD);
    commandsList.append(STARTVOLTAGE_CMD);
    commandsList.append(STOPVOLTAGE_CMD);
    commandsList.append(NUMBEROFPOINTS_CMD);

    commandsList.append(SETNPLC_CMD);

    commandsList.append(STARTMEASURE_CMD);
    commandsList.append(STOPMEASURE_CMD);
    commandsList.append(ENABLEREARMODE_CMD);
    commandsList.append(ENABLEGUARD_CMD);
    commandsList.append(ENABLEFRONTMODE_CMD);
    commandsList.append(DISABLEGUARD_CMD);

    //Instrument selection
    commandsList.append(cd2400_CMD);
    commandsList.append(cd2410_CMD);
    commandsList.append(cd2420_CMD);
    commandsList.append(cd2425_CMD);
    commandsList.append(cd2430_CMD);
    commandsList.append(cd2440_CMD);
    commandsList.append(cdS200_CMD);
    commandsList.append(cdAWP1050_CMD);

    //Testing commands
    commandsList.append(try_CMD);
    commandsList.append(send_CMD);

    //GPIB Conf
    commandsList.append(SETGPIBADDRESS);
    commandsList.append(CONFIGGPIB);







}
