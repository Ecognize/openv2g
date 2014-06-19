/*
 * Copyright (C) 2007-2014 Siemens AG
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
 * @version 0.9 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



#include "DecoderChannel.h"

#include "EXIConfig.h"
#include "EXIOptions.h"
#include "BitInputStream.h"
#include "EXITypes.h"
#include "MethodsBag.h"
/*#include "v2gEXICoder.h"*/
#include "ErrorCodes.h"

#include "StringValueTable.h"

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
#include "DynamicMemory.h"
#endif /* DYNAMIC_ALLOCATION */

#ifndef ABSTRACT_DECODER_CHANNEL_C
#define ABSTRACT_DECODER_CHANNEL_C

/* unsigned long == 64 bits, 10 * 7bits = 70 bits */
#define MAX_OCTETS_FOR_UNSIGNED_INTEGER_64 10
/* unsigned int == 32 bits, 5 * 7bits = 35 bits */
#define MAX_OCTETS_FOR_UNSIGNED_INTEGER_32 5

/* buffer for reading (arbitrary) large integer values */
static uint8_t maskedOctets[MAX_OCTETS_FOR_UNSIGNED_INTEGER_64];


static int _decodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv, int negative) {
	int errn = 0;
	int i = 0;
	uint8_t b;
	int k;

	do {
		/* Read the next octet */
		errn = decode(stream, &b);
		if (errn == 0) {
			if(i < MAX_OCTETS_FOR_UNSIGNED_INTEGER_64) {
				/* the 7 least significant bits hold the actual value */
				maskedOctets[i++] = (b & 127);
			} else {
				errn = EXI_UNSUPPORTED_INTEGER_VALUE;
			}
		}
	} while( errn == 0 && b >= 128 ); /* no more octets ? */

	if ( errn == 0 ) {
		/* For negative values, the Unsigned Integer holds the
		 * magnitude of the value minus 1 */

		switch(i) {
		case 1: /* 7 bits */
			if (negative) {
				iv->val.int8 =  (int8_t)(-( b + 1));
				iv->type = EXI_INTEGER_8;
			} else {
				iv->val.uint8 = b;
				iv->type = EXI_UNSIGNED_INTEGER_8;
			}
			break;
		case 2: /* 14 bits */
			iv->val.uint16 = 0;
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint16  = (uint16_t)((iv->val.uint16 << 7) | maskedOctets[k]);
			}
			if (negative) {
				iv->val.int16 = (int16_t)( -( iv->val.uint16 + 1 ));
				iv->type = EXI_INTEGER_16;
			} else {
				iv->type = EXI_UNSIGNED_INTEGER_16;
			}
			break;
		case 3: /* 21 bits */
		case 4: /* 28 bits */
			iv->val.uint32 = 0;
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint32 = (iv->val.uint32 << 7) | maskedOctets[k];
			}
			if (negative) {
				iv->val.int32 = (int32_t)(-( iv->val.uint32 + 1));
				if (iv->val.int32 <= INT16_MAX && iv->val.int32 >= INT16_MIN ) {
					iv->type = EXI_INTEGER_16;
				} else {
					iv->type = EXI_INTEGER_32;
				}
			} else {
				if (iv->val.uint32 <= UINT16_MAX) {
					iv->type = EXI_UNSIGNED_INTEGER_16;
				} else {
					iv->type = EXI_UNSIGNED_INTEGER_32;
				}
			}
			break;
		case 5: /* 35 bits */
		case 6: /* 42 bits */
		case 7: /* 49 bits */
		case 8: /* 56 bits */
		case 9: /* 63 bits */
		case 10: /* 70 bits */
			iv->val.uint64 = 0;
			for (k = i-1; k >= 0 ; k--) {
				iv->val.uint64  = (iv->val.uint64 << 7) | maskedOctets[k];
			}
			if (negative) {
				if (i > 9) {
					/* too large */
					return EXI_UNSUPPORTED_INTEGER_VALUE;
				}
				iv->val.int64 = (int64_t)(-( iv->val.uint64 + 1));
				if (iv->val.int64 <= INT32_MAX && iv->val.int64 >= INT32_MIN ) {
					iv->type = EXI_INTEGER_32;
				} else {
					iv->type = EXI_INTEGER_64;
				}
			} else {
				if (iv->val.uint64 <= UINT32_MAX) {
					iv->type = EXI_UNSIGNED_INTEGER_32;
					/* iv->val.uint32 = iv->val.uint64;*/
				} else {
					iv->type = EXI_UNSIGNED_INTEGER_64;
				}
			}
			break;
		default:
			errn = EXI_UNSUPPORTED_INTEGER_VALUE;
			break;
		}
	}

	return errn;
}

int decodeUnsignedInteger(bitstream_t* stream, exi_integer_t* iv) {
	return _decodeUnsignedInteger(stream, iv, 0);
}

int decodeUnsignedInteger16(bitstream_t* stream, uint16_t* uint16) {
	unsigned int mShift = 0;
	int errn = 0;
	uint8_t b;
	*uint16 = 0;

	do {
		/* 1. Read the next octet */
		errn = decode(stream, &b);
		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint16 = (uint16_t)(*uint16 + ((b & 127) << mShift));
		/* 3. Multiply the multiplier by 128 */
		mShift += 7;
		/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);

	return errn;
}

int decodeUnsignedInteger32(bitstream_t* stream, uint32_t* uint32) {
	/* 0XXXXXXX ... 1XXXXXXX 1XXXXXXX */
	unsigned int mShift = 0;
	int errn = 0;
	uint8_t b;
	*uint32 = 0;

	do {
		/* 1. Read the next octet */
		errn = decode(stream, &b);
		/* 2. Multiply the value of the unsigned number represented by the 7
		 * least significant
		 * bits of the octet by the current multiplier and add the result to
		 * the current value */
		*uint32 += (uint32_t)((b & 127) << mShift);
		/* 3. Multiply the multiplier by 128 */
		mShift += 7;
		/* 4. If the most significant bit of the octet was 1, go back to step 1 */
	} while (errn == 0 && (b >> 7) == 1);

	return errn;
}

/**
 * Decode an arbitrary precision non negative integer using a sequence of
 * octets. The most significant bit of the last octet is set to zero to
 * indicate sequence termination. Only seven bits per octet are used to
 * store the integer's value.
 */
int decodeUnsignedInteger64(bitstream_t* stream, uint64_t* uint64) {
	unsigned int mShift = 0;
	int errn = 0;
	uint8_t b;
	*uint64 = 0L;

	do {
		errn = decode(stream, &b);
		*uint64 += ((uint64_t) (b & 127)) << mShift;
		mShift += 7;
	} while (errn == 0 && (b >> 7) == 1);

	return errn;
}


int decodeInteger(bitstream_t* stream, exi_integer_t* iv) {
	int b;
	int errn = decodeBoolean(stream, &b);
	if (errn == 0) {
		errn = _decodeUnsignedInteger(stream, iv, b);
	}

	return errn;
}


/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger16(bitstream_t* stream, int16_t* int16) {
	int b;
	uint16_t uint16;
	int errn = decodeBoolean(stream, &b);

	if (errn == 0) {
		if (b) {
			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			errn = decodeUnsignedInteger16(stream, &uint16);
			*int16 = (int16_t)(-(uint16 + 1));
		} else {
			/* positive */
			errn = decodeUnsignedInteger16(stream, &uint16);
			*int16 = (int16_t)(uint16);
		}
	}

	return errn;
}

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger32(bitstream_t* stream, int32_t* int32) {
	int b;
	uint32_t uint32;
	int errn = decodeBoolean(stream, &b);

	if (errn == 0) {
		if (b) {
			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			errn = decodeUnsignedInteger32(stream, &uint32);
			*int32 = (int32_t)(-(uint32 + 1));
		} else {
			/* positive */
			errn = decodeUnsignedInteger32(stream, &uint32);
			*int32 = (int32_t)(uint32);
		}
	}

	return errn;
}

/**
 * Decode an arbitrary precision integer using a sign bit followed by a
 * sequence of octets. The most significant bit of the last octet is set to
 * zero to indicate sequence termination. Only seven bits per octet are used
 * to store the integer's value.
 */
int decodeInteger64(bitstream_t* stream, int64_t* int64) {
	int b;
	uint64_t uint64;
	int errn = decodeBoolean(stream, &b);

	if (errn == 0) {
		if (b) {
			/* For negative values, the Unsigned Integer holds the
			 * magnitude of the value minus 1 */
			errn = decodeUnsignedInteger64(stream, &uint64);
			*int64 = (int64_t)(-(uint64 + 1));
		} else {
			/* positive */
			errn = decodeUnsignedInteger64(stream, &uint64);
			*int64 = (int64_t)(uint64);
		}
	}

	return errn;
}

/**
 * Decode a Float datatype as two consecutive Integers.
 * The first Integer represents the mantissa of the floating point
 * number and the second Integer represents the base-10 exponent
 * of the floating point number.
 */
int decodeFloat(bitstream_t* stream, exi_float_me_t* f) {
	int errn = decodeInteger64(stream, &f->mantissa);
	if (errn == 0) {
		errn = decodeInteger16(stream, &f->exponent);
	}
	return errn;
}

/**
 * Decode a decimal represented as a Boolean sign followed by two Unsigned
 * Integers. A sign value of zero (0) is used to represent positive Decimal
 * values and a sign value of one (1) is used to represent negative Decimal
 * values The first Integer represents the integral portion of the Decimal
 * value. The second positive integer represents the fractional portion of
 * the decimal with the digits in reverse order to preserve leading zeros.
 */
int decodeDecimal(bitstream_t* stream, exi_decimal_t* d) {
	int errn = decodeBoolean(stream, &d->negative);
	if (errn == 0) {
		errn = decodeUnsignedInteger(stream, &d->integral);
		if (errn == 0) {
			errn = decodeUnsignedInteger(stream, &d->reverseFraction);
		}
	}

	return errn;
}

/**
 * Decode a sequence of characters for a given length.
 */
int decodeStringOnly(bitstream_t* stream, uint16_t len, exi_string_t* s) {
	int errn = 0;
	int extraChar = 0;
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
	extraChar = 1; /* null terminator */
#endif /* STRING_REPRESENTATION_ASCII */

	if ( (len + extraChar) > s->size) {
#if MEMORY_ALLOCATION == STATIC_ALLOCATION
		errn = EXI_ERROR_OUT_OF_STRING_BUFFER;
#endif /* STATIC_ALLOCATION */
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
		if(s->size > 0) {
			errn = exiFreeDynamicStringMemory(s);
			if(errn) {
				return errn;
			}
		}
		errn = exiAllocateDynamicStringMemory(s, s->len);
#endif /* DYNAMIC_ALLOCATION */
	}
	if(errn == 0) {
		errn = decodeCharacters(stream, len, s->characters);
		s->len = len;
	}

	return errn;
}

/**
 * Decode a length prefixed sequence of characters.
 */
int decodeString(bitstream_t* stream, exi_string_t* s) {
	int errn = decodeUnsignedInteger16(stream, &s->len);
	if (errn == 0) {
		errn = decodeStringOnly(stream, s->len, s);
	}
	return errn;
}

static int _readStringValueLocalHit(bitstream_t* stream, exi_state_t* state, uint16_t qnameID, uint32_t* localID) {
	int errn;
	uint16_t codingLength;

	if( state->stringTable.sizeLocalStrings > qnameID ) {
		errn = exiGetCodingLength(state->stringTable.numberOfLocalStrings[qnameID], &codingLength);
		if(errn == 0) {
			errn = decodeNBitUnsignedInteger(stream, codingLength, localID);
		}
	} else {
		errn = EXI_ERROR_OUT_OF_BOUNDS;
	}

	return errn;
}


static int _readStringValueGlobalHit(bitstream_t* stream, exi_state_t* state, uint32_t* globalID) {
	int errn;
	uint16_t codingLength;

	errn = exiGetCodingLength(state->stringTable.numberOfGlobalStrings, &codingLength);
	if(errn == 0) {
		errn = decodeNBitUnsignedInteger(stream, codingLength, globalID);
	}

	return errn;
}

int decodeStringValue(bitstream_t* stream, exi_state_t* state, uint16_t qnameID, exi_string_value_t* s) {
	uint16_t L;
	int errn = decodeUnsignedInteger16(stream, &L);
	if (errn == 0) {
		switch (L) {
		case 0:
			/* local value partition */
			s->type = EXI_STRING_VALUE_LOCAL_HIT;
			errn = _readStringValueLocalHit(stream, state, qnameID, &s->localID);
			break;
		case 1:
			/* found in global value partition */
			s->type = EXI_STRING_VALUE_GLOBAL_HIT;
			errn = _readStringValueGlobalHit(stream, state, &s->globalID);
			break;
		default:
			/* not found in global value (and local value) partition
			 * ==> string literal is encoded as a String with the length
			 * incremented by two */
			s->type = EXI_STRING_VALUE_MISS;
			s->miss.len = L = (uint16_t)(L - 2);
			errn = decodeStringOnly(stream, L, &(s->miss));
			if(errn == 0) {
#if EXI_OPTION_VALUE_PARTITION_CAPACITY != 0
#if EXI_OPTION_VALUE_MAX_LENGTH != 0
				/* If length L is greater than zero the string S is added */
				if(L > 0) {
					/* After encoding the string value, it is added to both the
					 * associated "local" value string table partition and the global
					 * value string table partition */
#if EXI_OPTION_VALUE_MAX_LENGTH < 0
				errn = exiAddStringValue(&state->stringTable, &(s->miss), qnameID);
# else /* EXI_v2gVALUE_MAX_LENGTH < 0  */
					if (L <= EXI_OPTION_VALUE_MAX_LENGTH) {
						errn = exiAddStringValue(&state->stringTable, &(s->miss), qnameID);
					}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH < 0  */
				}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH != 0 */
#endif /* EXI_OPTION_VALUE_PARTITION_CAPACITY != 0 */
			}
			break;
		}
	}

	return errn;
}

int decodeRCSStringValue(bitstream_t* stream, exi_state_t* state, uint16_t qnameID, exi_rcs_t* rcs, exi_string_value_t* s) {
	unsigned int i;
	uint32_t cp;
	uint16_t L;
	int errn = decodeUnsignedInteger16(stream, &L);
	if (errn == 0) {
		switch (L) {
		case 0:
			/* local value partition */
			s->type = EXI_STRING_VALUE_LOCAL_HIT;
			errn = _readStringValueLocalHit(stream, state, qnameID, &s->localID);
			break;
		case 1:
			/* found in global value partition */
			s->type = EXI_STRING_VALUE_GLOBAL_HIT;
			errn = _readStringValueGlobalHit(stream, state, &s->globalID);
			break;
		default:
			/* not found in global value (and local value) partition
			 * ==> string literal is encoded as a String with the length
			 * incremented by two */
			s->type = EXI_STRING_VALUE_MISS;
			s->miss.len = L = (uint16_t)(L - 2);

			if (L > s->miss.size) {
#if MEMORY_ALLOCATION == STATIC_ALLOCATION
				errn = EXI_ERROR_OUT_OF_STRING_BUFFER;
#endif /* STATIC_ALLOCATION */
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
				if(s->miss.size > 0) {
					errn = exiFreeDynamicStringMemory(&(s->miss));
				}
				if(errn == 0) {
					errn = exiAllocateDynamicStringMemory(&(s->miss), L);
				}
#endif /* DYNAMIC_ALLOCATION */
			}
			if(errn == 0) {
				for (i = 0; i < L && errn >= 0; i++) {
					errn = decodeNBitUnsignedInteger(stream, rcs->codingLength, &cp);
					s->miss.characters[i] = rcs->characters[cp];
				}
#if EXI_OPTION_VALUE_PARTITION_CAPACITY != 0
#if EXI_OPTION_VALUE_MAX_LENGTH != 0
				/* If length L is greater than zero the string S is added */
				if(errn == 0 && L > 0) {
					/* After encoding the string value, it is added to both the
					 * associated "local" value string table partition and the global
					 * value string table partition */
#if EXI_OPTION_VALUE_MAX_LENGTH < 0
					errn = exiAddStringValue(&state->stringTable, &(s->miss), qnameID);
# else /* EXI_OPTION_VALUE_MAX_LENGTH < 0  */
					if (L <= EXI_OPTION_VALUE_MAX_LENGTH) {
						errn = exiAddStringValue(&state->stringTable, &(s->miss), qnameID);
					}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH < 0  */
				}
#endif /* EXI_OPTION_VALUE_MAX_LENGTH != 0 */
#endif /* EXI_OPTION_VALUE_PARTITION_CAPACITY != 0 */
			}
			break;
		}
	}

	return errn;
}

/**
 * Decode a sequence of characters according to a given length.
 * Each character is represented by its UCS [ISO/IEC 10646]
 * code point encoded as an Unsigned Integer
 */
int decodeCharacters(bitstream_t* stream, uint16_t len, exi_string_character_t* chars) {
	unsigned int i;
	int errn = 0;

#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
	uint8_t b;
	for (i = 0; i < len && errn == 0; i++) {
		errn = decode(stream, &b);
		if(b < 128) {
			chars[i] = (exi_string_character_t)b;
		} else {
			errn = EXI_ERROR_STRINGVALUES_CHARACTER;
		}
	}
	/* null terminator \0 */
	chars[i] = '\0';

#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
	for (i = 0; i < len && errn == 0; i++) {
		errn = decodeUnsignedInteger32(stream, &chars[i]);
	}
#endif /* STRING_REPRESENTATION_UCS */




	return errn;
}

int decodeRCSCharacters(bitstream_t* stream, uint16_t len, exi_string_character_t* chars, uint16_t rcsCodeLength, uint16_t rcsSize, const exi_string_character_t rcsSet[]) {
	unsigned int i;
	int errn = 0;
	uint32_t uint32;
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
	uint8_t b;
#endif /* STRING_REPRESENTATION_ASCII */


	for (i = 0; i < len && errn == 0; i++) {
		errn = decodeNBitUnsignedInteger(stream, rcsCodeLength, &uint32);
		if(errn == 0) {
			if ( uint32 == rcsSize ) {
				/* RCS deviation */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
				errn = decode(stream, &b);
				if(b < 128) {
					chars[i] = (exi_string_character_t)b;
				} else {
					errn = EXI_ERROR_STRINGVALUES_CHARACTER;
				}
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
				errn = decodeUnsignedInteger32(stream, &chars[i]);
#endif /* STRING_REPRESENTATION_UCS */

			} else {
				/* RCS match */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_ASCII
				chars[i] = rcsSet[uint32];
#endif /* STRING_REPRESENTATION_ASCII */
#if STRING_REPRESENTATION == STRING_REPRESENTATION_UCS
				chars[i] = rcsSet[uint32];
#endif /* STRING_REPRESENTATION_UCS */
			}
		}
	}

	return errn;
}


/**
 * Decode a binary value as a length-prefixed sequence of octets.
 */
int decodeBinary(bitstream_t* stream, exi_bytes_t* bytes) {
	int errn = decodeUnsignedInteger16(stream, &bytes->len);
	if (errn == 0) {
		if (bytes->len > bytes->size) {
#if MEMORY_ALLOCATION == STATIC_ALLOCATION
			errn = EXI_ERROR_OUT_OF_BYTE_BUFFER;
#endif /* STATIC_ALLOCATION */
#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
			errn = exiFreeDynamicBinaryMemory(bytes);
			if(errn == 0) {
				errn = exiAllocateDynamicBinaryMemory(bytes, bytes->len);
			}
#endif /* DYNAMIC_ALLOCATION */
		}

		errn = decodeBytes(stream, bytes->len, bytes->data);
	}

	return errn;
}


int decodeBytes(bitstream_t* stream, uint16_t len, uint8_t* data) {
	unsigned int i;
	int errn = 0;
	uint8_t b;

	for (i = 0; i < len && errn == 0; i++) {
		errn = decode(stream, &b);
		data[i] = (uint8_t)b;
	}

	return errn;
}

/**
 * Decode Date-Time as sequence of values representing the individual
 * components of the Date-Time.
 */
int decodeDateTime(bitstream_t* stream, exi_datetime_type_t type, exi_datetime_t* datetime) {
	int errn = 0;

	datetime->type = type;

	datetime->year = 0;
	datetime->monthDay = 0;
	datetime->time = 0;
	datetime->presenceFractionalSecs = 0;
	datetime->fractionalSecs = 0;
	datetime->presenceTimezone = 0;
	datetime->timezone = 0;

	switch (type) {
	case EXI_DATETIME_GYEAR: /* Year, [Time-Zone] */
		errn = decodeInteger32(stream, &datetime->year);
		if (errn == 0) {
			datetime->year += DATETIME_YEAR_OFFSET;
		}
		break;
	case EXI_DATETIME_GYEARMONTH: /* Year, MonthDay, [TimeZone] */
	case EXI_DATETIME_DATE:
		errn = decodeInteger32(stream, &datetime->year);
		if (errn == 0) {
			datetime->year += DATETIME_YEAR_OFFSET;
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay);
		}
		break;
	case EXI_DATETIME_DATETIME: /* Year, MonthDay, Time, [FractionalSecs], [TimeZone] */
		/* e.g. "0001-01-01T00:00:00.111+00:33"  */
		errn = decodeInteger32(stream, &datetime->year);
		if (errn == 0) {
			datetime->year += DATETIME_YEAR_OFFSET;
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay);
			if (errn != 0) {
				break;
			}
		}
		/* no break */
	case EXI_DATETIME_TIME: /* Time, [FractionalSecs], [TimeZone] */
		/* e.g. "12:34:56.135"  */
		errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIME, &datetime->time);
		if (errn == 0) {
			errn = decodeBoolean(stream, &datetime->presenceFractionalSecs);
			if (errn == 0) {
				if (datetime->presenceFractionalSecs) {
					errn = decodeUnsignedInteger32(stream, &datetime->fractionalSecs);
				}
			}
		}
		break;
	case EXI_DATETIME_GMONTH: /* MonthDay, [TimeZone] */
		/* e.g. "--12" */
	case EXI_DATETIME_GMONTHDAY: /* MonthDay, [TimeZone] */
		/* e.g. "--01-28"  */
	case EXI_DATETIME_GDAY: /* MonthDay, [TimeZone] */
		/* "---16"  */
		errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_MONTHDAY, &datetime->monthDay );
		break;
	default:
		errn = EXI_UNSUPPORTED_DATETIME_TYPE;
		break;
	}

	if(errn == 0) {
		errn = decodeBoolean(stream, &datetime->presenceTimezone );
		if (errn == 0 && datetime->presenceTimezone) {
			errn = decodeNBitUnsignedInteger(stream, DATETIME_NUMBER_BITS_TIMEZONE, &datetime->timezone);
			datetime->timezone -= DATETIME_TIMEZONE_OFFSET_IN_MINUTES;
		}
	}

	return errn;
}

#endif

