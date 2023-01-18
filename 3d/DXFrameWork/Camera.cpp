#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
	mPos = { 0,0 };
	mfSpeed =5.0f;
}


Camera::~Camera()
{
}

void Camera::Update()
{
	if (KEYBOARD->keyPress('A'))
		mPos.x += mfSpeed;
	else if (KEYBOARD->keyPress('D'))
		mPos.x -= mfSpeed;
	if (KEYBOARD->keyPress('S'))
		mPos.y -= mfSpeed;
	else if (KEYBOARD->keyPress('W'))
		mPos.y += mfSpeed;
}
