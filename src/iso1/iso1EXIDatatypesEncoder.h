/*
 * Copyright (C) 2007-2017 Siemens AG
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
 * @version 2017-09-19 
 * @contact Richard.Kuntschke@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



/**
 * \file 	EXIDatatypesEncoder.h
 * \brief 	Encoder for datatype definitions
 *
 */

#ifndef EXI_iso1_DATATYPES_ENCODER_H
#define EXI_iso1_DATATYPES_ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif


#include "iso1EXIDatatypes.h"

#if DEPLOY_ISO1_CODEC == SUPPORT_YES

#include <stdint.h>

#include "EXITypes.h"


int encode_iso1ExiDocument(bitstream_t* stream, struct iso1EXIDocument* exiDoc);

#if DEPLOY_ISO1_CODEC_FRAGMENT == SUPPORT_YES
int encode_iso1ExiFragment(bitstream_t* stream, struct iso1EXIFragment* exiFrag);
#endif /* DEPLOY_ISO1_CODEC_FRAGMENT */


#endif /* DEPLOY_ISO1_CODEC */

#ifdef __cplusplus
}
#endif

#endif
