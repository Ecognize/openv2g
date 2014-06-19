/*
 * Copyright (C) 2007-2013 Siemens AG
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
 * @version 0.8
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer.com</p>
 * <p>Schema: input/appHandshake/V2G_CI_AppProtocol.xsd</p>
 *
 *
 ********************************************************************/



#ifdef __cplusplus
extern "C" {
#endif

#ifndef EXI_appHand_DECODER_H
#define EXI_appHand_DECODER_H

/**
* \file 	EXIDecoder.h
* \brief 	EXI Decoder
*
*/

#include "EXITypes.h"

/**
 * \brief 		Initialize EXI decoder
 *
 *         		Resets & initializes the EXI decoder.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       runtimeTable   	Runtime name-tables
 * \param       stringTable   	String table
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandInitDecoder(bitstream_t* stream, exi_state_t* state,
		exi_name_table_runtime_t runtimeTable, exi_value_table_t stringTable);


/**
 * \brief 		Reports last decoded qualified name
 *
 *         		Note: Qualified name only available for previously unknown qname. Otherwise make use of name table entries.
 *
 * \param       qname   		Qualified name
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandGetLastQName(exi_qname_t** qname);


/**
 * \brief 		Decodes next event
 *
 * 				Inspects EXI stream and decodes next EXI event.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       nextEvent   	Next event
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeNextEvent(bitstream_t* stream,
		exi_state_t* state, exi_event_t* nextEvent);


/**
 * \brief 		Decodes StartDocument (SD) event
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeStartDocument(bitstream_t* stream,
		exi_state_t* state);

/**
 * \brief 		Decodes EndDocument (ED) event
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeEndDocument(bitstream_t* stream,
		exi_state_t* state);

/**
 * \brief 		Decodes StartElement (SE) event
 *
 * 				Note: The first time a qnameID is larger than schema-informed NUMBER_OF_QNAMES it is possible to retrieve the qname by calling GetLastQName(...).
 * 				It is up to the caller to track qnames.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \return                  	Error-Code <> 0
 *
 */
int
exiappHandDecodeStartElement(bitstream_t* stream,
		exi_state_t* state, uint16_t* qnameID);


/**
 * \brief 		Decodes EndElement (EE) event
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeEndElement(bitstream_t* stream,
		exi_state_t* state, uint16_t* qnameID);


/**
 * \brief 		Decodes Characters (CH) event.
 *
 * 				Reports characters value.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       val		   		Characters value
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeCharacters(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);


/**
 * \brief 		Decodes Attribute (AT) event.
 *
 * 				Reports attribute qname and value.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \param       val		   		Characters value
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeAttribute(bitstream_t* stream,
		exi_state_t* state, uint16_t* qnameID, exi_value_t* val);


/**
 * \brief 		Decodes attribute xsi:nil
 *
 * 				Reports value.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       val		   		Characters value
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeAttributeXsiNil(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);


/**
 * \brief 		Decodes attribute xsi:type
 *
 * 				Reports value.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       val		   		Characters value
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeAttributeXsiType(bitstream_t* stream,
		exi_state_t* state, exi_value_t* val);


/**
 * \brief 		Decodes attribute/characters list value
 *
 * 				List values are special and are processed one by one.
 *
 * \param       stream   		Input Stream
 * \param       state   		Codec state
 * \param       qnameID   		Qualified Name ID
 * \param       val		   		List value
 * \param       lt		   		List type
 * \return                  	Error-Code <> 0
 *
 */
int exiappHandDecodeListValue(bitstream_t* stream, exi_state_t* state, uint16_t qnameID,
		exi_value_t* val, exi_list_t lt);

#endif

#ifdef __cplusplus
}
#endif

