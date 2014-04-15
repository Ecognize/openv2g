
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
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Sebastian.Kaebisch.EXT@siemens.com
 * @version 0.7
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXISeGen</p>
 *
 ********************************************************************/


#include "EXITypes.h"
#include "v2g_dataTypes.h"


static  void init_sessionIDType(struct sessionIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_faultMsgType(struct faultMsgType* type)
{	
	type->arraylen.data=0;

}

static  void init_NotificationType(struct NotificationType* type)
{		
	init_faultMsgType(&(type->FaultMsg));	
	type->isused.FaultMsg=0;

}

static  void init_service_string(struct service_string* type)
{	
	type->arraylen.data=0;

}

static  void init_CanonicalizationMethodType(struct CanonicalizationMethodType* type)
{	
	init_service_string(&(type->attr_Algorithm));

}

static  void init_SignatureMethodType(struct SignatureMethodType* type)
{	
	init_service_string(&(type->attr_Algorithm));

}

static  void init_DigestMethodType(struct DigestMethodType* type)
{	
	init_service_string(&(type->attr_Algorithm));

}

static  void init_DigestValueType(struct DigestValueType* type)
{	
	type->arraylen.data=0;

}

static  void init_ReferenceType(struct ReferenceType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_service_string(&(type->attr_URI));	
	type->isused.attr_URI=0;	
	init_service_string(&(type->attr_Type));	
	type->isused.attr_Type=0;	
	init_DigestMethodType(&(type->DigestMethod));	
	init_DigestValueType(&(type->DigestValue));

}

static  void init_SignedInfoType(struct SignedInfoType* type)
{
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_CanonicalizationMethodType(&(type->CanonicalizationMethod));	
	init_SignatureMethodType(&(type->SignatureMethod));	
	init_ReferenceType(&(type->Reference[0]));

	type->arraylen.Reference=0;
}

static  void init_SignatureValueType(struct SignatureValueType* type)
{	
	type->arraylen.data=0;

}

static  void init_X509IssuerSerialType(struct X509IssuerSerialType* type)
{	
	init_service_string(&(type->X509IssuerName));	

}

static  void init_service_byte(struct service_byte* type)
{	
	type->arraylen.data=0;

}

static  void init_X509DataType(struct X509DataType* type)
{	
	init_X509IssuerSerialType(&(type->X509IssuerSerial));	
	init_service_byte(&(type->X509SKI));	
	init_service_string(&(type->X509SubjectName));	
	init_service_byte(&(type->X509Certificate));	
	init_service_byte(&(type->X509CRL));

}

static  void init_KeyInfoType(struct KeyInfoType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_X509DataType(&(type->X509Data));

}

static  void init_SignatureType(struct SignatureType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_SignedInfoType(&(type->SignedInfo));	
	init_SignatureValueType(&(type->SignatureValue));	
	init_KeyInfoType(&(type->KeyInfo));	
	type->isused.KeyInfo=0;

}

static  void init_MessageHeaderType(struct MessageHeaderType* type)
{	
	init_sessionIDType(&(type->SessionID));	
	init_NotificationType(&(type->Notification));	
	type->isused.Notification=0;		
	type->isused.Signature=0;

}

static  void init_evccIDType(struct evccIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_SessionSetupReqType(struct SessionSetupReqType* type)
{	
	init_evccIDType(&(type->EVCCID));

}

static  void init_evseIDType(struct evseIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_SessionSetupResType(struct SessionSetupResType* type)
{		
	init_evseIDType(&(type->EVSEID));		
	type->isused.DateTimeNow=0;

}

static  void init_serviceScopeType(struct serviceScopeType* type)
{	
	type->arraylen.data=0;

}

static  void init_ServiceDiscoveryReqType(struct ServiceDiscoveryReqType* type)
{	
	init_serviceScopeType(&(type->ServiceScope));	
	type->isused.ServiceScope=0;		
	type->isused.ServiceCategory=0;

}

static  void init_PaymentOptionsType(struct PaymentOptionsType* type)
{

	type->arraylen.PaymentOption=0;

}

static  void init_serviceNameType(struct serviceNameType* type)
{	
	type->arraylen.data=0;

}

static  void init_ServiceTagType(struct ServiceTagType* type)
{		
	init_serviceNameType(&(type->ServiceName));	
	type->isused.ServiceName=0;		
	init_serviceScopeType(&(type->ServiceScope));	
	type->isused.ServiceScope=0;

}

static  void init_ServiceChargeType(struct ServiceChargeType* type)
{	
	init_ServiceTagType(&(type->ServiceTag));		

}

static  void init_ServiceType(struct ServiceType* type)
{	
	init_ServiceTagType(&(type->ServiceTag));	

}

static  void init_ServiceTagListType(struct ServiceTagListType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<3;i_loop++)
	{
		init_ServiceType(&(type->Service[i_loop]));
	}
	
	type->arraylen.Service=0;

}

static void init_ServiceDiscoveryResType(struct ServiceDiscoveryResType* type)
{		
	init_PaymentOptionsType(&(type->PaymentOptions));	
	init_ServiceChargeType(&(type->ChargeService));	
	init_ServiceTagListType(&(type->ServiceList));	
	type->isused.ServiceList=0;

}

static  void init_PhysicalValueType(struct PhysicalValueType* type)
{			
	type->isused.Unit=0;	

}

static  void init_ParameterType(struct ParameterType* type)
{	
	init_service_string(&(type->attr_Name));	
	init_service_string(&(type->attr_ValueType));					
	init_PhysicalValueType(&(type->physicalValue));	
	init_service_string(&(type->stringValue));

}

static  void init_ParameterSetType(struct ParameterSetType* type)
{
	int i_loop;
			
	for(i_loop=0; i_loop<2;i_loop++)
	{
		init_ParameterType(&(type->Parameter[i_loop]));
	}
	
	type->arraylen.Parameter=0;

}

static  void init_ServiceParameterListType(struct ServiceParameterListType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<2;i_loop++)
	{
		init_ParameterSetType(&(type->ParameterSet[i_loop]));
	}
	
	type->arraylen.ParameterSet=0;

}

static  void init_ServiceDetailResType(struct ServiceDetailResType* type)
{			
	init_ServiceParameterListType(&(type->ServiceParameterList));	
	type->isused.ServiceParameterList=0;

}

static  void init_SelectedServiceType(struct SelectedServiceType* type)
{			
	type->isused.ParameterSetID=0;

}

static  void init_SelectedServiceListType(struct SelectedServiceListType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<2;i_loop++)
	{
		init_SelectedServiceType(&(type->SelectedService[i_loop]));
	}
	
	type->arraylen.SelectedService=0;

}

static  void init_ServicePaymentSelectionReqType(struct ServicePaymentSelectionReqType* type)
{		
	init_SelectedServiceListType(&(type->SelectedServiceList));

}

static  void init_contractIDType(struct contractIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_certificateType(struct certificateType* type)
{	
	type->arraylen.data=0;

}

static  void init_SubCertificatesType(struct SubCertificatesType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<4;i_loop++)
	{
		init_certificateType(&(type->Certificate[i_loop]));
	}
	
	type->arraylen.Certificate=0;

}

static  void init_CertificateChainType(struct CertificateChainType* type)
{	
	init_certificateType(&(type->Certificate));	
	init_SubCertificatesType(&(type->SubCertificates));	
	type->isused.SubCertificates=0;

}

static  void init_PaymentDetailsReqType(struct PaymentDetailsReqType* type)
{	
	init_contractIDType(&(type->ContractID));	
	init_CertificateChainType(&(type->ContractSignatureCertChain));

}

static  void init_genChallengeType(struct genChallengeType* type)
{	
	type->arraylen.data=0;

}

static  void init_PaymentDetailsResType(struct PaymentDetailsResType* type)
{		
	init_genChallengeType(&(type->GenChallenge));	

}

static  void init_ContractAuthenticationReqType(struct ContractAuthenticationReqType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_genChallengeType(&(type->GenChallenge));	
	type->isused.GenChallenge=0;

}

static  void init_AC_EVChargeParameterType(struct AC_EVChargeParameterType* type)
{		
	init_PhysicalValueType(&(type->EAmount));	
	init_PhysicalValueType(&(type->EVMaxVoltage));	
	init_PhysicalValueType(&(type->EVMaxCurrent));	
	init_PhysicalValueType(&(type->EVMinCurrent));

}

static  void init_DC_EVStatusType(struct DC_EVStatusType* type)
{			
	type->isused.EVCabinConditioning=0;		
	type->isused.EVRESSConditioning=0;		

}

static  void init_DC_EVChargeParameterType(struct DC_EVChargeParameterType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));	
	init_PhysicalValueType(&(type->EVMaximumCurrentLimit));	
	init_PhysicalValueType(&(type->EVMaximumPowerLimit));	
	type->isused.EVMaximumPowerLimit=0;	
	init_PhysicalValueType(&(type->EVMaximumVoltageLimit));	
	init_PhysicalValueType(&(type->EVEnergyCapacity));	
	type->isused.EVEnergyCapacity=0;	
	init_PhysicalValueType(&(type->EVEnergyRequest));	
	type->isused.EVEnergyRequest=0;		
	type->isused.FullSOC=0;		
	type->isused.BulkSOC=0;

}

static  void init_ChargeParameterDiscoveryReqType(struct ChargeParameterDiscoveryReqType* type)
{			
	type->isused.AC_EVChargeParameter=0;		
	type->isused.DC_EVChargeParameter=0;

}

static  void init_RelativeTimeIntervalType(struct RelativeTimeIntervalType* type)
{			
	type->isused.duration=0;

}

static  void init_PMaxScheduleEntryType(struct PMaxScheduleEntryType* type)
{	
	init_RelativeTimeIntervalType(&(type->RelativeTimeInterval));	

}

static  void init_PMaxScheduleType(struct PMaxScheduleType* type)
{
	int i_loop;
			
	for(i_loop=0; i_loop<12;i_loop++)
	{
		init_PMaxScheduleEntryType(&(type->PMaxScheduleEntry[i_loop]));
	}
	
	type->arraylen.PMaxScheduleEntry=0;

}

static  void init_tariffDescriptionType(struct tariffDescriptionType* type)
{	
	type->arraylen.data=0;

}

static  void init_CostType(struct CostType* type)
{				
	type->isused.amountMultiplier=0;

}

static  void init_ConsumptionCostType(struct ConsumptionCostType* type)
{
	int i_loop;
			
	for(i_loop=0; i_loop<2;i_loop++)
	{
		init_CostType(&(type->Cost[i_loop]));
	}
	
	type->arraylen.Cost=0;	
	type->isused.Cost=0;

}

static  void init_SalesTariffEntryType(struct SalesTariffEntryType* type)
{
	int i_loop;
		
	init_RelativeTimeIntervalType(&(type->RelativeTimeInterval));		
	for(i_loop=0; i_loop<2;i_loop++)
	{
		init_ConsumptionCostType(&(type->ConsumptionCost[i_loop]));
	}
	
	type->arraylen.ConsumptionCost=0;	
	type->isused.ConsumptionCost=0;

}

static  void init_SalesTariffType(struct SalesTariffType* type)
{
	int i_loop;
		
	init_service_string(&(type->attr_Id));		
	init_tariffDescriptionType(&(type->SalesTariffDescription));	
	type->isused.SalesTariffDescription=0;		
	for(i_loop=0; i_loop<12;i_loop++)
	{
		init_SalesTariffEntryType(&(type->SalesTariffEntry[i_loop]));
	}
	
	type->arraylen.SalesTariffEntry=0;

}

static  void init_SAScheduleTupleType(struct SAScheduleTupleType* type)
{		
	init_PMaxScheduleType(&(type->PMaxSchedule));		
	type->isused.SalesTariff=0;

}

static  void init_SAScheduleListType(struct SAScheduleListType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<3;i_loop++)
	{
		init_SAScheduleTupleType(&(type->SAScheduleTuple[i_loop]));
	}
	
	type->arraylen.SAScheduleTuple=0;

}

static  void init_AC_EVSEChargeParameterType(struct AC_EVSEChargeParameterType* type)
{		
	init_PhysicalValueType(&(type->EVSEMaxVoltage));	
	init_PhysicalValueType(&(type->EVSEMaxCurrent));	
	init_PhysicalValueType(&(type->EVSEMinCurrent));

}

static  void init_DC_EVSEStatusType(struct DC_EVSEStatusType* type)
{		
	type->isused.EVSEIsolationStatus=0;			

}

static  void init_DC_EVSEChargeParameterType(struct DC_EVSEChargeParameterType* type)
{	
	init_DC_EVSEStatusType(&(type->DC_EVSEStatus));	
	init_PhysicalValueType(&(type->EVSEMaximumCurrentLimit));	
	init_PhysicalValueType(&(type->EVSEMaximumPowerLimit));	
	type->isused.EVSEMaximumPowerLimit=0;	
	init_PhysicalValueType(&(type->EVSEMaximumVoltageLimit));	
	init_PhysicalValueType(&(type->EVSEMinimumCurrentLimit));	
	init_PhysicalValueType(&(type->EVSEMinimumVoltageLimit));	
	init_PhysicalValueType(&(type->EVSECurrentRegulationTolerance));	
	type->isused.EVSECurrentRegulationTolerance=0;	
	init_PhysicalValueType(&(type->EVSEPeakCurrentRipple));	
	init_PhysicalValueType(&(type->EVSEEnergyToBeDelivered));	
	type->isused.EVSEEnergyToBeDelivered=0;

}

static  void init_ChargeParameterDiscoveryResType(struct ChargeParameterDiscoveryResType* type)
{			
	init_SAScheduleListType(&(type->SAScheduleList));		
	type->isused.AC_EVSEChargeParameter=0;		
	type->isused.DC_EVSEChargeParameter=0;

}

static  void init_ChargingProfileType(struct ChargingProfileType* type)
{

	type->arraylen.ProfileEntry=0;

}

static  void init_DC_EVPowerDeliveryParameterType(struct DC_EVPowerDeliveryParameterType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));		
	type->isused.BulkChargingComplete=0;	

}

static  void init_PowerDeliveryReqType(struct PowerDeliveryReqType* type)
{		
	init_ChargingProfileType(&(type->ChargingProfile));	
	type->isused.ChargingProfile=0;		
	type->isused.DC_EVPowerDeliveryParameter=0;

}

static  void init_PowerDeliveryResType(struct PowerDeliveryResType* type)
{			
	type->isused.AC_EVSEStatus=0;		
	type->isused.DC_EVSEStatus=0;

}

static  void init_meterIDType(struct meterIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_sigMeterReadingType(struct sigMeterReadingType* type)
{	
	type->arraylen.data=0;

}

static  void init_MeterInfoType(struct MeterInfoType* type)
{	
	init_meterIDType(&(type->MeterID));	
	init_PhysicalValueType(&(type->MeterReading));	
	type->isused.MeterReading=0;	
	init_sigMeterReadingType(&(type->SigMeterReading));	
	type->isused.SigMeterReading=0;		
	type->isused.MeterStatus=0;		
	type->isused.TMeter=0;

}

static  void init_ChargingStatusResType(struct ChargingStatusResType* type)
{		
	init_evseIDType(&(type->EVSEID));		
	init_PhysicalValueType(&(type->EVSEMaxCurrent));	
	type->isused.EVSEMaxCurrent=0;	
	init_MeterInfoType(&(type->MeterInfo));	
	type->isused.MeterInfo=0;		

}

static  void init_MeteringReceiptReqType(struct MeteringReceiptReqType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_sessionIDType(&(type->SessionID));		
	type->isused.SAScheduleTupleID=0;	
	init_MeterInfoType(&(type->MeterInfo));

}

static  void init_MeteringReceiptResType(struct MeteringReceiptResType* type)
{		

}

static  void init_rootCertificateIDType(struct rootCertificateIDType* type)
{	
	type->arraylen.data=0;

}

static  void init_ListOfRootCertificateIDsType(struct ListOfRootCertificateIDsType* type)
{
	int i_loop;
		
	for(i_loop=0; i_loop<20;i_loop++)
	{
		init_rootCertificateIDType(&(type->RootCertificateID[i_loop]));
	}
	
	type->arraylen.RootCertificateID=0;

}

static  void init_dHParamsType(struct dHParamsType* type)
{	
	type->arraylen.data=0;

}

static  void init_CertificateUpdateReqType(struct CertificateUpdateReqType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_CertificateChainType(&(type->ContractSignatureCertChain));	
	init_contractIDType(&(type->ContractID));	
	init_ListOfRootCertificateIDsType(&(type->ListOfRootCertificateIDs));	
	init_dHParamsType(&(type->DHParams));

}

static  void init_privateKeyType(struct privateKeyType* type)
{	
	type->arraylen.data=0;

}

static  void init_CertificateUpdateResType(struct CertificateUpdateResType* type)
{	
	init_service_string(&(type->attr_Id));		
	init_CertificateChainType(&(type->ContractSignatureCertChain));	
	init_privateKeyType(&(type->ContractSignatureEncryptedPrivateKey));	
	init_dHParamsType(&(type->DHParams));	
	init_contractIDType(&(type->ContractID));	

}

static  void init_CertificateInstallationReqType(struct CertificateInstallationReqType* type)
{	
	init_service_string(&(type->attr_Id));	
	type->isused.attr_Id=0;	
	init_certificateType(&(type->OEMProvisioningCert));	
	init_ListOfRootCertificateIDsType(&(type->ListOfRootCertificateIDs));	
	init_dHParamsType(&(type->DHParams));

}

static  void init_CertificateInstallationResType(struct CertificateInstallationResType* type)
{	
	init_service_string(&(type->attr_Id));		
	init_CertificateChainType(&(type->ContractSignatureCertChain));	
	init_privateKeyType(&(type->ContractSignatureEncryptedPrivateKey));	
	init_dHParamsType(&(type->DHParams));	
	init_contractIDType(&(type->ContractID));

}

static  void init_CableCheckReqType(struct CableCheckReqType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));

}

static  void init_CableCheckResType(struct CableCheckResType* type)
{		
	init_DC_EVSEStatusType(&(type->DC_EVSEStatus));	

}

static  void init_PreChargeReqType(struct PreChargeReqType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));	
	init_PhysicalValueType(&(type->EVTargetVoltage));	
	init_PhysicalValueType(&(type->EVTargetCurrent));

}

static  void init_PreChargeResType(struct PreChargeResType* type)
{		
	init_DC_EVSEStatusType(&(type->DC_EVSEStatus));	
	init_PhysicalValueType(&(type->EVSEPresentVoltage));

}

static  void init_CurrentDemandReqType(struct CurrentDemandReqType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));	
	init_PhysicalValueType(&(type->EVTargetCurrent));	
	init_PhysicalValueType(&(type->EVMaximumVoltageLimit));	
	type->isused.EVMaximumVoltageLimit=0;	
	init_PhysicalValueType(&(type->EVMaximumCurrentLimit));	
	type->isused.EVMaximumCurrentLimit=0;	
	init_PhysicalValueType(&(type->EVMaximumPowerLimit));	
	type->isused.EVMaximumPowerLimit=0;		
	type->isused.BulkChargingComplete=0;		
	init_PhysicalValueType(&(type->RemainingTimeToFullSoC));	
	type->isused.RemainingTimeToFullSoC=0;	
	init_PhysicalValueType(&(type->RemainingTimeToBulkSoC));	
	type->isused.RemainingTimeToBulkSoC=0;	
	init_PhysicalValueType(&(type->EVTargetVoltage));

}

static  void init_CurrentDemandResType(struct CurrentDemandResType* type)
{		
	init_DC_EVSEStatusType(&(type->DC_EVSEStatus));	
	init_PhysicalValueType(&(type->EVSEPresentVoltage));	
	init_PhysicalValueType(&(type->EVSEPresentCurrent));				
	init_PhysicalValueType(&(type->EVSEMaximumVoltageLimit));	
	type->isused.EVSEMaximumVoltageLimit=0;	
	init_PhysicalValueType(&(type->EVSEMaximumCurrentLimit));	
	type->isused.EVSEMaximumCurrentLimit=0;	
	init_PhysicalValueType(&(type->EVSEMaximumPowerLimit));	
	type->isused.EVSEMaximumPowerLimit=0;

}

static  void init_WeldingDetectionReqType(struct WeldingDetectionReqType* type)
{	
	init_DC_EVStatusType(&(type->DC_EVStatus));

}

static  void init_WeldingDetectionResType(struct WeldingDetectionResType* type)
{		
	init_DC_EVSEStatusType(&(type->DC_EVSEStatus));	
	init_PhysicalValueType(&(type->EVSEPresentVoltage));

}

static  void init_BodyType(struct BodyType* type)
{		
	type->isused.SessionSetupReq=0;		
	type->isused.SessionSetupRes=0;		
	type->isused.ServiceDiscoveryReq=0;		
	type->isused.ServiceDiscoveryRes=0;		
	type->isused.ServiceDetailReq=0;		
	type->isused.ServiceDetailRes=0;		
	type->isused.ServicePaymentSelectionReq=0;		
	type->isused.ServicePaymentSelectionRes=0;		
	type->isused.PaymentDetailsReq=0;		
	type->isused.PaymentDetailsRes=0;		
	type->isused.ContractAuthenticationReq=0;		
	type->isused.ContractAuthenticationRes=0;		
	type->isused.ChargeParameterDiscoveryReq=0;		
	type->isused.ChargeParameterDiscoveryRes=0;		
	type->isused.PowerDeliveryReq=0;		
	type->isused.PowerDeliveryRes=0;		
	type->isused.ChargingStatusReq=0;		
	type->isused.ChargingStatusRes=0;		
	type->isused.MeteringReceiptReq=0;		
	type->isused.MeteringReceiptRes=0;		
	type->isused.SessionStopReq=0;		
	type->isused.SessionStopRes=0;		
	type->isused.CertificateUpdateReq=0;		
	type->isused.CertificateUpdateRes=0;		
	type->isused.CertificateInstallationReq=0;		
	type->isused.CertificateInstallationRes=0;		
	type->isused.CableCheckReq=0;		
	type->isused.CableCheckRes=0;		
	type->isused.PreChargeReq=0;		
	type->isused.PreChargeRes=0;		
	type->isused.CurrentDemandReq=0;		
	type->isused.CurrentDemandRes=0;		
	type->isused.WeldingDetectionReq=0;		
	type->isused.WeldingDetectionRes=0;

}

static  void init_AnonType_V2G_Message(struct AnonType_V2G_Message* type)
{		
	init_BodyType(&(type->Body));

}

static void init_EXIDocumentType(struct EXIDocumentType* type)
{	
	init_AnonType_V2G_Message(&(type->V2G_Message));

}
