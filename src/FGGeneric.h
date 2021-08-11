/*
 * FGGeneric.h
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#ifndef SRC_FGGENERIC_H_
#define SRC_FGGENERIC_H_

#define FG_RADIO 1
#define FG_AUTOP 2
#define FG_SWITC 3
#define BUFLEN 512  //Max length of buffer

#include <string>
#include <string.h> //memset
#include <stdlib.h> //exit(0);
#include <unistd.h> // close
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Config.h"



namespace fg_saitek {

class FG_Generic {
public:
	FG_Generic();
	virtual ~FG_Generic();

	static void read_data_from_fg(int, char*, int);
	static void write_data_into_fg(int, char*, int);


};

} /* namespace fg_saitek */

#endif /* SRC_FGGENERIC_H_ */
