/*
 * Config.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "Config.h"

namespace fg_saitek {


std::string Config::radio_ip_adress = "127.0.0.1";
int Config::radio_port_in 	 = 49001;
int Config::radio_port_out   = 49002;

std::string Config::multi_ip_adress = "127.0.0.1";
int Config::multi_port_in    = 49003;
int Config::multi_port_out   = 49004;

std::string Config::switch_ip_adress = "127.0.0.1";
int Config::switch_port_in    = 49005;
int Config::switch_port_out   = 49006;

int Config::rate = 1000000;

Config::Config() {


}

Config::~Config() {

}


} /* namespace fg_saitek */
