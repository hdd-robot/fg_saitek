/*
 * FGGeneric.cpp
 *
 *  Created on: 10 août 2021
 *      Author: hdd
 */

#include "FGGeneric.h"
#include <iostream>
namespace fg_saitek {

FG_Generic::FG_Generic() {
	// TODO Auto-generated constructor stub

}

FG_Generic::~FG_Generic() {
	// TODO Auto-generated destructor stub
}

void FG_Generic::read_data_from_fg(int type_data, char *buf, int size) {

	struct sockaddr_in si_other;
	int s, recv_len;
	char buffer[BUFLEN];
	unsigned int slen = sizeof(si_other);

	int PORT_IN = 0;	//The port on which to listen for incoming data

	if (type_data == FG_RADIO) {
		PORT_IN = Config::getRadioPortIn();
	}

	if (type_data == FG_AUTOP) {
		PORT_IN = Config::getMultiPortIn();
	}

	if (type_data == FG_SWITC) {
		PORT_IN = Config::getSwitchPortIn();
	}

	//connect
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		exit(-2);
	}

	memset((char*) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT_IN);
	si_other.sin_addr.s_addr = htonl(INADDR_ANY);

	//bind socket to port
	if (bind(s, (struct sockaddr*) &si_other, sizeof(si_other)) == -1) {
		printf("error bind");
		exit(-3);
	}

	memset(buffer, 0x00, sizeof(buffer));
	//try to receive some data, this is a blocking call

	if ((recv_len = recvfrom(s, buffer, BUFLEN, 0, (struct sockaddr*) &si_other, &slen)) == -1) {
		printf(" error recvfrom()");
		exit(-4);
	}
	strcpy(buf, buffer);
	close(s);
}

void FG_Generic::write_data_into_fg(int type_data, char *buf, int size) {

	int PORT_OUT = 0;         //The port on which WRITE  for modified data
	std::string SERVER = "";  //server

	if (type_data == FG_RADIO) {
		PORT_OUT = Config::getRadioPortOut();
		SERVER = Config::getRadioIpAdress();
	}

	if (type_data == FG_AUTOP) {
		PORT_OUT = Config::getMultiPortOut();
		SERVER = Config::getMultiIpAdress();
	}

	if (type_data == FG_SWITC) {
		PORT_OUT = Config::getSwitchPortOut();
		SERVER = Config::getSwitchIpAdress();
	}


	struct sockaddr_in si_other;
	int s;
	char buffer[BUFLEN];
	int slen = sizeof(si_other);
	//connect
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1) {
		exit(-2);
	}

	memset((char *) &si_other, 0, sizeof(si_other));

	si_other.sin_family = AF_INET;
	si_other.sin_port  = htons(PORT_OUT);

	if (inet_aton(SERVER.c_str() , &si_other.sin_addr) == 0)
	{
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	strcpy(buffer, buf);

	if (sendto(s, buffer, strlen(buffer), 0, (struct sockaddr *) &si_other, slen) == -1) {
			perror("PError: ");
			printf(" error sendto()");
			exit(-6);
	}
	close(s);
}

} /* namespace fg_saitek */
