#pragma once

class cMiner;

class iMinerState
{
public:
	iMinerState();
	~iMinerState();

	virtual void Init(cMiner* pMiner) = 0;
	virtual void Update(cMiner* pMiner) = 0;
	virtual void Finish(cMiner* pMiner) = 0;
};

class cMoveState : public iMinerState
{
public:
	SINGLETON(cMoveState);

	virtual void Init(cMiner* pMiner) override;
	virtual void Update(cMiner* pMiner) override;
	virtual void Finish(cMiner* pMiner) override;
};

class cSleepState : public iMinerState
{
public:
	SINGLETON(cSleepState);

	virtual void Init(cMiner* pMiner) override;
	virtual void Update(cMiner* pMiner) override;
	virtual void Finish(cMiner* pMiner) override;
};

class cDrinkState : public iMinerState
{
public:
	SINGLETON(cDrinkState);

	virtual void Init(cMiner* pMiner) override;
	virtual void Update(cMiner* pMiner) override;
	virtual void Finish(cMiner* pMiner) override;
};

class cMineState : public iMinerState
{
public:
	SINGLETON(cMineState);

	virtual void Init(cMiner* pMiner) override;
	virtual void Update(cMiner* pMiner) override;
	virtual void Finish(cMiner* pMiner) override;
};

class cBankState : public iMinerState
{
public:
	SINGLETON(cBankState);

	virtual void Init(cMiner* pMiner) override;
	virtual void Update(cMiner* pMiner) override;
	virtual void Finish(cMiner* pMiner) override;
};