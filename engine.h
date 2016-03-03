#pragma once
#include "graphics.h"
#include"control.h"
#include"timer.h"
#include"sound.h"

class engine
{
public:
	int xlen, ylen;
	engine(HWND hWnd,keys *state,int,int,float,float);
	gfx gfxObject;
	unsigned char PutPixel(int x, int y, int r, int g, int b, float trans = 1,int sColor=0);
	bool launch();
	void mainCharacter();
	keys *lState;
	int key(int x);
	class pixel
	{
	public:
		pixel()
		{
			next=NULL;
			trans=255;
		}
		int x, y;
		unsigned char r, g, b,trans;
		pixel *next;
	};
	void bmpLoad(pixel*, char*x, int mask);
	void pngLoad(pixel*, wchar_t*x);
	void bmpDisplay(pixel *, int x, int y, float size = 1, float trans = 1, unsigned char sColor = 0, char* detect = NULL,float angle = 0, int ox = 0, int oy = 0);
	class image
	{
	public:
		image()
		{
			arrPix=NULL;
			next=NULL;
		}
		pixel* arrPix;
		float size;
		image* next;
	};
	class imgs
	{
	public:
		imgs()
		{
			arrImg=NULL;
			next=NULL;
			imageCode=-1;
		}
		image* arrImg;
		int imageCode;
		imgs* next;
	};
	imgs* loadedImg;
	void iLoad(char* fileName, int imageCode, int trans, char* size); //imageLoad
	void imageConv(pixel* fin, pixel* old, float size);
	void display(int imageCode, int x, int y, int size = 1, int trans = 100,unsigned char sColor=0,char* detect=NULL,float angle=0,int ox=0,int oy=0);
	float rotateX(int x, int y,float angle);
	float rotateY(int x,int y, float angle);
	pixel* a;
	bool tkey;
	struct character
	{
		char ch;
		char x[100];
		char y[100];
	}charr[52];
	void outText(char*,int,int,int,int,int,float);
	void centralControl();

	class turrent
	{
	public:
		turrent()
		{
			no=0;
			dir = 1;i=0;i2=0;
			exist=true;
			ani=false;
			next=NULL;
		}
		int no;
		int x, y, dir,i,i2,delay;
		float speed;
		bool exist,ani;
		turrent* next;
		timer ti;
	};
	class eBeamNode
	{
	public:
		eBeamNode()
		{
			dis=0;
			type=1;
			des=0;
			next=NULL;
		}
		float x, y;
		float speed;
		char dis;
		int type,des;
		eBeamNode* next ;
	};
	class hBeamNode
	{
	public:
		hBeamNode()
		{
			dis=0;
			type=1;
			no=0;
			des=0;
			anim=false;
			next=NULL;
		}
		float x, y;
		float speed;
		char dis;
		int type,no,des;
		bool anim;
		hBeamNode* next;
	};
	class eLaserNode
	{
	public:
		eLaserNode()
		{
			trans=20;
			rate=true;
			next=NULL;
			sndPlay = false;
		}
		int x1, x2, y, onTime, offTime,dir;
		float trans;
		bool rate,sndPlay;
		timer on, off,r,r2;
		eLaserNode* next;
	};
	
	
	void newTurrent(int noTurrent, int x, int y, int del=1000,float speed=1,int dir = 1);
	void compileTurrent();

	void newEBeam(int x, int y, float speed,int type=1);
	void compileEBEAM(bool);

	void newHBeam(int no,int x, int y, float speed);
	void compileHBeam(bool);

	void newELaser(int x1, int x2, int y, int onTime, int offTime,int dir=0);
	void compileELaser();

	//Main enemies
	class mineNode
	{
	public:
		mineNode()
		{
			no=0;
			dir=1;
			rot=0;
			health=16;
			exist=true;
			ani=false;
			mov=false;
			set=false;
			des=false;
			next=NULL;
		}
		int no;
		int x, y,dir,rot,health;
		float speed;
		bool exist, ani,mov,set,des;
		mineNode* next;
	}*mine;

	void newMine(int no,int x,int y,float speed=1);
	void compileMine(bool);

	class midNode
	{
	public:
		midNode()
		{
			no=0;
			dir=1;
			health=8;
			exist=true;
			set=false;
			fire=false;
			ani=true;
			next=NULL;
		}
		int no;
		int x, y, dir,health;
		bool exist,set,fire,ani;
		float speed;
		midNode* next;
	}*mid;

	void newMid(int no, int x, int y, float speed);
	void compileMid(bool com=true);

	class heavyNode
	{
	public:
		heavyNode()
		{
			no=0;
			dir=1;
			health=14;
			del=500;
			exist=true;
			set=false;
			fire=false;
			mov=true;
			ani=true;
			sn=true;
			next=NULL;
		}
		int no, x, y, dir, health, del;
		bool exist, set,fire,mov,ani,sn;
		float speed;
		timer t;
		heavyNode* next;
	}*heavy;

	void newHeavy(int no, int x, int y, int del, float speed);
	void compileHeavy(bool comp = true);
	//Animation Stuff Starts Here
	class aniImage
	{
	public:
		aniImage()
		{
			arrPix=NULL;
			next=NULL;
		}
		pixel* arrPix;
		aniImage* next;
	};

	class frameNo
		{
		public:
			frameNo()
			{
				imgTmp=NULL;
			}
			aniImage* imgTmp;
		};
	class anis
	{
	public:
		anis()
		{
			arrImg=NULL;
			next=NULL;
		}
		aniImage* arrImg;
		int aniCode;
		frameNo imgTmp[100];
		timer t[100];
		anis* next;
	};
	anis* aniPtr;
	void aniLoad(char* fileName,int aniCode,unsigned int noFrames,int trans,int size=100);
	int animate(int aniCode, unsigned char no, unsigned int tDelay, int, int, float, int dir = 1, unsigned char sColor = 0, char* detect = NULL);

	cSound snd;//Object to sound class
	turrent* turr;
	eBeamNode* eBeam;
	hBeamNode* hBeam;
	eLaserNode* eLaser;
	//Variables for runtime
	bool lclick;
	int angle, dir;
	float chX, chY,speedF;
	//float i = 0;
	void disHud();
	//Used for detection and collision
	char* detect;
	char* detectBody;
	char* detectVert;
	bool falling ,relexing,jumpOff,fly,armDis,boostIncrease,stopMoveSound,startMoveSound,heroCanFire,heroFire;
	int fY_T,armFixY,armFixX,fireType;
	float count, jumpSpeed, flySine, speedUp, speedDown , i ; 
	timer tHero,typeCng;
	bool motaGola,duck,duckP,duckU;
	int health ,healthTmp;//Hero's health
	double score ;//To store score of the player
	timer tDes;//To control health minus rate for hero
	timer tH;//To control the health minus rate
	void intDes(int no,int x,int y);

	int butPos[12];
	int button(int *a);
	void reset();
	void pauseTimer();
	void resumeTimer();
	int paused();
	int restart();
	int recordedAns(int answer);
	int paus; timer tPaus;
	int menu(); int disMenu ;
	void intitLevel(); 
	int level,oldScore ; 
	timer leftT;
	bool playG,firstQ,rQ,dem=false,howTo=false,credit=false;
	int timeLeft, answer, corAns, cntrlF = 5, laserDam = 10;
	timer creTimer;
	int creTran=0,creTran2=0,creY=500;
	bool creAccess = false,creAccess2=false,creAccess3=false,creAccess4=false;
	timer tSit;
	bool levelS = false,tutorial=false;
	timer tdel,tDel2;
};