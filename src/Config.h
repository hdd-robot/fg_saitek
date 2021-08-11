/*
 * Config.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_CONFIG_H_
#define SRC_CONFIG_H_
#include <string>
namespace fg_saitek {

class Config {
public:

	static std::string radio_ip_adress;
	static int radio_port_in;
	static int radio_port_out;

	static std::string multi_ip_adress;
	static int multi_port_in;
	static int multi_port_out;

	static std::string switch_ip_adress;
	static int switch_port_in;
	static int switch_port_out;

	static int rate;

public:
	Config();
	virtual ~Config();


	static std::string& getMultiIpAdress() {
		return multi_ip_adress;
	}

	static void setMultiIpAdress(const std::string &multiIpAdress) {
		multi_ip_adress = multiIpAdress;
	}

	static int getMultiPortIn() {
		return multi_port_in;
	}

	static void setMultiPortIn(int multiPortIn) {
		multi_port_in = multiPortIn;
	}

	static int getMultiPortOut() {
		return multi_port_out;
	}

	static void setMultiPortOut(int multiPortOut) {
		multi_port_out = multiPortOut;
	}

	static std::string& getRadioIpAdress() {
		return radio_ip_adress;
	}

	static void setRadioIpAdress(const std::string &radioIpAdress) {
		radio_ip_adress = radioIpAdress;
	}

	static int getRadioPortIn() {
		return radio_port_in;
	}

	void setRadioPortIn(int radioPortIn) {
		radio_port_in = radioPortIn;
	}

	static int getRadioPortOut() {
		return radio_port_out;
	}

	static void setRadioPortOut(int radioPortOut) {
		radio_port_out = radioPortOut;
	}

	static int getRate() {
		return rate;
	}

	static void setRate(int rates) {
		rate = rates;
	}

	static std::string& getSwitchIpAdress() {
		return switch_ip_adress;
	}

	static void setSwitchIpAdress(const std::string &switchIpAdress) {
		switch_ip_adress = switchIpAdress;
	}

	static int getSwitchPortIn() {
		return switch_port_in;
	}

	static void setSwitchPortIn(int switchPortIn) {
		switch_port_in = switchPortIn;
	}

	static int getSwitchPortOut() {
		return switch_port_out;
	}

	static void setSwitchPortOut(int switchPortOut) {
		switch_port_out = switchPortOut;
	}
};

} /* namespace nav_platform */

#endif /* SRC_Config_H_ */
