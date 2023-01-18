#pragma once
class cPathFollower
{
protected:
	GETSET(cPoint2N, m_ptFrom, From);
	GETSET(cPoint2N, m_ptTo, To);
	GETSET(float, m_fTime, Time);
	GETSET(cPathFollower*, m_pNext, Next);

protected:
	float m_fPassedTime;

public:
	cPathFollower(cPoint2N ptFrom, cPoint2N ptTo, float fTime);
	virtual ~cPathFollower();

	void Init(cPoint2N ptFrom, cPoint2N ptTo, float fTime);
	void Start(float fPassedTime = 0.0f);
	cPoint2N Update(cPathFollower** ppThis);
};

