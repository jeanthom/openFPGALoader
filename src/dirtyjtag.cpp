/*
 * Copyright (C) 2020 Jean THOMAS <pub0@github.jeanthomas.me>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <libusb.h>
#include <string.h>

#include <iostream>

#include "dirtyjtag.hpp"

static const uint16_t kDjtagVid = 0x1209;
static const uint16_t kDjtagPid = 0xC0CA;
static const uint8_t kDjtagEndpointWrite = 0x01;
static const uint8_t kDjtagEndpointRead = 0x82;
static const unsigned int kDjtagTimeout = 1000;

enum CommandIdentifier {
	CMD_STOP = 0x00,
	CMD_INFO = 0x01,
	CMD_FREQ = 0x02,
	CMD_XFER = 0x03,
	CMD_SETSIG = 0x04,
	CMD_GETSIG = 0x05,
	CMD_CLK = 0x06
};

enum SignalIdentifier {
	SIG_TCK = 1 << 1,
	SIG_TDI = 1 << 2,
	SIG_TDO = 1 << 3,
	SIG_TMS = 1 << 4,
	SIG_TRST = 1 << 5,
	SIG_SRST = 1 << 6
};

DirtyJtag::DirtyJtag(uint32_t clkHZ, bool verbose) : libusb_handle(nullptr)
{
	(void)verbose;

	/* libusb init */
	libusb_init(&libusb_ctx);
	libusb_handle = libusb_open_device_with_vid_pid(libusb_ctx, kDjtagVid, kDjtagPid);
	if (!libusb_handle) {
		std::cerr << "Unable to open a connection to your DirtyJTAG device. Please ensure device is plugged and permissions are set correctly." << std::endl;
		libusb_exit(libusb_ctx);
		throw std::exception();
	}
	int res = libusb_claim_interface(libusb_handle, 0);
	if (res) {
		std::cerr << "libusb error while claiming DirtyJTAG interface #0" << std::endl;
		libusb_close(libusb_handle);
		libusb_exit(libusb_ctx);
		throw std::exception();
	}

	setClkFreq(clkHZ);
}

DirtyJtag::~DirtyJtag()
{
	if (libusb_handle) {
		libusb_close(libusb_handle);
	}
	libusb_exit(libusb_ctx);
}

int DirtyJtag::setClkFreq(uint32_t clkHZ)
{
	const uint16_t clkKHZ = clkHZ/1000;
	if (clkKHZ < 1 || clkKHZ > 65535) {
		std::cerr << "Specified frequency is out of range" << std::endl;
		throw std::exception();
	}

	uint8_t setClkFreqCmd[] = {
		CMD_FREQ,
		clkKHZ >> 8,
		clkKHZ, 
		0x00
	};

	int transferred = 0;
	int res = libusb_bulk_transfer(
		libusb_handle,
		kDjtagEndpointWrite,
		setClkFreqCmd,
		sizeof(setClkFreqCmd)/sizeof(setClkFreqCmd[0]),
		&transferred,
		kDjtagTimeout);

	if (res) {
		std::cerr << "setClkFreq transfer error" << std::endl;
		return -1;
	} else {
		return 0;
	}
}

int DirtyJtag::setClkFreq(uint32_t clkHZ, char use_divide_by_5)
{
	(void)use_divide_by_5;
	return setClkFreq(clkHZ);
}

/**
 * store tms in
 * internal buffer
 */
int DirtyJtag::storeTMS(uint8_t *tms, int nb_bit, uint8_t tdi, bool read)
{
	std::cout << "storeTMS" << std::endl;

	(void)read;
	(void)nb_bit;
	(void)tdi;
	(void)tms;

	/* TODO */

	return -1;
}

int DirtyJtag::writeTMS(uint8_t *tdo, int len)
{
	std::cout << "writeTMS" << std::endl;

	(void)len;
	(void)tdo;

	/* TODO */

	return -1;
}

/**
 * store tdi in
 * internal buffer with tms
 * size must be <= 8
 */
int DirtyJtag::storeTDI(uint8_t tdi, int nb_bit, bool read)
{
	std::cout << "storeTDI" << std::endl;

	(void)tdi;
	(void)nb_bit;
	(void)read;

	/* TODO */

	return -1;
}

/**
 * store tdi in
 * internal buffer
 * since TDI is used in shiftDR and shiftIR, tms is always set to 0
 */
int DirtyJtag::storeTDI(uint8_t *tdi, int nb_byte, bool read)
{
	std::cout << "storeTDI (byte variant)" << std::endl;

	(void)tdi;
	(void)nb_byte;
	(void)read;

	/* TODO */

	return -1;
}

int DirtyJtag::writeTDI(uint8_t *tdo, int nb_bit)
{
	std::cout << "writeTDI" << std::endl;

	(void)tdo;
	(void)nb_bit;

	/* TODO */

	return -1;
}

int DirtyJtag::get_buffer_size()
{
	std::cout << "get_buffer_size" << std::endl;

	/* TODO */

	return -1;
}

bool DirtyJtag::isFull()
{
	std::cout << "isFull" << std::endl;

	/* TODO */

	return false;
}
