/*
 * saitekswitch.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKSWITCH_H_
#define SRC_SAITEKSWITCH_H_

#include <string>
#include <cstring>
#include <iostream>
#include "SaitekSuperPanel.h"

namespace fg_saitek {

typedef struct Saitek_Switch_data{
	char master_bat;
	char master_alt;
	char avionic;
	char fuel_pump;
	char de_ace;
	char pitot_heat;
	char cowl;
	char lght_panel;
	char lght_beacon;
	char lght_nav;
	char lght_strob;
	char lght_taxi;
	char lght_landing;
	char gear_up;
	char gear_down;
	char mag_off;
	char mag_right;
	char mag_left;
	char mag_both;
	char mag_start;
} Saitek_Switch_data;




class Saitek_Switch : public Saitek_Super_Panel{
private:
	Saitek_Switch_data data_struct_saitek;
public:
	Saitek_Switch(int);
	virtual ~Saitek_Switch();
	virtual void interpret_data();
	virtual void init_data_struct();
};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKSWITCH_H_ */
