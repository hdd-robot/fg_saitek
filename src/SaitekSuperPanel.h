/*
 * SaitekSuperPanel.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKSUPERPANEL_H_
#define SRC_SAITEKSUPERPANEL_H_

namespace fg_saitek {

class Saitek_Super_Panel {
protected:
	int file_descriptor;
	unsigned char  buffer_read[3]; // buffer read data
	unsigned char  buffer_write[4]; // buffer write data
public:

	Saitek_Super_Panel();
	virtual ~Saitek_Super_Panel();

	virtual void read_data_from_saitek();
	virtual void read_data_from_fligh_gear();

	virtual void write_data_into_saitek();
	virtual void write_data_into_flightGear();


	virtual void init_data_struct()=0;


	virtual void interpret_data()=0;


	/**
	 * return true if data changed, false otherwise
	 */
	virtual bool data_changed();


};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKSUPERPANEL_H_ */
