/*
 * config.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_
#include <string>
namespace fg_saitek {

class config {
public:
	std::string device;
	std::string ip_adress;
	int port_in;
	int port_out;
	int rate;

public:
	config();
	virtual ~config();
};

} /* namespace nav_platform */

#endif /* SRC_CONFIG_H_ */
