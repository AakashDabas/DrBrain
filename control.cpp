#include"control.h"

keys::keys()
{
	for (int i = 0; i < 255; i++)
		key[i] = false;
	l = r = m =inWin=clcr=cll= false;
}

void keys::onKey(const int a)
{
	key[a] = true;
}

void keys::offKey(const int a)
{
	key[a] = false;
}

bool keys::keyState(const int a)
{
	return key[a];
}

void keys::lDown()
{
	l = true;
}

void keys::lUp()
{
	l = false;
}

void keys::rDown()
{
	r = true;
}

void keys::rUp()
{
	r = false;
}

void keys::mDown()
{
	m = true;
}

void keys::mUp()
{
	m = false;
}

bool keys::mKeyl()
{
	return l;
}

bool keys::mKeyr()
{
	return r;
}

bool keys::mKeym()
{
	return m;
}

void keys::setxy(int a, int b)
{
	x = a;
	y = b;
}

int keys::getx()
{
	return x;
}

int keys::gety()
{
	return y;
}

void keys::offWin()
{
	inWin = false;
}

void keys::onWin()
{
	inWin = true;
}

bool keys::getWin()
{
	return inWin;
}

bool keys::getLeftClick()
{
	bool tmp = cll;
	cll = false;
	return tmp;
}

void keys::leftClickOn()
{
	cll = true;
}

void keys::reset()
{
	for (int i = 0; i < 255; i++)
		key[i] = false;
	l = r = m = inWin = clcr = cll = false;
}