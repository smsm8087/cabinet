#pragma once
class Timer
{
private:
	LPD3DXFONT font;

	bool isTimerStopped;

	INT64 ticksPerSecond;
	INT64 currentTime;
	INT64 lastTime;
	INT64 lastFPSUpdate;
	INT64 fpsUpdateInterval;

	UINT frameCount;
	float runningTime;
	float timeElapsed;
	float framePerSecond;


	Timer();
	~Timer();
public:
	static Timer* GetInstance()
	{
		static Timer instance;
		return &instance;
	}

	void Update();
	void Render();
	
	void Start();
	void Stop();

	bool IsTimerStopped() { return isTimerStopped; }
	float FramePerSecond() { return framePerSecond; }
	float RunningTime() { return runningTime; }
	float TimerElapsed()
	{
		return isTimerStopped ? 0.0f : timeElapsed;
	}
};

