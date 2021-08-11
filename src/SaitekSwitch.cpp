/*
 * saitekswitch.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "SaitekSwitch.h"


namespace fg_saitek {

Saitek_Switch::Saitek_Switch(int fd) {
	device_type = FG_SWITC;
	this->file_descriptor =fd;
}

Saitek_Switch::~Saitek_Switch() {

}

void Saitek_Switch::interpret_data_from_saitek() {

	init_data_struct();

	// Octet 0
	if(saitek_buffer_read[0] & 1)	{ data_struct_saitek.master_bat 	= 1 ; }
	if(saitek_buffer_read[0] & 2) 	{ data_struct_saitek.master_alt 	= 1 ; }
	if(saitek_buffer_read[0] & 4) 	{ data_struct_saitek.avionic 		= 1 ; }
	if(saitek_buffer_read[0] & 8) 	{ data_struct_saitek.fuel_pump 		= 1 ; }
	if(saitek_buffer_read[0] & 16) { data_struct_saitek.de_ace 		= 1 ; }
	if(saitek_buffer_read[0] & 32) { data_struct_saitek.pitot_heat 	= 1 ; }
	if(saitek_buffer_read[0] & 64) { data_struct_saitek.cowl 			= 1 ; }
	if(saitek_buffer_read[0] & 128){ data_struct_saitek.lght_panel 	= 1 ; }

	// Octet 2
	if(saitek_buffer_read[1] & 1)	{ data_struct_saitek.lght_beacon 	= 1 ; }
	if(saitek_buffer_read[1] & 2) 	{ data_struct_saitek.lght_nav 		= 1 ; }
	if(saitek_buffer_read[1] & 4) 	{ data_struct_saitek.lght_strob 	= 1 ; }
	if(saitek_buffer_read[1] & 8) 	{ data_struct_saitek.lght_taxi 		= 1 ; }
	if(saitek_buffer_read[1] & 16) { data_struct_saitek.lght_landing 	= 1 ; }
	if(saitek_buffer_read[1] & 32) { data_struct_saitek.mag_off 		= 1 ; }
	if(saitek_buffer_read[1] & 64) { data_struct_saitek.mag_right 		= 1 ; }
	if(saitek_buffer_read[1] & 128){ data_struct_saitek.mag_left 		= 1 ; }

	// Octet 2
	if(saitek_buffer_read[2] & 1)	{ data_struct_saitek.mag_both 		= 1 ; }
	if(saitek_buffer_read[2] & 2) 	{ data_struct_saitek.mag_start 		= 1 ; }
	if(saitek_buffer_read[2] & 4) 	{ data_struct_saitek.gear_up 		= 1 ; }
	if(saitek_buffer_read[2] & 8) 	{ data_struct_saitek.gear_down 		= 1 ; }

}


void Saitek_Switch::init_data_struct() {
	memset(&data_struct_saitek, 0, sizeof(data_struct_saitek));
}

void Saitek_Switch::prepar_data_for_flightGear() {
}

void Saitek_Switch::interpret_data_from_flightGear() {
}

void Saitek_Switch::prepar_data_for_saitek() {
}

} /* namespace fg_saitek */
