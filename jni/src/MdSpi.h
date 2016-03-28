#pragma once

#include "jni.h"
#include "ThostFtdcMdApi.h"

using namespace std;

class CtpMdSpi : public CThostFtdcMdSpi
{
public:
	CtpMdSpi(JavaVM *jvm, jobject jobj);
	~CtpMdSpi();

	///���ͻ����뽻�׺�̨������ͨ������ʱ����δ��¼ǰ�����÷��������á�
	virtual void OnFrontConnected();
	///���ͻ����뽻�׺�̨ͨ�����ӶϿ�ʱ���÷��������á���������������API���Զ��������ӣ��ͻ��˿ɲ�������
	virtual void OnFrontDisconnected(int nReason);
	///������ʱ���档����ʱ��δ�յ�����ʱ���÷��������á�
	virtual void OnHeartBeatWarning(int nTimeLapse);

	///��¼������Ӧ
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�ǳ�������Ӧ
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///����Ӧ��
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///��������Ӧ��
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///ȡ����������Ӧ��
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///����ѯ��Ӧ��
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///ȡ������ѯ��Ӧ��
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	///�������֪ͨ
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);
	///ѯ��֪ͨ
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp);

private:
	CThostFtdcMdApi* pMdApi;

	JavaVM *jvm;
	jobject jobj;

	jmethodID OnFrontConnected_mid;
	jmethodID OnFrontDisconnected_mid;
	jmethodID OnHeartBeatWarning_mid;
	jmethodID OnRspUserLogin_mid;
	jmethodID OnRspUserLogout_mid;
	jmethodID OnRspError_mid;
	jmethodID OnRspSubMarketData_mid;
	jmethodID OnRspUnSubMarketData_mid;
	jmethodID OnRspSubForQuoteRsp_mid;
	jmethodID OnRspUnSubForQuoteRsp_mid;
	jmethodID OnRtnDepthMarketData_mid;
	jmethodID OnRtnForQuoteRsp_mid;

	void MdSpiMethodSigInit();
};