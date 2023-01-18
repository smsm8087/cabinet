#include "stdafx.h"
#include "XmlTest.h"


XmlTest::XmlTest()
{
	monster = new Monster;
}


XmlTest::~XmlTest()
{
	delete monster;
}

void XmlTest::Update()
{
	monster->Update();
}

void XmlTest::Render()
{
	monster->Render();
}
