/*
 * SaitekGeneric.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "SaitekGeneric.h"
#include <iostream>

namespace fg_saitek {

// init static
struct hidraw_report_descriptor Saitek_Generic::rpt_desc;
struct hidraw_devinfo Saitek_Generic::info;
std::vector<std::vector<std::string>*> Saitek_Generic::lst_device_hid;
std::vector<std::vector<std::string>*> Saitek_Generic::lst_device_envent;

Saitek_Generic::Saitek_Generic() {

}

Saitek_Generic::~Saitek_Generic() {

}

const char* Saitek_Generic::bus_str(int bus) {
	switch (bus) {
	case BUS_USB:
		return "USB";
		break;
	case BUS_HIL:
		return "HIL";
		break;
	case BUS_BLUETOOTH:
		return "Bluetooth";
		break;
	case BUS_VIRTUAL:
		return "Virtual";
		break;
	default:
		return "Other";
		break;
	}
}

int Saitek_Generic::init_device(std::string device) {

	char buf[64];
	int res, desc_size;

	int fd = open(device.c_str(), O_RDWR | O_NONBLOCK);

	if (fd < 0) {
		perror("Unable to open device");
		return (-1);
	}

	memset(&rpt_desc, 0x0, sizeof(rpt_desc));
	memset(&info, 0x0, sizeof(info));
	memset(buf, 0x0, sizeof(buf));

	/* Get Report Descriptor Size */
	res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
	if (res < 0) {
		perror("HIDIOCGRDESCSIZE ERROR");
	}

	/* Get Report Descriptor */
	rpt_desc.size = desc_size;
	res = ioctl(fd, HIDIOCGRDESC, &rpt_desc);
	if (res < 0) {
		perror("HIDIOCGRDESC ERROR");
	}

	/* Get Raw Name */
	res = ioctl(fd, HIDIOCGRAWNAME(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("HIDIOCGRAWNAME ERROR");
	}

	/* Get Physical Location */
	res = ioctl(fd, HIDIOCGRAWPHYS(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("HIDIOCGRAWPHYS ERRROR");
	}

	/* Get Raw Info */
	res = ioctl(fd, HIDIOCGRAWINFO, &info);
	if (res < 0) {
		perror("HIDIOCGRAWINFO ERROR");
	}

	return fd;
}

int Saitek_Generic::disable_event_device(std::string device) {
	int res, fd, desc_size;
	;

	char buf[256];
	fd = open(device.c_str(), O_RDONLY | O_NONBLOCK);
	// do not close fd

	// Get NAME
	res = ioctl(fd, EVIOCGNAME(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("EVIOCGNAME ERROR");
	}

	// Getting exclusive access
	res = ioctl(fd, EVIOCGRAB, 1);
	if (res < 0) {
		perror("EVIOCGRAB ERROR ");
	}
	return fd;
}

int Saitek_Generic::read_from_saitek(char* buffer, int fd, int size) {
	memset(buffer, 0, size);
	read(fd, buffer, 255);
	return 0;
}

int Saitek_Generic::write_into_saitek(char *buffer, int fd, int saize) {
	write(fd, buffer, saize);
	return 0;
}



void Saitek_Generic::printBits(const size_t size, const void *const ptr) {
	char *b = (char*) ptr;
	char byte;
	int i, j;
	for (i = size - 1; i >= 0; i--) {
		for (j = 7; j >= 0; j--) {
			byte = (b[i] >> j) & 1;
			printf("%u", byte);
		}
	}
}

void Saitek_Generic::get_list_device_hid() {

	lst_device_hid.clear();
	std::vector<std::string> list_files;
	get_list_file(list_files, "/dev/", "hidraw");

	for (const auto e : list_files) {
		std::vector<std::string> lst_data;
		get_info_device_hid(lst_data, e);

		if ((lst_data[0].compare("HOLTEK Saitek Pro Flight Switch Panel") == 0) || (lst_data[0].compare("Saitek Pro Flight Multi Panel") == 0)
				|| (lst_data[0].compare("Saitek Pro Flight Radio Panel") == 0)) {

			std::vector<std::string> *new_device = new std::vector<std::string>();

			int panel_type = 0;
			if (lst_data[0].compare("Saitek Pro Flight Radio Panel") == 0)
				panel_type = STK_RADIO;
			if (lst_data[0].compare("Saitek Pro Flight Multi Panel") == 0)
				panel_type = STK_AUTOP;
			if (lst_data[0].compare("HOLTEK Saitek Pro Flight Switch Panel") == 0)
				panel_type = STK_SWITC;

			new_device->push_back(std::to_string(panel_type));
			new_device->push_back(e); // file hid
			new_device->push_back(lst_data[0]); // Name
			new_device->push_back(lst_data[1]); // Physique adress
			new_device->push_back(lst_data[2]); // Vendor:Product
			lst_device_hid.push_back(new_device);
		}
	}
}

void Saitek_Generic::get_list_device_event() {
	lst_device_envent.clear();
	std::vector<std::string> list_files;
	get_list_file(list_files, "/dev/input/", "event");

	for (const auto e : list_files) {
		std::vector<std::string> lst_data;
		get_info_device_event(lst_data, e);

		if ((lst_data[0].compare("HOLTEK Saitek Pro Flight Switch Panel") == 0) || (lst_data[0].compare("Saitek Pro Flight Radio Panel") == 0)
				|| (lst_data[0].compare("Saitek Pro Flight Multi Panel") == 0)) {

			std::vector<std::string> *new_device = new std::vector<std::string>();

			int panel_type = 0;
			if (lst_data[0].compare("Saitek Pro Flight Radio Panel") == 0)
				panel_type = STK_RADIO;
			if (lst_data[0].compare("Saitek Pro Flight Multi Panel") == 0)
				panel_type = STK_AUTOP;
			if (lst_data[0].compare("HOLTEK Saitek Pro Flight Switch Panel") == 0)
				panel_type = STK_SWITC;

			new_device->push_back(std::to_string(panel_type));
			new_device->push_back(e); // file hid
			new_device->push_back(lst_data[0]); // Name

			lst_device_envent.push_back(new_device);
		}
	}
}

void Saitek_Generic::get_info_device_hid(std::vector<std::string> &lst, std::string device) {
	char buf[64];
	int res, desc_size;

	int fd = open(device.c_str(), O_RDONLY | O_NONBLOCK);

	if (fd < 0) {
		perror("Unable to open device");
		return;
	}

	struct hidraw_report_descriptor device_desc;
	struct hidraw_devinfo device_info;
	memset(&device_desc, 0x0, sizeof(device_desc));
	memset(&device_info, 0x0, sizeof(device_info));
	memset(buf, 0x0, sizeof(buf));

	/* Get Report Descriptor Size */
	res = ioctl(fd, HIDIOCGRDESCSIZE, &desc_size);
	if (res < 0) {
		perror("HIDIOCGRDESCSIZE ERROR");
	}

	/* Get Report Descriptor */
	device_desc.size = desc_size;
	res = ioctl(fd, HIDIOCGRDESC, &device_desc);
	if (res < 0) {
		perror("HIDIOCGRDESC ERROR");
	}

	/* Get Raw Name */
	res = ioctl(fd, HIDIOCGRAWNAME(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("HIDIOCGRAWNAME ERROR");
	} else {
		lst.push_back(std::string(buf));
	}

	/* Get Physical Location */
	res = ioctl(fd, HIDIOCGRAWPHYS(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("HIDIOCGRAWPHYS ERRROR");
	} else {
		lst.push_back(std::string(buf));
	}

	/* Get Raw Info */
	res = ioctl(fd, HIDIOCGRAWINFO, &device_info);
	if (res < 0) {
		perror("HIDIOCGRAWINFO ERROR");
	} else {
		snprintf(buf, sizeof(buf), "%04hx:%04hx", device_info.vendor, device_info.product);
		lst.push_back(std::string(buf));
	}
	close(fd);
}

void Saitek_Generic::get_info_device_event(std::vector<std::string> &lst, std::string device) {
	int res, fd, desc_size;
	;
	char buf[256];
	struct hidraw_report_descriptor device_desc;
	struct hidraw_devinfo device_info;
	memset(&device_desc, 0x0, sizeof(device_desc));
	memset(&device_info, 0x0, sizeof(device_info));
	memset(buf, 0x0, sizeof(buf));

	fd = open(device.c_str(), O_RDONLY);

	// Get NAME
	res = ioctl(fd, EVIOCGNAME(sizeof(buf) - 1), buf);
	if (res < 0) {
		perror("EVIOCGNAME ERROR");
	}
	lst.push_back(std::string(buf));

	// Get NAME
	res = ioctl(fd, EVIOCGPHYS(sizeof(buf) - 1), buf);
	lst.push_back(std::string(buf));

	close(fd);
}

void Saitek_Generic::get_list_file(std::vector<std::string> &vec, std::string path, std::string filter) {
	for (const auto &entry : std::filesystem::directory_iterator(path)) {
		std::string pth = entry.path();
		if (pth.find(filter) != std::string::npos) {
			vec.push_back(entry.path());
		}
	}
}


} /* namespace fg_saitek */

