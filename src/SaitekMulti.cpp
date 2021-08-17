/*
 * SaitekMulti.cpp
 *
 *  Created on: 15 août 2021
 *      Author: hdd
 */

#include "SaitekMulti.h"

namespace fg_saitek {

Saitek_Multi::Saitek_Multi(int fd) {
	device_type = FG_AUTOP;
	this->size_saitek_buffer = 11;
	this->file_descriptor =fd;

}

Saitek_Multi::~Saitek_Multi() {

}

void Saitek_Multi::interpret_data_from_saitek() {
	memset(&data_multi_saitek, 0, sizeof(data_multi_saitek));

	if(saitek_buffer_read[0] & 1)	{ data_multi_saitek.rotAlt 	= '1' ; }
	if(saitek_buffer_read[0] & 2)	{ data_multi_saitek.rotVs 	= '1' ; }
	if(saitek_buffer_read[0] & 4)	{ data_multi_saitek.rotIas 	= '1' ; }
	if(saitek_buffer_read[0] & 8)	{ data_multi_saitek.rotHdg 	= '1' ; }
	if(saitek_buffer_read[0] & 16)	{ data_multi_saitek.rotCrs 	= '1' ; }
	if(saitek_buffer_read[0] & 32)	{ dataSTK_saved_multi.rotInc  = -dataSTK_saved_multi.rotInc   ; if(dataSTK_saved_multi.rotInc == 1){data_multi_saitek.rotInc  = '1' ;}}
	if(saitek_buffer_read[0] & 64)	{ dataSTK_saved_multi.rotDec  = -dataSTK_saved_multi.rotDec   ; if(dataSTK_saved_multi.rotDec == 1){data_multi_saitek.rotDec  = '1' ;}}
	if(saitek_buffer_read[0] & 128)	{ data_multi_saitek.botAp 	= '1' ; }

	if(saitek_buffer_read[1] & 1)	{ data_multi_saitek.botHdg 		= '1' ; }
	if(saitek_buffer_read[1] & 2)	{ data_multi_saitek.botNav 		= '1' ; }
	if(saitek_buffer_read[1] & 4)	{ data_multi_saitek.botIas 		= '1' ; }
	if(saitek_buffer_read[1] & 8)	{ data_multi_saitek.botAlt 		= '1' ; }
	if(saitek_buffer_read[1] & 16)	{ data_multi_saitek.botVs 		= '1' ; }
	if(saitek_buffer_read[1] & 32)	{ data_multi_saitek.botApr 		= '1' ; }
	if(saitek_buffer_read[1] & 64)	{ data_multi_saitek.botRev 		= '1' ; }
	if(saitek_buffer_read[1] & 128)	{ data_multi_saitek.botAutoTrot = '1' ; }

	if(saitek_buffer_read[2] & 1)	{ data_multi_saitek.botFlapsUp 	= '1' ; }
	if(saitek_buffer_read[2] & 2)	{ data_multi_saitek.botFlapsDown= '1' ; }
	if(saitek_buffer_read[2] & 4)	{ data_multi_saitek.trimUp		= '1' ; }
	if(saitek_buffer_read[2] & 8)	{ data_multi_saitek.trimDown	= '1' ; }

}

void Saitek_Multi::init_data_struct() {
	memset(&data_multi_saitek, 0, sizeof(data_multi_saitek));
	memset(&flightGear_multi_data, 0, sizeof(flightGear_multi_data));
	memset(&dataSTK_saved_multi, 1, sizeof(dataSTK_saved_multi));
}

void Saitek_Multi::prepar_data_for_flightGear() {
	memset(&flightGear_buffer_write, 0, sizeof(flightGear_buffer_write));

	//alt
	char rotary1pos[3]= "0";
	rotary1pos[0]= '0';
	if (data_multi_saitek.rotInc  == '1' && data_multi_saitek.rotAlt == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.rotDec  == '1' && data_multi_saitek.rotAlt == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//VS
	rotary1pos[0]= '0';
	if (data_multi_saitek.rotInc  == '1' && data_multi_saitek.rotVs == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.rotDec  == '1' && data_multi_saitek.rotVs == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//IAS
	rotary1pos[0]= '0';
	if (data_multi_saitek.rotInc  == '1' && data_multi_saitek.rotIas == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.rotDec  == '1' && data_multi_saitek.rotIas == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//HDG
	rotary1pos[0]= '0';
	if (data_multi_saitek.rotInc  == '1' && data_multi_saitek.rotHdg == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.rotDec  == '1' && data_multi_saitek.rotHdg == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//CRS
	rotary1pos[0]= '0';
	if (data_multi_saitek.rotInc  == '1' && data_multi_saitek.rotCrs == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.rotDec  == '1' && data_multi_saitek.rotCrs == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//TRIM
	rotary1pos[0]= '0';
	if (data_multi_saitek.trimUp    == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.trimDown  == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);

	//AP
	if (data_multi_saitek.botAp == '1' )  { strcat(flightGear_buffer_write,"1,"); }	else	{ strcat(flightGear_buffer_write,"0,"); }
	//HDG
	if (data_multi_saitek.botHdg == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }
	//NAV
	if (data_multi_saitek.botNav == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }
	//IAS
	if (data_multi_saitek.botIas == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }
	//ALT
	if (data_multi_saitek.botAlt == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }
	//VS
	if (data_multi_saitek.botVs == '1' )  { strcat(flightGear_buffer_write,"1,"); }	else	{ strcat(flightGear_buffer_write,"0,"); }
	//APR
	if (data_multi_saitek.botApr == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }
	//REV
	if (data_multi_saitek.botRev == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }

	// AUTO Trottle
	if (data_multi_saitek.botAutoTrot == '1' ) { strcat(flightGear_buffer_write,"1,"); } else	{ strcat(flightGear_buffer_write,"0,"); }

	//FLAPS
	rotary1pos[0]= '0';
	if (data_multi_saitek.botFlapsUp    == '1' ) { rotary1pos[0]='1'; }
	if (data_multi_saitek.botFlapsDown  == '1' ) { rotary1pos[0]='2'; }
	rotary1pos[1]=',';
	rotary1pos[2]='\0';
	strcat(flightGear_buffer_write,rotary1pos);
	strcat(flightGear_buffer_write,"\n");
}

void Saitek_Multi::interpret_data_from_flightGear() {
	std::string token;
	std::string receved_str = std::string(flightGear_buffer_read);
	std::vector<std::string> elements = tokenise(receved_str, ',');

	if(elements.size() != 13){
		return;
	}

	//ALT
	std::string alt_val = elements[0];
	strcpy(flightGear_multi_data.alt,  alt_val.c_str());

	//VS
	std::string vs_val = elements[1];
	strcpy(flightGear_multi_data.vs,  vs_val.c_str());

	//IAS
	std::string ias_val = elements[2];
	strcpy(flightGear_multi_data.ias,  ias_val.c_str());

	//HDG
	std::string hdg_val = elements[3];
	strcpy(flightGear_multi_data.hdg,  hdg_val.c_str());

	//CRS
	std::string crs_val = elements[4];
	strcpy(flightGear_multi_data.crs,  crs_val.c_str());

	/// BOTTONS
	std::string res;

	//AP BTN
	std::string ap = elements[5];
	if (ap.compare("true") == 0){ res="1"; } else{ res = "0";}
	strcpy(flightGear_multi_data.btnAp,  res.c_str());

	//HDG BTN
	std::string hdg = elements[6];
	if (hdg.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnHdg,  res.c_str());

	//NAV BTN
	std::string nav = elements[7];
	if (nav.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnNav,  res.c_str());

	//IAS BTN
	std::string ias = elements[8];
	if (ias.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnIas,  res.c_str());

	//ALT BTN
	std::string alt = elements[9];
	if (alt.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnAlt,  res.c_str());

	//VS BTN
	std::string vs = elements[10];
	if (vs.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnVs,  res.c_str());

	//APR BTN
	std::string apr = elements[11];
	if (apr.compare("true") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnApr,  res.c_str());

	//REV BTN
	std::string rev = elements[12];
	if (rev.compare("true\n") == 0) res="1"; else res = "0";
	strcpy(flightGear_multi_data.btnRev,  res.c_str());

}

void Saitek_Multi::prepar_data_for_saitek() {
	memset(&saitek_buffer_write, 0x00, sizeof(saitek_buffer_write));

	char buffer1[5];
	char buffer2[5];
	unsigned char btn = 0;

	memset(&buffer1, 0xA, 5);
	memset(&buffer2, 0xA, 5);

	if ((data_multi_saitek.rotAlt == '1')||(data_multi_saitek.rotVs == '1')) {
		saitekFillBuffer(buffer1, 5, flightGear_multi_data.alt);
		saitekFillBuffer(buffer2, 3, flightGear_multi_data.vs);
	}

	if (data_multi_saitek.rotIas == '1') {
		saitekFillBuffer(buffer1, 3, flightGear_multi_data.ias);
	}

	if (data_multi_saitek.rotHdg == '1') {
		saitekFillBuffer(buffer1, 3, flightGear_multi_data.hdg);
	}

	if (data_multi_saitek.rotCrs == '1') {
		saitekFillBuffer(buffer1, 3, flightGear_multi_data.crs);
	}


	if (strcmp(flightGear_multi_data.btnAp,"1")==0) {
		btn = btn | 1;
	}

	if (strcmp(flightGear_multi_data.btnHdg,"1")==0) {
		btn = btn | 2;
	}

	if (strcmp(flightGear_multi_data.btnNav,"1")==0) {
		btn = btn | 4;
	}

	if (strcmp(flightGear_multi_data.btnIas,"1")==0) {
		btn = btn | 8;
	}

	if (strcmp(flightGear_multi_data.btnAlt,"1")==0) {
		btn = btn | 16;
	}

	if (strcmp(flightGear_multi_data.btnVs,"1")==0) {
		btn = btn | 32;
	}

	if (strcmp(flightGear_multi_data.btnApr,"1")==0) {
		btn = btn | 64;
	}

	if (strcmp(flightGear_multi_data.btnRev,"1")==0) {
		btn = btn | 128;
	}

	//saitek_buffer_write[0] = saitek_buffer_write[0] + 15;

	if (saitek_buffer_write[0] == 2){
		saitek_buffer_write[0] = 18;
	}


	fgStrCpy(&saitek_buffer_write[0], buffer1, 5);
	fgStrCpy(&saitek_buffer_write[5], buffer2, 5);


	// bizzar !! pour ecrire un 2 sur saitek il faut ajouter 16
	if (saitek_buffer_write[0] == 2){
		saitek_buffer_write[0] = 2+16;
	}

//	if (saitek_buffer_write[0] == 5){
//			saitek_buffer_write[0] = ??;
//	}
//
//	if (saitek_buffer_write[0] == 7){
//			saitek_buffer_write[0] = ??;
//	}
//
//	if (saitek_buffer_write[0] == 9){
//			saitek_buffer_write[0] = ??;
//	}


	//write btn
	saitek_buffer_write[10] = btn;

}


void Saitek_Multi::saitekFillBuffer(char dest[], int size_dest, char src[]) {
	char  res[5];
	memset(&res, 0xA, sizeof(res));

	int size_input = 0;
	for (int i = 0 ; i < 5 ; i ++){
		if (src[i] == 0) {  //end of line in receved data
			break;
		}
		size_input++;
	}

	if (size_input == 0){
		src[0] = '0';
		size_input = 1;
	}

	for (int i = 0; i < size_input ; i++){
		if(src[i] == '.'){
			for (int j = i; j < size_input ; j++){
				src[j] = 0;
			}
			size_input = i;
			break;
		}
	}

	if (size_input == 0){
		src[0] = '0';
		size_input = 1;
	}


	for (int i = 0; i < size_dest ; i++){
		res[i+(5-size_input)] = src[i];
	}

	for (int i = 0; i < 5 ; i++){
		if(res[i] >= '0' && res[i] <= '9'){
			res[i] = (res[i] - '0');
		}
	}

	memcpy(dest,res,5);
}

void Saitek_Multi::fgStrCpy(char dest[], char src[], int size){
	int i = 0;
	while (i < size){
		dest[i] = src[i];
		i++;
	}
}


std::vector<std::string> Saitek_Multi::tokenise(const std::string &str, char dilimiter) {
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

} /* namespace fg_saitek */
