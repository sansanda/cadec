/*
  

  This program was written in Microsoft VC++ 6.0 Standard Edition.  It demonstrates
  use of SCPI commands to communicate with Keithley 2400 sourcemeter with GPIB interface.

  It makes use of the CEC488 driver for Keithley GPIB cards: KPCI-488, KPC-488.2 or KPC-488.2AT

  Please verify proper operation of the GPIB card by use of the TRTEST.exe utility program
  located typically in the \Program Files\CEC488 folder.  Use it to send *IDN? to the instrument
  and then read back (enter command) 50 bytes from the instrument.  If TRTEST.exe can 
  communiate with your SourceMeter, this program will work too.

  Be sure to open the workspace file, 2400.dsw, to run this example.


*/
#include "ieee-cpp.h"
#include "iostream.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "time.h"

void wait (int seconds)
{
	clock_t endwait;
	endwait = clock () + seconds * CLK_TCK;
	while (clock () < endwait) {}
}

int main ()
{
    int status,device,l,i,k=0,h=0,poll;
	long g;
	char c, r[85], sout[1000], choice = 0;

	settimeout (2000);	//changes timeout period from default of 10 secs to 2 secs
	
start:	
	cout << endl;
	cout << endl;
	cout << "This program was written for the Keithley 2400 SourceMeter Series.";
	cout << endl;
	cout << endl;
	cout << "What is the address of the 24xx SourceMeter to be used?  ";
	cin >>device;
	cout << endl;

	initialize (0,0);	// Initializes the GPIB system

	system ("cls");		//clears screen

	send (device,":*rst",&status);  // reset the instrument
	send (device,":OUTP:STAT OFF",&status);  // make sure the output is OFF


//	Test to see if device is present
	spoll (device,&poll,&status);	//reads status of device
	if (status == 0)
	{
		printf("Device found at Address %d is ready \n \n",device);
		send (device,"*idn?",&status);     
		enter (r,100,&l,device,&status);
		g=strlen(r);	//number of characters in string not including null character
		i=0;		//zeros the counter
		printf("You will be using a: \n \n");
		while (i<g)
		{
			while (r[i]!=',')
			{
				printf("%c",r[i]);		//prints KEITHLEY INSTRUMENTS INC.
				i++;
			}
			printf(" , ");
			i++;
			while (r[i]!=',')
			{
				printf("%c",r[i]);		//prints MODEL 24##
				i++;
			}
			i++;
			cout << endl;
			cout << endl;
			cout << "SN# is: ";
			while (r[i]!=',')
			{
				cout << ("%c",r[i]);		//prints serial number
				i++;
			}
			i++;
			cout << endl;
			cout << endl;
			cout << "Firmware revision,date and time / Display board / Analog board / Digital board";
			cout << endl;
			while ((r[i]!=',') && (i!=g))
			{
				printf("%c",r[i]);
				i++;
			}
			cout << endl;
			cout << endl;

		}

answer:
		cout << endl;
		cout << "Is this the correct multimeter 'y' or 'n'?  ";
		cin >> choice;
			if ((choice=='y')||(choice=='Y'))
			{
				system ("cls");
				goto loop;
			}
			if ((choice=='n')||(choice=='N'))
			{
				system ("cls");
				goto start;
			}
		cout << "You did not enter a valid option. Please try again or EXIT \n \n";
		goto answer;
	}
	if (status !=0)
	{
		system ("cls");
		printf("No device present or device not communicating at address %d \n \n \n",device);
		printf("This program was written for Keithley GPIB cards.  Verify \n");
		printf("operation of your Keithley GPIB card using the trtest.exe program\n");
		printf("\n \n \n");
		goto start;
	}
	
	system ("cls");

loop:

	cout << endl;
	cout << endl
//		<< "Enter 'i' to identify particulars of device at address "<<device<< ".\n"
		<< "Enter 'c' to measure current.\n"
		<< "Enter 's' to sweep voltage (1-2 VDC) and measure current.\n"
//		<< "Enter 't' to test code. \n"
		<< "Enter 'v' to measure applied DC volts up to 10 volts.\n"
		<< "Enter 'm' to communicate with new meter.\n"
		<< "Enter 'q' to EXIT program.\n"
		<< "Enter choice: ";
	cin >> choice;
	cout << endl
		<< endl;

/*//////////////////////////////////////////////////////////////*/

	if((choice=='i') || (choice=='I'))
	{
		//  Below identifies connected device at address ??
		send (device,":*rst",&status);
		send (device,"*idn?",&status);     
		enter (r,85,&l,device,&status);    
		printf("You are using a %s \n \n",r);
		cout << endl;
		goto loop;
	}

/*//////////////////////////////////////////////////////////////*/

	if((choice=='s') || (choice=='S'))
	{
		//	Below source volts & measure current sweep
		send (device,":*rst",&status);
		send (device,":TRAC:CLE",&status);
		send (device,":TRAC:POIN 11",&status);
		send (device,":SENS:FUNC:CONC OFF",&status);
		send (device,":SOUR:FUNC VOLT",&status);
		send (device,":SOUR:CLE:AUTO ON",&status);
		send (device,":SENS:FUNC 'CURR:DC'",&status);
		send (device,":SENS:CURR:PROT 0.1",&status);
		send (device,":SOUR:VOLT:START 1",&status);
		send (device,":SOUR:VOLT:STOP 2",&status);
		send (device,":SOUR:VOLT:STEP 0.1",&status);
		send (device,":SOUR:VOLT:MODE SWE",&status);
		send (device,":TRIG:COUN 11",&status);
		send (device,":FORM:ELEM VOLT,CURR",&status);
		send (device,":TRAC:FEED:CONT NEXT",&status);
		send (device,":OUTP:STAT ON",&status);
		send (device,":INIT",&status);
		wait(2);	//# of seconds delay to allow data to be stored
		send (device,":TRAC:DATA?",&status);
		enter (sout,1000,&l,device,&status);

		g=strlen(sout);	//number of characters in string not including null character
		i=0;		//zeros the counter
		printf("     Volts         Current\n");
		printf("     -----         -------\n");
		while (i<g)
		{
			while (sout[i]!=',')
			{
				printf("%c",sout[i]);
				i++;
			}
			printf(" , ");
			i++;
			while ((sout[i]!=',') && (i!=g))
			{
				printf("%c",sout[i]);
				i++;
			}
			i++;
			cout << endl;
		}
		cout << endl;
		goto loop;
	}

/*//////////////////////////////////////////////////////////////*/

	if((choice=='t') || (choice=='T'))
	{
		//	Below is the code test section
		for(c=0;c<5;c++)
			printf(" %d\n %d\n",2*c,2*c+1);
//		printf(" , ");
//		for(k=0;k<10;k++)
//			printf("%d",k);
		cout << endl;
		cout << endl;
		goto loop;
	}

/*/////////////////////////////////////////////////////////////*/

	if((choice=='v') || (choice=='V'))
	{
		//	Below measures volts DC
		send (device,":*rst",&status);
		send (device,":SOUR:FUNC VOLT",&status);
		send (device,":SOUR:VOLT:MODE FIX",&status);
		send (device,":SOUR:VOLT:RANG 10",&status);
		send (device,":SOUR:VOLT:LEV 0",&status);
		send (device,":SENS:FUNC 'VOLT'",&status);
		send (device,":SENS:VOLT:NPLC 10",&status);
		send (device,":SENS:CURR:PROT 0.105",&status);
		send (device,":SENS:CURR:RANG 0.105",&status);
		send (device,":FORM:ELEM VOLT",&status);
		send (device,":OUTP:STAT ON",&status);
		send (device,":INIT",&status);
		send (device,":READ?",&status);
		enter (r,30,&l,device,&status);
		printf("The voltage is %s VDC \n",r);
		cout << endl;
		send (device,":OUTP:STAT OFF",&status);
		goto loop;
	}

/*/////////////////////////////////////////////////////////////*/

	if((choice=='c') || (choice=='C'))
	{
		//	Below measures current DC
		send (device,":*rst",&status);
		send (device,":SOUR:FUNC VOLT",&status);
		send (device,":SOUR:VOLT:MODE FIX",&status);
		send (device,":SOUR:VOLT:RANG 10",&status);
		send (device,":SOUR:VOLT:LEV 0",&status);
		send (device,":SENS:FUNC 'CURR'",&status);
		send (device,":SENS:CURR:NPLC 10",&status);
		send (device,":SENS:CURR:PROT 1",&status);
		send (device,":SENS:CURR:RANG 1",&status);
		send (device,":FORM:ELEM CURR",&status);
		send (device,":OUTP:STAT ON",&status);
		send (device,":INIT",&status);
		send (device,":READ?",&status);
		enter (r,30,&l,device,&status);
		printf("The current is %s Amps \n",r);
		cout << endl;
		send (device,":OUTP:STAT OFF",&status);
		goto loop;
	}

/*//////////////////////////////////////////////////////////////*/

	if((choice=='m') || (choice=='M'))
	{
		initialize (0,0);	// Initialize the GPIB system
		send (device,":*rst",&status);
		send (device,":OUTP:STAT OFF",&status);
		system ("cls");
		goto start;
//		return 0;
	}

/*//////////////////////////////////////////////////////////////*/

	if((choice=='q') || (choice=='Q'))
	{
		initialize (0,0);	// Initialize the GPIB system
		send (device,":*rst",&status);
		send (device,":OUTP:STAT OFF",&status);
		return 0;
	}
/*//////////////////////////////////////////////////////////////*/

	cout << "You did not enter a valid option. Please try again or EXIT \n \n";
		goto loop;

  return 0;
}
