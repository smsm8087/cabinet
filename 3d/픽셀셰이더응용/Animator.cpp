#include "stdafx.h"
#include "Animator.h"


Animator::Animator(vector<AnimationClip>* clips, Type type)
{
	this->type = type;
	curClipNum = 0;
	isPlay = false;
	stopFunc = NULL;

	for (auto clip : *clips)
	{
		AnimationClip c = clip;
		c.time = c.time < 1 ? 100 : c.time;
		this->clips.push_back(c);
	}
}

Animator::~Animator()
{
}

void Animator::Play()
{
	isPlay = true;
	playTime = timeGetTime();
}

void Animator::Pause()
{
	isPlay = false;
}

void Animator::Stop()
{
	isPlay = false;
	curClipNum = 0;

	if (stopFunc != NULL)
		stopFunc();
}

void Animator::Update()
{
	if (!isPlay)
		return;

	AnimationClip clip = clips[curClipNum];

	if (timeGetTime() - playTime > clip.time)
	{
		curClipNum++;

		switch (type)
		{
		case Type::END:
			if (curClipNum >= clips.size())
				Stop();
			break;
		case Type::LOOP:
			curClipNum %= clips.size();
			break;
		default:
			break;
		}
		playTime = timeGetTime();
	}
}

void Animator::Render()
{
	clips[curClipNum].texture->Render();
}
