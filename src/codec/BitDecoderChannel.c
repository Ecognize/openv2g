/*
 * Copyright (C) 2007-2012 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer.com</p>
 ********************************************************************/



#include "DecoderChannel.h"
#include "BitInputStream.h"
#include "EXITypes.h"
#include "ErrorCodes.h"

#ifndef BIT_DECODER_CHANNEL_C
#define BIT_DECODER_CHANNEL_C


#if EXI_ALIGNMENT == BIT_PACKED

int decode(bitstream_t* stream, uint8_t* b) {
	uint32_t bb;
	int errn =  readBits(stream, 8, &bb);
	if (errn < 0) {
		return errn;
	}
	if (bb > 256) {
		return EXI_ERROR_UNEXPECTED_BYTE_VALUE;
	} else {
		*b = (uint8_t)bb;
	}
	return errn;
}

int decodeBoolean(bitstream_t* stream, int* b) {
	uint32_t ub;
	int errn = readBits(stream, 1, &ub);
	*b = (ub == 0) ? 0 : 1;
	return errn;
}

int decodeNBitUnsignedInteger(bitstream_t* stream, uint16_t nbits, uint32_t* uint32) {
	if (nbits == 0) {
		*uint32 = 0;
		return 0;
	} else {
		return readBits(stream, nbits, uint32);
	}
}

#endif

#endif

