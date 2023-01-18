#include "stdafx.h"
#include "Monster.h"


Monster::Monster()
{
	state = IDLE;
	world = new World;
	LoadXml();
	actions[state]->Play();

	world->scale = { 5, 5 };
	world->pos = { 300, 300 };
}


Monster::~Monster()
{
	SAFE_DELETE(world);
	for (auto a : actions)
		SAFE_DELETE(a);
}

void Monster::Update()
{
	if (KEYBOARD->KeyDown(VK_RIGHT) || KEYBOARD->KeyDown(VK_LEFT))
	{
		state = RUN;
		actions[state]->Play();
	}

	if (KEYBOARD->keyPress(VK_RIGHT))
	{
		world->pos.x++;				
	}
	if (KEYBOARD->keyPress(VK_LEFT))
	{
		world->pos.x--;		
	}	

	if (KEYBOARD->KeyUp(VK_RIGHT) || KEYBOARD->KeyUp(VK_LEFT))
	{
		state = IDLE;
		actions[state]->Play();
	}

	if (KEYBOARD->KeyDown(VK_SPACE))
	{
		state = ATTACK;
		actions[state]->Play();
	}

	actions[state]->Update();
	world->Update();
}

void Monster::Render()
{
	world->SetWorld();
	actions[state]->Render();
}

void Monster::LoadXml()
{
	XmlDocument* doc = new XmlDocument;
	doc->LoadFile("image/monster.xml");

	XmlElement* atlas = doc->FirstChildElement("TextureAtlas");
	string path = atlas->Attribute("imagePath");
	path = "image/" + path;

	//string 을 wstring으로 바꾸기
	wstring wPath;
	wPath.assign(path.begin(), path.end());

	XmlElement* action = atlas->FirstChildElement();
	for (; action != NULL; action = action->NextSiblingElement())
	{
		Type type = (Type)action->UnsignedAttribute("type");
		DWORD time = action->UnsignedAttribute("time");

		vector<AnimationClip> clips;
		XmlElement* sprite = action->FirstChildElement();
		for (; sprite != NULL; sprite = sprite->NextSiblingElement())
		{
			D3DXVECTOR2 cutStart;
			D3DXVECTOR2 cutEnd;
			cutStart.x = sprite->FloatAttribute("x");
			cutStart.y = sprite->FloatAttribute("y");
			cutEnd.x = sprite->FloatAttribute("w");
			cutEnd.y = sprite->FloatAttribute("h");
			cutEnd += cutStart;

			Texture* texture = Texture::Add(wPath, cutStart, cutEnd);
			clips.push_back(AnimationClip(texture, time));
		}
		Animator* animator = new Animator(&clips, type);
		actions.push_back(animator);
	}

	delete doc;
}
