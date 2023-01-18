#pragma once

class iMsgRcvr
{
public:
	virtual void OnReceiveMessage(cObject* pSender, string sMessageType, void* pMessage = NULL) = 0;
};


#define g_pMessageCenter cMessageCenter::GetInstance()

class cMessageCenter
{
private:
	map<string, set<iMsgRcvr*>> m_mapRcvr;

public:
	SINGLETON(cMessageCenter);

public:
	void AddReceiver(string sMessageType, iMsgRcvr* pReceiver);
	void RemoveReceiver(string sMessageType, iMsgRcvr* pReceiver);
	void SendMessageToRcvr(cObject* pSender, string sMessageType, void* pMessage = NULL);
};

