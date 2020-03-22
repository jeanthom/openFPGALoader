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

#ifndef DIRTYJTAG_H
#define DIRTYJTAG_H
#include <libusb.h>
#include <iostream>
#include <string>
#include <vector>

#include "board.hpp"
#include "jtagInterface.hpp"

/*!
 * \file dirtyjtag.hpp
 * \class DirtyJtag
 * \brief libusb-based DirtyJTAG driver
 * \author Jean THOMAS
 */

class DirtyJtag : public JtagInterface {
	libusb_context *libusb_ctx;
	libusb_device_handle *libusb_handle;
public:
	DirtyJtag(uint32_t clkHZ, bool verbose = false);
	virtual ~DirtyJtag();

	int setClkFreq(uint32_t clkHZ) override;
	int setClkFreq(uint32_t clkHZ, char use_divide_by_5) override;

	/* TMS */
	int storeTMS(uint8_t *tms, int _bit_len, uint8_t tdi = 1,
		bool read = false) override;
	int writeTMS(uint8_t *tdo, int len = 0) override;

	/* TDI */
	int storeTDI(uint8_t tdi, int nb_bit, bool read) override;
	int storeTDI(uint8_t *tdi, int nb_byte, bool read) override;
	int writeTDI(uint8_t *tdo, int nb_bit) override;

	/*!
	 * \brief return internal buffer size (in byte).
	 * \return _buffer_size divided by 2 (two byte for clk) and divided by 8 (one
	 * state == one byte)
	 */
	int get_buffer_size() override;

	bool isFull() override;
};
#endif
