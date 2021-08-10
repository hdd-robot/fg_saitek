/*
 * SaitekSuperPanel.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "SaitekSuperPanel.h"
#include "SaitekGeneric.h"

namespace fg_saitek {

Saitek_Super_Panel::Saitek_Super_Panel() {
	// TODO Auto-generated constructor stub

}

Saitek_Super_Panel::~Saitek_Super_Panel() {
	// TODO Auto-generated destructor stub
}

void Saitek_Super_Panel::read_data_from_saitek() {

	Saitek_Generic::read_from_saitek(buffer_read, this->file_descriptor,3);

	Saitek_Generic::printBits(3, &buffer_read);

	printf(" %hhx -", buffer_read[0]);
	printf(" %hhx -", buffer_read[1]);
	printf(" %hhx -", buffer_read[2]);
	std::cout << std::endl;

}

void Saitek_Super_Panel::write_data_into_saitek() {
//	buffer_write[0]=0x00;
//	buffer_write[1]=0x08;
//	buffer_write[2]=0x10;
//	buffer_write[3]=0x20;

	buffer_write[0]=0x00;
	buffer_write[1]=0x01 | 0x02 | 0x04;

	//[0x00, 0x01 | 0x02 | 0x04]
	//[0x00, 0x08 | 0x10 | 0x20]

	Saitek_Generic::write_into_saitek(buffer_write, this->file_descriptor, 2);
}


bool Saitek_Super_Panel::data_changed() {
	if ((buffer_read[0] == 0) &&
		(buffer_read[1] == 0) &&
		(buffer_read[2] == 0)){
		return true;
	}
	return false;
}

void Saitek_Super_Panel::read_data_from_fligh_gear() {
}

void Saitek_Super_Panel::write_data_into_flightGear() {
}

} /* namespace fg_saitek */
