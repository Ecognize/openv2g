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
 * @version 0.6 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 ********************************************************************/



#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>
#include <stdio.h>


#ifndef EXI_TYPES_H
#define EXI_TYPES_H

#define BITS_IN_BYTE 8

#define DATETIME_YEAR_OFFSET 2000
#define DATETIME_NUMBER_BITS_MONTHDAY 9
#define DATETIME_NUMBER_BITS_TIME 17
#define DATETIME_NUMBER_BITS_TIMEZONE 11
#define DATETIME_MONTH_MULTIPLICATOR 32
#define DATETIME_TIMEZONE_OFFSET_IN_MINUTES 896

#define UINT_MAX_VALUE 65535

/* EXI Debug mode */
/* Increases code footprint but offers addition functionalities, e.g. string retrieving  */
#define EXI_DEBUG_ON 1
#define EXI_DEBUG_OFF 2
#define EXI_DEBUG EXI_DEBUG_OFF

/* EXI stream */
#define BYTE_ARRAY 1
#define FILE_STREAM 2
/*#define EXI_STREAM FILE_STREAM */

#define EXI_STREAM BYTE_ARRAY

#define EXI_ELEMENT_STACK_SIZE 16

#define FLOAT_EXPONENT_SPECIAL_VALUES -16384
#define FLOAT_MANTISSA_INFINITY 1
#define FLOAT_MANTISSA_MINUS_INFINITY -1
#define FLOAT_MANTISSA_NOT_A_NUMBER 0

typedef struct {
#if EXI_STREAM == BYTE_ARRAY
	/*	Byte Array */
	uint32_t size; /* array size */
	uint8_t* data; /* int data array */
	uint32_t* pos; /* next position in array */
#endif
#if EXI_STREAM == FILE_STREAM
	/* FILE */
	FILE *file;
#endif
	/* Current byte buffer & its remaining bit capacity */
	uint8_t buffer;
	uint8_t capacity;
} bitstream_t;


typedef enum {
	/* Binary */
	EXI_DATATYPE_BINARY_BASE64,
	EXI_DATATYPE_BINARY_HEX,
	/* Boolean */
	EXI_DATATYPE_BOOLEAN,
	EXI_DATATYPE_BOOLEAN_FACET,
	/* Decimal */
	EXI_DATATYPE_DECIMAL,
	/* Float & Double */
	EXI_DATATYPE_FLOAT,
	/* N-Bit Unsigned Integer */
	EXI_DATATYPE_NBIT_UNSIGNED_INTEGER,
	/* Unsigned Integer */
	EXI_DATATYPE_UNSIGNED_INTEGER,
	/* (Signed) Integer */
	EXI_DATATYPE_INTEGER,
	/* Datetime */
	EXI_DATATYPE_DATETIME,
	/* String */
	EXI_DATATYPE_STRING,
	/* Restricted Character Set String */
	EXI_DATATYPE_RCS_STRING,
	/* Enumeration */
	EXI_DATATYPE_ENUMERATION,
	/* List */
	EXI_DATATYPE_LIST
} exi_datatype_t;


typedef enum {
	/* Unsigned Integer */
	EXI_UNSIGNED_INTEGER_8,
	EXI_UNSIGNED_INTEGER_16,
	EXI_UNSIGNED_INTEGER_32,
	EXI_UNSIGNED_INTEGER_64,
	/* (Signed) Integer */
	EXI_INTEGER_8,
	EXI_INTEGER_16,
	EXI_INTEGER_32,
	EXI_INTEGER_64
} exi_integer_type_t;

typedef enum {
	EXI_EVENT_START_DOCUMENT,
	EXI_EVENT_END_DOCUMENT,
	EXI_EVENT_START_ELEMENT,
	EXI_EVENT_START_ELEMENT_NS,
	EXI_EVENT_START_ELEMENT_GENERIC,
	EXI_EVENT_START_ELEMENT_GENERIC_UNDECLARED,
	EXI_EVENT_END_ELEMENT,
	EXI_EVENT_END_ELEMENT_UNDECLARED,
	EXI_EVENT_CHARACTERS,
	EXI_EVENT_CHARACTERS_GENERIC,
	EXI_EVENT_CHARACTERS_GENERIC_UNDECLARED,
	EXI_EVENT_ATTRIBUTE_XSI_TYPE,
	EXI_EVENT_ATTRIBUTE_XSI_NIL,
	EXI_EVENT_ATTRIBUTE,
	EXI_EVENT_ATTRIBUTE_NS,
	EXI_EVENT_ATTRIBUTE_GENERIC,
	EXI_EVENT_ATTRIBUTE_INVALID_VALUE,
	EXI_EVENT_ATTRIBUTE_ANY_INVALID_VALUE,
	EXI_EVENT_ATTRIBUTE_GENERIC_UNDECLARED,
	/* error state */
	EXI_EVENT_ERROR
} exi_event_t;


/* differ datetime types */
typedef enum {
	EXI_DATETIME_GYEAR,
	EXI_DATETIME_GYEARMONTH,
	EXI_DATETIME_DATE,
	EXI_DATETIME_DATETIME,
	EXI_DATETIME_GMONTH,
	EXI_DATETIME_GMONTHDAY,
	EXI_DATETIME_GDAY,
	EXI_DATETIME_TIME
} exi_datetime_type_t;


typedef struct {
	/* Bytes Size and array container */
	uint16_t size;
	uint8_t* data;
	/* current length (len <= size) */
	uint16_t len;
} bytes_t;

/* Universal Character Set (UCS) strings */
typedef struct {
	/* UCS size and UCS character container*/
	uint16_t size;
	uint32_t* codepoints;
	/* current length == number of code-points, (len <= size) */
	uint16_t len;
} string_ucs_t;

/* Restricted Characeter Set */
typedef struct {
	/* size and UCS character codep*/
	uint16_t size;
	/* rcs codepoints */
	uint32_t* codepoints;
	/* character coding length*/
	uint8_t codingLength; /* less than 256 characters */
} rcs_t;

/* ASCII strings */
typedef struct {
	/* size of String array */
	uint16_t size;
	char* chars;
	/* current length can be retrieved by calling strlen(chars)*/
} string_ascii_t;

typedef struct {
	exi_integer_type_t type;
	union {
		/* unsigned values */
		int8_t int8;
		int16_t int16;
		int32_t int32;
		int32_t int64;
		/* (signed) values */
		uint8_t uint8;
		uint16_t uint16;
		uint32_t uint32;
		uint64_t uint64;
	} val;
} integer_t;

typedef struct {
	/* range of the mantissa is -(2^63) to 2^63-1 */
	int64_t mantissa;
	/* range of the exponent is - (2^14-1) to 2^14-1 */
	int32_t exponent; /* base-10 */
} float_me_t;

typedef struct {
	/* a sign value */
	int negative;
	/* represents the integral portion of the Decimal */
	integer_t integral;
	/* represents the fractional portion of the Decimal with the digits in reverse order to preserve leading zeros */
	integer_t reverseFraction;
} decimal_t;



typedef struct {
	/* datetime type */
	exi_datetime_type_t type;
	/* values */
	int32_t year;
	uint32_t monthDay;
	uint32_t time;
	int presenceFractionalSecs;
	uint32_t fractionalSecs;
	int presenceTimezone;
	uint32_t timezone;
} datetime_t;



/* TODO list support */
typedef struct {
	/* list item type */
	exi_datatype_t type;
	/* number of items */
	uint16_t len;
	/* special datatypes */
	exi_integer_type_t intType;
	exi_datetime_type_t datetimeType;

	/* List container with memory size */
	/* uint16_t size;
	uint8_t* data;*/
} list_t;

/* efficient ID qname */
typedef struct {
	uint16_t namespaceURI;
	uint16_t localPart;
} eqname_t;

/* ascii qname */
typedef struct {
	string_ascii_t namespaceURI;
	string_ascii_t localName;
} qname_t;

/* ==================================== */
/* LocalName Entries */
struct exiNamePartition {
	/* length of array */
	uint16_t len;
#if EXI_DEBUG == EXI_DEBUG_ON
	/* array of string entries */
	char** names;
#endif /*EXI_DEBUG*/
};

typedef struct exiNameTablePrepopulated {
	/* length of both arrays (uris & localNames) */
	uint16_t len;
#if EXI_DEBUG == EXI_DEBUG_ON
	/* URI entries*/
	char** uris;
#endif /*EXI_DEBUG*/
	/* localName entries divided by URI */
	struct exiNamePartition * localNames;
} exi_name_table_prepopulated_t;


/* not used */
#define EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_CHARACTERS 1
#define EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES 1
#define EXI_RESERVED_NUMBER_URI_PARTITION_ENTRIES 0
#define EXI_RESERVED_NUMBER_LOCALNAME_PARTITION_ENTRIES 0

typedef enum {
	EXI_NAME_PARTITION_URI,
	EXI_NAME_PARTITION_LOCALNAME
} exi_name_partition_type_t;

typedef struct {
	 char* uri;
	 uint16_t uriID;
} exi_uri_partition_t;

typedef struct {
	 char* localName;
	 uint16_t localNameID;
	 uint16_t uriID;
} exi_localname_partition_t;

typedef struct {
	exi_name_partition_type_t namePartitionType;
    struct
    {
		exi_uri_partition_t uriPartition;
        exi_localname_partition_t localNamePartition;
    } entry;
} exi_name_partition_t;

typedef struct exiNameTableRuntime {
	/* maximum number of characters in the name partitions entries PLUS null terminators */
	char characters[EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_CHARACTERS + EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES];
	uint16_t numberOfUsedCharacters; /* initially zero <= EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_CHARACTERS */
	/* maximum number of name partitions entries. Name partitions entries consist in all uri, and local-name partition entries */
	exi_name_partition_t namePartitionsEntries[EXI_MAXIMUM_NUMBER_OF_NAME_PARTITION_ENTRIES];
	/* uint16_t numberOfUsedNamePartitions; */ /* initially zero */
	/* added entries */
	uint16_t addedUriEntries; /* initially zero */
	uint16_t addedLocalNameEntries; /* initially zero */
} exi_name_table_runtime_t;






typedef struct {
	/* stack of grammar states */
	int16_t grammarStack[EXI_ELEMENT_STACK_SIZE];
	/* stack of grammar elements */
	eqname_t elementStack[EXI_ELEMENT_STACK_SIZE];
	uint16_t stackIndex;
	/* event-code */
	uint32_t eventCode;
	/* string table entries */
	exi_name_table_prepopulated_t nameTablePrepopulated;
	exi_name_table_runtime_t nameTableRuntime;
} exi_state_t;

typedef struct {
	/* type of value */
	exi_datatype_t type;

	/* base types */
	int boolean;
	integer_t integer;

	/*uint16_t uint8;
	uint16_t uint16;
	uint32_t uint32;
	uint64_t uint64;
	int8_t int8;
	int16_t int16;
	int32_t int32;
	int64_t int64;*/

	uint32_t enumeration;

	/* Bytes, Strings and Lists are not native types anymore */
	bytes_t binary;
	string_ucs_t string;
	float_me_t float_me;
	decimal_t decimal;
	datetime_t datetime;
	list_t list;
	eqname_t eqname;
} exi_value_t;

/*
 * ERROR-Codes
 */
#define EXI_ERROR_INPUT_STREAM_EOF -10
#define EXI_ERROR_OUTPUT_STREAM_EOF -11
#define EXI_ERROR_INPUT_FILE_HANDLE -12
#define EXI_ERROR_OUTPUT_FILE -13

#define EXI_ERROR_OUT_OF_BOUNDS -100
#define EXI_ERROR_OUT_OF_STRING_BUFFER -101
#define EXI_ERROR_OUT_OF_ASCII_BUFFER -102
#define EXI_ERROR_OUT_OF_BYTE_BUFFER -103
#define EXI_ERROR_OUT_OF_GRAMMAR_STACK -104

#define EXI_ERROR_UNKOWN_EVENT -109
#define EXI_ERROR_UNKOWN_EVENT_CODE -110
#define EXI_ERROR_UNEXPECTED_EVENT_LEVEL1 -111
#define EXI_ERROR_UNEXPECTED_EVENT_LEVEL2 -112

#define EXI_ERROR_UNEXPECTED_START_DOCUMENT -113
#define EXI_ERROR_UNEXPECTED_END_DOCUMENT -114
#define EXI_ERROR_UNEXPECTED_START_ELEMENT -115
#define EXI_ERROR_UNEXPECTED_START_ELEMENT_GENERIC -116
#define EXI_ERROR_UNEXPECTED_END_ELEMENT -117
#define EXI_ERROR_UNEXPECTED_CHARACTERS -118
#define EXI_ERROR_UNEXPECTED_ATTRIBUTE -119
#define EXI_ERROR_UNEXPECTED_ATTRIBUTE_XSI_TYPE -120
#define EXI_ERROR_UNEXPECTED_ATTRIBUTE_XSI_NIL -121
#define EXI_ERROR_UNEXPECTED_GRAMMAR_ID -122
#define EXI_ERROR_UNEXPECTED_ATTRIBUTE_MOVE_TO_CONTENT_RULE -123


#define EXI_UNSUPPORTED_STRING_TABLE_LOCAL_HIT -130
#define EXI_UNSUPPORTED_STRING_TABLE_GLOBAL_HIT -131
#define EXI_UNSUPPORTED_NBIT_INTEGER_LENGTH -132
#define EXI_UNSUPPORTED_EVENT_CODE_CHARACTERISTICS -133
#define EXI_UNSUPPORTED_INTEGER_VALUE_TYPE -134
#define EXI_UNSUPPORTED_INTEGER_VALUE -135
#define EXI_NEGATIVE_UNSIGNED_INTEGER_VALUE -136
#define EXI_UNSUPPORTED_LIST_VALUE_TYPE -137
#define EXI_UNSUPPORTED_HEADER_COOKIE -138
#define EXI_UNSUPPORTED_HEADER_OPTIONS -139

#define EXI_ERROR_UNEXPECTED_BYTE_VALUE -200
#define EXI_ERROR_UNEXPECTED_DATETIME_TYPE -201

#define EXI_ERROR_CONVERSION_NO_ASCII_CHARACTERS -300
#define EXI_ERROR_CONVERSION_TYPE_TO_STRING -301

#endif

#ifdef __cplusplus
}
#endif
