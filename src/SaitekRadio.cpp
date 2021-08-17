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
	this->size_saitek_buffer = 22;
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

	//XPDR
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

	//XPDR
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

}


std::vector<std::string> Saitek_Radio::tokenise(const std::string &str, char dilimiter){
    std::vector<std::string> tokens;
    int first = 0;
    while(first<str.size()){
        int second = str.find_first_of(dilimiter,first);
        if(second==std::string::npos){
            second = str.size();
        }
        std::string token = str.substr(first, second-first);
        tokens.push_back(token);
        first = second + 1;
    }
    return tokens;
}


void Saitek_Radio::interpret_data_from_flightGear() {

	std::string token;
	std::string receved_str = std::string(flightGear_buffer_read);
	std::vector<std::string> elements = tokenise(receved_str, ',');

	if(elements.size() != 13){
		return;
	}

	//com1 standby
	std::string com1stby = 	elements[0];
	std::vector<std::string>  com1stby_elements = tokenise(com1stby, '.');
	strcpy(flightGear_Radio_data.com1stb,  com1stby_elements[0].c_str());
	strcpy(flightGear_Radio_data.com1stbd, com1stby_elements[1].c_str());

	//com1 active
	std::string com1active =  elements[1];
	std::vector<std::string>  com1act_elements = tokenise(com1active, '.');
	strcpy(flightGear_Radio_data.com1,  com1act_elements[0].c_str());
	strcpy(flightGear_Radio_data.com1d, com1act_elements[1].c_str());

	//com2 standby
	std::string com2stby = 	elements[2];
	std::vector<std::string>  com2stby_elements = tokenise(com2stby, '.');
	strcpy(flightGear_Radio_data.com2stb,  com2stby_elements[0].c_str());
	strcpy(flightGear_Radio_data.com2stbd, com2stby_elements[1].c_str());

	//com2 active
	std::string com2active =  elements[3];
	std::vector<std::string>  com2act_elements = tokenise(com2active, '.');
	strcpy(flightGear_Radio_data.com2,  com2act_elements[0].c_str());
	strcpy(flightGear_Radio_data.com2d, com2act_elements[1].c_str());

	//nav1 stby
	std::string nav1stby = 	elements[4];
	std::vector<std::string>  nav1stby_elements = tokenise(nav1stby, '.');
	strcpy(flightGear_Radio_data.nav1stb,  nav1stby_elements[0].c_str());
	strcpy(flightGear_Radio_data.nav1stbd, nav1stby_elements[1].c_str());

	//nav1 active
	std::string nav1active = 	elements[5];
	std::vector<std::string>  nav1active_elements = tokenise(nav1active, '.');
	strcpy(flightGear_Radio_data.nav1,  nav1active_elements[0].c_str());
	strcpy(flightGear_Radio_data.nav1d, nav1active_elements[1].c_str());

	//nav1 stby
	std::string nav2stby = 	elements[6];
	std::vector<std::string>  nav2stby_elements = tokenise(nav2stby, '.');
	strcpy(flightGear_Radio_data.nav2stb,  nav2stby_elements[0].c_str());
	strcpy(flightGear_Radio_data.nav2stbd, nav2stby_elements[1].c_str());

	//nav2 active
	std::string nav2active = 	elements[7];
	std::vector<std::string>  nav2active_elements = tokenise(nav2active, '.');
	strcpy(flightGear_Radio_data.nav2,  nav2active_elements[0].c_str());
	strcpy(flightGear_Radio_data.nav2d, nav2active_elements[1].c_str());


	//adf standby
	std::string adfstby = 	elements[8];
	strcpy(flightGear_Radio_data.adfstb,  adfstby.c_str());

	//adf active
	std::string adfactive = elements[9];
	strcpy(flightGear_Radio_data.adf,  adfactive.c_str());

	//dme miles
	std::string dme = 	elements[10];
	std::vector<std::string>  dme_elements = tokenise(dme, '.');
	strcpy(flightGear_Radio_data.dme, dme_elements[0].c_str());
	if(dme_elements.size()==2){
		strcpy(flightGear_Radio_data.dmed,  dme_elements[1].c_str());
	}

	//dme time
	std::string dmetime = 	elements[11];
	std::vector<std::string>  dmetime_elements = tokenise(dmetime, '.');
	strcpy(flightGear_Radio_data.dmemin,  dmetime_elements[0].c_str());
	if(dmetime_elements.size()==2){
		strcpy(flightGear_Radio_data.dmemind,  dmetime_elements[1].c_str());
	}

	//adf standby
	std::string xpdr = 	elements[12];
	strcpy(flightGear_Radio_data.xpdr,  xpdr.c_str());

}

void Saitek_Radio::prepar_data_for_saitek() {

	memset(&saitek_buffer_write, 0x00, sizeof(saitek_buffer_write));

	// le premier octet peut etre 1 ou A // A pour ne rien afficher // ne peut etre 0, ni 2-9

	//COM1

	if (data_radio_saitek.topCom1 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com1, flightGear_Radio_data.com1d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.com1stb, flightGear_Radio_data.com1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botCom1 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com1, flightGear_Radio_data.com1d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.com1stb, flightGear_Radio_data.com1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);

	}

	//COM2
	if (data_radio_saitek.topCom2 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com2, flightGear_Radio_data.com2d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.com2stb, flightGear_Radio_data.com2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botCom2 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.com2, flightGear_Radio_data.com2d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.com2stb, flightGear_Radio_data.com2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	//NAV 1

	if (data_radio_saitek.topNav1 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav1, flightGear_Radio_data.nav1d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav1stb, flightGear_Radio_data.nav1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botNav1 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav1, flightGear_Radio_data.nav1d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav1stb, flightGear_Radio_data.nav1stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}

	//NAV 2
	if (data_radio_saitek.topNav2 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botNav2 == '1') {
		char buffer[5];
		freqToBuf(flightGear_Radio_data.nav2, flightGear_Radio_data.nav2d, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToBuf(flightGear_Radio_data.nav2stb, flightGear_Radio_data.nav2stbd, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}


	//ADF
	if (data_radio_saitek.topAdf == '1') {

		char buffer[5];
		freqToADF(flightGear_Radio_data.adf, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToADF(flightGear_Radio_data.adfstb, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botAdf == '1') {
		char buffer[5];
		freqToADF(flightGear_Radio_data.adf, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToADF(flightGear_Radio_data.adfstb, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}


	//DME
	if (data_radio_saitek.topDme == '1') {
		char buffer[5];
		freqToDMEMin(flightGear_Radio_data.dmemin, buffer);
		fgStrCpy(&saitek_buffer_write[0], buffer, 5);
		freqToDME(flightGear_Radio_data.dme, flightGear_Radio_data.dmed, buffer);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);

	}

	if (data_radio_saitek.botDme == '1') {
		char buffer[5];
		freqToDMEMin(flightGear_Radio_data.dmemin, buffer);
		fgStrCpy(&saitek_buffer_write[10], buffer, 5);
		freqToDME(flightGear_Radio_data.dme, flightGear_Radio_data.dmed, buffer);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);

	}

	//XPDR
	if (data_radio_saitek.topXpdr == '1') {
		char buffer[5];
		char blank[5]; int i = 5; while (i--){blank[i]=0xA;}
		freqToXPDR(flightGear_Radio_data.xpdr, buffer);
		fgStrCpy(&saitek_buffer_write[0], blank, 5);
		fgStrCpy(&saitek_buffer_write[5], buffer, 5);
	}

	if (data_radio_saitek.botXpdr == '1') {
		char buffer[5];
		char blank[5]; int i = 5; while (i--){blank[i]=0xA;}
		freqToXPDR(flightGear_Radio_data.xpdr, buffer);
		fgStrCpy(&saitek_buffer_write[10], blank, 5);
		fgStrCpy(&saitek_buffer_write[15], buffer, 5);
	}
}


void Saitek_Radio::freqToDMEMin(char* entier, char* buffer) {
	char cp_entier[5];
	memset(&cp_entier, 0x00, sizeof(cp_entier));
	char dme_val[5];
	memset(&dme_val, 0x00, sizeof(dme_val));


	std::cout << +entier[0] << +entier[1] << +entier[2] << +entier[3] << +entier[4] << std::endl;

	int size_entier = 0;
	for (int i = 0 ; i < 4 ; i ++){
		if (entier[i] == 0) {
			break;
		}
		size_entier = i+1;
	}

	if (size_entier == 0){
		entier[0] = '0';
		size_entier = 1;
	}

	for (int i = 0; i < size_entier ; i++){
		cp_entier[i+(4-size_entier)] = entier[i];
	}



	int val = 0;
	try {
		val = std::stoi(cp_entier);
	}
	catch (std::exception const & e) {
		val = 0xffffff;
	}


	if (val > 999){
		val = 999;
	}
	if (val <= 1){
		val = 1;
	}
	strcpy (cp_entier, std::to_string(val).c_str());

	for (int i = 0 ; i < 4 ; i ++){
		if (cp_entier[i] == 0) {
			break;
		}
		size_entier = i+1;
	}

	if (size_entier == 0){
		cp_entier[0] = '0';
		size_entier = 1;
	}

	for (int i = 0; i < size_entier ; i++){
		dme_val[i+(5-size_entier)] = cp_entier[i];
	}

	if (dme_val[0]== 0) { buffer[0]= 0xA; } else { buffer[0] = dme_val[0] - '0';}
	if (dme_val[1]== 0) { buffer[1]= 0xA; } else { buffer[1] = dme_val[1] - '0';}
	if (dme_val[2]== 0) { buffer[3]= 0xA; } else { buffer[2] = dme_val[2] - '0';}
	if (dme_val[3]== 0) { buffer[4]= 0xA; } else { buffer[3] = dme_val[3] - '0';}
	if (dme_val[4]== 0) { buffer[5]= 0xA; } else { buffer[4] = dme_val[4] - '0';}

}

void Saitek_Radio::freqToDME(char entier[], char decimal[], char buffer[]) {


	char dme_val[5];
	memset(&dme_val, 0x00, sizeof(dme_val));

	dme_val[4]=decimal[0];

	int size_entier = 0;
	for (int i = 0 ; i < 5 ; i ++){
		if (entier[i] == 0) {
			break;
		}
		size_entier = i+1;
	}

	if (size_entier == 0){
		entier[0] = '0';
		size_entier = 1;
	}

	for (int i = 0; i < size_entier ; i++){
		dme_val[i+(4-size_entier)] = entier[i];
	}

	if (dme_val[0]== 0) { buffer[0]= 0xA; } else { buffer[0] = dme_val[0] - '0';}
	if (dme_val[1]== 0) { buffer[1]= 0xA; } else { buffer[1] = dme_val[1] - '0';}
	if (dme_val[2]== 0) { buffer[2]= 0xA; } else { buffer[2] = dme_val[2] - '0';}
	if (dme_val[3]== 0) { buffer[3]= 0xD0; } else { buffer[3] =  abs((dme_val[3] - '0') + 0xD0);}

	buffer[4] = dme_val[4] - '0';

}

void Saitek_Radio::freqToADF(char* entier, char* buffer) {

	if (strlen(entier) == 4){
		buffer[0] = 0xA;
		buffer[1] = entier[0] - '0';
		buffer[2] = entier[1] - '0';
		buffer[3] = entier[2] - '0';
		buffer[4] = entier[3] - '0';
	}
	else{

		buffer[0] = 0xA;
		buffer[1] = 0xA;
		buffer[2] = entier[0] - '0';
		buffer[3] = entier[1] - '0';
		buffer[4] = entier[2] - '0';
	}
}



void Saitek_Radio::freqToXPDR(char* entier, char* buffer) {

	char xpdr_val[5];
	memset(&xpdr_val, '0', sizeof(xpdr_val));

	int size_entier = 0;
	for (int i = 0 ; i < 5 ; i ++){
		if (entier[i] == 0 || entier[i] == '\n' ) {  //end of line in receved data
			break;
		}
		size_entier = i+1;
	}

	if (size_entier == 0){
		entier[0] = '0';
		size_entier = 1;
	}

	for (int i = 0; i < size_entier ; i++){
		xpdr_val[i+(4-size_entier)] = entier[i];
	}


	buffer[0] = 0xA;
	buffer[1] = xpdr_val[0] - '0'  +  0xD0;
	buffer[2] = xpdr_val[1] - '0'  +  0xD0;
	buffer[3] = xpdr_val[2] - '0'  +  0xD0;
	buffer[4] = xpdr_val[3] - '0'  +  0xD0;

}

void Saitek_Radio::fgStrCpy(char dest[], char src[], int size){
	int i = 0;
	while (i < size){
		dest[i] = src[i];
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

void Saitek_Radio::debug_buffer(char buf[], int size) {

	for (int i = 0 ; i < size ; i++){
		std::cout << std::hex << buf[i] << " ";
	}
	std::cout << std::endl;
}

} /* namespace fg_saitek */
