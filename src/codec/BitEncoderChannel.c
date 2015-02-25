/*
 * Copyright (C) 2007-2015 Siemens AG
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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @version 0.9.3 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#include "EncoderChannel.h"

#include "EXIOptions.h"
#include "BitOutputStream.h"
#include "EXITypes.h"

#ifndef BIT_ENCODER_CHANNEL_C
#define BIT_ENCODER_CHANNEL_C

#if EXI_OPTION_ALIGNMENT == BIT_PACKED


int encode(bitstream_t* stream, uint8_t b) {
	return writeBits(stream, 8, b);
}

/**
 * Encode a single boolean value. A false value is encoded as bit 0 and true
 * value is encode as bit 1.
 */
int encodeBoolean(bitstream_t* stream, int b) {
	uint8_t val = b ? 1 : 0;
	return writeBits(stream, 1, val);
}


/**
 * Encode n-bit unsigned integer. The n least significant bits of parameter
 * b starting with the most significant, i.e. from left to right.
 */
int encodeNBitUnsignedInteger(bitstream_t* stream, uint16_t nbits, uint32_t val)  {
	int errn = 0;
	if (nbits > 0) {
		errn = writeBits(stream, nbits, val);
	}
	return errn;
}

/**
 * Flush underlying bit output stream.
 */
int encodeFinish(bitstream_t* stream) {
	return flush(stream);
}


#endif /* alignment */

#endif












