#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
	isTimerStopped = true;
	ticksPerSecond = 0;
	currentTime = 0;
	lastTime = 0;
	lastFPSUpdate = 0;
	frameCount = 0;
	runningTime = 0;
	timeElapsed = 0;
	framePerSecond = 0;
	font = NULL;
	//초당 진동수를 반환하는 함수
	QueryPerformanceFrequency((LARGE_INTEGER*)&ticksPerSecond);
	fpsUpdateInterval = ticksPerSecond >> 1;
}


Timer::~Timer()
{
}

void Timer::Update()
{
	if (isTimerStopped)
		return;

	//현재 진동수를 반환하는 함수
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeElapsed = (float)(currentTime - lastTime)
		/ (float)ticksPerSecond;
	runningTime += timeElapsed;

	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime /
			(float)ticksPerSecond;
		float tempLastTime = (float)lastFPSUpdate /
			(float)ticksPerSecond;
		framePerSecond = (float)frameCount /
			(tempCurrentTime - tempLastTime);

		lastFPSUpdate = currentTime;
		frameCount = 0;
	}
	
	lastTime = currentTime;
}

void Timer::Render()
{
	if (font == NULL)
	{
		D3DXFONT_DESC desc = {};
		desc.Width = 20;
		desc.Height = 20;
		desc.CharSet = HANGUL_CHARSET;
		wstring str = L"궁서체";
		wcscpy_s(desc.FaceName, str.c_str());

		D3DXCreateFontIndirect(DEVICE,
			&desc, &font);
	}

	wstring str = to_wstring((int)framePerSecond);

	RECT rect = { 0, 5, 100, 25 };

	font->DrawText(NULL, str.c_str(), -1,
		&rect, DT_LEFT, 0xffff0000);
}

void Timer::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;
}

void Timer::Stop()
{
	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (float)(stopTime - lastTime)
		/ (float)ticksPerSecond;
	isTimerStopped;
}
