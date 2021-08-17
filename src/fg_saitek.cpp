#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include "Config.h"
#include "SaitekGeneric.h"
#include "SaitekSuperPanel.h"
#include "SaitekSwitch.h"
#include "SaitekRadio.h"
#include "SaitekMulti.h"

using namespace fg_saitek;

static volatile int keepRunning = 1;

std::vector<Saitek_Super_Panel*> obj_saitek;
void print_hello_msg();
void intHandler(int p);

void intHandler(int p) {
	std::cout << "Goodbye ! \n" << std::endl;
	keepRunning = 0;

	// close file events descriptors
	for (auto evt : Saitek_Generic::lst_device_envent) {
		close(std::stoi((*evt)[3])); // close files descriptor opend for blocking keyboard interaction
		delete (evt);
	}

	// close file hid descriptors
	for (auto hid : Saitek_Generic::lst_device_hid) {
		close(std::stoi((*hid)[5])); // close files descriprots
		delete (hid);
	}

	// free objects
	for (auto obj : obj_saitek) {
		delete (obj);
	}

	exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
	print_hello_msg();
	signal(SIGINT, intHandler);

	// Block keyboard interaction
	// Type ; file ; Name ; fd
	Saitek_Generic::get_list_device_event();
	for (auto evt : Saitek_Generic::lst_device_envent) {
		int fd = Saitek_Generic::disable_event_device((*evt)[1]);
		evt->push_back(std::to_string(fd));
	}

	// get list device
	Saitek_Generic::get_list_device_hid();
	// Type ; File ; Name ; Phys @ ; Vendor:Product ; fd
	for (auto hid : Saitek_Generic::lst_device_hid) {
		int fd = Saitek_Generic::init_device((*hid)[1]);
		hid->push_back(std::to_string(fd));
	}

	for (auto hid : Saitek_Generic::lst_device_hid) {
		Saitek_Super_Panel *obj = nullptr;
		if (std::stoi((*hid)[0]) == STK_RADIO) {
			obj = new Saitek_Radio(std::stoi((*hid)[5]));
		}
		if (std::stoi((*hid)[0]) == STK_AUTOP) {
			obj = new Saitek_Multi(std::stoi((*hid)[5]));
		}
		if (std::stoi((*hid)[0]) == STK_SWITC) {
			obj = new Saitek_Switch(std::stoi((*hid)[5]));
		}

		if (obj != nullptr) {
			obj_saitek.push_back(obj);
		}
	}

	for (auto obj : obj_saitek) {
		obj->init_data_struct();
	}

	while (keepRunning) {
		int saitek_touched = 0;


		for (auto obj : obj_saitek) {
			saitek_touched = 0;
			obj->read_data_from_saitek();
			if (obj->data_saitek_changed()) {
				obj->interpret_data_from_saitek();
				obj->prepar_data_for_flightGear();
				obj->write_data_into_flightGear();
			}

			obj->read_data_from_flightGear();
			if (obj->data_flightGear_changed() || saitek_touched == 1) {
				obj->interpret_data_from_flightGear();
				obj->prepar_data_for_saitek();
				obj->write_data_into_saitek();
			}
		}
		usleep(Config::getRate() * 1);
	}

	return 0;
}



void print_hello_msg(){


	std::cout << std::endl;
	std::cout << "  ███████╗ ██████╗       ███████╗ █████╗ ██╗████████╗███████╗██╗  ██╗ " << std::endl;
	std::cout << "  ██╔════╝██╔════╝       ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██║ ██╔╝ " << std::endl;
	std::cout << "  █████╗  ██║  ███╗█████╗███████╗███████║██║   ██║   █████╗  █████╔╝  " << std::endl;
	std::cout << "  ██╔══╝  ██║   ██║╚════╝╚════██║██╔══██║██║   ██║   ██╔══╝  ██╔═██╗  " << std::endl;
	std::cout << "  ██║     ╚██████╔╝      ███████║██║  ██║██║   ██║   ███████╗██║  ██╗ " << std::endl;
	std::cout << "  ╚═╝      ╚═════╝       ╚══════╝╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝╚═╝  ╚═╝ " << std::endl;
	std::cout << std::endl;

}


