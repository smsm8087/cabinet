#pragma once
class Player 
{
private:
	Texture * playerTexture;

	
	D3DXVECTOR2 playerPivot;
public:
	Player();
	~Player();
	World*	 world;
	void Update();
	void Render();
	D3DXVECTOR2 GetPivot() { return playerPivot; }
};

