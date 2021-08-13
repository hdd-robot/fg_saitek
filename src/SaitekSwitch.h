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
	char gear_up_down;;
	char mag_val;


} Saitek_Switch_data;


typedef struct Saitek_FlightGear_data{
	char gear_n;
	char gear_l;
	char gear_r;
}Saitek_FlightGear_data;



class Saitek_Switch : public Saitek_Super_Panel{
protected:
	Saitek_Switch_data data_struct_saitek;
public:
	Saitek_Switch(int);
	virtual ~Saitek_Switch();
	virtual void interpret_data_from_saitek();
	virtual void init_data_struct();
	virtual void prepar_data_for_flightGear();
	virtual void interpret_data_from_flightGear();
	virtual void prepar_data_for_saitek();
};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKSWITCH_H_ */
