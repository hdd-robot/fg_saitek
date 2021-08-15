/*
 * SaitekSuperPanel.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKSUPERPANEL_H_
#define SRC_SAITEKSUPERPANEL_H_
#include <cstring>
#include <iostream>
#include "SaitekGeneric.h"
#include "FGGeneric.h"


namespace fg_saitek {

class Saitek_Super_Panel {
protected:
	int  file_descriptor;
	int  size_saitek_buffer;
	char saitek_buffer_read[255];
	char saitek_buffer_write[255];

	char flightGear_buffer_read_saved[255];

	char flightGear_buffer_read[255];
	char flightGear_buffer_write[255];

	int  device_type;

public:


	virtual void read_data_from_saitek();
	virtual void read_data_from_flightGear();

	virtual void write_data_into_saitek();
	virtual void write_data_into_flightGear();

	virtual bool data_saitek_changed();
	virtual bool data_flightGear_changed();

	virtual void process();


	virtual void init_data_struct()=0;
	virtual void interpret_data_from_saitek()=0;
	virtual void prepar_data_for_flightGear()=0;
	virtual void interpret_data_from_flightGear()=0;
	virtual void prepar_data_for_saitek()=0;

	/**
	 * return true if data changed, false otherwise
	 */


};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKSUPERPANEL_H_ */
