/*
 * SaitekMulti.h
 *
 *  Created on: 15 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKMULTI_H_
#define SRC_SAITEKMULTI_H_
#include <string>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include "SaitekSuperPanel.h"

namespace fg_saitek {

typedef struct saitek_Multi_data{
	unsigned char data[3];
	unsigned char modified;

    unsigned char rotAlt;   //0
    unsigned char rotVs;	//1
    unsigned char rotIas;	//2
    unsigned char rotHdg;	//3
    unsigned char rotCrs;	//4

    unsigned char rotInc;	//5
    unsigned char rotDec;	//6

    unsigned char botAp;    //7
    unsigned char botHdg;	//8
    unsigned char botNav;	//9
    unsigned char botIas;	//10
    unsigned char botAlt;	//11
    unsigned char botVs;	//12
    unsigned char botApr;	//13
    unsigned char botRev;	//14

    unsigned char botAutoTrot;	//15

    unsigned char botFlapsUp;	//16
    unsigned char botFlapsDown;	//17

    unsigned char  trimUp;		//18
    unsigned char  trimDown;	//19

}Saitek_Multi_data;

typedef struct flightGear_Multi_data{
	char alt[10];
	char vs[10];
	char ias[10];
	char hdg[10];
	char crs[10];

	char btnAp[10];
	char btnHdg[10];
	char btnNav[10];
	char btnIas[10];
	char btnAlt[10];
	char btnVs[10];
	char btnApr[10];
	char btnRev[10];
}FlightGear_Multi_data;


typedef struct dataSTKsavedMulti{
    char rotIncD;
    char rotDecD;
}DataSTKsavedMulti;


class Saitek_Multi : public Saitek_Super_Panel {
protected:
	Saitek_Multi_data data_multi_saitek;
	FlightGear_Multi_data flightGear_multi_data;
	DataSTKsavedMulti dataSTK_saved_multi;
	void fgStrCpy(char dest[], char src[], int size);

	void saitekFillBuffer(char dest[], int size_dest, char src[]);

public:
	Saitek_Multi(int);
	virtual ~Saitek_Multi();
	virtual void interpret_data_from_saitek();
	virtual void init_data_struct();
	virtual void prepar_data_for_flightGear();
	virtual void interpret_data_from_flightGear();
	virtual void prepar_data_for_saitek();
	std::vector<std::string> tokenise(const std::string &str, char dilimiter);
};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKMULTI_H_ */
