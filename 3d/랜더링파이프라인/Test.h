
class Test
{
protected:
	D3DXVECTOR2 worldPos;
	float		Angle;
	bool		isActive;
public:
	virtual void Update() = 0;
	virtual void Render() = 0;
	virtual void SetAngle(float _Angle) { Angle = _Angle; }
	virtual float GetAngle() { return Angle; }
	virtual void SetActive(bool _isActive) { isActive = _isActive; }
	virtual bool GetActive() { return isActive; }

	virtual D3DXVECTOR2 GetWorldPos() { return worldPos; }
	virtual void SetWorldPos(D3DXVECTOR2 _worldPos) { worldPos = _worldPos; }
};