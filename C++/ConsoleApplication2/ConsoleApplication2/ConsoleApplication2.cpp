// ConsoleApplication2.cpp: 콘솔 응용 프로그램의 진입점을 정의합니다.
//

#include "stdafx.h"

void Write()
{
	XmlDocument* document = new XmlDocument;
	XmlElement* player = document->NewElement("Player");
	player->SetAttribute("filePath", "image/player.png");
	document->InsertFirstChild(player);

	XmlElement* state = document->NewElement("State");
	state->SetAttribute("HP", 500);
	state->SetAttribute("ATTACK", 200);
	player->InsertFirstChild(state);

	XmlElement* action = document->NewElement("Action");
	action->SetAttribute("Type", "loop");
	player->InsertEndChild(action);

	XmlElement* frame = document->NewElement("Frame");
	frame->SetAttribute("x", 10);
	frame->SetAttribute("y", 10);
	frame->SetAttribute("z", 10);

	action->InsertEndChild(frame);


	document->SaveFile("test.xml");

	delete document;
}
void Read()
{
	XmlDocument* document = new XmlDocument;
	document->LoadFile("test.xml");

	XmlElement* player = document->FirstChildElement();
	cout << "FilePath : " << player->Attribute("filePath") << endl;

	XmlElement* state = player->FirstChildElement();
	cout << "HP : " << state->IntAttribute("HP") << endl;
	cout << "ATK : " << state->IntAttribute("ATTACK") << endl;


	XmlElement* action = player->FirstChildElement("Action");
	cout << "Type : " << action->Attribute("Type") << endl;


}
int main()
{
	//Write();

	Read();
    return 0;
}

