#pragma once
class XmlTest : public Test
{
private:
	Monster * monster;
public:
	XmlTest();
	~XmlTest();

	void Update();
	void Render();
};

