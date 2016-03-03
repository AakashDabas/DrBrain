#pragma once

class keys
{
	bool key[255];
	bool l, r, m,inWin,cll,clcr;
	int x, y;
public:
	int cx, cy;
	keys();
	bool keyState(const int a);
	void onKey(const int a);
	void offKey(const int a);
	void lDown();
	void lUp();
	void rDown();
	void rUp();
	void mDown();
	void mUp();
	bool mKeyl();
	bool mKeyr();
	bool mKeym();
	void setxy(int, int);
	int getx();
	int gety();
	void offWin();
	void onWin();
	bool getWin();
	bool getLeftClick();
	void leftClickOn();
	void reset();
};