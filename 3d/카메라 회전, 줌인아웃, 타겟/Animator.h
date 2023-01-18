#pragma once

struct AnimationClip
{
	Texture* texture;
	DWORD time;

	AnimationClip()
	{
		texture = NULL;
		time = 0;
	}
	AnimationClip(Texture* texture, DWORD time)
	{
		this->texture = texture;
		this->time = time;
	}
};
/*
namespace ANISTATE
{
	enum Type
	{
		END,
		LOOP
	};
}*/
enum class Type
{
	END,
	LOOP
};

class Animator
{
private:
	vector<AnimationClip> clips;

	Type type;
	bool isPlay;
	DWORD playTime;
	UINT curClipNum;

	function<void()> stopFunc;
public:
	Animator(vector<AnimationClip>* clips, Type type = Type::END);
	~Animator();

	void Play();
	void Pause();
	void Stop();

	void Update();
	void Render();

	void SetClipInit() { curClipNum = 0; }
	Texture* GetTexture()
	{
		return clips[curClipNum].texture;
	}

	UINT GetCurClipNum() { return curClipNum; }

	void SetStopFunc(function<void()> func) { stopFunc = func; }
};

