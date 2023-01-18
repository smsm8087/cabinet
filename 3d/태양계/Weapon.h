#pragma once
class Bullet;
class Weapon
{
private:
	float	weaponRotZ;
	Texture* weaponTexture;
	vector<Bullet*> bullets;
public:
	Weapon(D3DXVECTOR2 _pivot);
	~Weapon();
	World*	 world;

	void Update();
	void Render();
};

