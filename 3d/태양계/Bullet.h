#pragma once
class Bullet
{
private:
	Texture * texture;

	float	  bulletRotZ;
public:
	Bullet(float _Rotz);
	~Bullet();
	World*	  world;

	void Update();
	void Render();
};

