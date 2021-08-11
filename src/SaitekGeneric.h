/*
 * SaitekGeneric.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_SAITEKGENERIC_H_
#define SRC_SAITEKGENERIC_H_

#define STK_RADIO 1
#define STK_AUTOP 2
#define STK_SWITC 3

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <filesystem>


/* Linux */
#include <linux/types.h>
#include <linux/input.h>
#include <linux/hidraw.h>

/*
* Ugly hack to work around failing compilation on systems that don't
* yet populate new version of hidraw.h to userspace.
*/
#ifndef HIDIOCSFEATURE
#warning Please have your distro update the userspace kernel headers
#define HIDIOCSFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x06, len)
#define HIDIOCGFEATURE(len)    _IOC(_IOC_WRITE|_IOC_READ, 'H', 0x07, len)
#endif

/* Unix */
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

/* C */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>


namespace fg_saitek {

class Saitek_Generic {
public:
	static struct hidraw_report_descriptor rpt_desc;
	static struct hidraw_devinfo info;
	static std::vector<std::vector<std::string>*> lst_device_hid;
	static std::vector<std::vector<std::string>*> lst_device_envent;


	static const char* bus_str(int);
	static void printBits(size_t const size, void const * const ptr);

	Saitek_Generic();
	virtual ~Saitek_Generic();

	/**
	 *init_device
	 */
	static int init_device(std::string);

	/**
	 * disable_event_device
	 */
	static int disable_event_device(std::string);


	static void get_list_device_hid();

	static void get_list_device_event();


	static void get_info_device_hid(std::vector<std::string>&, std::string);
	static void get_info_device_event(std::vector<std::string>&, std::string);


	static void get_list_file(std::vector<std::string> & , std::string, std::string filter );


	static int read_from_saitek(char* buffer, int, int);

	static int write_into_saitek(char* buffer, int, int);



};

} /* namespace fg_saitek */

#endif /* SRC_SAITEKGENERIC_H_ */
