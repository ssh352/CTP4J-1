#pragma once

#include "windows.h"
#include "MdSpi.h"

//#include <iostream>
//#include <fstream> 

#define DOUBLE_MAX 1.7976931348623158e+308

using namespace std;
//std::ofstream file;
double getDouble(double d) {
	if (d == DOUBLE_MAX) {
		return 0;
	}
	else {
		return d;
	}
}

CtpMdSpi::CtpMdSpi(JavaVM *vm, jobject obj) {
	jvm = vm;
	jobj = obj;

	MdSpiMethodSigInit();

	//file.open("1.log", std::iostream::app);
}

CtpMdSpi::~CtpMdSpi() {
	OnFrontConnected_mid = NULL;
	OnFrontDisconnected_mid = NULL;
	OnHeartBeatWarning_mid = NULL;
	OnRspUserLogin_mid = NULL;
	OnRspUserLogout_mid = NULL;
	OnRspError_mid = NULL;
	OnRspSubMarketData_mid = NULL;
	OnRspUnSubMarketData_mid = NULL;
	OnRspSubForQuoteRsp_mid = NULL;
	OnRspUnSubForQuoteRsp_mid = NULL;
	OnRtnDepthMarketData_mid = NULL;
	OnRtnForQuoteRsp_mid = NULL;
}

void CtpMdSpi::MdSpiMethodSigInit() {
	JNIEnv *jenv;
	if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		jclass jcls = jenv->GetObjectClass(jobj);

		OnFrontConnected_mid = jenv->GetMethodID(jcls, "onFrontConnected", "()V");
		OnFrontDisconnected_mid = jenv->GetMethodID(jcls, "onFrontDisconnected", "(I)V");
		OnHeartBeatWarning_mid = jenv->GetMethodID(jcls, "onHeartBeatWarning", "(I)V");
		OnRspUserLogin_mid = jenv->GetMethodID(jcls, "onRspUserLogin", "(Lcn/yiwang/ctp/struct/CTPRspUserLogin;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspUserLogout_mid = jenv->GetMethodID(jcls, "onRspUserLogout", "(Lcn/yiwang/ctp/struct/CTPUserLogout;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspError_mid = jenv->GetMethodID(jcls, "onRspError", "(Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspSubMarketData_mid = jenv->GetMethodID(jcls, "onRspSubMarketData", "(Lcn/yiwang/ctp/struct/CTPSpecificInstrument;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspUnSubMarketData_mid = jenv->GetMethodID(jcls, "onRspUnSubMarketData", "(Lcn/yiwang/ctp/struct/CTPSpecificInstrument;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspSubForQuoteRsp_mid = jenv->GetMethodID(jcls, "onRspSubForQuoteRsp", "(Lcn/yiwang/ctp/struct/CTPSpecificInstrument;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRspUnSubForQuoteRsp_mid = jenv->GetMethodID(jcls, "onRspUnSubForQuoteRsp", "(Lcn/yiwang/ctp/struct/CTPSpecificInstrument;Lcn/yiwang/ctp/struct/CTPRspInfo;IZ)V");
		OnRtnDepthMarketData_mid = jenv->GetMethodID(jcls, "onRtnDepthMarketData", "(Lcn/yiwang/ctp/struct/CTPDepthMarketData;)V");
		OnRtnForQuoteRsp_mid = jenv->GetMethodID(jcls, "onRtnForQuoteRsp", "(Lcn/yiwang/ctp/struct/CTPForQuoteRsp;)V");
	}
	jvm->DetachCurrentThread();
}


///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
void CtpMdSpi::OnFrontConnected() {
	if (OnFrontConnected_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnFrontConnected_mid);
		}
		jvm->DetachCurrentThread();
	}
}


///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
void CtpMdSpi::OnFrontDisconnected(int nReason) {
	if (OnFrontDisconnected_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnFrontDisconnected_mid, nReason);
		}
		jvm->DetachCurrentThread();
	}
}


///心跳超时警告。当长时间未收到报文时，该方法被调用。
void CtpMdSpi::OnHeartBeatWarning(int nTimeLapse) {
	if (OnHeartBeatWarning_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
			jenv->CallObjectMethod(jobj, OnHeartBeatWarning_mid, nTimeLapse);
		}
		jvm->DetachCurrentThread();
	}
}


///登录请求响应
void CtpMdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogin_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		
			jclass CTPRspUserLogin_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspUserLogin;");
			jmethodID CTPRspUserLogin_mid = jenv->GetMethodID(CTPRspUserLogin_cls, "<init>", "()V");
			jobject CTPRspUserLogin_obj = jenv->NewObject(CTPRspUserLogin_cls, CTPRspUserLogin_mid, "");

			jfieldID  TradingDayg_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "TradingDay", "Ljava/lang/String;");
			jfieldID  LoginTime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "LoginTime", "Ljava/lang/String;");
			jfieldID  BrokerID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "BrokerID", "Ljava/lang/String;");
			jfieldID  UserID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "UserID", "Ljava/lang/String;");
			jfieldID  SystemName_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SystemName", "Ljava/lang/String;");
			jfieldID  FrontID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "FrontID", "I");
			jfieldID  SessionID_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SessionID", "I");
			jfieldID  MaxOrderRef_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "MaxOrderRef", "Ljava/lang/String;");
			jfieldID  SHFETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "SHFETime", "Ljava/lang/String;");
			jfieldID  DCETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "DCETime", "Ljava/lang/String;");
			jfieldID  CZCETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "CZCETime", "Ljava/lang/String;");
			jfieldID  FFEXTime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "FFEXTime", "Ljava/lang/String;");
			jfieldID  INETime_fid = jenv->GetFieldID(CTPRspUserLogin_cls, "INETime", "Ljava/lang/String;");

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


			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));

			//file.open("log.log", std::iostream::app);
			//file << "jRequestID:" << nRequestID << std::endl;
			jenv->CallObjectMethod(jobj, OnRspUserLogin_mid, CTPRspUserLogin_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///登出请求响应
void CtpMdSpi::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogout_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
		
			jclass CTPUserLogout_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPUserLogout;");
			jmethodID CTPUserLogout_mid = jenv->GetMethodID(CTPUserLogout_cls, "<init>", "()V");
			jobject CTPUserLogout_obj = jenv->NewObject(CTPUserLogout_cls, CTPUserLogout_mid, "");

			jfieldID  BrokerID_fid = jenv->GetFieldID(CTPUserLogout_cls, "BrokerID", "Ljava/lang/String;");
			jfieldID  UserID_fid = jenv->GetFieldID(CTPUserLogout_cls, "UserID", "Ljava/lang/String;");

			jenv->SetObjectField(CTPUserLogout_obj, BrokerID_fid, jenv->NewStringUTF(pUserLogout->BrokerID));
			jenv->SetObjectField(CTPUserLogout_obj, UserID_fid, jenv->NewStringUTF(pUserLogout->UserID));
			

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));


			jenv->CallObjectMethod(jobj, OnRspUserLogout_mid, CTPUserLogout_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///错误应答
void CtpMdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUserLogout_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");

			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));


			jenv->CallObjectMethod(jobj, OnRspError_mid, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///订阅行情应答
void CtpMdSpi::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspSubMarketData_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {
	
			jclass CTPSpecificInstrument_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSpecificInstrument;");
			jmethodID CTPSpecificInstrument_mid = jenv->GetMethodID(CTPSpecificInstrument_cls, "<init>", "()V");
			jobject CTPSpecificInstrument_obj = jenv->NewObject(CTPSpecificInstrument_cls, CTPSpecificInstrument_mid, "");
			jfieldID  InstrumentID_fid = jenv->GetFieldID(CTPSpecificInstrument_cls, "InstrumentID", "Ljava/lang/String;");
			jenv->SetObjectField(CTPSpecificInstrument_obj, InstrumentID_fid, jenv->NewStringUTF(pSpecificInstrument->InstrumentID));

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");
			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));

		
			jenv->CallObjectMethod(jobj, OnRspSubMarketData_mid, CTPSpecificInstrument_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///取消订阅行情应答
void CtpMdSpi::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUnSubMarketData_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPSpecificInstrument_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSpecificInstrument;");
			jmethodID CTPSpecificInstrument_mid = jenv->GetMethodID(CTPSpecificInstrument_cls, "<init>", "()V");
			jobject CTPSpecificInstrument_obj = jenv->NewObject(CTPSpecificInstrument_cls, CTPSpecificInstrument_mid, "");
			jfieldID  InstrumentID_fid = jenv->GetFieldID(CTPSpecificInstrument_cls, "InstrumentID", "Ljava/lang/String;");
			jenv->SetObjectField(CTPSpecificInstrument_obj, InstrumentID_fid, jenv->NewStringUTF(pSpecificInstrument->InstrumentID));

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");
			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));

		
			jenv->CallObjectMethod(jobj, OnRspUnSubMarketData_mid, CTPSpecificInstrument_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///订阅询价应答
void CtpMdSpi::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspSubForQuoteRsp_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPSpecificInstrument_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSpecificInstrument;");
			jmethodID CTPSpecificInstrument_mid = jenv->GetMethodID(CTPSpecificInstrument_cls, "<init>", "()V");
			jobject CTPSpecificInstrument_obj = jenv->NewObject(CTPSpecificInstrument_cls, CTPSpecificInstrument_mid, "");
			jfieldID  InstrumentID_fid = jenv->GetFieldID(CTPSpecificInstrument_cls, "InstrumentID", "Ljava/lang/String;");
			jenv->SetObjectField(CTPSpecificInstrument_obj, InstrumentID_fid, jenv->NewStringUTF(pSpecificInstrument->InstrumentID));

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");
			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));

		
			jenv->CallObjectMethod(jobj, OnRspSubForQuoteRsp_mid, CTPSpecificInstrument_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///取消订阅询价应答
void CtpMdSpi::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {
	if (OnRspUnSubForQuoteRsp_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPSpecificInstrument_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPSpecificInstrument;");
			jmethodID CTPSpecificInstrument_mid = jenv->GetMethodID(CTPSpecificInstrument_cls, "<init>", "()V");
			jobject CTPSpecificInstrument_obj = jenv->NewObject(CTPSpecificInstrument_cls, CTPSpecificInstrument_mid, "");
			jfieldID  InstrumentID_fid = jenv->GetFieldID(CTPSpecificInstrument_cls, "InstrumentID", "Ljava/lang/String;");
			jenv->SetObjectField(CTPSpecificInstrument_obj, InstrumentID_fid, jenv->NewStringUTF(pSpecificInstrument->InstrumentID));

			jclass CTPRspInfo_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPRspInfo;");
			jmethodID CTPRspInfo_mid = jenv->GetMethodID(CTPRspInfo_cls, "<init>", "()V");
			jobject CTPRspInfo_obj = jenv->NewObject(CTPRspInfo_cls, CTPRspInfo_mid, "");
			jfieldID  ErrorID_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorID", "I");
			jfieldID  ErrorMsg_fid = jenv->GetFieldID(CTPRspInfo_cls, "ErrorMsg", "Ljava/lang/String;");

			jenv->SetIntField(CTPRspInfo_obj, ErrorID_fid, pRspInfo->ErrorID);
			jenv->SetObjectField(CTPRspInfo_obj, ErrorMsg_fid, jenv->NewStringUTF(pRspInfo->ErrorMsg));


			jenv->CallObjectMethod(jobj, OnRspUnSubForQuoteRsp_mid, CTPSpecificInstrument_obj, CTPRspInfo_obj, nRequestID, bIsLast);
		}
		jvm->DetachCurrentThread();
	}
}


///深度行情通知
void CtpMdSpi::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData) {
	if (OnRtnDepthMarketData_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPDepthMarketData_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPDepthMarketData;");
			jmethodID CTPDepthMarketData_mid = jenv->GetMethodID(CTPDepthMarketData_cls, "<init>", "()V");
			jobject CTPDepthMarketData_obj = jenv->NewObject(CTPDepthMarketData_cls, CTPDepthMarketData_mid, "");
			jfieldID TradingDay_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "TradingDay", "Ljava/lang/String;");
			jfieldID InstrumentID_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "InstrumentID", "Ljava/lang/String;");
			jfieldID ExchangeID_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "ExchangeID", "Ljava/lang/String;");
			jfieldID ExchangeInstID_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "ExchangeInstID", "Ljava/lang/String;");
			jfieldID LastPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "LastPrice", "F");
			jfieldID PreSettlementPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "PreSettlementPrice", "F");
			jfieldID PreClosePrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "PreClosePrice", "F");
			jfieldID PreOpenInterest_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "PreOpenInterest", "F");
			jfieldID OpenPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "OpenPrice", "F");
			jfieldID HighestPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "HighestPrice", "F");
			jfieldID LowestPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "LowestPrice", "F");
			jfieldID Volume_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "Volume", "I");
			jfieldID Turnover_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "Turnover", "F");
			jfieldID OpenInterest_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "OpenInterest", "F");
			jfieldID ClosePrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "ClosePrice", "F");
			jfieldID SettlementPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "SettlementPrice", "F");
			jfieldID UpperLimitPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "UpperLimitPrice", "F");
			jfieldID LowerLimitPrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "LowerLimitPrice", "F");
			jfieldID PreDelta_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "PreDelta", "F");
			jfieldID CurrDelta_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "CurrDelta", "F");
			jfieldID UpdateTime_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "UpdateTime", "Ljava/lang/String;");
			jfieldID UpdateMillisec_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "UpdateMillisec", "I");
			jfieldID BidPrice1_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidPrice1", "F");
			jfieldID BidVolume1_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidVolume1", "I");
			jfieldID AskPrice1_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskPrice1", "F");
			jfieldID AskVolume1_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskVolume1", "I");
			jfieldID BidPrice2_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidPrice2", "F");
			jfieldID BidVolume2_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidVolume2", "I");
			jfieldID AskPrice2_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskPrice2", "F");
			jfieldID AskVolume2_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskVolume2", "I");
			jfieldID BidPrice3_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidPrice3", "F");
			jfieldID BidVolume3_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidVolume3", "I");
			jfieldID AskPrice3_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskPrice3", "F");
			jfieldID AskVolume3_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskVolume3", "I");
			jfieldID BidPrice4_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidPrice4", "F");
			jfieldID BidVolume4_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidVolume4", "I");
			jfieldID AskPrice4_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskPrice4", "F");
			jfieldID AskVolume4_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskVolume4", "I");
			jfieldID BidPrice5_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidPrice5", "F");
			jfieldID BidVolume5_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "BidVolume5", "I");
			jfieldID AskPrice5_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskPrice5", "F");
			jfieldID AskVolume5_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AskVolume5", "I");
			jfieldID AveragePrice_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "AveragePrice", "F");
			jfieldID ActionDay_fid = jenv->GetFieldID(CTPDepthMarketData_cls, "ActionDay", "Ljava/lang/String;");

			jenv->SetObjectField(CTPDepthMarketData_obj, TradingDay_fid, jenv->NewStringUTF(pDepthMarketData->TradingDay));
			jenv->SetObjectField(CTPDepthMarketData_obj, InstrumentID_fid, jenv->NewStringUTF(pDepthMarketData->InstrumentID));
			jenv->SetObjectField(CTPDepthMarketData_obj, ExchangeID_fid, jenv->NewStringUTF(pDepthMarketData->ExchangeID));
			jenv->SetObjectField(CTPDepthMarketData_obj, ExchangeInstID_fid, jenv->NewStringUTF(pDepthMarketData->ExchangeInstID));
			jenv->SetFloatField(CTPDepthMarketData_obj, LastPrice_fid, getDouble(pDepthMarketData->LastPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, PreSettlementPrice_fid, getDouble(pDepthMarketData->PreSettlementPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, PreClosePrice_fid, getDouble(pDepthMarketData->PreClosePrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, PreOpenInterest_fid, getDouble(pDepthMarketData->PreOpenInterest));
			jenv->SetFloatField(CTPDepthMarketData_obj, OpenPrice_fid, getDouble(pDepthMarketData->OpenPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, HighestPrice_fid, getDouble(pDepthMarketData->HighestPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, LowestPrice_fid, getDouble(pDepthMarketData->LowestPrice));
			jenv->SetIntField(CTPDepthMarketData_obj, Volume_fid, pDepthMarketData->Volume);
			jenv->SetFloatField(CTPDepthMarketData_obj, Turnover_fid, getDouble(pDepthMarketData->Turnover));
			jenv->SetFloatField(CTPDepthMarketData_obj, OpenInterest_fid, getDouble(pDepthMarketData->OpenInterest));
			jenv->SetFloatField(CTPDepthMarketData_obj, ClosePrice_fid, getDouble(pDepthMarketData->ClosePrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, SettlementPrice_fid, getDouble(pDepthMarketData->SettlementPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, UpperLimitPrice_fid, getDouble(pDepthMarketData->UpperLimitPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, LowerLimitPrice_fid, getDouble(pDepthMarketData->LowerLimitPrice));
			jenv->SetFloatField(CTPDepthMarketData_obj, PreDelta_fid, getDouble(pDepthMarketData->PreDelta));
			jenv->SetFloatField(CTPDepthMarketData_obj, CurrDelta_fid, getDouble(pDepthMarketData->CurrDelta));
			jenv->SetObjectField(CTPDepthMarketData_obj, UpdateTime_fid, jenv->NewStringUTF(pDepthMarketData->UpdateTime));
			jenv->SetIntField(CTPDepthMarketData_obj, UpdateMillisec_fid, pDepthMarketData->UpdateMillisec);
			jenv->SetFloatField(CTPDepthMarketData_obj, BidPrice1_fid, getDouble(pDepthMarketData->BidPrice1));
			jenv->SetIntField(CTPDepthMarketData_obj, BidVolume1_fid, pDepthMarketData->BidVolume1);
			jenv->SetFloatField(CTPDepthMarketData_obj, AskPrice1_fid, getDouble(pDepthMarketData->AskPrice1));
			jenv->SetIntField(CTPDepthMarketData_obj, AskVolume1_fid, pDepthMarketData->AskVolume1);
			jenv->SetFloatField(CTPDepthMarketData_obj, BidPrice2_fid, getDouble(pDepthMarketData->BidPrice2));
			jenv->SetIntField(CTPDepthMarketData_obj, BidVolume2_fid, pDepthMarketData->BidVolume2);
			jenv->SetFloatField(CTPDepthMarketData_obj, AskPrice2_fid, getDouble(pDepthMarketData->AskPrice2));
			jenv->SetIntField(CTPDepthMarketData_obj, AskVolume2_fid, pDepthMarketData->AskVolume2);
			jenv->SetFloatField(CTPDepthMarketData_obj, BidPrice3_fid, getDouble(pDepthMarketData->BidPrice3));
			jenv->SetIntField(CTPDepthMarketData_obj, BidVolume3_fid, pDepthMarketData->BidVolume3);
			jenv->SetFloatField(CTPDepthMarketData_obj, AskPrice3_fid, getDouble(pDepthMarketData->AskPrice3));
			jenv->SetIntField(CTPDepthMarketData_obj, AskVolume3_fid, pDepthMarketData->AskVolume3);
			jenv->SetFloatField(CTPDepthMarketData_obj, BidPrice4_fid, getDouble(pDepthMarketData->BidPrice4));
			jenv->SetIntField(CTPDepthMarketData_obj, BidVolume4_fid, pDepthMarketData->BidVolume4);
			jenv->SetFloatField(CTPDepthMarketData_obj, AskPrice4_fid, getDouble(pDepthMarketData->AskPrice4));
			jenv->SetIntField(CTPDepthMarketData_obj, AskVolume4_fid, pDepthMarketData->AskVolume4);
			jenv->SetFloatField(CTPDepthMarketData_obj, BidPrice5_fid, getDouble(pDepthMarketData->BidPrice5));
			jenv->SetIntField(CTPDepthMarketData_obj, BidVolume5_fid, pDepthMarketData->BidVolume5);
			jenv->SetFloatField(CTPDepthMarketData_obj, AskPrice5_fid, getDouble(pDepthMarketData->AskPrice5));
			jenv->SetIntField(CTPDepthMarketData_obj, AskVolume5_fid, pDepthMarketData->AskVolume5);
			jenv->SetFloatField(CTPDepthMarketData_obj, AveragePrice_fid, getDouble(pDepthMarketData->AveragePrice));
			jenv->SetObjectField(CTPDepthMarketData_obj, ActionDay_fid, jenv->NewStringUTF(pDepthMarketData->ActionDay));

			jenv->CallObjectMethod(jobj, OnRtnDepthMarketData_mid, CTPDepthMarketData_obj); 
		}
		jvm->DetachCurrentThread();
	}
}


///询价通知
void CtpMdSpi::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {
	if (OnRtnForQuoteRsp_mid != NULL) {
		JNIEnv *jenv;
		if (jvm->AttachCurrentThread((void **)&jenv, NULL) == JNI_OK) {

			jclass CTPForQuoteRsp_cls = jenv->FindClass("Lcn/yiwang/ctp/struct/CTPForQuoteRsp;");
			jmethodID CTPForQuoteRsp_mid = jenv->GetMethodID(CTPForQuoteRsp_cls, "<init>", "()V");
			jobject CTPForQuoteRsp_obj = jenv->NewObject(CTPForQuoteRsp_cls, CTPForQuoteRsp_mid, "");
			jfieldID TradingDay_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "TradingDay", "Ljava/lang/String;");
			jfieldID InstrumentID_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "InstrumentID", "Ljava/lang/String;");
			jfieldID ForQuoteSysID_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "ForQuoteSysID", "Ljava/lang/String;");
			jfieldID ForQuoteTime_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "ForQuoteTime", "Ljava/lang/String;");
			jfieldID ActionDay_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "ActionDay", "Ljava/lang/String;");
			jfieldID ExchangeID_fid = jenv->GetFieldID(CTPForQuoteRsp_cls, "ExchangeID", "Ljava/lang/String;");

			jenv->SetObjectField(CTPForQuoteRsp_obj, TradingDay_fid, jenv->NewStringUTF(pForQuoteRsp->TradingDay));
			jenv->SetObjectField(CTPForQuoteRsp_obj, InstrumentID_fid, jenv->NewStringUTF(pForQuoteRsp->InstrumentID));
			jenv->SetObjectField(CTPForQuoteRsp_obj, ForQuoteSysID_fid, jenv->NewStringUTF(pForQuoteRsp->ForQuoteSysID));
			jenv->SetObjectField(CTPForQuoteRsp_obj, ForQuoteTime_fid, jenv->NewStringUTF(pForQuoteRsp->ForQuoteTime));
			jenv->SetObjectField(CTPForQuoteRsp_obj, ActionDay_fid, jenv->NewStringUTF(pForQuoteRsp->ActionDay));
			jenv->SetObjectField(CTPForQuoteRsp_obj, ExchangeID_fid, jenv->NewStringUTF(pForQuoteRsp->ExchangeID));

			jenv->CallObjectMethod(jobj, OnRtnForQuoteRsp_mid, CTPForQuoteRsp_obj);
		}
		jvm->DetachCurrentThread();
	}
}

