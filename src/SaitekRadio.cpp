/*
 * SaitekRadio.cpp
 *
 *  Created on: 12 août 2021
 *      Author: hdd
 */

#include "SaitekRadio.h"

namespace fg_saitek {

Saitek_Radio::Saitek_Radio(int fd) {
	device_type = FG_RADIO;
	this->file_descriptor =fd;

}

Saitek_Radio::~Saitek_Radio() {

}

void Saitek_Radio::init_data_struct() {
	memset(&data_radio_saitek, 0, sizeof(data_radio_saitek));
	memset(&flightGear_Radio_data, 0, sizeof(flightGear_Radio_data));
	memset(&dataSTKsaved, 1, sizeof(dataSTKsaved));
}


void Saitek_Radio::interpret_data_from_saitek() {
	memset(&data_radio_saitek, 0, sizeof(data_radio_saitek));
	// Octet 0
	/*
	if((buffer[2] & 1)	&& (dataSTKsaved.topIncD == 1)){ data_radio_saitek.topIncD = 1 ; dataSTKsaved.topIncD = -dataSTKsaved.topIncD  ;}
	if((buffer[2] & 2)	&& (dataSTKsaved.topDecD == 1)){ data_radio_saitek.topDecD = 1 ; dataSTKsaved.topDecD = -dataSTKsaved.topDecD 	;}
	if((buffer[2] & 4)	&& (dataSTKsaved.topInc  == 1)){ data_radio_saitek.topInc  = 1 ; dataSTKsaved.topInc  = -dataSTKsaved.topInc 	;}
	if((buffer[2] & 8)	&& (dataSTKsaved.topDec  == 1)){ data_radio_saitek.topDec  = 1 ; dataSTKsaved.topDec  = -dataSTKsaved.topDec 	;}
	if((buffer[2] & 16) && (dataSTKsaved.botIncD == 1)){ data_radio_saitek.botIncD = 1 ; dataSTKsaved.botIncD = -dataSTKsaved.botIncD 	;}
	if((buffer[2] & 32) && (dataSTKsaved.botDecD == 1)){ data_radio_saitek.botDecD = 1 ; dataSTKsaved.botDecD = -dataSTKsaved.botDecD 	;}
	if((buffer[2] & 64) && (dataSTKsaved.botInc  == 1)){ data_radio_saitek.botInc  = 1 ; dataSTKsaved.botInc  = -dataSTKsaved.botInc 	;}
	if((buffer[2] & 128)&& (dataSTKsaved.botDec  == 1)){ data_radio_saitek.botDec  = 1 ; dataSTKsaved.botDec  = -dataSTKsaved.botDec 	;}
	*/
	if(saitek_buffer_read[2] & 1)	{ dataSTKsaved.topIncD = -dataSTKsaved.topIncD  ; if(dataSTKsaved.topIncD== 1){data_radio_saitek.topIncD = '1' ;}   }
	if(saitek_buffer_read[2] & 2)	{ dataSTKsaved.topDecD = -dataSTKsaved.topDecD  ; if(dataSTKsaved.topDecD== 1){data_radio_saitek.topDecD = '1' ;}   }
	if(saitek_buffer_read[2] & 4)	{ dataSTKsaved.topInc  = -dataSTKsaved.topInc   ; if(dataSTKsaved.topInc == 1){data_radio_saitek.topInc  = '1' ;}   }
	if(saitek_buffer_read[2] & 8)	{ dataSTKsaved.topDec  = -dataSTKsaved.topDec   ; if(dataSTKsaved.topDec == 1){data_radio_saitek.topDec  = '1' ;}   }
	if(saitek_buffer_read[2] & 16)	{ dataSTKsaved.botIncD = -dataSTKsaved.botIncD  ; if(dataSTKsaved.botIncD== 1){data_radio_saitek.botIncD = '1' ;}   }
	if(saitek_buffer_read[2] & 32)	{ dataSTKsaved.botDecD = -dataSTKsaved.botDecD  ; if(dataSTKsaved.botDecD== 1){data_radio_saitek.botDecD = '1' ;}   }
	if(saitek_buffer_read[2] & 64)	{ dataSTKsaved.botInc  = -dataSTKsaved.botInc   ; if(dataSTKsaved.botInc == 1){data_radio_saitek.botInc  = '1' ;}   }
	if(saitek_buffer_read[2] & 128)	{ dataSTKsaved.botDec  = -dataSTKsaved.botDec   ; if(dataSTKsaved.botDec == 1){data_radio_saitek.botDec  = '1' ;}   }

	// Octet 1
	if(saitek_buffer_read[1] & 1)	{ data_radio_saitek.botCom2 	= '1' ; }
	if(saitek_buffer_read[1] & 2) 	{ data_radio_saitek.botNav1 	= '1' ; }
	if(saitek_buffer_read[1] & 4) 	{ data_radio_saitek.botNav2 	= '1' ; }
	if(saitek_buffer_read[1] & 8) 	{ data_radio_saitek.botAdf 		= '1' ; }
	if(saitek_buffer_read[1] & 16) 	{ data_radio_saitek.botDme 		= '1' ; }
	if(saitek_buffer_read[1] & 32) 	{ data_radio_saitek.botXpdr 	= '1' ; }
	if(saitek_buffer_read[1] & 64) 	{ data_radio_saitek.topSwcPush  = '1' ; }
	if(saitek_buffer_read[1] & 128) { data_radio_saitek.botSwcPush  = '1' ; }

	// Octet 2
	if(saitek_buffer_read[0] & 1)	{ data_radio_saitek.topCom1 	= '1' ; }
	if(saitek_buffer_read[0] & 2) 	{ data_radio_saitek.topCom2 	= '1' ; }
	if(saitek_buffer_read[0] & 4) 	{ data_radio_saitek.topNav1 	= '1' ; }
	if(saitek_buffer_read[0] & 8) 	{ data_radio_saitek.topNav2 	= '1' ; }
	if(saitek_buffer_read[0] & 16) 	{ data_radio_saitek.topAdf 		= '1' ; }
	if(saitek_buffer_read[0] & 32) 	{ data_radio_saitek.topDme 		= '1' ; }
	if(saitek_buffer_read[0] & 64) 	{ data_radio_saitek.topXpdr 	= '1' ; }
	if(saitek_buffer_read[0] & 128) { data_radio_saitek.botCom1 	= '1' ; }

}


void Saitek_Radio::prepar_data_for_flightGear() {

	memset(&flightGear_buffer_write, 0, sizeof(flightGear_buffer_write));
    // TOP
	//COM1
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topCom1 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	char rotary1pos[3]= "0";

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topCom1 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topCom1 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topCom1 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topCom1 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';


	strcat(flightGear_buffer_write,rotary1pos);

	//COM2
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topCom2 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topCom2 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topCom2 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topCom2 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topCom2 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//NAV1
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topNav1 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topNav1 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topNav1 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topNav1 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topNav1 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//NAV2
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topNav2 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topNav2 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topNav2 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topNav2 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topNav2 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//ADF
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topAdf == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topAdf == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topAdf == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topAdf == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topAdf == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);


	//DME
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topDme == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topDme == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topDme == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topDme == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topDme == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//DME
	if (data_radio_saitek.topSwcPush == '1' && data_radio_saitek.topXpdr == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.topInc  == '1' && data_radio_saitek.topXpdr == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.topDec  == '1' && data_radio_saitek.topXpdr == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.topIncD == '1' && data_radio_saitek.topXpdr == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.topDecD == '1' && data_radio_saitek.topXpdr == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);
	// TOP
	//COM1
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botCom1 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botCom1 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botCom1 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botCom1 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botCom1 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//COM2
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botCom2 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botCom2 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botCom2 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botCom2 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botCom2 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//NAV1
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botNav1 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botNav1 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botNav1 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botNav1 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botNav1 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//NAV2
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botNav2 == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botNav2 == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botNav2 == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botNav2 == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botNav2 == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//ADF
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botAdf == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botAdf == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botAdf == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botAdf == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botAdf == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//DME
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botDme == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botDme == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botDme == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botDme == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botDme == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//DME
	if (data_radio_saitek.botSwcPush == '1' && data_radio_saitek.botXpdr == '1' ) { strcat(flightGear_buffer_write,"1,"); } 	else	{ strcat(flightGear_buffer_write,"0,"); }

	rotary1pos[0]= '0';
	if (data_radio_saitek.botInc  == '1' && data_radio_saitek.botXpdr == '1' ) { rotary1pos[0]='1'; }
	if (data_radio_saitek.botDec  == '1' && data_radio_saitek.botXpdr == '1' ) { rotary1pos[0]='2'; }
	if (data_radio_saitek.botIncD == '1' && data_radio_saitek.botXpdr == '1' ) { rotary1pos[0]='3'; }
	if (data_radio_saitek.botDecD == '1' && data_radio_saitek.botXpdr == '1' ) { rotary1pos[0]='4'; }
	rotary1pos[1]='\0';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	strcat(flightGear_buffer_write,"\n");

	std::cout << flightGear_buffer_write <<std::endl;

}


void Saitek_Radio::interpret_data_from_flightGear() {
	const char dil[3] = ".,";
	char *token;

	//com1 standby
	token = strtok(flightGear_buffer_read, dil);

	strcpy(flightGear_Radio_data.com1stb, token);

	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com1stbd, token);

	//com1 active
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com1, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com1d, token);

	//com2 standby
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com2stb, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com2stbd, token);

	//com2 Active
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com2, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.com2d, token);

	//nav1 stb
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav1stb, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav1stbd, token);

	//nav1 a
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav1, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav1d, token);

	//nav2 stb
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav2stb, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav2stbd, token);

	//nav2 stb
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav2, token);
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.nav2d, token);

	//adf stf
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.adfstb, token);
	token = (char*)"00";
	strcpy(flightGear_Radio_data.adfstbd, token);

	//adf
	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.adf, token);
	token = (char*)"00";
	strcpy(flightGear_Radio_data.adfd, token);

	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.dme, token);
	token = (char*)"00";
	strcpy(flightGear_Radio_data.dmed, token);

	token = strtok(NULL, dil);
	strcpy(flightGear_Radio_data.xpdr, token);

}

void Saitek_Radio::prepar_data_for_saitek() {

	// le premier bit peut etre 1 ou A // A pour ne rien afficher // ne peut etre 0, ni 2-9

	if (data_radio_saitek.topCom1 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com1, flightGear_Radio_data.com1d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.com1stb, flightGear_Radio_data.com1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botCom1 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com1, flightGear_Radio_data.com1d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.com1stb, flightGear_Radio_data.com1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);

	}

	if (data_radio_saitek.topCom2 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com2, flightGear_Radio_data.com2d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.com2stb, flightGear_Radio_data.com2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botCom2 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com2, flightGear_Radio_data.com2d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.com2stb, flightGear_Radio_data.com2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	if (data_radio_saitek.topNav1 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav1, flightGear_Radio_data.nav1d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav1stb, flightGear_Radio_data.nav1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botNav1 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav1, flightGear_Radio_data.nav1d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav1stb, flightGear_Radio_data.nav1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	if (data_radio_saitek.topNav2 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botNav2 == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	//DME
	if (data_radio_saitek.topDme == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botDme == 1) {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	//XPDR
	if (data_radio_saitek.topXpdr == 1) {
		char buffer[5];
		freqToXPDR(flightGear_Radio_data.xpdr, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botXpdr == 1) {
		char buffer[5];
		freqToXPDR(flightGear_Radio_data.xpdr, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
	}


}


void Saitek_Radio::freqToDME(char* entier, char* decimal, char* buffer) {

}


void Saitek_Radio::freqToXPDR(char* entier, char* buffer) {
	buffer[0] = entier[0] - '0';
	buffer[1] = entier[1] - '0';
	buffer[2] = entier[2] - '0';
	buffer[3] = entier[3] - '0';

}

void Saitek_Radio::fgStrCpy(char src[], char dest[], int size){
	int i = 0;
	while (i < size){
		src[i] = dest[i];
		i++;
	}
}

void Saitek_Radio::freqToBuf(char* entier, char* decimal, char* buffer) {

	// printf(" %c , %c , %c .  %c , %c \n ",entier[0],entier[1],entier[2],decimal[0],decimal[1]);

	buffer[0] = entier[0] - '0';
	buffer[1] = entier[1] - '0';
	buffer[2] = abs((entier[2] - '0') + 0xD0);


	buffer[3] = decimal[0] - '0';
	buffer[4] = decimal[1] - '0';
}



} /* namespace fg_saitek */
