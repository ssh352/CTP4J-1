#pragma once

#include "windows.h"
#include "TraderSpi.h"

#include <fstream> 

#define DOUBLE_MAX 1.7976931348623158e+308

using namespace std;
//std::ofstream file;


double toDouble(double d) {
	if (d == DOUBLE_MAX) {
		return 0;
	}
	else {
		return d;
	}
}

jstring charTojstring_cn(JNIEnv* env, char* str)
{
	jstring rtn = 0;
	int slen = strlen(str);
	unsigned short * buffer = 0;
	if (slen == 0)
		rtn = (env)->NewStringUTF(str);
	else
	{
		int length = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, NULL, 0);
		buffer = (unsigned short *)malloc(length * 2 + 1);
		if (MultiByteToWideChar(CP_ACP, 0, (LPCSTR)str, slen, (LPWSTR)buffer, length) >0)
			rtn = (env)->NewString((jchar*)buffer, length);
	}
	if (buffer)
		free(buffer);
	return rtn;
}

CtpTraderSpi::CtpTraderSpi(JavaVM *vm, jobject obj) {
	jvm = vm;
	jobj = obj;

	TraderSpiMethodSigInit();
	//file.open("log.log", std::iostream::app);
}

CtpTraderSpi::~CtpTraderSpi() {
	OnFrontConnected_mid = NULL;
	OnFrontDisconnected_mid = NULL;
	OnHeartBeatWarning_mid = NULL;
	OnRspUserLogin_mid = NULL;
	OnRspUserLogout_mid = NULL;
	OnRspError_mid = NULL;
	OnRspQryExchange_mid = NULL;
	OnRspQryInstrument_mid = NULL;
	OnRtnOrder_mid = NULL;
	OnRtnTrade_mid = NULL;
	OnRspQryInvestorPosition_mid = NULL;
	OnRspQryTradingAccount_mid = NULL;
	OnRspOrderInsert_mid = NULL;
	OnErrRtnOrderInsert_mid = NULL;
	OnRspOrderAction_mid = NULL;
	OnErrRtnOrderAction_mid = NULL;
	OnRspQrySettlementInfoConfirm_mid = NULL;
	OnRspSettlementInfoConfirm_mid = NULL;
	OnRspQrySettlementInfo_mid = NULL;
	OnRspQryInstrumentMarginRate_mid = NULL;
	OnRspQryInstrumentCommissionRate_mid = NULL;
	OnRspQryInvestorPositionDetail_mid = NULL;
}

void CtpTraderSpi::TraderSpiMethodSigInit() {
	JNIEnv *jenv;
	if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		jclass jcls = jenv->GetObjectClass(jobj);

		OnFrontConnected_mid = jenv->GetMethodID(jcls, "onFrontConnected", "()V");
		OnFrontDisconnected_mid = jenv->GetMethodID(jcls, "onFrontDisconnected", "(I)V");
		OnHeartBeatWarning_mid = jenv->GetMethodID(jcls, "onHeartBeatWarning", "(I)V");
		OnRspUserLogin_mid = jenv->GetMethodID(jcls, "onRspUserLogin", "(Lcn/yiwang/ctp/struct/CTPRspUserLogin;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspUserLogout_mid = jenv->GetMethodID(jcls, "onRspUserLogout", "(Lcn/yiwang/ctp/struct/CTPUserLogout;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryExchange_mid = jenv->GetMethodID(jcls, "onRspQryExchange", "(Lcn/yiwang/ctp/struct/CTPExchange;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryInstrument_mid = jenv->GetMethodID(jcls, "onRspQryInstrument", "(Lcn/yiwang/ctp/struct/CTPInstrument;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspError_mid = jenv->GetMethodID(jcls, "onRspError", "(Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRtnOrder_mid = jenv->GetMethodID(jcls, "onRtnOrder", "(Lcn/yiwang/ctp/struct/CTPOrder;)V");
		OnRtnTrade_mid = jenv->GetMethodID(jcls, "onRtnTrade", "(Lcn/yiwang/ctp/struct/CTPTrade;)V");
		OnRspQryInvestorPosition_mid = jenv->GetMethodID(jcls, "onRspQryInvestorPosition", "(Lcn/yiwang/ctp/struct/CTPInvestorPosition;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryTradingAccount_mid = jenv->GetMethodID(jcls, "onRspQryTradingAccount", "(Lcn/yiwang/ctp/struct/CTPTradingAccount;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspOrderInsert_mid = jenv->GetMethodID(jcls, "onRspOrderInsert", "(Lcn/yiwang/ctp/struct/CTPInputOrder;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnErrRtnOrderInsert_mid = jenv->GetMethodID(jcls, "onErrRtnOrderInsert", "(Lcn/yiwang/ctp/struct/CTPInputOrder;Lcn/yiwang/ctp/struct/CTPRspInfo;)V");
		OnRspOrderAction_mid = jenv->GetMethodID(jcls, "onRspOrderAction", "(Lcn/yiwang/ctp/struct/CTPInputOrderAction;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnErrRtnOrderAction_mid = jenv->GetMethodID(jcls, "onErrRtnOrderAction", "(Lcn/yiwang/ctp/struct/CTPOrderAction;Lcn/yiwang/ctp/struct/CTPRspInfo;)V");
		OnRspQrySettlementInfoConfirm_mid = jenv->GetMethodID(jcls, "onRspQrySettlementInfoConfirm", "(Lcn/yiwang/ctp/struct/CTPSettlementInfoConfirm;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspSettlementInfoConfirm_mid = jenv->GetMethodID(jcls, "onRspSettlementInfoConfirm", "(Lcn/yiwang/ctp/struct/CTPSettlementInfoConfirm;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQrySettlementInfo_mid = jenv->GetMethodID(jcls, "onRspQrySettlementInfo", "(Lcn/yiwang/ctp/struct/CTPSettlementInfo;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryInstrumentMarginRate_mid = jenv->GetMethodID(jcls, "onRspQryInstrumentMarginRate", "(Lcn/yiwang/ctp/struct/CTPInstrumentMarginRate;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryInstrumentCommissionRate_mid = jenv->GetMethodID(jcls, "onRspQryInstrumentCommissionRate", "(Lcn/yiwang/ctp/struct/CTPInstrumentCommissionRate;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspQryInvestorPositionDetail_mid = jenv->GetMethodID(jcls, "onRspQryInvestorPositionDetail", "(Lcn/yiwang/ctp/struct/CTPInvestorPositionDetail;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
	}
	jvm->DetachCurrentThread();
}


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CtpTraderSpi::OnFrontConnected() {
	if (OnFrontConnected_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnFrontConnected_mid);
		}
		jvm->DetachCurrentThread();
	}
}


///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void CtpTraderSpi::OnFrontDisconnected(int nReason) {
	if (OnFrontDisconnected_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnFrontDisconnected_mid, nReason);
		}
		jvm->DetachCurrentThread();
	}
}


///心跳超时警告。当长时间未收到报文时，该方法被调用。
void CtpTraderSpi::OnHeartBeatWarning(int nTimeLapse) {
	if (OnHeartBeatWarning_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnHeartBeatWarning_mid, nTimeLapse);
		}
		jvm->DetachCurrentThread();
	}
}


///登录请求响应
void CtpTraderSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogin_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		
			jobject CTPRspUserLogin_obj = NULL;
			if (pRspUserLogin) {
				jclass CTPRspUserLogin_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspUserLogin;");
				jmethodID CTPRspUserLogin_mid = jenv->GetMethodID(CTPRspUserLogin_cls, "<init>", "()V");
				CTPRspUserLogin_obj = jenv->NewObject(CTPRspUserLogin_cls, CTPRspUserLogin_mid, "");

				jfieldID TradingDayg_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID LoginTime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "LoginTime", "Ljava/lang/String;");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "UserID", "Ljava/lang/String;");
				jfieldID SystemName_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SystemName", "Ljava/lang/String;");
				jfieldID FrontID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "FrontID", "I");
				jfieldID SessionID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SessionID", "I");
				jfieldID MaxOrderRef_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "MaxOrderRef", "Ljava/lang/String;");
				jfieldID SHFETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SHFETime", "Ljava/lang/String;");
				jfieldID DCETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "DCETime", "Ljava/lang/String;");
				jfieldID CZCETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "CZCETime", "Ljava/lang/String;");
				jfieldID FFEXTime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "FFEXTime", "Ljava/lang/String;");
				jfieldID INETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "INETime", "Ljava/lang/String;");

				jenv->SetObjectField(CTPRspUserLogin_obj, TradingDayg_fid, jenv->NewStringUTF(pRspUserLogin->TradingDay));
				jenv->SetObjectField(CTPRspUserLogin_obj, LoginTime_fid, jenv->NewStringUTF(pRspUserLogin->LoginTime));
				jenv->SetObjectField(CTPRspUserLogin_obj, BrokerID_fid, jenv->NewStringUTF(pRspUserLogin->BrokerID));
				jenv->SetObjectField(CTPRspUserLogin_obj, UserID_fid, jenv->NewStringUTF(pRspUserLogin->UserID));
				jenv->SetObjectField(CTPRspUserLogin_obj, SystemName_fid, jenv->NewStringUTF(pRspUserLogin->SystemName));
				jenv->SetIntField(CTPRspUserLogin_obj, FrontID_fid, pRspUserLogin->FrontID);
				jenv->SetIntField(CTPRspUserLogin_obj, SessionID_fid, pRspUserLogin->SessionID);
				jenv->SetObjectField(CTPRspUserLogin_obj, MaxOrderRef_fid, jenv->NewStringUTF(pRspUserLogin->MaxOrderRef));
				jenv->SetObjectField(CTPRspUserLogin_obj, SHFETime_fid, jenv->NewStringUTF(pRspUserLogin->SHFETime));
				jenv->SetObjectField(CTPRspUserLogin_obj, DCETime_fid, jenv->NewStringUTF(pRspUserLogin->DCETime));
				jenv->SetObjectField(CTPRspUserLogin_obj, CZCETime_fid, jenv->NewStringUTF(pRspUserLogin->CZCETime));
				jenv->SetObjectField(CTPRspUserLogin_obj, FFEXTime_fid, jenv->NewStringUTF(pRspUserLogin->FFEXTime));
				jenv->SetObjectField(CTPRspUserLogin_obj, INETime_fid, jenv->NewStringUTF(pRspUserLogin->INETime));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspUserLogin_mid, CTPRspUserLogin_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///登出请求响应
void CtpTraderSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogout_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		
			jobject CTPUserLogout_obj = NULL;
			if (pUserLogout) {
				jclass CTPUserLogout_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPUserLogout;");
				jmethodID CTPUserLogout_mid = jenv->GetMethodID(CTPUserLogout_cls, "<init>", "()V");
				CTPUserLogout_obj = jenv->NewObject(CTPUserLogout_cls, CTPUserLogout_mid, "");

				jfieldID BrokerID_fid = jenv->GetFieldID(CTPUserLogout_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPUserLogout_cls, "UserID", "Ljava/lang/String;");

				jenv->SetObjectField(CTPUserLogout_obj, BrokerID_fid, jenv->NewStringUTF(pUserLogout->BrokerID));
				jenv->SetObjectField(CTPUserLogout_obj, UserID_fid, jenv->NewStringUTF(pUserLogout->UserID));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspUserLogout_mid, CTPUserLogout_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///请求查询交易所响应
void CtpTraderSpi::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {

	if (OnRspQryExchange_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jobject CTPExchange_obj = NULL;
			if (pExchange) {
				jclass CTPExchange_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPExchange;");
				jmethodID CTPExchange_mid = jenv->GetMethodID(CTPExchange_cls, "<init>", "()V");
				CTPExchange_obj = jenv->NewObject(CTPExchange_cls, CTPExchange_mid, "");

				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPExchange_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID ExchangeName_fid = jenv->GetFieldID(CTPExchange_cls, "ExchangeName", "Ljava/lang/String;");
				jfieldID ExchangeProperty_fid = jenv->GetFieldID(CTPExchange_cls, "ExchangeProperty", "C");

				jenv->SetObjectField(CTPExchange_obj, ExchangeID_fid, jenv->NewStringUTF(pExchange->ExchangeID));
				jenv->SetObjectField(CTPExchange_obj, ExchangeName_fid, jenv->NewStringUTF(pExchange->ExchangeName));
				jenv->SetCharField(CTPExchange_obj, ExchangeProperty_fid, pExchange->ExchangeProperty);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}
			jenv->CallObjectMethod(jobj, OnRspQryExchange_mid, CTPExchange_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///请求查询合约响应
void CtpTraderSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryInstrument_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jobject CTPInstrument_obj = NULL;
			if (pInstrument) {
				jclass CTPInstrument_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInstrument;");
				jmethodID CTPInstrument_mid = jenv->GetMethodID(CTPInstrument_cls, "<init>", "()V");
				CTPInstrument_obj = jenv->NewObject(CTPInstrument_cls, CTPInstrument_mid, "");

				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInstrument_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPInstrument_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID InstrumentName_fid = jenv->GetFieldID(CTPInstrument_cls, "InstrumentName", "Ljava/lang/String;");
				jfieldID ExchangeInstID_fid = jenv->GetFieldID(CTPInstrument_cls, "ExchangeInstID", "Ljava/lang/String;");
				jfieldID ProductID_fid = jenv->GetFieldID(CTPInstrument_cls, "ProductID", "Ljava/lang/String;");
				jfieldID ProductClass_fid = jenv->GetFieldID(CTPInstrument_cls, "ProductClass", "C");
				jfieldID DeliveryYear_fid = jenv->GetFieldID(CTPInstrument_cls, "DeliveryYear", "I");
				jfieldID DeliveryMonth_fid = jenv->GetFieldID(CTPInstrument_cls, "DeliveryMonth", "I");
				jfieldID MaxMarketOrderVolume_fid = jenv->GetFieldID(CTPInstrument_cls, "MaxMarketOrderVolume", "I");
				jfieldID MinMarketOrderVolume_fid = jenv->GetFieldID(CTPInstrument_cls, "MinMarketOrderVolume", "I");
				jfieldID MaxLimitOrderVolume_fid = jenv->GetFieldID(CTPInstrument_cls, "MaxLimitOrderVolume", "I");
				jfieldID MinLimitOrderVolume_fid = jenv->GetFieldID(CTPInstrument_cls, "MinLimitOrderVolume", "I");
				jfieldID VolumeMultiple_fid = jenv->GetFieldID(CTPInstrument_cls, "VolumeMultiple", "I");
				jfieldID PriceTick_fid = jenv->GetFieldID(CTPInstrument_cls, "PriceTick", "F");
				jfieldID CreateDate_fid = jenv->GetFieldID(CTPInstrument_cls, "CreateDate", "Ljava/lang/String;");
				jfieldID OpenDate_fid = jenv->GetFieldID(CTPInstrument_cls, "OpenDate", "Ljava/lang/String;");
				jfieldID ExpireDate_fid = jenv->GetFieldID(CTPInstrument_cls, "ExpireDate", "Ljava/lang/String;");
				jfieldID StartDelivDate_fid = jenv->GetFieldID(CTPInstrument_cls, "StartDelivDate", "Ljava/lang/String;");
				jfieldID EndDelivDate_fid = jenv->GetFieldID(CTPInstrument_cls, "EndDelivDate", "Ljava/lang/String;");
				jfieldID InstLifePhase_fid = jenv->GetFieldID(CTPInstrument_cls, "InstLifePhase", "C");
				jfieldID IsTrading_fid = jenv->GetFieldID(CTPInstrument_cls, "IsTrading", "I");
				jfieldID PositionType_fid = jenv->GetFieldID(CTPInstrument_cls, "PositionType", "C");
				jfieldID PositionDateType_fid = jenv->GetFieldID(CTPInstrument_cls, "PositionDateType", "C");
				jfieldID LongMarginRatio_fid = jenv->GetFieldID(CTPInstrument_cls, "LongMarginRatio", "F");
				jfieldID ShortMarginRatio_fid = jenv->GetFieldID(CTPInstrument_cls, "ShortMarginRatio", "F");
				jfieldID MaxMarginSideAlgorithm_fid = jenv->GetFieldID(CTPInstrument_cls, "MaxMarginSideAlgorithm", "C");
				jfieldID UnderlyingInstrID_fid = jenv->GetFieldID(CTPInstrument_cls, "UnderlyingInstrID", "Ljava/lang/String;");
				jfieldID StrikePrice_fid = jenv->GetFieldID(CTPInstrument_cls, "StrikePrice", "F");
				jfieldID OptionsType_fid = jenv->GetFieldID(CTPInstrument_cls, "OptionsType", "C");
				jfieldID UnderlyingMultiple_fid = jenv->GetFieldID(CTPInstrument_cls, "UnderlyingMultiple", "F");
				jfieldID CombinationType_fid = jenv->GetFieldID(CTPInstrument_cls, "CombinationType", "C");

				jenv->SetObjectField(CTPInstrument_obj, InstrumentID_fid, jenv->NewStringUTF(pInstrument->InstrumentID));
				jenv->SetObjectField(CTPInstrument_obj, ExchangeID_fid, jenv->NewStringUTF(pInstrument->ExchangeID));
				jenv->SetObjectField(CTPInstrument_obj, InstrumentName_fid, charTojstring_cn(jenv, pInstrument->InstrumentName));//jenv->NewStringUTF(pInstrument->InstrumentName));
				jenv->SetObjectField(CTPInstrument_obj, ExchangeInstID_fid, jenv->NewStringUTF(pInstrument->ExchangeInstID));
				jenv->SetObjectField(CTPInstrument_obj, ProductID_fid, jenv->NewStringUTF(pInstrument->ProductID));
				jenv->SetCharField(CTPInstrument_obj, ProductClass_fid, pInstrument->ProductClass);
				jenv->SetIntField(CTPInstrument_obj, DeliveryYear_fid, pInstrument->DeliveryYear);
				jenv->SetIntField(CTPInstrument_obj, DeliveryMonth_fid, pInstrument->DeliveryMonth);
				jenv->SetIntField(CTPInstrument_obj, MaxMarketOrderVolume_fid, pInstrument->MaxMarketOrderVolume);
				jenv->SetIntField(CTPInstrument_obj, MinMarketOrderVolume_fid, pInstrument->MinMarketOrderVolume);
				jenv->SetIntField(CTPInstrument_obj, MaxLimitOrderVolume_fid, pInstrument->MaxLimitOrderVolume);
				jenv->SetIntField(CTPInstrument_obj, MinLimitOrderVolume_fid, pInstrument->MinLimitOrderVolume);
				jenv->SetIntField(CTPInstrument_obj, VolumeMultiple_fid, pInstrument->VolumeMultiple);
				jenv->SetFloatField(CTPInstrument_obj, PriceTick_fid, toDouble(pInstrument->PriceTick));
				jenv->SetObjectField(CTPInstrument_obj, CreateDate_fid, jenv->NewStringUTF(pInstrument->CreateDate));
				jenv->SetObjectField(CTPInstrument_obj, OpenDate_fid, jenv->NewStringUTF(pInstrument->OpenDate));
				jenv->SetObjectField(CTPInstrument_obj, ExpireDate_fid, jenv->NewStringUTF(pInstrument->ExpireDate));
				jenv->SetObjectField(CTPInstrument_obj, StartDelivDate_fid, jenv->NewStringUTF(pInstrument->StartDelivDate));
				jenv->SetObjectField(CTPInstrument_obj, EndDelivDate_fid, jenv->NewStringUTF(pInstrument->EndDelivDate));
				jenv->SetCharField(CTPInstrument_obj, InstLifePhase_fid, pInstrument->InstLifePhase);
				jenv->SetIntField(CTPInstrument_obj, IsTrading_fid, pInstrument->IsTrading);
				jenv->SetCharField(CTPInstrument_obj, PositionType_fid, pInstrument->PositionType);
				jenv->SetCharField(CTPInstrument_obj, PositionDateType_fid, pInstrument->PositionDateType);
				jenv->SetFloatField(CTPInstrument_obj, LongMarginRatio_fid, toDouble(pInstrument->LongMarginRatio));
				jenv->SetFloatField(CTPInstrument_obj, ShortMarginRatio_fid, toDouble(pInstrument->ShortMarginRatio));
				jenv->SetCharField(CTPInstrument_obj, MaxMarginSideAlgorithm_fid, pInstrument->MaxMarginSideAlgorithm);
				jenv->SetObjectField(CTPInstrument_obj, UnderlyingInstrID_fid, jenv->NewStringUTF(pInstrument->UnderlyingInstrID));
				jenv->SetFloatField(CTPInstrument_obj, StrikePrice_fid, toDouble(pInstrument->StrikePrice));
				jenv->SetCharField(CTPInstrument_obj, OptionsType_fid, pInstrument->OptionsType);
				jenv->SetFloatField(CTPInstrument_obj, UnderlyingMultiple_fid, toDouble(pInstrument->UnderlyingMultiple));
				jenv->SetCharField(CTPInstrument_obj, CombinationType_fid, pInstrument->CombinationType);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}


			jenv->CallObjectMethod(jobj, OnRspQryInstrument_mid, CTPInstrument_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///错误应答
void CtpTraderSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogout_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

			jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));


			jenv->CallObjectMethod(jobj, OnRspError_mid, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///报单通知
void CtpTraderSpi::OnRtnOrder(CThostFtdcOrderField *pOrder) {
	if (OnRtnOrder_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPOrder_obj = NULL;
			if (pOrder) {
				jclass CTPOrder_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPOrder;");
				jmethodID CTPOrder_mid = jenv->GetMethodID(CTPOrder_cls, "<init>", "()V");
				CTPOrder_obj = jenv->NewObject(CTPOrder_cls, CTPOrder_mid, "");

				jfieldID BrokerID_fid = jenv->GetFieldID(CTPOrder_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPOrder_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPOrder_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPOrder_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPOrder_cls, "UserID", "Ljava/lang/String;");
				jfieldID OrderPriceType_fid = jenv->GetFieldID(CTPOrder_cls, "OrderPriceType", "C");
				jfieldID Direction_fid = jenv->GetFieldID(CTPOrder_cls, "Direction", "C");
				jfieldID CombOffsetFlag_fid = jenv->GetFieldID(CTPOrder_cls, "CombOffsetFlag", "Ljava/lang/String;");
				jfieldID CombHedgeFlag_fid = jenv->GetFieldID(CTPOrder_cls, "CombHedgeFlag", "Ljava/lang/String;");
				jfieldID LimitPrice_fid = jenv->GetFieldID(CTPOrder_cls, "LimitPrice", "F");
				jfieldID VolumeTotalOriginal_fid = jenv->GetFieldID(CTPOrder_cls, "VolumeTotalOriginal", "I");
				jfieldID TimeCondition_fid = jenv->GetFieldID(CTPOrder_cls, "TimeCondition", "C");
				jfieldID GTDDate_fid = jenv->GetFieldID(CTPOrder_cls, "GTDDate", "Ljava/lang/String;");
				jfieldID VolumeCondition_fid = jenv->GetFieldID(CTPOrder_cls, "VolumeCondition", "C");
				jfieldID MinVolume_fid = jenv->GetFieldID(CTPOrder_cls, "MinVolume", "I");
				jfieldID ContingentCondition_fid = jenv->GetFieldID(CTPOrder_cls, "ContingentCondition", "C");
				jfieldID StopPrice_fid = jenv->GetFieldID(CTPOrder_cls, "StopPrice", "F");
				jfieldID ForceCloseReason_fid = jenv->GetFieldID(CTPOrder_cls, "ForceCloseReason", "C");
				jfieldID IsAutoSuspend_fid = jenv->GetFieldID(CTPOrder_cls, "IsAutoSuspend", "I");
				jfieldID BusinessUnit_fid = jenv->GetFieldID(CTPOrder_cls, "BusinessUnit", "Ljava/lang/String;");
				jfieldID RequestID_fid = jenv->GetFieldID(CTPOrder_cls, "RequestID", "I");
				jfieldID OrderLocalID_fid = jenv->GetFieldID(CTPOrder_cls, "OrderLocalID", "Ljava/lang/String;");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPOrder_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID ParticipantID_fid = jenv->GetFieldID(CTPOrder_cls, "ParticipantID", "Ljava/lang/String;");
				jfieldID ClientID_fid = jenv->GetFieldID(CTPOrder_cls, "ClientID", "Ljava/lang/String;");
				jfieldID ExchangeInstID_fid = jenv->GetFieldID(CTPOrder_cls, "ExchangeInstID", "Ljava/lang/String;");
				jfieldID TraderID_fid = jenv->GetFieldID(CTPOrder_cls, "TraderID", "Ljava/lang/String;");
				jfieldID InstallID_fid = jenv->GetFieldID(CTPOrder_cls, "InstallID", "I");
				jfieldID OrderSubmitStatus_fid = jenv->GetFieldID(CTPOrder_cls, "OrderSubmitStatus", "C");
				jfieldID NotifySequence_fid = jenv->GetFieldID(CTPOrder_cls, "NotifySequence", "I");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPOrder_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPOrder_cls, "SettlementID", "I");
				jfieldID OrderSysID_fid = jenv->GetFieldID(CTPOrder_cls, "OrderSysID", "Ljava/lang/String;");
				jfieldID OrderSource_fid = jenv->GetFieldID(CTPOrder_cls, "OrderSource", "C");
				jfieldID OrderStatus_fid = jenv->GetFieldID(CTPOrder_cls, "OrderStatus", "C");
				jfieldID OrderType_fid = jenv->GetFieldID(CTPOrder_cls, "OrderType", "C");
				jfieldID VolumeTraded_fid = jenv->GetFieldID(CTPOrder_cls, "VolumeTraded", "I");
				jfieldID VolumeTotal_fid = jenv->GetFieldID(CTPOrder_cls, "VolumeTotal", "I");
				jfieldID InsertDate_fid = jenv->GetFieldID(CTPOrder_cls, "InsertDate", "Ljava/lang/String;");
				jfieldID InsertTime_fid = jenv->GetFieldID(CTPOrder_cls, "InsertTime", "Ljava/lang/String;");
				jfieldID ActiveTime_fid = jenv->GetFieldID(CTPOrder_cls, "ActiveTime", "Ljava/lang/String;");
				jfieldID SuspendTime_fid = jenv->GetFieldID(CTPOrder_cls, "SuspendTime", "Ljava/lang/String;");
				jfieldID UpdateTime_fid = jenv->GetFieldID(CTPOrder_cls, "UpdateTime", "Ljava/lang/String;");
				jfieldID CancelTime_fid = jenv->GetFieldID(CTPOrder_cls, "CancelTime", "Ljava/lang/String;");
				jfieldID ActiveTraderID_fid = jenv->GetFieldID(CTPOrder_cls, "ActiveTraderID", "Ljava/lang/String;");
				jfieldID ClearingPartID_fid = jenv->GetFieldID(CTPOrder_cls, "ClearingPartID", "Ljava/lang/String;");
				jfieldID SequenceNo_fid = jenv->GetFieldID(CTPOrder_cls, "SequenceNo", "I");
				jfieldID FrontID_fid = jenv->GetFieldID(CTPOrder_cls, "FrontID", "I");
				jfieldID SessionID_fid = jenv->GetFieldID(CTPOrder_cls, "SessionID", "I");
				jfieldID UserProductInfo_fid = jenv->GetFieldID(CTPOrder_cls, "UserProductInfo", "Ljava/lang/String;");
				jfieldID StatusMsg_fid = jenv->GetFieldID(CTPOrder_cls, "StatusMsg", "Ljava/lang/String;");
				jfieldID UserForceClose_fid = jenv->GetFieldID(CTPOrder_cls, "UserForceClose", "I");
				jfieldID ActiveUserID_fid = jenv->GetFieldID(CTPOrder_cls, "ActiveUserID", "Ljava/lang/String;");
				jfieldID BrokerOrderSeq_fid = jenv->GetFieldID(CTPOrder_cls, "BrokerOrderSeq", "I");
				jfieldID RelativeOrderSysID_fid = jenv->GetFieldID(CTPOrder_cls, "RelativeOrderSysID", "Ljava/lang/String;");
				jfieldID ZCETotalTradedVolume_fid = jenv->GetFieldID(CTPOrder_cls, "ZCETotalTradedVolume", "I");
				jfieldID IsSwapOrder_fid = jenv->GetFieldID(CTPOrder_cls, "IsSwapOrder", "I");

				jenv->SetObjectField(CTPOrder_obj, BrokerID_fid, jenv->NewStringUTF(pOrder->BrokerID));
				jenv->SetObjectField(CTPOrder_obj, InvestorID_fid, jenv->NewStringUTF(pOrder->InvestorID));
				jenv->SetObjectField(CTPOrder_obj, InstrumentID_fid, jenv->NewStringUTF(pOrder->InstrumentID));
				jenv->SetObjectField(CTPOrder_obj, OrderRef_fid, jenv->NewStringUTF(pOrder->OrderRef));
				jenv->SetObjectField(CTPOrder_obj, UserID_fid, jenv->NewStringUTF(pOrder->UserID));
				jenv->SetCharField(CTPOrder_obj, OrderPriceType_fid, pOrder->OrderPriceType);
				jenv->SetCharField(CTPOrder_obj, Direction_fid, pOrder->Direction);
				jenv->SetObjectField(CTPOrder_obj, CombOffsetFlag_fid, jenv->NewStringUTF(pOrder->CombOffsetFlag));
				jenv->SetObjectField(CTPOrder_obj, CombHedgeFlag_fid, jenv->NewStringUTF(pOrder->CombHedgeFlag));
				jenv->SetFloatField(CTPOrder_obj, LimitPrice_fid, pOrder->LimitPrice);
				jenv->SetIntField(CTPOrder_obj, VolumeTotalOriginal_fid, pOrder->VolumeTotalOriginal);
				jenv->SetCharField(CTPOrder_obj, TimeCondition_fid, pOrder->TimeCondition);
				jenv->SetObjectField(CTPOrder_obj, GTDDate_fid, jenv->NewStringUTF(pOrder->GTDDate));
				jenv->SetCharField(CTPOrder_obj, VolumeCondition_fid, pOrder->VolumeCondition);
				jenv->SetIntField(CTPOrder_obj, MinVolume_fid, pOrder->MinVolume);
				jenv->SetCharField(CTPOrder_obj, ContingentCondition_fid, pOrder->ContingentCondition);
				jenv->SetFloatField(CTPOrder_obj, StopPrice_fid, pOrder->StopPrice);
				jenv->SetCharField(CTPOrder_obj, ForceCloseReason_fid, pOrder->ForceCloseReason);
				jenv->SetIntField(CTPOrder_obj, IsAutoSuspend_fid, pOrder->IsAutoSuspend);
				jenv->SetObjectField(CTPOrder_obj, BusinessUnit_fid, jenv->NewStringUTF(pOrder->BusinessUnit));
				jenv->SetIntField(CTPOrder_obj, RequestID_fid, pOrder->RequestID);
				jenv->SetObjectField(CTPOrder_obj, OrderLocalID_fid, jenv->NewStringUTF(pOrder->OrderLocalID));
				jenv->SetObjectField(CTPOrder_obj, ExchangeID_fid, jenv->NewStringUTF(pOrder->ExchangeID));
				jenv->SetObjectField(CTPOrder_obj, ParticipantID_fid, jenv->NewStringUTF(pOrder->ParticipantID));
				jenv->SetObjectField(CTPOrder_obj, ClientID_fid, jenv->NewStringUTF(pOrder->ClientID));
				jenv->SetObjectField(CTPOrder_obj, ExchangeInstID_fid, jenv->NewStringUTF(pOrder->ExchangeInstID));
				jenv->SetObjectField(CTPOrder_obj, TraderID_fid, jenv->NewStringUTF(pOrder->TraderID));
				jenv->SetIntField(CTPOrder_obj, InstallID_fid, pOrder->InstallID);
				jenv->SetCharField(CTPOrder_obj, OrderSubmitStatus_fid, pOrder->OrderSubmitStatus);
				jenv->SetIntField(CTPOrder_obj, NotifySequence_fid, pOrder->NotifySequence);
				jenv->SetObjectField(CTPOrder_obj, TradingDay_fid, jenv->NewStringUTF(pOrder->TradingDay));
				jenv->SetIntField(CTPOrder_obj, SettlementID_fid, pOrder->SettlementID);
				jenv->SetObjectField(CTPOrder_obj, OrderSysID_fid, jenv->NewStringUTF(pOrder->OrderSysID));
				jenv->SetCharField(CTPOrder_obj, OrderSource_fid, pOrder->OrderSource);
				jenv->SetCharField(CTPOrder_obj, OrderStatus_fid, pOrder->OrderStatus);
				jenv->SetCharField(CTPOrder_obj, OrderType_fid, pOrder->OrderType);
				jenv->SetIntField(CTPOrder_obj, VolumeTraded_fid, pOrder->VolumeTraded);
				jenv->SetIntField(CTPOrder_obj, VolumeTotal_fid, pOrder->VolumeTotal);
				jenv->SetObjectField(CTPOrder_obj, InsertDate_fid, jenv->NewStringUTF(pOrder->InsertDate));
				jenv->SetObjectField(CTPOrder_obj, InsertTime_fid, jenv->NewStringUTF(pOrder->InsertTime));
				jenv->SetObjectField(CTPOrder_obj, ActiveTime_fid, jenv->NewStringUTF(pOrder->ActiveTime));
				jenv->SetObjectField(CTPOrder_obj, SuspendTime_fid, jenv->NewStringUTF(pOrder->SuspendTime));
				jenv->SetObjectField(CTPOrder_obj, UpdateTime_fid, jenv->NewStringUTF(pOrder->UpdateTime));
				jenv->SetObjectField(CTPOrder_obj, CancelTime_fid, jenv->NewStringUTF(pOrder->CancelTime));
				jenv->SetObjectField(CTPOrder_obj, ActiveTraderID_fid, jenv->NewStringUTF(pOrder->ActiveTraderID));
				jenv->SetObjectField(CTPOrder_obj, ClearingPartID_fid, jenv->NewStringUTF(pOrder->ClearingPartID));
				jenv->SetIntField(CTPOrder_obj, SequenceNo_fid, pOrder->SequenceNo);
				jenv->SetIntField(CTPOrder_obj, FrontID_fid, pOrder->FrontID);
				jenv->SetIntField(CTPOrder_obj, SessionID_fid, pOrder->SessionID);
				jenv->SetObjectField(CTPOrder_obj, UserProductInfo_fid, jenv->NewStringUTF(pOrder->UserProductInfo));
				jenv->SetObjectField(CTPOrder_obj, StatusMsg_fid, jenv->NewStringUTF(pOrder->StatusMsg));
				jenv->SetIntField(CTPOrder_obj, UserForceClose_fid, pOrder->UserForceClose);
				jenv->SetObjectField(CTPOrder_obj, ActiveUserID_fid, jenv->NewStringUTF(pOrder->ActiveUserID));
				jenv->SetIntField(CTPOrder_obj, BrokerOrderSeq_fid, pOrder->BrokerOrderSeq);
				jenv->SetObjectField(CTPOrder_obj, RelativeOrderSysID_fid, jenv->NewStringUTF(pOrder->RelativeOrderSysID));
				jenv->SetIntField(CTPOrder_obj, ZCETotalTradedVolume_fid, pOrder->ZCETotalTradedVolume);
				jenv->SetIntField(CTPOrder_obj, IsSwapOrder_fid, pOrder->IsSwapOrder);
			}

			jenv->CallObjectMethod(jobj, OnRtnOrder_mid, CTPOrder_obj);
		}
		jvm->DetachCurrentThread();
	}
}
///成交通知
void CtpTraderSpi::OnRtnTrade(CThostFtdcTradeField *pTrade) {
	if (OnRtnTrade_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPTrade_obj = NULL;
			if (pTrade) {
				jclass CTPTrade_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPTrade;");
				jmethodID CTPTrade_mid = jenv->GetMethodID(CTPTrade_cls, "<init>", "()V");
				CTPTrade_obj = jenv->NewObject(CTPTrade_cls, CTPTrade_mid, "");

				jfieldID BrokerID_fid = jenv->GetFieldID(CTPTrade_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPTrade_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPTrade_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPTrade_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPTrade_cls, "UserID", "Ljava/lang/String;");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPTrade_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID TradeID_fid = jenv->GetFieldID(CTPTrade_cls, "TradeID", "Ljava/lang/String;");
				jfieldID Direction_fid = jenv->GetFieldID(CTPTrade_cls, "Direction", "C");
				jfieldID OrderSysID_fid = jenv->GetFieldID(CTPTrade_cls, "OrderSysID", "Ljava/lang/String;");
				jfieldID ParticipantID_fid = jenv->GetFieldID(CTPTrade_cls, "ParticipantID", "Ljava/lang/String;");
				jfieldID ClientID_fid = jenv->GetFieldID(CTPTrade_cls, "ClientID", "Ljava/lang/String;");
				jfieldID TradingRole_fid = jenv->GetFieldID(CTPTrade_cls, "TradingRole", "C");
				jfieldID ExchangeInstID_fid = jenv->GetFieldID(CTPTrade_cls, "ExchangeInstID", "Ljava/lang/String;");
				jfieldID OffsetFlag_fid = jenv->GetFieldID(CTPTrade_cls, "OffsetFlag", "C");
				jfieldID HedgeFlag_fid = jenv->GetFieldID(CTPTrade_cls, "HedgeFlag", "C");
				jfieldID Price_fid = jenv->GetFieldID(CTPTrade_cls, "Price", "F");
				jfieldID Volume_fid = jenv->GetFieldID(CTPTrade_cls, "Volume", "I");
				jfieldID TradeDate_fid = jenv->GetFieldID(CTPTrade_cls, "TradeDate", "Ljava/lang/String;");
				jfieldID TradeTime_fid = jenv->GetFieldID(CTPTrade_cls, "TradeTime", "Ljava/lang/String;");
				jfieldID TradeType_fid = jenv->GetFieldID(CTPTrade_cls, "TradeType", "C");
				jfieldID PriceSource_fid = jenv->GetFieldID(CTPTrade_cls, "PriceSource", "C");
				jfieldID TraderID_fid = jenv->GetFieldID(CTPTrade_cls, "TraderID", "Ljava/lang/String;");
				jfieldID OrderLocalID_fid = jenv->GetFieldID(CTPTrade_cls, "OrderLocalID", "Ljava/lang/String;");
				jfieldID ClearingPartID_fid = jenv->GetFieldID(CTPTrade_cls, "ClearingPartID", "Ljava/lang/String;");
				jfieldID BusinessUnit_fid = jenv->GetFieldID(CTPTrade_cls, "BusinessUnit", "Ljava/lang/String;");
				jfieldID SequenceNo_fid = jenv->GetFieldID(CTPTrade_cls, "SequenceNo", "I");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPTrade_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPTrade_cls, "SettlementID", "I");
				jfieldID BrokerOrderSeq_fid = jenv->GetFieldID(CTPTrade_cls, "BrokerOrderSeq", "I");
				jfieldID TradeSource_fid = jenv->GetFieldID(CTPTrade_cls, "TradeSource", "C");

				jenv->SetObjectField(CTPTrade_obj, BrokerID_fid, jenv->NewStringUTF(pTrade->BrokerID));
				jenv->SetObjectField(CTPTrade_obj, InvestorID_fid, jenv->NewStringUTF(pTrade->InvestorID));
				jenv->SetObjectField(CTPTrade_obj, InstrumentID_fid, jenv->NewStringUTF(pTrade->InstrumentID));
				jenv->SetObjectField(CTPTrade_obj, OrderRef_fid, jenv->NewStringUTF(pTrade->OrderRef));
				jenv->SetObjectField(CTPTrade_obj, UserID_fid, jenv->NewStringUTF(pTrade->UserID));
				jenv->SetObjectField(CTPTrade_obj, ExchangeID_fid, jenv->NewStringUTF(pTrade->ExchangeID));
				jenv->SetObjectField(CTPTrade_obj, TradeID_fid, jenv->NewStringUTF(pTrade->TradeID));
				jenv->SetCharField(CTPTrade_obj, Direction_fid, pTrade->Direction);
				jenv->SetObjectField(CTPTrade_obj, OrderSysID_fid, jenv->NewStringUTF(pTrade->OrderSysID));
				jenv->SetObjectField(CTPTrade_obj, ParticipantID_fid, jenv->NewStringUTF(pTrade->ParticipantID));
				jenv->SetObjectField(CTPTrade_obj, ClientID_fid, jenv->NewStringUTF(pTrade->ClientID));
				jenv->SetCharField(CTPTrade_obj, TradingRole_fid, pTrade->TradingRole);
				jenv->SetObjectField(CTPTrade_obj, ExchangeInstID_fid, jenv->NewStringUTF(pTrade->ExchangeInstID));
				jenv->SetCharField(CTPTrade_obj, OffsetFlag_fid, pTrade->OffsetFlag);
				jenv->SetCharField(CTPTrade_obj, HedgeFlag_fid, pTrade->HedgeFlag);
				jenv->SetFloatField(CTPTrade_obj, Price_fid, pTrade->Price);
				jenv->SetIntField(CTPTrade_obj, Volume_fid, pTrade->Volume);
				jenv->SetObjectField(CTPTrade_obj, TradeDate_fid, jenv->NewStringUTF(pTrade->TradeDate));
				jenv->SetObjectField(CTPTrade_obj, TradeTime_fid, jenv->NewStringUTF(pTrade->TradeTime));
				jenv->SetCharField(CTPTrade_obj, TradeType_fid, pTrade->TradeType);
				jenv->SetCharField(CTPTrade_obj, PriceSource_fid, pTrade->PriceSource);
				jenv->SetObjectField(CTPTrade_obj, TraderID_fid, jenv->NewStringUTF(pTrade->TraderID));
				jenv->SetObjectField(CTPTrade_obj, OrderLocalID_fid, jenv->NewStringUTF(pTrade->OrderLocalID));
				jenv->SetObjectField(CTPTrade_obj, ClearingPartID_fid, jenv->NewStringUTF(pTrade->ClearingPartID));
				jenv->SetObjectField(CTPTrade_obj, BusinessUnit_fid, jenv->NewStringUTF(pTrade->BusinessUnit));
				jenv->SetIntField(CTPTrade_obj, SequenceNo_fid, pTrade->SequenceNo);
				jenv->SetObjectField(CTPTrade_obj, TradingDay_fid, jenv->NewStringUTF(pTrade->TradingDay));
				jenv->SetIntField(CTPTrade_obj, SettlementID_fid, pTrade->SettlementID);
				jenv->SetIntField(CTPTrade_obj, BrokerOrderSeq_fid, pTrade->BrokerOrderSeq);
				jenv->SetCharField(CTPTrade_obj, TradeSource_fid, pTrade->TradeSource);
			}

			jenv->CallObjectMethod(jobj, OnRtnTrade_mid, CTPTrade_obj);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询投资者持仓响应
void CtpTraderSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryInvestorPosition_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInvestorPosition_obj = NULL;
			if (pInvestorPosition) {
				jclass CTPInvestorPosition_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInvestorPosition;");
				jmethodID CTPInvestorPosition_mid = jenv->GetMethodID(CTPInvestorPosition_cls, "<init>", "()V");
				CTPInvestorPosition_obj = jenv->NewObject(CTPInvestorPosition_cls, CTPInvestorPosition_mid, "");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID PosiDirection_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PosiDirection", "C");
				jfieldID HedgeFlag_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "HedgeFlag", "C");
				jfieldID PositionDate_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PositionDate", "C");
				jfieldID YdPosition_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "YdPosition", "I");
				jfieldID Position_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "Position", "I");
				jfieldID LongFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "LongFrozen", "I");
				jfieldID ShortFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "ShortFrozen", "I");
				jfieldID LongFrozenAmount_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "LongFrozenAmount", "F");
				jfieldID ShortFrozenAmount_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "ShortFrozenAmount", "F");
				jfieldID OpenVolume_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "OpenVolume", "I");
				jfieldID CloseVolume_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CloseVolume", "I");
				jfieldID OpenAmount_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "OpenAmount", "F");
				jfieldID CloseAmount_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CloseAmount", "F");
				jfieldID PositionCost_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PositionCost", "F");
				jfieldID PreMargin_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PreMargin", "F");
				jfieldID UseMargin_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "UseMargin", "F");
				jfieldID FrozenMargin_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "FrozenMargin", "F");
				jfieldID FrozenCash_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "FrozenCash", "F");
				jfieldID FrozenCommission_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "FrozenCommission", "F");
				jfieldID CashIn_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CashIn", "F");
				jfieldID Commission_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "Commission", "F");
				jfieldID CloseProfit_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CloseProfit", "F");
				jfieldID PositionProfit_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PositionProfit", "F");
				jfieldID PreSettlementPrice_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "PreSettlementPrice", "F");
				jfieldID SettlementPrice_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "SettlementPrice", "F");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "SettlementID", "I");
				jfieldID OpenCost_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "OpenCost", "F");
				jfieldID ExchangeMargin_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "ExchangeMargin", "F");
				jfieldID CombPosition_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CombPosition", "I");
				jfieldID CombLongFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CombLongFrozen", "I");
				jfieldID CombShortFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CombShortFrozen", "I");
				jfieldID CloseProfitByDate_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CloseProfitByDate", "F");
				jfieldID CloseProfitByTrade_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "CloseProfitByTrade", "F");
				jfieldID TodayPosition_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "TodayPosition", "I");
				jfieldID MarginRateByMoney_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "MarginRateByMoney", "F");
				jfieldID MarginRateByVolume_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "MarginRateByVolume", "F");
				jfieldID StrikeFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "StrikeFrozen", "I");
				jfieldID StrikeFrozenAmount_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "StrikeFrozenAmount", "F");
				jfieldID AbandonFrozen_fid = jenv->GetFieldID(CTPInvestorPosition_cls, "AbandonFrozen", "I");

				jenv->SetObjectField(CTPInvestorPosition_obj, InstrumentID_fid, jenv->NewStringUTF(pInvestorPosition->InstrumentID));
				jenv->SetObjectField(CTPInvestorPosition_obj, BrokerID_fid, jenv->NewStringUTF(pInvestorPosition->BrokerID));
				jenv->SetObjectField(CTPInvestorPosition_obj, InvestorID_fid, jenv->NewStringUTF(pInvestorPosition->InvestorID));
				jenv->SetCharField(CTPInvestorPosition_obj, PosiDirection_fid, pInvestorPosition->PosiDirection);
				jenv->SetCharField(CTPInvestorPosition_obj, HedgeFlag_fid, pInvestorPosition->HedgeFlag);
				jenv->SetCharField(CTPInvestorPosition_obj, PositionDate_fid, pInvestorPosition->PositionDate);
				jenv->SetIntField(CTPInvestorPosition_obj, YdPosition_fid, pInvestorPosition->YdPosition);
				jenv->SetIntField(CTPInvestorPosition_obj, Position_fid, pInvestorPosition->Position);
				jenv->SetIntField(CTPInvestorPosition_obj, LongFrozen_fid, pInvestorPosition->LongFrozen);
				jenv->SetIntField(CTPInvestorPosition_obj, ShortFrozen_fid, pInvestorPosition->ShortFrozen);
				jenv->SetFloatField(CTPInvestorPosition_obj, LongFrozenAmount_fid, pInvestorPosition->LongFrozenAmount);
				jenv->SetFloatField(CTPInvestorPosition_obj, ShortFrozenAmount_fid, pInvestorPosition->ShortFrozenAmount);
				jenv->SetIntField(CTPInvestorPosition_obj, OpenVolume_fid, pInvestorPosition->OpenVolume);
				jenv->SetIntField(CTPInvestorPosition_obj, CloseVolume_fid, pInvestorPosition->CloseVolume);
				jenv->SetFloatField(CTPInvestorPosition_obj, OpenAmount_fid, pInvestorPosition->OpenAmount);
				jenv->SetFloatField(CTPInvestorPosition_obj, CloseAmount_fid, pInvestorPosition->CloseAmount);
				jenv->SetFloatField(CTPInvestorPosition_obj, PositionCost_fid, pInvestorPosition->PositionCost);
				jenv->SetFloatField(CTPInvestorPosition_obj, PreMargin_fid, pInvestorPosition->PreMargin);
				jenv->SetFloatField(CTPInvestorPosition_obj, UseMargin_fid, pInvestorPosition->UseMargin);
				jenv->SetFloatField(CTPInvestorPosition_obj, FrozenMargin_fid, pInvestorPosition->FrozenMargin);
				jenv->SetFloatField(CTPInvestorPosition_obj, FrozenCash_fid, pInvestorPosition->FrozenCash);
				jenv->SetFloatField(CTPInvestorPosition_obj, FrozenCommission_fid, pInvestorPosition->FrozenCommission);
				jenv->SetFloatField(CTPInvestorPosition_obj, CashIn_fid, pInvestorPosition->CashIn);
				jenv->SetFloatField(CTPInvestorPosition_obj, Commission_fid, pInvestorPosition->Commission);
				jenv->SetFloatField(CTPInvestorPosition_obj, CloseProfit_fid, pInvestorPosition->CloseProfit);
				jenv->SetFloatField(CTPInvestorPosition_obj, PositionProfit_fid, pInvestorPosition->PositionProfit);
				jenv->SetFloatField(CTPInvestorPosition_obj, PreSettlementPrice_fid, pInvestorPosition->PreSettlementPrice);
				jenv->SetFloatField(CTPInvestorPosition_obj, SettlementPrice_fid, pInvestorPosition->SettlementPrice);
				jenv->SetObjectField(CTPInvestorPosition_obj, TradingDay_fid, jenv->NewStringUTF(pInvestorPosition->TradingDay));
				jenv->SetIntField(CTPInvestorPosition_obj, SettlementID_fid, pInvestorPosition->SettlementID);
				jenv->SetFloatField(CTPInvestorPosition_obj, OpenCost_fid, pInvestorPosition->OpenCost);
				jenv->SetFloatField(CTPInvestorPosition_obj, ExchangeMargin_fid, pInvestorPosition->ExchangeMargin);
				jenv->SetIntField(CTPInvestorPosition_obj, CombPosition_fid, pInvestorPosition->CombPosition);
				jenv->SetIntField(CTPInvestorPosition_obj, CombLongFrozen_fid, pInvestorPosition->CombLongFrozen);
				jenv->SetIntField(CTPInvestorPosition_obj, CombShortFrozen_fid, pInvestorPosition->CombShortFrozen);
				jenv->SetFloatField(CTPInvestorPosition_obj, CloseProfitByDate_fid, pInvestorPosition->CloseProfitByDate);
				jenv->SetFloatField(CTPInvestorPosition_obj, CloseProfitByTrade_fid, pInvestorPosition->CloseProfitByTrade);
				jenv->SetIntField(CTPInvestorPosition_obj, TodayPosition_fid, pInvestorPosition->TodayPosition);
				jenv->SetFloatField(CTPInvestorPosition_obj, MarginRateByMoney_fid, pInvestorPosition->MarginRateByMoney);
				jenv->SetFloatField(CTPInvestorPosition_obj, MarginRateByVolume_fid, pInvestorPosition->MarginRateByVolume);
				jenv->SetIntField(CTPInvestorPosition_obj, StrikeFrozen_fid, pInvestorPosition->StrikeFrozen);
				jenv->SetFloatField(CTPInvestorPosition_obj, StrikeFrozenAmount_fid, pInvestorPosition->StrikeFrozenAmount);
				jenv->SetIntField(CTPInvestorPosition_obj, AbandonFrozen_fid, pInvestorPosition->AbandonFrozen);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQryInvestorPosition_mid, CTPInvestorPosition_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询资金账户响应
void CtpTraderSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryTradingAccount_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPTradingAccount_obj = NULL;
			if (pTradingAccount) {
				jclass CTPTradingAccount_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPTradingAccount;");
				jmethodID CTPTradingAccount_mid = jenv->GetMethodID(CTPTradingAccount_cls, "<init>", "()V");
				CTPTradingAccount_obj = jenv->NewObject(CTPTradingAccount_cls, CTPTradingAccount_mid, "");
				jfieldID AccountID_fid = jenv->GetFieldID(CTPTradingAccount_cls, "AccountID", "Ljava/lang/String;");
				jfieldID PreMortgage_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreMortgage", "F");
				jfieldID PreCredit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreCredit", "F");
				jfieldID PreDeposit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreDeposit", "F");
				jfieldID PreBalance_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreBalance", "F");
				jfieldID PreMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreMargin", "F");
				jfieldID InterestBase_fid = jenv->GetFieldID(CTPTradingAccount_cls, "InterestBase", "F");
				jfieldID Interest_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Interest", "F");
				jfieldID Deposit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Deposit", "F");
				jfieldID Withdraw_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Withdraw", "F");
				jfieldID FrozenMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FrozenMargin", "F");
				jfieldID FrozenCash_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FrozenCash", "F");
				jfieldID FrozenCommission_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FrozenCommission", "F");
				jfieldID CurrMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "CurrMargin", "F");
				jfieldID CashIn_fid = jenv->GetFieldID(CTPTradingAccount_cls, "CashIn", "F");
				jfieldID Commission_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Commission", "F");
				jfieldID CloseProfit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "CloseProfit", "F");
				jfieldID PositionProfit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PositionProfit", "F");
				jfieldID Balance_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Balance", "F");
				jfieldID Available_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Available", "F");
				jfieldID WithdrawQuota_fid = jenv->GetFieldID(CTPTradingAccount_cls, "WithdrawQuota", "F");
				jfieldID Reserve_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Reserve", "F");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPTradingAccount_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SettlementID", "I");
				jfieldID Credit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Credit", "F");
				jfieldID Mortgage_fid = jenv->GetFieldID(CTPTradingAccount_cls, "Mortgage", "F");
				jfieldID ExchangeMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "ExchangeMargin", "F");
				jfieldID DeliveryMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "DeliveryMargin", "F");
				jfieldID ExchangeDeliveryMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "ExchangeDeliveryMargin", "F");
				jfieldID ReserveBalance_fid = jenv->GetFieldID(CTPTradingAccount_cls, "ReserveBalance", "F");
				jfieldID CurrencyID_fid = jenv->GetFieldID(CTPTradingAccount_cls, "CurrencyID", "Ljava/lang/String;");
				jfieldID PreFundMortgageIn_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreFundMortgageIn", "F");
				jfieldID PreFundMortgageOut_fid = jenv->GetFieldID(CTPTradingAccount_cls, "PreFundMortgageOut", "F");
				jfieldID FundMortgageIn_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FundMortgageIn", "F");
				jfieldID FundMortgageOut_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FundMortgageOut", "F");
				jfieldID FundMortgageAvailable_fid = jenv->GetFieldID(CTPTradingAccount_cls, "FundMortgageAvailable", "F");
				jfieldID MortgageableFund_fid = jenv->GetFieldID(CTPTradingAccount_cls, "MortgageableFund", "F");
				jfieldID SpecProductMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductMargin", "F");
				jfieldID SpecProductFrozenMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductFrozenMargin", "F");
				jfieldID SpecProductCommission_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductCommission", "F");
				jfieldID SpecProductFrozenCommission_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductFrozenCommission", "F");
				jfieldID SpecProductPositionProfit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductPositionProfit", "F");
				jfieldID SpecProductCloseProfit_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductCloseProfit", "F");
				jfieldID SpecProductPositionProfitByAlg_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductPositionProfitByAlg", "F");
				jfieldID SpecProductExchangeMargin_fid = jenv->GetFieldID(CTPTradingAccount_cls, "SpecProductExchangeMargin", "F");

				jenv->SetObjectField(CTPTradingAccount_obj, AccountID_fid, jenv->NewStringUTF(pTradingAccount->AccountID));
				jenv->SetFloatField(CTPTradingAccount_obj, PreMortgage_fid, pTradingAccount->PreMortgage);
				jenv->SetFloatField(CTPTradingAccount_obj, PreCredit_fid, pTradingAccount->PreCredit);
				jenv->SetFloatField(CTPTradingAccount_obj, PreDeposit_fid, pTradingAccount->PreDeposit);
				jenv->SetFloatField(CTPTradingAccount_obj, PreBalance_fid, pTradingAccount->PreBalance);
				jenv->SetFloatField(CTPTradingAccount_obj, PreMargin_fid, pTradingAccount->PreMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, InterestBase_fid, pTradingAccount->InterestBase);
				jenv->SetFloatField(CTPTradingAccount_obj, Interest_fid, pTradingAccount->Interest);
				jenv->SetFloatField(CTPTradingAccount_obj, Deposit_fid, pTradingAccount->Deposit);
				jenv->SetFloatField(CTPTradingAccount_obj, Withdraw_fid, pTradingAccount->Withdraw);
				jenv->SetFloatField(CTPTradingAccount_obj, FrozenMargin_fid, pTradingAccount->FrozenMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, FrozenCash_fid, pTradingAccount->FrozenCash);
				jenv->SetFloatField(CTPTradingAccount_obj, FrozenCommission_fid, pTradingAccount->FrozenCommission);
				jenv->SetFloatField(CTPTradingAccount_obj, CurrMargin_fid, pTradingAccount->CurrMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, CashIn_fid, pTradingAccount->CashIn);
				jenv->SetFloatField(CTPTradingAccount_obj, Commission_fid, pTradingAccount->Commission);
				jenv->SetFloatField(CTPTradingAccount_obj, CloseProfit_fid, pTradingAccount->CloseProfit);
				jenv->SetFloatField(CTPTradingAccount_obj, PositionProfit_fid, pTradingAccount->PositionProfit);
				jenv->SetFloatField(CTPTradingAccount_obj, Balance_fid, pTradingAccount->Balance);
				jenv->SetFloatField(CTPTradingAccount_obj, Available_fid, pTradingAccount->Available);
				jenv->SetFloatField(CTPTradingAccount_obj, WithdrawQuota_fid, pTradingAccount->WithdrawQuota);
				jenv->SetFloatField(CTPTradingAccount_obj, Reserve_fid, pTradingAccount->Reserve);
				jenv->SetObjectField(CTPTradingAccount_obj, TradingDay_fid, jenv->NewStringUTF(pTradingAccount->TradingDay));
				jenv->SetIntField(CTPTradingAccount_obj, SettlementID_fid, pTradingAccount->SettlementID);
				jenv->SetFloatField(CTPTradingAccount_obj, Credit_fid, pTradingAccount->Credit);
				jenv->SetFloatField(CTPTradingAccount_obj, Mortgage_fid, pTradingAccount->Mortgage);
				jenv->SetFloatField(CTPTradingAccount_obj, ExchangeMargin_fid, pTradingAccount->ExchangeMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, DeliveryMargin_fid, pTradingAccount->DeliveryMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, ExchangeDeliveryMargin_fid, pTradingAccount->ExchangeDeliveryMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, ReserveBalance_fid, pTradingAccount->ReserveBalance);
				jenv->SetObjectField(CTPTradingAccount_obj, CurrencyID_fid, jenv->NewStringUTF(pTradingAccount->CurrencyID));
				jenv->SetFloatField(CTPTradingAccount_obj, PreFundMortgageIn_fid, pTradingAccount->PreFundMortgageIn);
				jenv->SetFloatField(CTPTradingAccount_obj, PreFundMortgageOut_fid, pTradingAccount->PreFundMortgageOut);
				jenv->SetFloatField(CTPTradingAccount_obj, FundMortgageIn_fid, pTradingAccount->FundMortgageIn);
				jenv->SetFloatField(CTPTradingAccount_obj, FundMortgageOut_fid, pTradingAccount->FundMortgageOut);
				jenv->SetFloatField(CTPTradingAccount_obj, FundMortgageAvailable_fid, pTradingAccount->FundMortgageAvailable);
				jenv->SetFloatField(CTPTradingAccount_obj, MortgageableFund_fid, pTradingAccount->MortgageableFund);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductMargin_fid, pTradingAccount->SpecProductMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductFrozenMargin_fid, pTradingAccount->SpecProductFrozenMargin);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductCommission_fid, pTradingAccount->SpecProductCommission);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductFrozenCommission_fid, pTradingAccount->SpecProductFrozenCommission);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductPositionProfit_fid, pTradingAccount->SpecProductPositionProfit);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductCloseProfit_fid, pTradingAccount->SpecProductCloseProfit);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductPositionProfitByAlg_fid, pTradingAccount->SpecProductPositionProfitByAlg);
				jenv->SetFloatField(CTPTradingAccount_obj, SpecProductExchangeMargin_fid, pTradingAccount->SpecProductExchangeMargin);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQryTradingAccount_mid, CTPTradingAccount_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///报单录入请求响应
void CtpTraderSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspOrderInsert_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInputOrder_obj = NULL;
			if (pInputOrder) {
				jclass CTPInputOrder_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInputOrder;");
				jmethodID CTPInputOrder_mid = jenv->GetMethodID(CTPInputOrder_cls, "<init>", "()V");
				CTPInputOrder_obj = jenv->NewObject(CTPInputOrder_cls, CTPInputOrder_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInputOrder_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInputOrder_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInputOrder_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPInputOrder_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPInputOrder_cls, "UserID", "Ljava/lang/String;");
				jfieldID OrderPriceType_fid = jenv->GetFieldID(CTPInputOrder_cls, "OrderPriceType", "C");
				jfieldID Direction_fid = jenv->GetFieldID(CTPInputOrder_cls, "Direction", "C");
				jfieldID CombOffsetFlag_fid = jenv->GetFieldID(CTPInputOrder_cls, "CombOffsetFlag", "Ljava/lang/String;");
				jfieldID CombHedgeFlag_fid = jenv->GetFieldID(CTPInputOrder_cls, "CombHedgeFlag", "Ljava/lang/String;");
				jfieldID LimitPrice_fid = jenv->GetFieldID(CTPInputOrder_cls, "LimitPrice", "F");
				jfieldID VolumeTotalOriginal_fid = jenv->GetFieldID(CTPInputOrder_cls, "VolumeTotalOriginal", "I");
				jfieldID TimeCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "TimeCondition", "C");
				jfieldID GTDDate_fid = jenv->GetFieldID(CTPInputOrder_cls, "GTDDate", "Ljava/lang/String;");
				jfieldID VolumeCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "VolumeCondition", "C");
				jfieldID MinVolume_fid = jenv->GetFieldID(CTPInputOrder_cls, "MinVolume", "I");
				jfieldID ContingentCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "ContingentCondition", "C");
				jfieldID StopPrice_fid = jenv->GetFieldID(CTPInputOrder_cls, "StopPrice", "F");
				jfieldID ForceCloseReason_fid = jenv->GetFieldID(CTPInputOrder_cls, "ForceCloseReason", "C");
				jfieldID IsAutoSuspend_fid = jenv->GetFieldID(CTPInputOrder_cls, "IsAutoSuspend", "I");
				jfieldID BusinessUnit_fid = jenv->GetFieldID(CTPInputOrder_cls, "BusinessUnit", "Ljava/lang/String;");
				jfieldID RequestID_fid = jenv->GetFieldID(CTPInputOrder_cls, "RequestID", "I");
				jfieldID UserForceClose_fid = jenv->GetFieldID(CTPInputOrder_cls, "UserForceClose", "I");
				jfieldID IsSwapOrder_fid = jenv->GetFieldID(CTPInputOrder_cls, "IsSwapOrder", "I");

				jenv->SetObjectField(CTPInputOrder_obj, BrokerID_fid, jenv->NewStringUTF(pInputOrder->BrokerID));
				jenv->SetObjectField(CTPInputOrder_obj, InvestorID_fid, jenv->NewStringUTF(pInputOrder->InvestorID));
				jenv->SetObjectField(CTPInputOrder_obj, InstrumentID_fid, jenv->NewStringUTF(pInputOrder->InstrumentID));
				jenv->SetObjectField(CTPInputOrder_obj, OrderRef_fid, jenv->NewStringUTF(pInputOrder->OrderRef));
				jenv->SetObjectField(CTPInputOrder_obj, UserID_fid, jenv->NewStringUTF(pInputOrder->UserID));
				jenv->SetCharField(CTPInputOrder_obj, OrderPriceType_fid, pInputOrder->OrderPriceType);
				jenv->SetCharField(CTPInputOrder_obj, Direction_fid, pInputOrder->Direction);
				jenv->SetObjectField(CTPInputOrder_obj, CombOffsetFlag_fid, jenv->NewStringUTF(pInputOrder->CombOffsetFlag));
				jenv->SetObjectField(CTPInputOrder_obj, CombHedgeFlag_fid, jenv->NewStringUTF(pInputOrder->CombHedgeFlag));
				jenv->SetFloatField(CTPInputOrder_obj, LimitPrice_fid, pInputOrder->LimitPrice);
				jenv->SetIntField(CTPInputOrder_obj, VolumeTotalOriginal_fid, pInputOrder->VolumeTotalOriginal);
				jenv->SetCharField(CTPInputOrder_obj, TimeCondition_fid, pInputOrder->TimeCondition);
				jenv->SetObjectField(CTPInputOrder_obj, GTDDate_fid, jenv->NewStringUTF(pInputOrder->GTDDate));
				jenv->SetCharField(CTPInputOrder_obj, VolumeCondition_fid, pInputOrder->VolumeCondition);
				jenv->SetIntField(CTPInputOrder_obj, MinVolume_fid, pInputOrder->MinVolume);
				jenv->SetCharField(CTPInputOrder_obj, ContingentCondition_fid, pInputOrder->ContingentCondition);
				jenv->SetFloatField(CTPInputOrder_obj, StopPrice_fid, pInputOrder->StopPrice);
				jenv->SetCharField(CTPInputOrder_obj, ForceCloseReason_fid, pInputOrder->ForceCloseReason);
				jenv->SetIntField(CTPInputOrder_obj, IsAutoSuspend_fid, pInputOrder->IsAutoSuspend);
				jenv->SetObjectField(CTPInputOrder_obj, BusinessUnit_fid, jenv->NewStringUTF(pInputOrder->BusinessUnit));
				jenv->SetIntField(CTPInputOrder_obj, RequestID_fid, pInputOrder->RequestID);
				jenv->SetIntField(CTPInputOrder_obj, UserForceClose_fid, pInputOrder->UserForceClose);
				jenv->SetIntField(CTPInputOrder_obj, IsSwapOrder_fid, pInputOrder->IsSwapOrder);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspOrderInsert_mid, CTPInputOrder_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///报单录入错误回报
void CtpTraderSpi::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo) {
	if (OnErrRtnOrderInsert_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInputOrder_obj = NULL;
			if (pInputOrder) {
				jclass CTPInputOrder_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInputOrder;");
				jmethodID CTPInputOrder_mid = jenv->GetMethodID(CTPInputOrder_cls, "<init>", "()V");
				CTPInputOrder_obj = jenv->NewObject(CTPInputOrder_cls, CTPInputOrder_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInputOrder_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInputOrder_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInputOrder_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPInputOrder_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID UserID_fid = jenv->GetFieldID(CTPInputOrder_cls, "UserID", "Ljava/lang/String;");
				jfieldID OrderPriceType_fid = jenv->GetFieldID(CTPInputOrder_cls, "OrderPriceType", "C");
				jfieldID Direction_fid = jenv->GetFieldID(CTPInputOrder_cls, "Direction", "C");
				jfieldID CombOffsetFlag_fid = jenv->GetFieldID(CTPInputOrder_cls, "CombOffsetFlag", "Ljava/lang/String;");
				jfieldID CombHedgeFlag_fid = jenv->GetFieldID(CTPInputOrder_cls, "CombHedgeFlag", "Ljava/lang/String;");
				jfieldID LimitPrice_fid = jenv->GetFieldID(CTPInputOrder_cls, "LimitPrice", "F");
				jfieldID VolumeTotalOriginal_fid = jenv->GetFieldID(CTPInputOrder_cls, "VolumeTotalOriginal", "I");
				jfieldID TimeCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "TimeCondition", "C");
				jfieldID GTDDate_fid = jenv->GetFieldID(CTPInputOrder_cls, "GTDDate", "Ljava/lang/String;");
				jfieldID VolumeCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "VolumeCondition", "C");
				jfieldID MinVolume_fid = jenv->GetFieldID(CTPInputOrder_cls, "MinVolume", "I");
				jfieldID ContingentCondition_fid = jenv->GetFieldID(CTPInputOrder_cls, "ContingentCondition", "C");
				jfieldID StopPrice_fid = jenv->GetFieldID(CTPInputOrder_cls, "StopPrice", "F");
				jfieldID ForceCloseReason_fid = jenv->GetFieldID(CTPInputOrder_cls, "ForceCloseReason", "C");
				jfieldID IsAutoSuspend_fid = jenv->GetFieldID(CTPInputOrder_cls, "IsAutoSuspend", "I");
				jfieldID BusinessUnit_fid = jenv->GetFieldID(CTPInputOrder_cls, "BusinessUnit", "Ljava/lang/String;");
				jfieldID RequestID_fid = jenv->GetFieldID(CTPInputOrder_cls, "RequestID", "I");
				jfieldID UserForceClose_fid = jenv->GetFieldID(CTPInputOrder_cls, "UserForceClose", "I");
				jfieldID IsSwapOrder_fid = jenv->GetFieldID(CTPInputOrder_cls, "IsSwapOrder", "I");

				jenv->SetObjectField(CTPInputOrder_obj, BrokerID_fid, jenv->NewStringUTF(pInputOrder->BrokerID));
				jenv->SetObjectField(CTPInputOrder_obj, InvestorID_fid, jenv->NewStringUTF(pInputOrder->InvestorID));
				jenv->SetObjectField(CTPInputOrder_obj, InstrumentID_fid, jenv->NewStringUTF(pInputOrder->InstrumentID));
				jenv->SetObjectField(CTPInputOrder_obj, OrderRef_fid, jenv->NewStringUTF(pInputOrder->OrderRef));
				jenv->SetObjectField(CTPInputOrder_obj, UserID_fid, jenv->NewStringUTF(pInputOrder->UserID));
				jenv->SetCharField(CTPInputOrder_obj, OrderPriceType_fid, pInputOrder->OrderPriceType);
				jenv->SetCharField(CTPInputOrder_obj, Direction_fid, pInputOrder->Direction);
				jenv->SetObjectField(CTPInputOrder_obj, CombOffsetFlag_fid, jenv->NewStringUTF(pInputOrder->CombOffsetFlag));
				jenv->SetObjectField(CTPInputOrder_obj, CombHedgeFlag_fid, jenv->NewStringUTF(pInputOrder->CombHedgeFlag));
				jenv->SetFloatField(CTPInputOrder_obj, LimitPrice_fid, pInputOrder->LimitPrice);
				jenv->SetIntField(CTPInputOrder_obj, VolumeTotalOriginal_fid, pInputOrder->VolumeTotalOriginal);
				jenv->SetCharField(CTPInputOrder_obj, TimeCondition_fid, pInputOrder->TimeCondition);
				jenv->SetObjectField(CTPInputOrder_obj, GTDDate_fid, jenv->NewStringUTF(pInputOrder->GTDDate));
				jenv->SetCharField(CTPInputOrder_obj, VolumeCondition_fid, pInputOrder->VolumeCondition);
				jenv->SetIntField(CTPInputOrder_obj, MinVolume_fid, pInputOrder->MinVolume);
				jenv->SetCharField(CTPInputOrder_obj, ContingentCondition_fid, pInputOrder->ContingentCondition);
				jenv->SetFloatField(CTPInputOrder_obj, StopPrice_fid, pInputOrder->StopPrice);
				jenv->SetCharField(CTPInputOrder_obj, ForceCloseReason_fid, pInputOrder->ForceCloseReason);
				jenv->SetIntField(CTPInputOrder_obj, IsAutoSuspend_fid, pInputOrder->IsAutoSuspend);
				jenv->SetObjectField(CTPInputOrder_obj, BusinessUnit_fid, jenv->NewStringUTF(pInputOrder->BusinessUnit));
				jenv->SetIntField(CTPInputOrder_obj, RequestID_fid, pInputOrder->RequestID);
				jenv->SetIntField(CTPInputOrder_obj, UserForceClose_fid, pInputOrder->UserForceClose);
				jenv->SetIntField(CTPInputOrder_obj, IsSwapOrder_fid, pInputOrder->IsSwapOrder);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnErrRtnOrderInsert_mid, CTPInputOrder_obj, CTPRspInfo_obj);
		}
		jvm->DetachCurrentThread();
	}
}

///报单操作请求响应
void CtpTraderSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspOrderAction_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInputOrderAction_obj = NULL;
			if (pInputOrderAction) {
				jclass CTPInputOrderAction_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInputOrderAction;");
				jmethodID CTPInputOrderAction_mid = jenv->GetMethodID(CTPInputOrderAction_cls, "<init>", "()V");
				CTPInputOrderAction_obj = jenv->NewObject(CTPInputOrderAction_cls, CTPInputOrderAction_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID OrderActionRef_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "OrderActionRef", "I");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID RequestID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "RequestID", "I");
				jfieldID FrontID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "FrontID", "I");
				jfieldID SessionID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "SessionID", "I");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID OrderSysID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "OrderSysID", "Ljava/lang/String;");
				jfieldID ActionFlag_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "ActionFlag", "C");
				jfieldID LimitPrice_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "LimitPrice", "F");
				jfieldID VolumeChange_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "VolumeChange", "I");
				jfieldID UserID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "UserID", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInputOrderAction_cls, "InstrumentID", "Ljava/lang/String;");

				jenv->SetObjectField(CTPInputOrderAction_obj, BrokerID_fid, jenv->NewStringUTF(pInputOrderAction->BrokerID));
				jenv->SetObjectField(CTPInputOrderAction_obj, InvestorID_fid, jenv->NewStringUTF(pInputOrderAction->InvestorID));
				jenv->SetIntField(CTPInputOrderAction_obj, OrderActionRef_fid, pInputOrderAction->OrderActionRef);
				jenv->SetObjectField(CTPInputOrderAction_obj, OrderRef_fid, jenv->NewStringUTF(pInputOrderAction->OrderRef));
				jenv->SetIntField(CTPInputOrderAction_obj, RequestID_fid, pInputOrderAction->RequestID);
				jenv->SetIntField(CTPInputOrderAction_obj, FrontID_fid, pInputOrderAction->FrontID);
				jenv->SetIntField(CTPInputOrderAction_obj, SessionID_fid, pInputOrderAction->SessionID);
				jenv->SetObjectField(CTPInputOrderAction_obj, ExchangeID_fid, jenv->NewStringUTF(pInputOrderAction->ExchangeID));
				jenv->SetObjectField(CTPInputOrderAction_obj, OrderSysID_fid, jenv->NewStringUTF(pInputOrderAction->OrderSysID));
				jenv->SetCharField(CTPInputOrderAction_obj, ActionFlag_fid, pInputOrderAction->ActionFlag);
				jenv->SetFloatField(CTPInputOrderAction_obj, LimitPrice_fid, pInputOrderAction->LimitPrice);
				jenv->SetIntField(CTPInputOrderAction_obj, VolumeChange_fid, pInputOrderAction->VolumeChange);
				jenv->SetObjectField(CTPInputOrderAction_obj, UserID_fid, jenv->NewStringUTF(pInputOrderAction->UserID));
				jenv->SetObjectField(CTPInputOrderAction_obj, InstrumentID_fid, jenv->NewStringUTF(pInputOrderAction->InstrumentID));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspOrderAction_mid, CTPInputOrderAction_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///报单操作错误回报
void CtpTraderSpi::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo) {
	if (OnRspOrderAction_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPOrderAction_obj = NULL;
			if (pOrderAction) {
				jclass CTPOrderAction_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPOrderAction;");
				jmethodID CTPOrderAction_mid = jenv->GetMethodID(CTPOrderAction_cls, "<init>", "()V");
				CTPOrderAction_obj = jenv->NewObject(CTPOrderAction_cls, CTPOrderAction_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPOrderAction_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPOrderAction_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID OrderActionRef_fid = jenv->GetFieldID(CTPOrderAction_cls, "OrderActionRef", "I");
				jfieldID OrderRef_fid = jenv->GetFieldID(CTPOrderAction_cls, "OrderRef", "Ljava/lang/String;");
				jfieldID RequestID_fid = jenv->GetFieldID(CTPOrderAction_cls, "RequestID", "I");
				jfieldID FrontID_fid = jenv->GetFieldID(CTPOrderAction_cls, "FrontID", "I");
				jfieldID SessionID_fid = jenv->GetFieldID(CTPOrderAction_cls, "SessionID", "I");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPOrderAction_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID OrderSysID_fid = jenv->GetFieldID(CTPOrderAction_cls, "OrderSysID", "Ljava/lang/String;");
				jfieldID ActionFlag_fid = jenv->GetFieldID(CTPOrderAction_cls, "ActionFlag", "C");
				jfieldID LimitPrice_fid = jenv->GetFieldID(CTPOrderAction_cls, "LimitPrice", "F");
				jfieldID VolumeChange_fid = jenv->GetFieldID(CTPOrderAction_cls, "VolumeChange", "I");
				jfieldID ActionDate_fid = jenv->GetFieldID(CTPOrderAction_cls, "ActionDate", "Ljava/lang/String;");
				jfieldID ActionTime_fid = jenv->GetFieldID(CTPOrderAction_cls, "ActionTime", "Ljava/lang/String;");
				jfieldID TraderID_fid = jenv->GetFieldID(CTPOrderAction_cls, "TraderID", "Ljava/lang/String;");
				jfieldID InstallID_fid = jenv->GetFieldID(CTPOrderAction_cls, "InstallID", "I");
				jfieldID OrderLocalID_fid = jenv->GetFieldID(CTPOrderAction_cls, "OrderLocalID", "Ljava/lang/String;");
				jfieldID ActionLocalID_fid = jenv->GetFieldID(CTPOrderAction_cls, "ActionLocalID", "Ljava/lang/String;");
				jfieldID ParticipantID_fid = jenv->GetFieldID(CTPOrderAction_cls, "ParticipantID", "Ljava/lang/String;");
				jfieldID ClientID_fid = jenv->GetFieldID(CTPOrderAction_cls, "ClientID", "Ljava/lang/String;");
				jfieldID BusinessUnit_fid = jenv->GetFieldID(CTPOrderAction_cls, "BusinessUnit", "Ljava/lang/String;");
				jfieldID OrderActionStatus_fid = jenv->GetFieldID(CTPOrderAction_cls, "OrderActionStatus", "C");
				jfieldID UserID_fid = jenv->GetFieldID(CTPOrderAction_cls, "UserID", "Ljava/lang/String;");
				jfieldID StatusMsg_fid = jenv->GetFieldID(CTPOrderAction_cls, "StatusMsg", "Ljava/lang/String;");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPOrderAction_cls, "InstrumentID", "Ljava/lang/String;");

				jenv->SetObjectField(CTPOrderAction_obj, BrokerID_fid, jenv->NewStringUTF(pOrderAction->BrokerID));
				jenv->SetObjectField(CTPOrderAction_obj, InvestorID_fid, jenv->NewStringUTF(pOrderAction->InvestorID));
				jenv->SetIntField(CTPOrderAction_obj, OrderActionRef_fid, pOrderAction->OrderActionRef);
				jenv->SetObjectField(CTPOrderAction_obj, OrderRef_fid, jenv->NewStringUTF(pOrderAction->OrderRef));
				jenv->SetIntField(CTPOrderAction_obj, RequestID_fid, pOrderAction->RequestID);
				jenv->SetIntField(CTPOrderAction_obj, FrontID_fid, pOrderAction->FrontID);
				jenv->SetIntField(CTPOrderAction_obj, SessionID_fid, pOrderAction->SessionID);
				jenv->SetObjectField(CTPOrderAction_obj, ExchangeID_fid, jenv->NewStringUTF(pOrderAction->ExchangeID));
				jenv->SetObjectField(CTPOrderAction_obj, OrderSysID_fid, jenv->NewStringUTF(pOrderAction->OrderSysID));
				jenv->SetCharField(CTPOrderAction_obj, ActionFlag_fid, pOrderAction->ActionFlag);
				jenv->SetFloatField(CTPOrderAction_obj, LimitPrice_fid, pOrderAction->LimitPrice);
				jenv->SetIntField(CTPOrderAction_obj, VolumeChange_fid, pOrderAction->VolumeChange);
				jenv->SetObjectField(CTPOrderAction_obj, ActionDate_fid, jenv->NewStringUTF(pOrderAction->ActionDate));
				jenv->SetObjectField(CTPOrderAction_obj, ActionTime_fid, jenv->NewStringUTF(pOrderAction->ActionTime));
				jenv->SetObjectField(CTPOrderAction_obj, TraderID_fid, jenv->NewStringUTF(pOrderAction->TraderID));
				jenv->SetIntField(CTPOrderAction_obj, InstallID_fid, pOrderAction->InstallID);
				jenv->SetObjectField(CTPOrderAction_obj, OrderLocalID_fid, jenv->NewStringUTF(pOrderAction->OrderLocalID));
				jenv->SetObjectField(CTPOrderAction_obj, ActionLocalID_fid, jenv->NewStringUTF(pOrderAction->ActionLocalID));
				jenv->SetObjectField(CTPOrderAction_obj, ParticipantID_fid, jenv->NewStringUTF(pOrderAction->ParticipantID));
				jenv->SetObjectField(CTPOrderAction_obj, ClientID_fid, jenv->NewStringUTF(pOrderAction->ClientID));
				jenv->SetObjectField(CTPOrderAction_obj, BusinessUnit_fid, jenv->NewStringUTF(pOrderAction->BusinessUnit));
				jenv->SetCharField(CTPOrderAction_obj, OrderActionStatus_fid, pOrderAction->OrderActionStatus);
				jenv->SetObjectField(CTPOrderAction_obj, UserID_fid, jenv->NewStringUTF(pOrderAction->UserID));
				jenv->SetObjectField(CTPOrderAction_obj, StatusMsg_fid, jenv->NewStringUTF(pOrderAction->StatusMsg));
				jenv->SetObjectField(CTPOrderAction_obj, InstrumentID_fid, jenv->NewStringUTF(pOrderAction->InstrumentID));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspOrderAction_mid, CTPOrderAction_obj, CTPRspInfo_obj);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询结算信息确认响应
void CtpTraderSpi::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQrySettlementInfoConfirm_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPSettlementInfoConfirm_obj = NULL;
			if (pSettlementInfoConfirm) {
				jclass CTPSettlementInfoConfirm_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSettlementInfoConfirm;");
				jmethodID CTPSettlementInfoConfirm_mid = jenv->GetMethodID(CTPSettlementInfoConfirm_cls, "<init>", "()V");
				CTPSettlementInfoConfirm_obj = jenv->NewObject(CTPSettlementInfoConfirm_cls, CTPSettlementInfoConfirm_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID ConfirmDate_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "ConfirmDate", "Ljava/lang/String;");
				jfieldID ConfirmTime_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "ConfirmTime", "Ljava/lang/String;");

				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, BrokerID_fid, jenv->NewStringUTF(pSettlementInfoConfirm->BrokerID));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, InvestorID_fid, jenv->NewStringUTF(pSettlementInfoConfirm->InvestorID));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, ConfirmDate_fid, jenv->NewStringUTF(pSettlementInfoConfirm->ConfirmDate));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, ConfirmTime_fid, jenv->NewStringUTF(pSettlementInfoConfirm->ConfirmTime));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQrySettlementInfoConfirm_mid, CTPSettlementInfoConfirm_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///投资者结算结果确认响应
void CtpTraderSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspSettlementInfoConfirm_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPSettlementInfoConfirm_obj = NULL;
			if (pSettlementInfoConfirm) {
				jclass CTPSettlementInfoConfirm_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSettlementInfoConfirm;");
				jmethodID CTPSettlementInfoConfirm_mid = jenv->GetMethodID(CTPSettlementInfoConfirm_cls, "<init>", "()V");
				CTPSettlementInfoConfirm_obj = jenv->NewObject(CTPSettlementInfoConfirm_cls, CTPSettlementInfoConfirm_mid, "");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID ConfirmDate_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "ConfirmDate", "Ljava/lang/String;");
				jfieldID ConfirmTime_fid = jenv->GetFieldID(CTPSettlementInfoConfirm_cls, "ConfirmTime", "Ljava/lang/String;");

				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, BrokerID_fid, jenv->NewStringUTF(pSettlementInfoConfirm->BrokerID));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, InvestorID_fid, jenv->NewStringUTF(pSettlementInfoConfirm->InvestorID));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, ConfirmDate_fid, jenv->NewStringUTF(pSettlementInfoConfirm->ConfirmDate));
				jenv->SetObjectField(CTPSettlementInfoConfirm_obj, ConfirmTime_fid, jenv->NewStringUTF(pSettlementInfoConfirm->ConfirmTime));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspSettlementInfoConfirm_mid, CTPSettlementInfoConfirm_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询投资者结算结果响应
void CtpTraderSpi::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQrySettlementInfo_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPSettlementInfo_obj = NULL;
			if (pSettlementInfo) {
				jclass CTPSettlementInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSettlementInfo;");
				jmethodID CTPSettlementInfo_mid = jenv->GetMethodID(CTPSettlementInfo_cls, "<init>", "()V");
				CTPSettlementInfo_obj = jenv->NewObject(CTPSettlementInfo_cls, CTPSettlementInfo_mid, "");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "SettlementID", "I");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID SequenceNo_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "SequenceNo", "I");
				jfieldID Content_fid = jenv->GetFieldID(CTPSettlementInfo_cls, "Content", "Ljava/lang/String;");

				jenv->SetObjectField(CTPSettlementInfo_obj, TradingDay_fid, jenv->NewStringUTF(pSettlementInfo->TradingDay));
				jenv->SetIntField(CTPSettlementInfo_obj, SettlementID_fid, pSettlementInfo->SettlementID);
				jenv->SetObjectField(CTPSettlementInfo_obj, BrokerID_fid, jenv->NewStringUTF(pSettlementInfo->BrokerID));
				jenv->SetObjectField(CTPSettlementInfo_obj, InvestorID_fid, jenv->NewStringUTF(pSettlementInfo->InvestorID));
				jenv->SetIntField(CTPSettlementInfo_obj, SequenceNo_fid, pSettlementInfo->SequenceNo);
				jenv->SetObjectField(CTPSettlementInfo_obj, Content_fid, jenv->NewStringUTF(pSettlementInfo->Content));
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQrySettlementInfo_mid, CTPSettlementInfo_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}



///请求查询合约保证金率响应
void CtpTraderSpi::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryInstrumentMarginRate_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInstrumentMarginRate_obj = NULL;
			if (pInstrumentMarginRate) {
				jclass CTPInstrumentMarginRate_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInstrumentMarginRate;");
				jmethodID CTPInstrumentMarginRate_mid = jenv->GetMethodID(CTPInstrumentMarginRate_cls, "<init>", "()V");
				CTPInstrumentMarginRate_obj = jenv->NewObject(CTPInstrumentMarginRate_cls, CTPInstrumentMarginRate_mid, "");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID InvestorRange_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "InvestorRange", "C");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID HedgeFlag_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "HedgeFlag", "C");
				jfieldID LongMarginRatioByMoney_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "LongMarginRatioByMoney", "F");
				jfieldID LongMarginRatioByVolume_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "LongMarginRatioByVolume", "F");
				jfieldID ShortMarginRatioByMoney_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "ShortMarginRatioByMoney", "F");
				jfieldID ShortMarginRatioByVolume_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "ShortMarginRatioByVolume", "F");
				jfieldID IsRelative_fid = jenv->GetFieldID(CTPInstrumentMarginRate_cls, "IsRelative", "I");

				jenv->SetObjectField(CTPInstrumentMarginRate_obj, InstrumentID_fid, jenv->NewStringUTF(pInstrumentMarginRate->InstrumentID));
				jenv->SetCharField(CTPInstrumentMarginRate_obj, InvestorRange_fid, pInstrumentMarginRate->InvestorRange);
				jenv->SetObjectField(CTPInstrumentMarginRate_obj, BrokerID_fid, jenv->NewStringUTF(pInstrumentMarginRate->BrokerID));
				jenv->SetObjectField(CTPInstrumentMarginRate_obj, InvestorID_fid, jenv->NewStringUTF(pInstrumentMarginRate->InvestorID));
				jenv->SetCharField(CTPInstrumentMarginRate_obj, HedgeFlag_fid, pInstrumentMarginRate->HedgeFlag);
				jenv->SetFloatField(CTPInstrumentMarginRate_obj, LongMarginRatioByMoney_fid, pInstrumentMarginRate->LongMarginRatioByMoney);
				jenv->SetFloatField(CTPInstrumentMarginRate_obj, LongMarginRatioByVolume_fid, pInstrumentMarginRate->LongMarginRatioByVolume);
				jenv->SetFloatField(CTPInstrumentMarginRate_obj, ShortMarginRatioByMoney_fid, pInstrumentMarginRate->ShortMarginRatioByMoney);
				jenv->SetFloatField(CTPInstrumentMarginRate_obj, ShortMarginRatioByVolume_fid, pInstrumentMarginRate->ShortMarginRatioByVolume);
				jenv->SetIntField(CTPInstrumentMarginRate_obj, IsRelative_fid, pInstrumentMarginRate->IsRelative);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQryInstrumentMarginRate_mid, CTPInstrumentMarginRate_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询合约手续费率响应
void CtpTraderSpi::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryInstrumentCommissionRate_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInstrumentCommissionRate_obj = NULL;
			if (pInstrumentCommissionRate) {
				jclass CTPInstrumentCommissionRate_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInstrumentCommissionRate;");
				jmethodID CTPInstrumentCommissionRate_mid = jenv->GetMethodID(CTPInstrumentCommissionRate_cls, "<init>", "()V");
				CTPInstrumentCommissionRate_obj = jenv->NewObject(CTPInstrumentCommissionRate_cls, CTPInstrumentCommissionRate_mid, "");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID InvestorRange_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "InvestorRange", "C");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID OpenRatioByMoney_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "OpenRatioByMoney", "F");
				jfieldID OpenRatioByVolume_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "OpenRatioByVolume", "F");
				jfieldID CloseRatioByMoney_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "CloseRatioByMoney", "F");
				jfieldID CloseRatioByVolume_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "CloseRatioByVolume", "F");
				jfieldID CloseTodayRatioByMoney_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "CloseTodayRatioByMoney", "F");
				jfieldID CloseTodayRatioByVolume_fid = jenv->GetFieldID(CTPInstrumentCommissionRate_cls, "CloseTodayRatioByVolume", "F");

				jenv->SetObjectField(CTPInstrumentCommissionRate_obj, InstrumentID_fid, jenv->NewStringUTF(pInstrumentCommissionRate->InstrumentID));
				jenv->SetCharField(CTPInstrumentCommissionRate_obj, InvestorRange_fid, pInstrumentCommissionRate->InvestorRange);
				jenv->SetObjectField(CTPInstrumentCommissionRate_obj, BrokerID_fid, jenv->NewStringUTF(pInstrumentCommissionRate->BrokerID));
				jenv->SetObjectField(CTPInstrumentCommissionRate_obj, InvestorID_fid, jenv->NewStringUTF(pInstrumentCommissionRate->InvestorID));
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, OpenRatioByMoney_fid, pInstrumentCommissionRate->OpenRatioByMoney);
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, OpenRatioByVolume_fid, pInstrumentCommissionRate->OpenRatioByVolume);
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, CloseRatioByMoney_fid, pInstrumentCommissionRate->CloseRatioByMoney);
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, CloseRatioByVolume_fid, pInstrumentCommissionRate->CloseRatioByVolume);
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, CloseTodayRatioByMoney_fid, pInstrumentCommissionRate->CloseTodayRatioByMoney);
				jenv->SetFloatField(CTPInstrumentCommissionRate_obj, CloseTodayRatioByVolume_fid, pInstrumentCommissionRate->CloseTodayRatioByVolume);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQryInstrumentCommissionRate_mid, CTPInstrumentCommissionRate_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}

///请求查询投资者持仓明细响应
void CtpTraderSpi::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspQryInvestorPositionDetail_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jobject CTPInvestorPositionDetail_obj = NULL;
			if (pInvestorPositionDetail) {
				jclass CTPInvestorPositionDetail_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPInvestorPositionDetail;");
				jmethodID CTPInvestorPositionDetail_mid = jenv->GetMethodID(CTPInvestorPositionDetail_cls, "<init>", "()V");
				CTPInvestorPositionDetail_obj = jenv->NewObject(CTPInvestorPositionDetail_cls, CTPInvestorPositionDetail_mid, "");
				jfieldID InstrumentID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "InstrumentID", "Ljava/lang/String;");
				jfieldID BrokerID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "BrokerID", "Ljava/lang/String;");
				jfieldID InvestorID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "InvestorID", "Ljava/lang/String;");
				jfieldID HedgeFlag_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "HedgeFlag", "C");
				jfieldID Direction_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "Direction", "C");
				jfieldID OpenDate_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "OpenDate", "Ljava/lang/String;");
				jfieldID TradeID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "TradeID", "Ljava/lang/String;");
				jfieldID Volume_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "Volume", "I");
				jfieldID OpenPrice_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "OpenPrice", "F");
				jfieldID TradingDay_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "TradingDay", "Ljava/lang/String;");
				jfieldID SettlementID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "SettlementID", "I");
				jfieldID TradeType_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "TradeType", "C");
				jfieldID CombInstrumentID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "CombInstrumentID", "Ljava/lang/String;");
				jfieldID ExchangeID_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "ExchangeID", "Ljava/lang/String;");
				jfieldID CloseProfitByDate_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "CloseProfitByDate", "F");
				jfieldID CloseProfitByTrade_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "CloseProfitByTrade", "F");
				jfieldID PositionProfitByDate_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "PositionProfitByDate", "F");
				jfieldID PositionProfitByTrade_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "PositionProfitByTrade", "F");
				jfieldID Margin_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "Margin", "F");
				jfieldID ExchMargin_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "ExchMargin", "F");
				jfieldID MarginRateByMoney_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "MarginRateByMoney", "F");
				jfieldID MarginRateByVolume_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "MarginRateByVolume", "F");
				jfieldID LastSettlementPrice_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "LastSettlementPrice", "F");
				jfieldID SettlementPrice_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "SettlementPrice", "F");
				jfieldID CloseVolume_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "CloseVolume", "I");
				jfieldID CloseAmount_fid = jenv->GetFieldID(CTPInvestorPositionDetail_cls, "CloseAmount", "F");

				jenv->SetObjectField(CTPInvestorPositionDetail_obj, InstrumentID_fid, jenv->NewStringUTF(pInvestorPositionDetail->InstrumentID));
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, BrokerID_fid, jenv->NewStringUTF(pInvestorPositionDetail->BrokerID));
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, InvestorID_fid, jenv->NewStringUTF(pInvestorPositionDetail->InvestorID));
				jenv->SetCharField(CTPInvestorPositionDetail_obj, HedgeFlag_fid, pInvestorPositionDetail->HedgeFlag);
				jenv->SetCharField(CTPInvestorPositionDetail_obj, Direction_fid, pInvestorPositionDetail->Direction);
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, OpenDate_fid, jenv->NewStringUTF(pInvestorPositionDetail->OpenDate));
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, TradeID_fid, jenv->NewStringUTF(pInvestorPositionDetail->TradeID));
				jenv->SetIntField(CTPInvestorPositionDetail_obj, Volume_fid, pInvestorPositionDetail->Volume);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, OpenPrice_fid, pInvestorPositionDetail->OpenPrice);
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, TradingDay_fid, jenv->NewStringUTF(pInvestorPositionDetail->TradingDay));
				jenv->SetIntField(CTPInvestorPositionDetail_obj, SettlementID_fid, pInvestorPositionDetail->SettlementID);
				jenv->SetCharField(CTPInvestorPositionDetail_obj, TradeType_fid, pInvestorPositionDetail->TradeType);
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, CombInstrumentID_fid, jenv->NewStringUTF(pInvestorPositionDetail->CombInstrumentID));
				jenv->SetObjectField(CTPInvestorPositionDetail_obj, ExchangeID_fid, jenv->NewStringUTF(pInvestorPositionDetail->ExchangeID));
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, CloseProfitByDate_fid, pInvestorPositionDetail->CloseProfitByDate);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, CloseProfitByTrade_fid, pInvestorPositionDetail->CloseProfitByTrade);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, PositionProfitByDate_fid, pInvestorPositionDetail->PositionProfitByDate);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, PositionProfitByTrade_fid, pInvestorPositionDetail->PositionProfitByTrade);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, Margin_fid, pInvestorPositionDetail->Margin);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, ExchMargin_fid, pInvestorPositionDetail->ExchMargin);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, MarginRateByMoney_fid, pInvestorPositionDetail->MarginRateByMoney);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, MarginRateByVolume_fid, pInvestorPositionDetail->MarginRateByVolume);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, LastSettlementPrice_fid, pInvestorPositionDetail->LastSettlementPrice);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, SettlementPrice_fid, pInvestorPositionDetail->SettlementPrice);
				jenv->SetIntField(CTPInvestorPositionDetail_obj, CloseVolume_fid, pInvestorPositionDetail->CloseVolume);
				jenv->SetFloatField(CTPInvestorPositionDetail_obj, CloseAmount_fid, pInvestorPositionDetail->CloseAmount);
			}

			jobject CTPRspInfo_obj = NULL;
			if (pRspInfo) {
				jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
				jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
				CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

				jfieldID ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
				jfieldID ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

				jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
				jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, charTojstring_cn(jenv, pRspInfo->ErrorMsg));
			}

			jenv->CallObjectMethod(jobj, OnRspQryInvestorPositionDetail_mid, CTPInvestorPositionDetail_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


