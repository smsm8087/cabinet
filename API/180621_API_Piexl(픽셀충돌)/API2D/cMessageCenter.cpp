#include "stdafx.h"
#include "cMessageCenter.h"


cMessageCenter::cMessageCenter()
{
}


cMessageCenter::~cMessageCenter()
{
}

void cMessageCenter::AddReceiver(string sMessageType, iMsgRcvr * pReceiver)
{
	m_mapRcvr[sMessageType].insert(pReceiver);
}

void cMessageCenter::RemoveReceiver(string sMessageType, iMsgRcvr * pReceiver)
{
	m_mapRcvr[sMessageType].erase(pReceiver);
}

void cMessageCenter::SendMessageToRcvr(cObject* pSender, string sMessageType, void * pMessage)
{
	for (iMsgRcvr* p : m_mapRcvr[sMessageType])
	{
		p->OnReceiveMessage(pSender, sMessageType, pMessage);
	}
}
