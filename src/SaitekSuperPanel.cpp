/*
 * SaitekSuperPanel.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "SaitekSuperPanel.h"

namespace fg_saitek {



void Saitek_Super_Panel::read_data_from_saitek() {
	Saitek_Generic::read_from_saitek(saitek_buffer_read, this->file_descriptor,3);


//  debug bits
//  Saitek_Generic::printBits(4, &saitek_buffer_read);

//  debug
//	printf(" %hhx -", saitek_buffer_read[0]);
//	printf(" %hhx -", saitek_buffer_read[1]);
//	printf(" %hhx -", saitek_buffer_read[2]);
//	std::cout << std::endl;

}

void Saitek_Super_Panel::write_data_into_saitek() {
	//	buffer_write[0]=0x00;
	//	buffer_write[1]=0x08;
	//	buffer_write[2]=0x10;
	//	buffer_write[3]=0x20;

	//	buffer_write[0]=0x00;
	//	buffer_write[1]=0x01 | 0x02 | 0x04;

	//[0x00, 0x01 | 0x02 | 0x04]
	//[0x00, 0x08 | 0x10 | 0x20]
	std::cout << "********************" << sizeof(saitek_buffer_write) << std::hex << saitek_buffer_write[0] << std::endl;
	Saitek_Generic::write_into_saitek(saitek_buffer_write, this->file_descriptor, this->size_saitek_buffer);
}


bool Saitek_Super_Panel::data_saitek_changed() {
	if ((saitek_buffer_read[0] == 0) &&
		(saitek_buffer_read[1] == 0) &&
		(saitek_buffer_read[2] == 0)){
		return false;
	}
	return true;
}

bool Saitek_Super_Panel::data_flightGear_changed() {

	bool changed = false;

	for (int i=0; i < sizeof(flightGear_buffer_read); i++){
		if (flightGear_buffer_read[i] != flightGear_buffer_read_saved[i]){
			changed = true;
			break;
		}
	}

	strcpy(flightGear_buffer_read_saved, flightGear_buffer_read);

	return changed;
}


void Saitek_Super_Panel::read_data_from_flightGear() {
	std::cout << "start reading " << std::endl;
	FG_Generic::read_data_from_fg(device_type, flightGear_buffer_read, sizeof(flightGear_buffer_read));
	std::cout << flightGear_buffer_read << std::endl;
	std::cout << "end reading " << std::endl;
}

void Saitek_Super_Panel::write_data_into_flightGear() {
	FG_Generic::write_data_into_fg(device_type, flightGear_buffer_write, sizeof(flightGear_buffer_write));
}


void Saitek_Super_Panel::process() {
	read_data_from_flightGear();
	if (data_flightGear_changed()){
		interpret_data_from_flightGear();
		prepar_data_for_saitek();
		write_data_into_saitek();
	}

	read_data_from_saitek();
	if (data_saitek_changed()){
		init_data_struct();
		interpret_data_from_saitek();
		prepar_data_for_flightGear();
		write_data_into_flightGear();
	}
}

} /* namespace fg_saitek */
