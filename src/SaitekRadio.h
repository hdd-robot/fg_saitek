/*
 * SaitekRadio.h
 *
 *  Created on: 12 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKRADIO_H_
#define SRC_SAITEKRADIO_H_
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "SaitekSuperPanel.h"

namespace fg_saitek {


typedef struct saitek_Radio_data{
	unsigned char data[3];
	unsigned char modified;

    unsigned char topCom1;
    unsigned char topCom2;
    unsigned char topNav1;
    unsigned char topNav2;
    unsigned char topAdf;
    unsigned char topDme;
    unsigned char topXpdr;

    unsigned char topInc;
    unsigned char topDec;
    unsigned char topIncD;
    unsigned char topDecD;
    unsigned char topSwcPush;

    unsigned char botCom1;
    unsigned char botCom2;
    unsigned char botNav1;
    unsigned char botNav2;
    unsigned char botAdf;
    unsigned char botDme;
    unsigned char botXpdr;

    unsigned char botInc;
    unsigned char botDec;
    unsigned char botIncD;
    unsigned char botDecD;
    unsigned char botSwcPush;
}Saitek_Radio_data;

typedef struct flightGear_Radio_data{
    char com1stb[10];
    char com1stbd[10];
    char com1[10];
    char com1d[10];

    char com2stb[10];
    char com2stbd[10];
    char com2[10];
    char com2d[10];

    char nav1stb[10];
    char nav1stbd[10];
    char nav1[10];
    char nav1d[10];

    char nav2stb[10];
    char nav2stbd[10];
    char nav2[10];
    char nav2d[10];

    char adf[10];
 //   char adfd[10];
    char adfstb[10];
 //   char adfstbd[10];

    char dme[10];
    char dmed[10];
    char dmemin[10];
    char dmemind[10];

    char xpdr[10];
}FlightGear_Radio_data;

typedef struct dataSTKsaved{
    char topInc;
    char topDec;
    char topIncD;
    char topDecD;
    char botInc;
	char botDec;
	char botIncD;
	char botDecD;
}DataSTKsaved;



class Saitek_Radio : public Saitek_Super_Panel{
protected:
	Saitek_Radio_data data_radio_saitek;
	FlightGear_Radio_data flightGear_Radio_data;
	DataSTKsaved dataSTKsaved;



public:
	Saitek_Radio(int);
	virtual ~Saitek_Radio();
	virtual void interpret_data_from_saitek();
	virtual void init_data_struct();
	virtual void prepar_data_for_flightGear();
	virtual void interpret_data_from_flightGear();
	virtual void prepar_data_for_saitek();

	void freqToDME(char entier[], char decimal[], char buffer[]);
	void freqToDMEMin(char* entier, char* buffer);
	void freqToXPDR(char* entier, char* buffer);
	void fgStrCpy(char dest[], char src[],int size);
	void freqToBuf(char* entier, char* decimal, char* buffer);
	void freqToADF(char* entier, char* buffer);
	std::vector<std::string> tokenise(const std::string &str, char dilimiter);
	void debug_buffer(char[], int);

};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKRADIO_H_ */
