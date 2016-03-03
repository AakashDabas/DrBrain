#define _CRT_SECURE_NO_DEPRECATE
#include<assert.h>
#include"engine.h"
#include<stdio.h>
#include<math.h>
#include<stdio.h>
#include<time.h>
#include<fstream>
#include<Gdiplus.h>
#pragma comment(lib,"gdiplus.lib")
using namespace Gdiplus;
timer tUni;
engine::engine(HWND hWnd, keys *state, int xlen, int ylen,float sizeX,float sizeY)	
	:
	gfxObject(hWnd,xlen,ylen,sizeX,sizeY)
{
	tUni.start();
	loadedImg = new imgs;
	a = new pixel;
	tkey = false;
	mine=NULL;
	mid=NULL;
	heavy=NULL;
	aniPtr=new anis;
	turr=NULL;
	eBeam=NULL;
	hBeam=NULL;
	eLaser=NULL;
	lclick = false;
	angle = 0;
	dir = 1;
	chX = 600;
	chY = 300;
	speedF=2;
	detect = new char[256];
	detectBody = new char[256];
	detectVert = new char[256];
	falling = false;
	relexing=false;
	jumpOff=false;
	fly=false;
	armDis=true;
	boostIncrease=false;
	stopMoveSound=false;
	startMoveSound=false;
	heroCanFire=true;
	heroFire=false;
	fY_T = 0;
	armFixY=0;
	armFixX=0;
	fireType=2;
	count = 0; 
	jumpSpeed = 1; 
	flySine = 0;
	speedUp = 1; 
	speedDown = 3; i = 0;
	motaGola = false;
	duck=false;
	duckP=false;
	duckU=false;
	health = 100;//Hero's health
	healthTmp=100;
	score = 0;//To store score of the player
	paus=0;
	disMenu = 0;
	oldScore = 0;
	playG = false;
	firstQ=true;
	rQ=false;
	timeLeft = 100;
	answer=0;
	//New initailizations
	this->xlen = xlen;
	this->ylen = ylen;
	lState = state;
	butPos[0] = butPos[1] = 100;
	butPos[2] = butPos[3] = 200;
	butPos[4] = butPos[5] = 300;
	butPos[6] = butPos[7] = 400;
	tdel.start();

	iLoad("Rendered//Loading.png", 53, 20,"100");
	iLoad("Rendered//Back.png", 56, 1, "100");
	iLoad("Rendered//Logo.png", 57, 1, "100");
	gfxObject.BeginFrame(1); 
	display(56, 0, 0);
	display(53, 100, 100); 
	gfxObject.EndFrame();
	level = 15;
	iLoad("Rendered//Gun.png", 1, 250, "100");
	iLoad("Rendered//Body.bmp", 2, 250, "100");//Done
	iLoad("Rendered//Verticle.bmp", 3, 250, "100");//Done
	iLoad("Rendered//TurrentBeam1.jpg",4,250,"100");
	iLoad("Rendered//Turrent1Det.bmp", 5, 250, "100");
	iLoad("Rendered//Turrent1//Turrent10001.png", 6, 250, "100");
	iLoad("Rendered//Turrent1Destroy//Turrent1Destroy0030.png", 7, 250, "100");
	iLoad("Rendered//heroBullet1.png", 8, 250, "100");
	iLoad("Rendered//LaserMach.png", 9, 250, "100");
	iLoad("Rendered//MineDetect.bmp", 10, 250, "100");
	iLoad("Rendered//LaserMachR.png", 11, 250, "100");
	iLoad("Rendered//LaserMachR2.png", 12, 250, "100");
	iLoad("Rendered//RoboDuckD.png", 13, 250, "100");
	iLoad("Rendered//HeavyFireBullet.png", 14, 250, "100");
	iLoad("Rendered//MidFireBullet.bmp", 15, 250, "100");
	iLoad("Rendered//MineC//MineC0001.png", 16, 250, "100");
	iLoad("Rendered//MidDes//MidDes0035.png", 17, 1, "100");
	iLoad("Rendered//HeavyMove//HeavyMove0001.png", 18, 1, "100");
	iLoad("Rendered//HeavyDes//HeavyDes0040.png", 19, 1, "100");
	//Nums loaded here
	iLoad("Rendered//Nums//No0001.png", 20, 1, "100");
	iLoad("Rendered//Nums//No0002.png", 21, 1, "100");
	iLoad("Rendered//Nums//No0003.png", 22, 1, "100");
	iLoad("Rendered//Nums//No0004.png", 23, 1, "100");
	iLoad("Rendered//Nums//No0005.png", 24, 1, "100");
	iLoad("Rendered//Nums//No0006.png", 25, 1, "100");
	iLoad("Rendered//Nums//No0007.png", 26, 1, "100");
	iLoad("Rendered//Nums//No0008.png", 27, 1, "100");
	iLoad("Rendered//Nums//No0009.png", 28, 1, "100");
	iLoad("Rendered//Nums//No0010.png", 29, 1, "100");
	iLoad("Rendered//Nums//d.png", 30, 1, "100");
	iLoad("Rendered//Hud.png", 31, 1, "100");
	iLoad("Rendered//HudH.png", 32, 1, "100");
	iLoad("Rendered//Options//1.png", 33, 1, "100");
	iLoad("Rendered//Options//2.png", 34, 1, "100");
	iLoad("Rendered//Options//3.png", 35, 1, "100");
	iLoad("Rendered//Options//4.png", 36, 1, "100");
	iLoad("Rendered//ThisAnswer.png", 37, 1, "100");
	iLoad("Rendered//Buttons//ButtonsP.png", 38, 1, "100");
	iLoad("Rendered//Buttons//ButtonsH.png", 39, 1, "100");
	iLoad("Rendered//Buttons//ButtonsC.png", 40, 1, "100"); 
	iLoad("Rendered//Buttons//ButtonsE.png", 41, 1, "100");
	iLoad("Rendered//Buttons//ButtonsSh.png", 43, 1, "100");
	iLoad("Rendered//cursor.png", 44, 250, "100");
	iLoad("Rendered//Buttons//ButtonsR.png", 45, 1, "100");
	iLoad("Rendered//Buttons//ButtonsRe.png", 46, 1, "100");
	iLoad("Rendered//Buttons//ButtonsE.png", 47, 1, "100");
	iLoad("Rendered//Buttons//ButtonsM.png", 48, 1, "100");
	iLoad("Rendered//WrongAnswer.png", 67, 1, "100");
	iLoad("Rendered//TimeUp.png", 49, 1, "100");
	iLoad("Rendered//Dead.png", 50, 1, "100");
	iLoad("Rendered//Fire1.png", 54, 1, "100");
	iLoad("Rendered//Fire2.png", 55, 1, "100");
	iLoad("Rendered//RoboDem//RoboDem0040.png", 58, 1, "100");
	iLoad("Rendered//HOW TO.png", 59, 1, "100");
	iLoad("Rendered//Credit//CreditMain.png", 60, 1, "100");
	iLoad("Rendered//Credit//Credit1.png", 61, 1, "100");
	iLoad("Rendered//Credit//Credit2.png", 62, 1, "100");
	iLoad("Rendered//Done.png", 63, 1, "100");
	iLoad("Rendered//PressSpace.png", 64, 1, "100");
	iLoad("Rendered//SelectL.png", 65, 1, "100");
	iLoad("Rendered//Tuto.png", 66, 1, "100");

    iLoad("Rendered//Questions//1.png", 71, 1, "100");
	iLoad("Rendered//Questions//2.png", 72, 1, "100");
	iLoad("Rendered//Questions//3.png", 73, 1, "100");
	iLoad("Rendered//Questions//4.png", 74, 1, "100");
	iLoad("Rendered//Questions//5.png", 75, 1, "100");
	iLoad("Rendered//Questions//6.png", 76, 1, "100");
	iLoad("Rendered//Questions//7.png", 77, 1, "100");
	iLoad("Rendered//Questions//8.png", 78, 1, "100");
	iLoad("Rendered//Questions//9.png", 79, 1, "100");
	iLoad("Rendered//Questions//10.png", 80, 1, "100");
	iLoad("Rendered//Questions//11.png", 81, 1, "100");
	iLoad("Rendered//Questions//12.png", 82, 1, "100");
	iLoad("Rendered//Questions//13.png", 83, 1, "100");
	iLoad("Rendered//Questions//14.png", 84, 1, "100");
	iLoad("Rendered//Questions//15.png", 85, 1, "100");

	iLoad("Rendered//Answer//1.png", 91, 1, "100");
	iLoad("Rendered//Answer//2.png", 92, 1, "100");
	iLoad("Rendered//Answer//3.png", 93, 1, "100");
	iLoad("Rendered//Answer//4.png", 94, 1, "100");
	iLoad("Rendered//Answer//5.png", 95, 1, "100");
	iLoad("Rendered//Answer//6.png", 96, 1, "100");
	iLoad("Rendered//Answer//7.png", 97, 1, "100");
	iLoad("Rendered//Answer//8.png", 98, 1, "100");
	iLoad("Rendered//Answer//9.png", 99, 1, "100");
	iLoad("Rendered//Answer//10.png", 100, 1, "100");
	iLoad("Rendered//Answer//11.png", 101, 1, "100");
	iLoad("Rendered//Answer//12.png", 102, 1, "100");
	iLoad("Rendered//Answer//13.png", 103, 1, "100");
	iLoad("Rendered//Answer//14.png", 104, 1, "100");
	iLoad("Rendered//Answer//15.png", 105, 1, "100");

	iLoad("Rendered//Levels//1.png", 111, 1, "100");
	iLoad("Rendered//Levels//2.png", 112, 1, "100");
	iLoad("Rendered//Levels//3.png", 113, 1, "100");
	iLoad("Rendered//Levels//4.png", 114, 1, "100");
	iLoad("Rendered//Levels//5.png", 115, 1, "100");
	iLoad("Rendered//Levels//6.png", 116, 1, "100");
	iLoad("Rendered//Levels//7.png", 117, 1, "100");
	iLoad("Rendered//Levels//8.png", 118, 1, "100");
	iLoad("Rendered//Levels//9.png", 119, 1, "100");
	iLoad("Rendered//Levels//10.png", 120, 1, "100");
	iLoad("Rendered//Levels//11.png", 121, 1, "100");
	iLoad("Rendered//Levels//12.png", 122, 1, "100");
	iLoad("Rendered//Levels//13.png", 123, 1, "100");
	iLoad("Rendered//Levels//14.png", 124, 1, "100");
	iLoad("Rendered//Levels//15.png", 125, 1, "100");

	aniLoad("Rendered//Standing//RoboStand0.png",0,20,10,100);
	aniLoad("Rendered//Running//RoboAniRunning0.png", 1, 26, 10, 100);
	aniLoad("Rendered//Jumping//RoboJumping0.png", 2, 20, 10, 100);
	aniLoad("Rendered//BoostJump//RoboBoostJump0.png", 3, 20, 10, 100);//Done
	aniLoad("Rendered//Falling//RoboFalling0.png", 4, 8, 10, 100);//Done
	aniLoad("Rendered//ComingDown//RoboComingDown0.png", 5, 18, 10, 100);//Done
	aniLoad("Rendered//Firing//RoboFiring0.png", 6, 9, 10, 100);
	aniLoad("Rendered//Goingup//Goingup0.png", 7, 8, 10, 100);
	aniLoad("Rendered//BoostIncrease//RoboBoostIncrease0.png", 8, 20, 10, 100);
	aniLoad("Rendered//Turrent1//Turrent10.png", 9, 15, 10, 100);
	gfxObject.BeginFrame(1); display(56, 0, 0); display(57,550,200); gfxObject.EndFrame();
	aniLoad("Rendered//Turrent1Destroy//Turrent1Destroy0.png", 10, 30, 10, 100);
	aniLoad("Rendered//heroBullets1//heroBullets10.png", 11, 45, 10, 100);
	aniLoad("Rendered//heroBullets1//heroBulletsC0.png", 12, 20, 10, 100);
	aniLoad("Rendered//RoboDuckD//RoboDuckD0.png", 13, 20, 10, 100);
	aniLoad("Rendered//RoboDuckU//RoboDuckU0.png", 14, 20, 10, 100);
	aniLoad("Rendered//HeavyFire//HeavyFire0.png", 15, 15, 10, 100);
	aniLoad("Rendered//HeavyMove//HeavyMove0.png", 16, 40, 10, 100);
	aniLoad("Rendered//MidFire//MidFire0.png", 17, 15, 10, 100);
	aniLoad("Rendered//MidMove//MidMove0.png", 18, 40, 10, 50);
	aniLoad("Rendered//MineC//MineC0.png", 19, 30, 10, 100);
	aniLoad("Rendered//MineAC//MineAC0.png", 20, 30, 10, 100);
	aniLoad("Rendered//MineB//MineB0.png", 21, 34, 10, 100);
	aniLoad("Rendered//MidDes//MidDes0.png", 22, 35, 1, 100);
	aniLoad("Rendered//HeavyDes//HeavyDes0.png", 23, 40, 1, 100);
	aniLoad("Rendered//RoboDem//RoboDem0.png", 24, 40, 1, 100);
	aniLoad("Rendered//Dr Brain//DRBRAIN0.png", 25, 20, 1, 100);

	snd.iniDirectSound(hWnd);
	snd.load(0, "Sounds//Small.wav");
	snd.load(1, "Sounds//Blow.wav");
	snd.load(2, "Sounds//Land.wav");
	snd.load(3, "Sounds//Jump.wav");
	snd.load(4, "Sounds//HFire1.wav");
	snd.load(7, "Sounds//fire2.wav");
	snd.load(8, "Sounds//fireC.wav");
	snd.load(9, "Sounds//MineMove.wav");
	snd.load(10, "Sounds//HealthDown.wav");
	snd.load(11, "Sounds//1.wav");
	snd.load(12, "Sounds//2.wav");
	snd.load(13, "Sounds//3.wav");
	snd.load(14, "Sounds//4.wav");
	snd.load(15, "Sounds//5.wav");
	snd.load(16, "Sounds//6.wav");
	for (int i = 0; i < 20;i++)
		snd.load(100+i, "Sounds//HTurrentFire3.wav");
	for (int i = 0; i < 20; i++)
		snd.load(120 + i, "Sounds//TDestroy.wav");
	for (int i = 1; i <= 20; i++)
		snd.load(140 + i, "Sounds//MineBlast.wav");
	for (int i = 1; i < 20; i++)
		snd.load(160 + i, "Sounds//HTurrentFire2.wav");
	for (int i = 0; i < 20; i++)
		snd.load(180 + i, "Sounds//MidDes.wav");
	for (int i = 1; i < 20; i++)
		snd.load(200 + i, "Sounds//HTurrentFire.wav");
	for (int i = 0; i < 20; i++)
		snd.load(220 + i, "Sounds//ELaserUp.wav");
	for (int i = 0; i < 20; i++)
		snd.load(240 + i, "Sounds//ELaserDown.wav");
	level = 15;
	tDel2.start();
}

unsigned char engine::PutPixel(int x, int y, int r, int g, int b, float trans,int sColor)
{
	return gfxObject.PutPixel(x, y, r, g, b, trans,sColor);
}

void engine::iLoad(char* fileName, int imageCode, int trans, char* size)
{
	imgs* imgsTmp = loadedImg;
	while (imgsTmp->next != NULL)
	{
		assert(imgsTmp->imageCode != imageCode);
		imgsTmp = imgsTmp->next;
	}
	assert(imgsTmp->imageCode != imageCode);
	if (imgsTmp->arrImg != NULL)
	{
		imgsTmp->next = new imgs;
		imgsTmp = imgsTmp->next;
	}
	imgsTmp->arrImg = new image;
	imgsTmp->imageCode = imageCode;
	imgsTmp->arrImg->arrPix = new pixel;
	int i = 0;
	for (i = 0; fileName[i] != '\0'; i++);
	if (fileName[i - 1] == 'p'&&fileName[i - 2] == 'm'&&fileName[i - 3] == 'b')
		bmpLoad(imgsTmp->arrImg->arrPix, fileName, trans);
	else
	{
		int j = 0;
		for (j = 0; fileName[j] != '\0'; j++);
		wchar_t* fileNameTmp = new wchar_t[j+10];
		for (j = 0; fileName[j] != '\0';j++)
		{
				fileNameTmp[j] = fileName[j];
		}
		fileNameTmp[j] = '\0';
		FILE *pngFile = fopen(fileName, "rb");	//To check exsisting file
		if (pngFile == NULL)
			assert(0 && "File Not Found.png");			
		if (fileNameTmp[0] == 'c');
			pngLoad(imgsTmp->arrImg->arrPix, fileNameTmp);
	}
	imgsTmp->arrImg->size = 100;
	pixel*tmp = new pixel;
	while (*size != '\0')
	{
		int sizeNum = 0;
		while (*size != ','&&*size != '\0')
		{
			sizeNum *= 10;
			sizeNum += *size - 48;
			size++;
			if (*size < '0' || *size>'9')
				if (*size != ',' && *size != '\0')
					assert(0&&"Invalid Character In Loading Image");
		}
		if (*size == ',')
			size++;
		image* tmp = imgsTmp->arrImg;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new image;
		tmp = tmp->next;
		tmp->size = sizeNum;
		tmp->arrPix = new pixel;
		imageConv(tmp->arrPix, imgsTmp->arrImg->arrPix, sizeNum / 100.0f);
	}
}

void engine::imageConv(pixel* fin, pixel* told, float size)
{
	int x, y;
	x = y = -1;
	pixel* old = told;
	while (old != NULL)
	{
		fin->r = old->r;
		fin->g = old->g;
		fin->b = old->b;
		fin->x = old->x*size;
		fin->y = old->y*size;
		if (x != fin->x || y != fin->y)
		{
			x = (fin->x);
			y = (fin->y);
			fin->next = new pixel;
			fin = fin->next;

		}
		old = old->next;
	}
}

void engine::aniLoad(char* fileNameF, int aniCode, unsigned int noFrames, int trans, int size)
{
	int i = 0, j = 0, o = 0;
	char fileName[100];
	for (o = 0; fileNameF[o] != '\0'; o++)
	{
		fileName[o] = fileNameF[o];
	}
	fileName[o] = '\0';
	for (j = 0; fileName[j] != '\0'; j++);
	if (j>=1)
	if (fileName[j - 1] == 'p')
	{
		fileName[j] = 'b';
		fileName[j+1] = 'm';
		fileName[j+2] = 'p';
	}
	else
	{
		fileName[j] = 'p';
		fileName[j+1] = 'n';
		fileName[j+2] = 'g';
	}
	if (j >= 4)
	{
		fileName[j - 4] = '0';
		fileName[j - 3] = '0';
		fileName[j - 2] = '0';
		fileName[j - 1] = '.';
		fileName[j + 3] = '\0';
		j -= 2;
	}

	anis* aniTmp = aniPtr;
	if (aniTmp->arrImg == NULL)//First element
		aniTmp->arrImg = new aniImage;
	else
	{
		while (aniTmp->next != NULL)
		{
			if (aniTmp->aniCode == aniCode)
			{
				assert(0 && "Animated Sequence Name Already Exists");
			}
			aniTmp = aniTmp->next;
		}
		if (aniTmp->aniCode == aniCode)
			assert(0 && "Animated Sequence Name Already Exists");
		aniTmp->next = new anis;
		aniTmp = aniTmp->next;
		aniTmp->arrImg = new aniImage;//-----------------------
	}
	aniTmp->aniCode = aniCode;
	aniImage* imgTmp = aniTmp->arrImg;
	while (i < noFrames)
	{
		i++;
		int tm = i,it = 0;
		while (tm)
		{
			fileName[j-it] = tm % 10 + '0';
			tm /= 10;
			it++;
		}
		if (i > 1)
		{
			imgTmp->next = new aniImage;
			imgTmp = imgTmp->next;
		}
		imgTmp->arrPix = new pixel;
		if (fileName[j + 4] != 'g')
			bmpLoad(imgTmp->arrPix, fileName, trans);
		else
		{
			int j = 0;
			for (j = 0; fileName[j] != '\0'; j++);
			wchar_t* fileNameTmp = new wchar_t[100];
			for (j = 0; fileName[j] != '\0'; j++)
				fileNameTmp[j] = fileName[j];
			fileNameTmp[j] = fileName[j];
			if (fileNameTmp[0] == 'c');
			pngLoad(imgTmp->arrPix, fileNameTmp);
		}
	}

}

int engine::animate(int aniCode, unsigned char num, unsigned int tDelay, int x, int y, float trans = 1.0f, int dir, unsigned char sColor, char* detect)
{
	anis* tmp = aniPtr;
	bool key = true;
	if (tmp->aniCode == aniCode)
		key = false;
	while (tmp->next != NULL&&key)
	{
		tmp = tmp->next;
		if (tmp->aniCode == aniCode)
			key = false;
	}
	if (tmp == NULL || tmp->aniCode != aniCode)
		assert(0&&"Invalid aniCode! Doesn't exist or not loaded");
	tmp->t[num].start();
	if (tmp->imgTmp[num].imgTmp == NULL)
	{
		bmpDisplay(tmp->arrImg->arrPix, x, y, dir, trans, sColor, detect);
		tmp->imgTmp[num].imgTmp = tmp->arrImg;
	}
	else if (tmp->imgTmp[num].imgTmp != NULL)
		bmpDisplay(tmp->imgTmp[num].imgTmp->arrPix, x, y, dir, trans, sColor, detect);
	if (tmp->t[num].elapsed()>(tDelay*10/25.0))
	{
		
		if (tmp->imgTmp[num].imgTmp->next != NULL)
			tmp->imgTmp[num].imgTmp = tmp->imgTmp[num].imgTmp->next;
		else
		{
			tmp->imgTmp[num].imgTmp = NULL;
			return 0;//Done one sequence
		}
	}
	return 1;
}

void engine::bmpLoad(pixel* ptrT, char *fileName, int r)
{
	pixel* ptr = ptrT;
	FILE *bmpFile = fopen(fileName, "rb");
	if (bmpFile == NULL)
		assert(0 && "The File Is Not Found.bmp");		
	unsigned int fileOffset;
	int width, height;
	fseek(bmpFile, 10, SEEK_SET);
	fread(&fileOffset, 4, 1, bmpFile);
	fseek(bmpFile, 18, SEEK_SET);
	fread(&width, 4, 1, bmpFile);
	fread(&height, 4, 1, bmpFile);
	fseek(bmpFile, fileOffset, SEEK_SET);
	int nPaddingBytesPerRow = (4 - ((width * 3) % 4)) % 4;
	unsigned char tmp[3];
	int i = 0;
	for (int y = height - 1; y >= 0; y--, i++)
	{
		for (int x = 0; x < width; x++)
		{
			fread(tmp, sizeof(tmp), 1, bmpFile);
			if (tmp[2]<r || tmp[1]<r || tmp[0]<r)
			{
				if (ptr->next == NULL)
				{
					ptr->x = x;
					ptr->y = y;
					ptr->r = tmp[2];
					ptr->g = tmp[1];
					ptr->b = tmp[0];
					ptr->next = new pixel;
				}
				else
				{
					ptr = ptr->next;
					ptr->x = x;
					ptr->y = y;
					ptr->r = tmp[2];
					ptr->g = tmp[1];
					ptr->b = tmp[0];
					ptr->next = new pixel;
				}
			}
		}
		fseek(bmpFile, nPaddingBytesPerRow, SEEK_CUR);
	}
	ptr->next = NULL;
	fclose(bmpFile);
}

void engine::pngLoad(pixel* a, wchar_t* fileName)
{
	GdiplusStartupInput StartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &StartupInput, NULL);
	Gdiplus::Bitmap bitmap(fileName);
	Gdiplus::Color pix;
	pixel* tmp = a;
	for (int i = 0; i < bitmap.GetWidth(); i++)
		for (int j = 0; j < bitmap.GetHeight(); j++)
		{
			bitmap.GetPixel(i, j, &pix);
			if (pix.GetA()>110)
			{
				if (a->next==NULL)
				{
					a->x = i;
					a->y = j;
					a->r = pix.GetR();
					a->g = pix.GetG();
					a->b = pix.GetB();
					a->trans = pix.GetA();
					a->next = new pixel;
				}
				else
				{
					a = a->next;
					a->x = i;
					a->y = j;
					a->r = pix.GetR();
					a->g = pix.GetG();
					a->b = pix.GetB();
					a->trans =  pix.GetA();
					a->next = new pixel;
				}
			}
		}
	a->next = NULL;
}

void engine::display(int imageCode, int x, int y, int size, int trans,unsigned char sColor,char* detect,float angle,int ox,int oy)
{
	imgs* imgTmp = loadedImg;
	while (imgTmp->next != NULL&&imgTmp->imageCode != imageCode)
	{
		imgTmp = imgTmp->next;
	}
	assert(imgTmp->imageCode == imageCode);
	image* tmp = imgTmp->arrImg;
	while (tmp->next != NULL&&tmp->size != size)
		tmp = tmp->next;
	if (tmp->size != size)
		bmpDisplay(imgTmp->arrImg->arrPix, x, y, size, trans/100.0,sColor,detect,angle,ox,oy);
	else
		bmpDisplay(tmp->arrPix, x, y, 1, trans/100.0,sColor,detect,angle,ox,oy);
}

float engine::rotateX(int x,int y,float angle)
{
	return (x*cos(angle) - y*sin(angle));
}

float engine::rotateY(int x,int y, float angle)
{
	return (x*sin(angle) + y*cos(angle));
}

void engine::bmpDisplay(pixel *a, int x, int y, float size, float trans, unsigned char sColor, char* detect,float angle, int ox, int oy)
{
	pixel *ptr = a;
	if (detect)
		memset(detect, false, 256);
	int det;
	int xTm, yTm;
	int Del = 0;
	if (!angle)	 		
	while (ptr != NULL)//&&Del<tUni.elapsed())
	{
		Del += 10;
		float Ttrans = ptr->trans*trans/255.0;
		if (Ttrans < 0)
			Ttrans = 0;
		xTm = ptr->x;
		yTm = ptr->y;
		if (xTm != 0 || yTm != 0)
		{
			if (size < 0)
				det = PutPixel(ptr->x*size + x, ptr->y*size*-1 + y, ptr->r, ptr->g, ptr->b, Ttrans, sColor);
			else
				det = PutPixel(ptr->x*size + x, ptr->y*size + y, ptr->r, ptr->g, ptr->b, Ttrans, sColor);

			if (detect&&det)
				detect[det] = true;
			if (detect)
			{
				if (ptr->x <= 24 && det == 1)
					detect[0] = -1;
				else if (ptr->x >= 25 && ptr->x <= 54 && det == 1)
					detect[0] = -2;
				if (ptr->y < 3 && det)
					detect[255] = -1;
			}
		}
		ptr = ptr->next;
	}
	else
	{
		angle = (22 * angle) / (180 * 7.0);
		while (ptr != NULL)
		{
			float Ttrans = ptr->trans*trans / 255.0;
			if (Ttrans < 0)
				Ttrans = 0;
			float xFin, yFin;
			int xTmp=0, yTmp=0;
			xFin = rotateX(ptr->x-ox, ptr->y-oy, angle)+ox;
			yFin = rotateY(ptr->x-ox,ptr->y-oy, angle)+oy;
			PutPixel(xFin + x, yFin + y, ptr->r, ptr->g, ptr->b, Ttrans, 255);
			for (float i = 0.1; i < 0.5; i += 0.1999)
				{
				xFin -= i;
				PutPixel(xFin + x, yFin + y, ptr->r, ptr->g, ptr->b, Ttrans);
				}
			ptr = ptr->next;
		}
	}
}

bool engine::launch()
{
	gfxObject.BeginFrame(level);
	lclick = lState->getLeftClick();
	tPaus.start();
	if (disMenu == 0)
	{
		tdel.start();
		if (tdel.elapsed()>1000)
		{
			disMenu = menu();
			if (disMenu == 1)
			{
				playG = true;
			}
			else if (disMenu == 2)
			{
				howTo = true;
			}
			else if (disMenu == 3)
			{
				credit = true;
				creTimer.start();
			}
		}
		gfxObject.EndFrame();
		return 0;
	}
	if (level != 1 && playG&&!levelS)
	{
		static int levelTmp = 1;
		display(65, 500, 300);
		if (key(38) && levelTmp < level&&tDel2.elapsed()>200)
		{
			levelTmp++;
			tDel2.reset();
		}
		if (key(40) && levelTmp > 1&&tDel2.elapsed()>200)
		{
			levelTmp--;
			tDel2.reset();
		}
		if (key(13))
		{
			levelS = true;
			level = levelTmp;
			intitLevel();
		}
		intDes(levelTmp, 1000, 590);
		gfxObject.EndFrame();
		return false;
	}
	if (level == 1 && playG&&!tutorial)
	{
		display(125, 0, 0,1,100,1);
		display(66, 50,10);
		if (key(13))
		{
			tutorial = true;
			reset();
			leftT.reset();
			leftT.start();
			intitLevel();
		}
		mainCharacter();
		compileHBeam(1);
		disHud();
		gfxObject.EndFrame();
		return 0;
	}
	if (level == 16)
	{
		snd.play(11,0);
		animate(25, 0, 24, 200, 200);
		display(63, 240, 0);
		gfxObject.EndFrame();
		return false;
	}
	if (credit)
	{
		gfxObject.BeginFrame(1);
		if (creTran <= 200&&creAccess2==false)
		{
			if (creTimer.ticTic(50))
			{

				if (creTran < 100)
					creTran += 4;
				else
					creTran += 2;
			}
			if (creTran < 100)
				display(56, 0, 0, 1, creTran);
			else if (creTran < 200)
			{
				display(56, 0, 0, 1, 100);
				display(60, 0, 0, 1, creTran % 100);
			}
			creAccess = false;
			if (creTran == 200)
			{
				creTimer.reset();
				creTran++;
			}
		}
		else if (!creAccess2)
		{
			display(60, 0, 0, 1, 100);
			if (creTimer.ticTic(5000))
				creAccess = true;
			if (creAccess&&creTran < 300 && creTimer.ticTic(50))
				creTran++;

			if (creTran < 300)
				display(61, 150, -300, 1, creTran % 100);
			else if (!creAccess2)
			{
				display(61, 150, -300);
			}
			if (key(' ') || key(27))
			{
				creAccess2 = true;
				creAccess = false;
				creTran = 300;
				creTimer.reset();
			}
		}
		if (creAccess2&&!creAccess4)
		{
			display(60, 0, 0, 1, 100);
			if (!creAccess3&&creTimer.ticTic(3000))
			{
				creAccess3 = true;
			}
			else if (creTimer.ticTic(50))
			{
				creTran2++;
				if (creY > -1000)
					creY--;
			}
			if (creAccess3)
			{
				if (creTran2<100)
					display(62, 0, creY, 1, creTran2);
				else
				{
					display(62, 0, creY);
				}
				if (key(' ')&&creY>-1000)
					creY -= 5;
				if (creY <= -1000 && key(' '))
				{
					creAccess4 = true;
					creTimer.reset();
					creTran2 = 100;
				}
			}
		}
		if (creAccess4)
		{
			display(60, 0, 0, 1, 100);
			if (creTimer.ticTic(2000))
			{
				credit = false;
				disMenu = 0;
			}
		}

		gfxObject.EndFrame();
		return false;
	}
	if (howTo)
	{
		snd.play(11, 0);
		display(59, 0, 0);
		if (key(27))
		{
			howTo = false;
			disMenu = 0;
			snd.stop(11);
		}
		gfxObject.EndFrame();
		return false;

	}
	if (key(27)&& tPaus.ticTic(500))
	{
		if (paus != -1)
		{
			paus = -1;
			playG = false;
			pauseTimer();
		}
		else
		{
			playG = true;
			paus = 0;
			snd.stop(11);
			resumeTimer();
		}
		if (paus)
		{
			pauseTimer();
			snd.stopa();
			snd.stop(11 + level % 6);
		}
		else
		{
			resumeTimer();
			snd.resume();
			for (int k = 1; k < 6; k++)
				snd.stop(11 + k);
		}
	}
	if (healthTmp <= 0)
	{
		if (!dem)
		{
			if (dir==1)
				dem = !animate(24, 0, 23, chX, chY);
			else
				dem = !animate(24, 0, 23, chX+170, chY-4,1,-1);
		}
		if (dem)
		{
			display(50, 0, 0);
			if (dir==1)
				display(58, chX, chY);
			else
				display(58, chX+170, chY-4,-1);
			int response = restart();
			if (response == 1)
				intitLevel();
			else if (response == 2)
				return true;
		}
	}
	else if (timeLeft-leftT.elapsed()/1000 <= 0)
	{
		int response = restart();
		if (response == 1)
			intitLevel();
		else if (response == 2)
			return true;
		display(49, 0, 0);
	}
	else if (answer != 0)
	{
		int response=recordedAns(answer);
		if (response == 1)
			intitLevel();
		else if (response == 2)
			return true;
	}

	else if (paus == -1)
	{
		if (key(23))
			playG = true;
		paus = paused();
		if (paus == 1)
			playG = true;
		if (paus == 2)
		{
			playG = true;
			intitLevel();
		}
		if (paus == 4)
		{
			tdel.start();
			tdel.reset();
			disMenu = 0;
			reset();
			playG = false;
			tutorial = false;
			levelS = false;
		}
	}
	else if (playG) //Needs to call the reset function here
		centralControl();
	if (disMenu == 4||paus==3)
		return true;
	gfxObject.EndFrame();
	return 0;
}

int engine::key(int a)
{
	if (a == 'l')
		return lState->mKeyl();
	else if (a == 'r')
		return lState->mKeyr();
	else if (a == 'm')
		return lState->mKeym();
	else if (a == 'x')
		return lState->getx()*1920/xlen;
	else if (a == 'y')
		return lState->gety()*1020/ylen;
	else if (a == 'c')
		return lclick;
	if (a >= 'a'&&a <= 'z')
		a -= 'a' - 'A';
	return lState->keyState(a);
}

void engine::outText(char* a,int x,int y,int r=255,int g=255,int b=255,float trans=1.0f)
{
	int i = 0,k=0;
	while (a[i] != '\0')
	{
		int j = 0;
		if ((a[i] >= 'A'&&a[i]<='Z'))
		{

			while (charr[a[i] - 'A'].x[j] != '\0')
			{
				PutPixel(charr[a[i] - 'A'].x[j]+i*13-k*5+x, charr[a[i] - 'A'].y[j]+y,r,g,b,trans);
				j++;
				
			}
			if (a[i] == 'I' || a[i] == 'J' )
				k++;
		}
		if ((a[i] >= 'a'&&a[i] <= 'z'))
		{
			int z = a[i] - 'a' + 26;
			while (charr[a[i] - 'a' + 26].x[j] != '\0')
			{

				PutPixel(charr[a[i] - 'a' + 26].x[j] + i * 13 - k * 5 + x, charr[a[i] - 'a'+ 26].y[j] + y, r, g, b, trans);
				j++;

			}
			if (a[i] == 'i' || a[i] == 'j')
				k++;
		}

		i++;
	}
}

void engine::newTurrent(int noTurrent,int x,int y,int del,float speed,int dir)
{
	turrent* tmpTurr;
	if (!turr)
	{
		turr = new turrent;
		turr->dir = dir;
		turr->no = noTurrent;
		turr->x = x;
		turr->y = y;
		turr->delay = del;
		turr->speed = speed;
	}
	else
	{
		tmpTurr = turr;
		if (turr)
			while (tmpTurr->next != NULL)
				tmpTurr = tmpTurr->next;
		tmpTurr->next = new turrent;
		tmpTurr = tmpTurr->next;
		tmpTurr->x = x;
		tmpTurr->y = y;
		tmpTurr->dir = dir;
		tmpTurr->no = noTurrent;
		tmpTurr->next = NULL;
		tmpTurr->delay = del;
		tmpTurr->speed = speed;
	}
}

void engine::compileTurrent()
{
	turrent* tmpTurr = turr;
	char* detectB = new char[256];
	bool detBeam = false;
	int turrTmp;
	while (tmpTurr)
	{
		if (tmpTurr->exist)
		{
			detBeam = false;
			int fix = 0;
			if (tmpTurr->dir < 0)
				fix = -1200;
			for (int i = 0; i < 1200 && !detBeam; i++)
				for (int j = 0; j < 50; j++)
				{
					turrTmp = gfxObject.GtPixel(i + tmpTurr->x + fix, tmpTurr->y + j-8);
					if (turrTmp == 2 || turrTmp == 4||turrTmp==8)
						detBeam = true;
					//PutPixel(i + tmpTurr->x+fix, tmpTurr->y + j-8 , 255, 0, 0); // for detection of turrent range
				}

			if (detBeam && tmpTurr->ti.ticTic(tmpTurr->delay) != 0)
			{
				if (tmpTurr->i2==6)
					snd.play(100 + tmpTurr->no, -1500);
				tmpTurr->i2++;
				if (!animate(9, tmpTurr->no, 20, tmpTurr->x, tmpTurr->y, 1, tmpTurr->dir, 3,detectB))
				{
					tmpTurr->ti.start();
					if (tmpTurr->dir==1)
						newEBeam(tmpTurr->x+tmpTurr->dir*2+5, tmpTurr->y + 13, (float)tmpTurr->dir*tmpTurr->speed);
					else
						newEBeam(tmpTurr->x + tmpTurr->dir * 2 -40, tmpTurr->y + 13, (float)tmpTurr->dir*tmpTurr->speed);
					tmpTurr->i2=0;
				}
			}
			else
				display(6, tmpTurr->x, tmpTurr->y, tmpTurr->dir, 100, 3,detectB);
			if (detectB[4]||detectB[8])//Something with bullet
			{
				compileHBeam(false);
				tmpTurr->exist = false;
 				tmpTurr->ani = true;
				snd.play(120 + tmpTurr->no, -1000);
			}
		}
		else
		{
			if (tmpTurr->ani)
			{
				animate(10, tmpTurr->no, 41, tmpTurr->x, tmpTurr->y, 1, tmpTurr->dir);
				tmpTurr->i++;
				if (tmpTurr->i == 30)
				{
					tmpTurr->ani = false; 
					score += (score / 100) + 10;
				}
			}			
			else
			{
				display(7, tmpTurr->x, tmpTurr->y, tmpTurr->dir, 100, 1);
				
			}
		}
		tmpTurr = tmpTurr->next;
	}
}

void engine::newEBeam(int x, int y, float speed,int type)
{
	eBeamNode* tmp;
	if (!eBeam)
	{
		eBeam = new eBeamNode;
		eBeam->x = x;
		eBeam->y = y;
		eBeam->speed = speed;
		eBeam->type = type;
	}
	else
	{
		tmp = eBeam;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new eBeamNode;
		tmp = tmp->next;
		tmp->x = x;
		tmp->y = y;
		tmp->speed = speed;
		tmp->type = type;
	}
}

void engine::compileEBEAM(bool inc=true)
{
	eBeamNode* tmp = eBeam;
	eBeamNode* tmp2=new eBeamNode;
	char* detB = new char[256];
	memset(detB,0,256);
	while (tmp)
	{
		if (tmp->type==1)
			display(4,tmp->x,tmp->y,1,100,5,detB);
		else if (tmp->type == 2)
			display(15, tmp->x, tmp->y, 1, 100, 10, detB);
		else if (tmp->type == 3)
		{
			if (tmp->speed>0)
				display(14, tmp->x, tmp->y, 1, 100, 12, detB);
			else
				display(14, tmp->x, tmp->y, -1, 100, 12, detB);
			if (detB[4])
			{
				compileHBeam(false);
				tmp->des++;
			}
			if (detB[8])
			{
				compileHBeam(false);
				tmp->des += 3;
			}
			if (tmp->des >= 4||detB[2]||detB[1]||detB[50])
			{
				compileHBeam(false);
				if (tmp == eBeam)
					eBeam = eBeam->next;
				tmp2->next = tmp->next;
				
			}
			if (detB[2] || detB[7])
				health -= 20;
			
		}
		if (tmp->type!=3&&(detB[2]||detB[1]||detB[4]||detB[8]||detB[50]))//Needs to add the health minus here
		{
			compileHBeam(false);
			if (tmp == eBeam)
				eBeam = eBeam->next;
			tmp2->next = tmp->next;
			if (detB[2])// || detB[7])		   //Calculates loss in hero's heatlh
			{
				switch (tmp->type)
				{
				case 1:health -= 15; break;
				case 2:health -= 15; break;
				}
			}
		}
		if (tmp->x>=1920)
			tmp2->next = tmp->next;
		if (inc)
		{
			if (tmp->type == 3)
				tmp->x += tmp->speed * 5;
			else if (tmp->type == 1)
				tmp->x += tmp->speed * 5;
			else
				tmp->x += tmp->speed*3.5;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void engine::newHBeam(int no, int x, int y, float speed)
{
	hBeamNode* tmp;
	int i = 0;
	if (!hBeam)
	{
		hBeam = new hBeamNode;
		hBeam->x = x;
		hBeam->y = y;
		hBeam->speed = speed;
		hBeam->type = no;
		hBeam->no = 0;
	}
	else
	{
		tmp = hBeam;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new hBeamNode;
		tmp = tmp->next;
		tmp->x = x;
		tmp->y = y;
		tmp->speed = speed;
		tmp->type = no;
		tmp->no = i;
	}
}

void engine::compileHBeam(bool inc=true)
{
	hBeamNode* tmp = hBeam;
	hBeamNode* tmp2 = new hBeamNode;
	char* detH = new char[256];
	memset(detH, 0, 256);
	bool manualDis = false;
	while (tmp)
	{
		manualDis = false;
		if (tmp->type == 1)
		{
			if (tmp->speed > 0)
			{
				display(8, tmp->x + 150, tmp->y + 84, 1, 100, 4, detH);
				display(8, tmp->x + 152, tmp->y + 84, 1, 0, 4, detH);
				if (tmp->x + 150 + 10 > 1920)
					manualDis = true;
			}
			else if (tmp->speed < 0)
			{
				display(8, tmp->x, tmp->y + 84, 1, 100, 4, detH);
				display(8, tmp->x-2, tmp->y + 84, 1, 0, 4, detH);
				if (tmp->x + 10 < 0)
					manualDis = true;
			}
			if (detH[3] || detH[5]||detH[10])
				tmp->des++;
			if (detH[6]||detH[9]||detH[11])
			{
				tmp->des ++;
			}
			if (detH[12])
				tmp->des = 2;
			if (manualDis || detH[1]||detH[50]||tmp->des>=2)
			{
				if (tmp == hBeam)
					hBeam = hBeam->next;
				tmp2->next = tmp->next;
			}
		}
		else if (tmp->type == 2)
		{
			if (tmp->speed > 0)
			{
				animate(12, tmp->no, 20, tmp->x+30, tmp->y + 75, 1, 1, 8, detH);
				if (tmp->x + 150 + 10 > 1920)
				{
					manualDis = true;
					snd.stop(8);
				}
			}
			else if (tmp->speed < 0)
			{
				animate(12, tmp->no, 20, tmp->x+130, tmp->y + 75, 1, -1, 8, detH);
				if (tmp->x + 10 < 0)
				{
					manualDis = true;
					snd.stop(8);
				}
			}
			snd.play(8, -1000);
			if (detH[3] || detH[5]||detH[10])
				tmp->des++;
			if (detH[6]||detH[9]||detH[11])
				tmp->des = 8;
			if (detH[12])
				tmp->des = 4;
			if (manualDis || detH[1] || detH[50]|| tmp->des >= 4)
			{
				motaGola = false;
				if (tmp == hBeam)
					hBeam = hBeam->next;
				tmp2->next = tmp->next;
			}
		}
		if (inc)
		{
			if (tmp->type == 1)
				tmp->x += tmp->speed * 3;
			else
				tmp->x += tmp->speed*2.2;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void engine::newELaser(int x1, int x2, int y, int onTime, int offTime,int dir)
{
	eLaserNode* tmp = eLaser;
	if (!eLaser)
	{
		eLaser = new eLaserNode;
		eLaser->x1 = x1;
		eLaser->x2 = x2;
		eLaser->y = y;
		eLaser->onTime = onTime;
		eLaser->offTime = offTime;
		eLaser->next = NULL;
		eLaser->dir = dir;
		eLaser->on.start();
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new eLaserNode;
		tmp = tmp->next;
		tmp->x1 = x1;
		tmp->x2 = x2;
		tmp->y = y;
		tmp->onTime = onTime;
		tmp->offTime = offTime;
		tmp->next = NULL;
		tmp->dir = dir;
		tmp->on.start();
	}

}

void engine::compileELaser()
{
	eLaserNode* tmp = eLaser;
	int no = 0;
	while (tmp)
	{
		tmp->r.start();//To time the effects in the laser beam;
		if (tmp->on.ticTic(tmp->onTime))
		{
			tmp->off.start();
			
		}
		if (tmp->off.ticTic(tmp->offTime))
		{
			tmp->on.start();
		}
		else if (tmp->on.ticTic(tmp->onTime)&&tmp->trans>0&&tmp->r.ticTic(10))
		{
			if (!tmp->sndPlay)
			{
				snd.play(240 + no, -1500);
				tmp->sndPlay = true;
			}
			tmp->trans--;
			if (tmp->trans >=20)
				tmp->trans = 19;
		} 			
		if (!tmp->on.ticTic(tmp->onTime) && tmp->trans < 20 && tmp->r.ticTic(10))
		{
			if (!tmp->sndPlay)
			{
				snd.play(220 + no, -1000);
				tmp->sndPlay = true;
			}
			tmp->trans++;
		}
		if (tmp->trans < 90&&tmp->trans>=20&&tmp->rate&&tmp->r.ticTic(10))
			tmp->trans++;
		else if (tmp->trans > 20 && tmp->r.ticTic(10))
		{
			tmp->trans--;
			tmp->rate = false;
		}
		else if (tmp->trans==20)
			tmp->rate = true;
		if (tmp->dir == 0)
		{

			for (int i = tmp->x1 + 12; i < tmp->x2 - 10; i++)
				for (int j = 0; j < 18; j++)
					if (gfxObject.PutPixel(i, tmp->y + j + 8, 200, 0, 0, tmp->trans / 100, 50) == 2 && tmp->trans >= 15 && tDes.ticTic(250))
					{
						tDes.start();
						health -= laserDam;
					}
			display(9, tmp->x1, tmp->y, 1, 100, 1);
			display(9, tmp->x2, tmp->y, -1, 100, 1);
		}
		else
		{
			for (int i = tmp->x1; i < tmp->x2; i++)
				for (int j = 0; j < 18; j++)
					if (gfxObject.PutPixel(tmp->y + j + 8, i + 5, 200, 0, 0, tmp->trans / 100, 50) == 2 && tmp->trans >= 15&&tDes.ticTic(250))
					{
						tDes.start();
						health -= laserDam;
					}
			display(11, tmp->y, tmp->x1, 1, 100, 1);
			display(12, tmp->y, tmp->x2,1, 100, 1);
		}
		if (tmp->trans == 21)
			tmp->sndPlay = false;
		tmp = tmp->next;
	}
}

void engine::mainCharacter()
{
	//To Do the Collision Detection
	snd.stop(11);
	if (!duck)
	{
		display(2, chX + 55, chY + 20, 1, 0, 0, detectBody);
		display(3, chX + 65, chY + 150, 1, 0, 0, detectVert);

		if (armDis&&!relexing)
		{
			if (key(32) && heroCanFire)
			{
				if (fireType == 2 && motaGola == false)
				{
					newHBeam(2, chX + armFixX, chY + armFixY, dir * 3);
					motaGola = true;
					snd.play(7, 0);
					heroCanFire = false;
					heroFire = true;
					tHero.start();
				}
				else if (fireType == 1)
				{
					newHBeam(1, chX + armFixX, chY + armFixY, dir * 3);
					snd.play(4, -100);
					heroCanFire = false;
					heroFire = true;
					tHero.start();
				}
			}
			if (heroFire)
			{
				if (tHero.ticTic(180))
				{
					heroCanFire = true;
					heroFire = false;
				}
				if (dir == 1)
					animate(6, 0, 20, chX + armFixX, chY + armFixY - 4, 1, dir, 2);
				else
					animate(6, 0, 20, chX - armFixX + 170, chY + armFixY - 4, 1, dir, 2);
			}
			else if (dir == 1)
				display(1, chX + armFixX, chY + armFixY, dir, 100, 2);//Firing *******************************************
			else if (dir == -1)
				display(1, chX + 170 - armFixX, chY + armFixY, dir, 100, 2);
		}
		if (detectVert[1] == true || jumpOff)
		{
			if ((key('s')||key(40))&&!jumpOff)
				duck = true;
			if (falling)
			{
				falling = false;
				char* detectTmp = new char[256];
				display(3, chX + 65, chY + 150, 1, 0, 0, detectTmp);
				while (detectTmp[1])
				{
					chY--;
					display(3, chX + 65, chY + 150, 1, 0, 0, detectTmp);
				}
				chY += 2;
				snd.stop(1);
				if (chY - fY_T > 5)
					relexing = true;
				snd.play(2, 0);
			}
			if (jumpOff)
			{
				if (count == 0)
				{
					armDis = false;
					int spTmp;
					if (i < 11)
						spTmp = 60;
					else
						spTmp = 15;
					if (dir == 1)
						jumpOff = animate(2, 0, spTmp, chX, chY, 1, dir, 2);
					else if (dir == -1)
						jumpOff = animate(2, 0, spTmp, chX + 170, chY, 1, dir, 2);
					i++;
					if (!jumpOff)
					{
						chY -= -4;
						count = 1;
						armDis = true;
						i = 0;
					}
					speedDown = 1;
				}
				if (count >= 1)
				{
					jumpOff = true;
					chY -= jumpSpeed;
					count += 0.8;//Decides the interval for which the robo moves upward
					if (jumpSpeed > 0)
						jumpSpeed -= 0.01;
					if (dir == -1)
						animate(7, 0, 41, chX + 170, chY, 1, dir, 2);
					else
						animate(7, 0, 41, chX, chY, 1, dir, 2);
					armFixY = -21;
					armFixX = 8;
				}
				if (count > 10)
				{
					count = 0;
					jumpOff = false;
					jumpSpeed = 1;
					chY -= 10;
					armFixY = -12;
					armFixX = 7;
				}
			}
			else
			{
				if (relexing)
				{
					if (dir == 1)
						relexing = animate(5, 0, 20, chX, chY, 1, dir, 2);
					else if (dir == -1)
						relexing = animate(5, 0, 20, chX + 170, chY, 1, dir, 2);
				}
				else if ((key('w') || key(38)) && !jumpOff)
				{
					jumpOff = true;
					snd.stop(0);
					snd.play(3, -1000);
				}
				else if (key('a') || key(37))
				{
					dir = -1;
					if (detectBody[0] != -1)
						chX -= speedF*cntrlF;
					animate(1, 0, 41, chX + 170, chY, 1, dir, 2);
					armFixY = 4;
					armFixX = 1;
					snd.play(0, -2000);
				}
				else if (key('d') || key(39))
				{
					dir = 1;
					if (detectBody[0] != -2)
						chX += speedF*cntrlF;
					animate(1, 0, 41, chX, chY, 1, dir, 2);
					armFixY = 4;
					armFixX = 1;
					snd.play(0, -2000);
				}
				else if (1)
				{
					snd.stop(0);
					if (dir == -1)
						animate(0, 0, 41, chX + 170, chY, 1, dir, 2, detect);
					else
						animate(0, 0, 41, chX, chY, 1, dir, 2, detect);
					armFixY = 4;
					armFixX = 2;
				}
			}

		}
		else if (!jumpOff)
		{
			snd.stop(0);
			if (key('a') || key(37))
				dir = -1;
			else if (key('d') || key(39))
				dir = 1;
			if (!falling)
				fY_T = chY;
			falling = true;
		}
		if (falling)
		{
			if (key(16))
			{
				if (detectBody[255] != -1&&chY>0)
					chY -= speedUp*cntrlF;
				boostIncrease = true;
				if (speedUp < 1.2)
					speedUp += 0.005;
				if (dir == 1)
					animate(8, 0, 41, chX, chY + 8, 1, dir, 2);
				else if (dir == -1)
					animate(8, 0, 41, chX + 170, chY + 8, 1, dir, 2);
				speedDown = 0;
				snd.play(1, -1000);
			}
			else
			{
				speedUp = 0.5;
				boostIncrease = false;
			}
			if (key('w') || key(38))
			{
				if (!key(16))
					snd.play(1, -2000);
				if ((key('a') || key(37)) && !boostIncrease)
				{
					animate(3, 0, 41, chX + 170, chY + 8, 1, dir, 2);
					fly = true;
				}
				else if ((key('d') || key(39)) && !boostIncrease)
				{
					animate(3, 0, 41, chX, chY + 8, 1, dir, 2);
					fly = true;
				}
				else if (!boostIncrease)
				{
					if (dir == 1)
					{
						animate(3, 0, 41, chX, chY + 8, 1, dir, 2);
						fly = true;
					}
					else if (dir == -1)
					{
						animate(3, 0, 41, chX + 170, chY + 8, 1, dir, 2);
						fly = true;
					}
				}
				if (!key(16))
					chY += sin(flySine)*0.1;
				flySine += 0.2;
				armFixY = -12;
				armFixX = 7;
				speedDown = 0.2;
			}
			else
			{
				if (!key(16))
					snd.stop(1);
				chY += speedDown*cntrlF;
				if (speedDown < 3)
					speedDown += 0.07;
				fly = false;
				armFixY = -10;
				armFixX = 8;
			}
			if (dir == 1 && !fly&&!boostIncrease)
				animate(4, 0, 41, chX, chY + 10, 1, dir, 2, detect);
			else if (dir == -1 && !fly&&!boostIncrease)
				animate(4, 0, 41, chX + 170, chY + 10, 1, dir, 2, detect);
		}
		if ((detectVert[1] == false || jumpOff || relexing) && detectBody[0] == false)
		{
			if (relexing)
				speedF = 0.4;
			if (fly)
				speedF = 0.7;
			speedF = 1;
		}
		if (detectVert[1] == false)
		{
			if ((key('a') || key(37)) && detectBody[0] != -1)
			{
				chX -= speedF*cntrlF;
				dir = -1;
			}
			else if ((key('d') || key(39)) && detectBody[0] != -2)
			{
				chX += speedF*cntrlF;
				dir = 1;
			}
		}
		
	}
	else if ((key('s') || key(40))&&!duckU)
	{
		if (duckP)
		{
			if (key(32) && heroCanFire)
			{
				if (fireType == 2 && motaGola == false )
				{
					newHBeam(2, chX + armFixX , chY +41, dir * 3);
					motaGola = true;
					snd.play(7, 0);
					heroCanFire = false;
					heroFire = true;
					tHero.start();
				}
				else if (fireType == 1 )
				{
					newHBeam(1, chX + armFixX, chY +41, dir * 3);
					snd.play(4, -100);
					heroCanFire = false;
					heroFire = true;
					tHero.start();
				}
			}
			if (heroFire)
			{
				if (tHero.ticTic(180))
				{
					heroCanFire = true;
					heroFire = false;
				}
				if (dir == 1)
					animate(6, 0, 20, chX + armFixX, chY - 4 + 40, 1, dir, 7);
				else
					animate(6, 0, 20, chX - armFixX + 170, chY - 4 + 40, 1, dir, 7);
			}
			else if (dir == 1)
				display(1, chX + armFixX, chY + 41, dir, 100, 7);//Firing *******************************************
			else if (dir == -1)
				display(1, chX + 170 - armFixX, chY + 41, dir, 100, 7);
		}
		if (key('a')||key(37))
			dir = -1;
		else if (key('d')||key(39))
			dir = 1;
		if (dir == 1)
		{
			if (!duckP)
				duckP = !animate(13, 0, 0, chX, chY, 1, dir,7);
			else
				display(13, chX, chY, dir, 100, 7);
		}
		else if (dir == -1)
		{
			if (!duckP)
				duckP = !animate(13, 0, 0, chX+170, chY, 1, dir,7);
			else
				display(13, chX + 170, chY, dir, 100, 7);
		}
		//To enable firing while ducked
		
	}
	else
	{
		if (duckP)
		{
			duckU = true;
			duckP = false;
		}
		if (dir==1)
			duck = duckU = animate(14, 0, 0, chX, chY,1,1,7);
		else if (dir==-1)
			duck = duckU = animate(14, 0, 0, chX+170, chY,1,dir,7);
	}


	if (key('z') && typeCng.ticTic(500) != 0)  //To change the fireType of the Robo
	{
		typeCng.start();
		if (fireType == 1)
			fireType = 2;
		else if (fireType == 2)
			fireType = 1;
	}

}

void engine::newMine(int no,int x, int y,float speed)
{
	mineNode* tmp = mine;
	if (!mine)
	{
		mine = new mineNode;
		mine->no = no;
		mine->x = x;
		mine->y = y;
		mine->speed = speed;
		mine->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new mineNode;
		tmp = tmp->next;
		tmp->no = no;
		tmp->x=x;
		tmp->y = y;
		tmp->speed = speed;
		tmp->next = NULL;
	}
}

void engine::compileMine(bool com = true)
{
	mineNode* tmp = mine;
	mineNode* tmp2 = new mineNode;
	int det;
	char* detectB = new char[256];
	memset(detectB, 0, 256);
	while (tmp)
	{

		if (!tmp->ani)
		{
			det = 0;
			while (det != 1 && tmp->set == false)
			{
				det = gfxObject.GtPixel(tmp->x, tmp->y);
				if (det != 1)
					tmp->y++;
			}
			tmp->set = true;//restricts any further change in height
			det = 0;
			if (!tmp->mov) //Detection of Hero Position if in range
			{
				for (int i = 0; i < 1500 && det != 2; i++)
					det = gfxObject.GtPixel(i + tmp->x, tmp->y-50);
				if (det == 2)
				{
					tmp->mov = true;
					tmp->dir = 1;
				}
				det = 0;
				for (int i = 0; i < 1400 && det != 2; i++)
					det = gfxObject.GtPixel(tmp->x - i, tmp->y-50);
				if (det == 2)
				{
					tmp->mov = true;
					tmp->dir = -1;
				}
			}
			else if (tmp->mov)
			{
				snd.play(9, -3000);
				det = 0;
				if (tmp->dir == -1)
					display(10, tmp->x + 20, tmp->y, 1, 0, 0, detectB);
				if (tmp->dir == 1)
					display(10, tmp->x + 70, tmp->y, 1, 0, 0, detectB);
				if (detectB[1]==false)
				{
					tmp->dir *= -1;
				}
				det = 0;
				for (int i = 0; i < 10 && det != 1; i++)		//Detection of wall
				{
					if (tmp->dir == 1)
						det = gfxObject.GtPixel(tmp->x + 60, tmp->y - 20 + i);
					if (tmp->dir == -1)
						det = gfxObject.GtPixel(tmp->x + 20, tmp->y - 20 + i);
					if (det == 1)
					{
						tmp->dir *= -1;
					}
				}
				if (tmp->dir == 1&&com)
				{
					animate(19, tmp->no, 41, tmp->x, tmp->y - 65, 1, 1, 6, detectB);
					tmp->x += tmp->speed*3;
				}
				if (tmp->dir == -1&&com)
				{
					animate(20, tmp->no, 41, tmp->x, tmp->y - 65, 1, 1, 6, detectB);
					tmp->x -= tmp->speed*3;
				}
			}
			if (!tmp->mov)
				display(16, tmp->x, tmp->y - 65, 1, 100, 6, detectB);
		}
		else if (tmp->ani&&!tmp->des)  //Blast animation
		{
			tmp->des = !animate(21, tmp->no, 41, tmp->x, tmp->y - 65,1,1,6,detectB);
			snd.play(140+tmp->no, -100);
			snd.stop(9);
			if (tmp->des&&!detectB[2]&& !detectB[7])
				score += score / 50 + 50;
		}
		else if (tmp->des)
		{
			snd.stop(140 + tmp->no);
			tmp2->next = tmp->next;
		}
		if ((detectB[7] || detectB[2])&&tmp->ani==NULL)
		{
			tmp->ani = true;
			health -= 30;
		}
		if (detectB[4] == true)
			tmp->health -= 2;
		if (detectB[8]==true)
			tmp->health -= 8;
		if (tmp->health <= 0)
		{
			tmp->ani = true;
		}
		tmp2 = tmp;
		tmp = tmp->next;
	}
}

void engine::newMid(int no, int x, int y, float speed)
{
	midNode* tmp = mid;
	if (!mid)
	{
		mid = new midNode;
		mid->x = x;
		mid->y = y;
		mid->no = no;
		mid->speed = speed;
		mid->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new midNode;
		tmp = tmp->next;
		tmp->x = x;
		tmp->y = y;
		tmp->no = no;
		tmp->speed = speed;
		tmp->next = NULL;
	}
}

void engine::compileMid(bool com)
{
	midNode* tmp = mid;
	char* detectB = new char[256];
	memset(detectB, 0, 256);
	int det;
	while (tmp)
	{
		if(tmp->exist)
		{
			if (!tmp->set)
		{
			while (gfxObject.GtPixel(tmp->x, tmp->y+164) != 1)
				tmp->y++;
			tmp->set = true;
		}
			else
			{
				//To decide direction to move
				det = 0;
				for (int i = 0; i < 600 && det != 1; i++)
					if (gfxObject.GtPixel(tmp->x - i*tmp->dir, tmp->y + 50) == 2)
						{
							det = 1;
						}
				if (det == 1)
					tmp->dir *= -1;
				if (tmp->dir == -1)//Detection of edge
				{
						display(10, tmp->x - 20, tmp->y + 164, 1, 1, 0, detectB);
				}
				if (tmp->dir == 1)
					{
						display(10, tmp->x + 70, tmp->y + 164, 1, 1, 0, detectB);
				}
				if (detectB[1] == false)
					tmp->dir *= -1;
				for (int i = 0; i < 10 && det != 1; i++)		//Detection of wall
				{
					if (tmp->dir == 1)
						det = gfxObject.GtPixel(tmp->x + 60, tmp->y + 50 + i);
					if (tmp->dir == -1)
						det = gfxObject.GtPixel(tmp->x - 20, tmp->y + 50 + i);
					if (det == 1)
						tmp->dir *= -1;
				}
				det = 0;
				if (tmp->dir == 1)//Detects for firing case
					for (int i = 0; i < 800; i++)
					{
					if (gfxObject.GtPixel(tmp->x + 50 + i, tmp->y + 50) == 2)
						tmp->fire = true;

					}
				else
					for (int i = 0; i < 900; i++)
					{
					if (gfxObject.GtPixel(tmp->x - i, tmp->y + 50) == 2)
						tmp->fire = true;

					}
				if (tmp->fire)
				{
					if (tmp->dir == 1)
						tmp->fire = animate(17, tmp->no, 41, tmp->x + 5, tmp->y + 5, 1, tmp->dir, 9, detectB);
					else if (tmp->dir == -1)
						tmp->fire = animate(17, tmp->no, 41, tmp->x + 45, tmp->y + 5, 1, tmp->dir, 9, detectB);
					if (tmp->fire == false)//do fire sound is also going to be here
					{
						if (tmp->dir == 1)
							newEBeam(tmp->x + 80, tmp->y + 73, 3, 2);
						if (tmp->dir == -1)
							newEBeam(tmp->x - 50, tmp->y + 73, -3, 2);
						snd.play(161 + tmp->no, -1000);
					}

				}
				else
				{
					tmp->x += tmp->dir*tmp->speed*2.5;
					if (tmp->dir == 1)
						animate(18, tmp->no, 41, tmp->x, tmp->y + 5, 1, tmp->dir, 9, detectB);
					else if (tmp->dir == -1)
						animate(18, tmp->no, 41, tmp->x + 50, tmp->y + 5, 1, tmp->dir, 9, detectB);
				}
			}
			if (detectB[4])
				tmp->health--;
			if (detectB[8])
				tmp->health -= 4;
			if (tmp->health <= 0)	//Needs to add the health minus for hero
				tmp->exist = false;
			if (detectB[2] && tDes.ticTic(500))
			{
				health -= 5;
				tDes.start();
			}
		}
		else
		{
			if (tmp->ani)
			{
				if (tmp->dir == 1)
					tmp->ani=animate(22, tmp->no, 41, tmp->x-110, tmp->y+5, 1, tmp->dir);
				else
					tmp->ani=animate(22, tmp->no, 41, tmp->x+160, tmp->y+5, 1, tmp->dir);
				snd.play(180+tmp->no, -100);
				if (!tmp->ani)
					score += score / 100 + 20;
			}
			else
			{
				if (tmp->dir == 1)
					display(17, tmp->x-110, tmp->y+5, 1);
				else
					display(17, tmp->x+160, tmp->y+5, -1);
			}

		}
		tmp = tmp->next;
	}
}

void engine::newHeavy(int no, int x, int y, int del, float speed)
{
	heavyNode* tmp = heavy;
	if (!heavy)
	{
		heavy = new heavyNode;
		heavy->no = no;
		heavy->x = x;
		heavy->y = y;
		heavy->del = del;
		heavy->speed = speed;
		heavy->next = NULL;
	}
	else
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new heavyNode;
		tmp = tmp->next;
		tmp->no = no;
		tmp->x = x;
		tmp->y = y;
		tmp->del = del;
		tmp->speed = speed;
		tmp->next = NULL;
	}
}

void engine::compileHeavy(bool comp)
{
	heavyNode* tmp = heavy;
	char* detectB = new char[256];
	memset(detectB, 0, 256);
	int det = 0;
	while (tmp)
	{
		if (tmp->exist)
		{
			if (!tmp->set)
			{
				while (gfxObject.GtPixel(tmp->x, tmp->y + 153) != 1)
					tmp->y++;
				tmp->set = true;
			}
			if (tmp->dir == -1)//Detection of edge
				display(10, tmp->x + 20, tmp->y + 151, 1, 0, 0, detectB);
			if (tmp->dir == 1)
				display(10, tmp->x + 100, tmp->y + 151, 1, 0, 0, detectB);
			if (detectB[1] == false)
				tmp->dir *= -1;
			det = 0;
			for (int i = 0; i < 10 && det != 1; i++)		//Detection of wall
			{
				if (tmp->dir == 1)
					det = gfxObject.GtPixel(tmp->x + 130, tmp->y + 100 + i);
				if (tmp->dir == -1)
					det = gfxObject.GtPixel(tmp->x, tmp->y + 100 + i);
				if (det == 1)
					tmp->dir *= -1;
			}
			if (tmp->dir == 1)//Detects for firing case
			{
				for (int i = 0; i < 1000; i++)
				{
					if (gfxObject.GtPixel(tmp->x + 100 + i, tmp->y + 50) == 2)
						tmp->fire = true;
					//PutPixel(tmp->x + 100 + i, tmp->y + 50, 255, 0, 0);
				}
				if (tmp->fire == false)
					tmp->mov = true;
			}
			else
			{
				for (int i = 0; i < 1000; i++)
				{
					if (gfxObject.GtPixel(tmp->x - i, tmp->y + 50) == 2)
						tmp->fire = true;
					//	PutPixel(tmp->x - i, tmp->y + 50, 255, 0, 0);
				}
				if (tmp->fire == false)
					tmp->mov = true;
			}
			if (tmp->fire&&tmp->t.ticTic(tmp->del))
			{
				tmp->mov = false;
				snd.play(201 + tmp->no, -100);
				if (tmp->dir == 1)
					tmp->fire = animate(15, tmp->no, 41, tmp->x + 24, tmp->y + 13, 1, 1, 11, detectB);
				else
					tmp->fire = animate(15, tmp->no, 41, tmp->x + 105, tmp->y + 13, 1, -1, 11, detectB);
				if (tmp->fire == false)
				{
					tmp->t.start();
					if (tmp->dir == 1)
						newEBeam(tmp->x+120, tmp->y+86, 2, 3);
					else
						newEBeam(tmp->x+10, tmp-> y+86, -2, 3);
				}
			}
			else if (tmp->mov)
			{
				if (tmp->dir == 1)
					animate(16, tmp->no, 41, tmp->x, tmp->y + 10, 1, 1, 11, detectB);
				else
					animate(16, tmp->no, 41, tmp->x + 130, tmp->y + 10, 1, -1, 11, detectB);
				if (comp)
					tmp->x += tmp->dir*tmp->speed*2;
			}
			else
			{
				if (tmp->dir == 1)
					display(18, tmp->x, tmp->y + 10, 1, 100, 11, detectB);
				else
					display(18, tmp->x + 130, tmp->y + 10, -1, 100, 11, detectB);
			}
			if (detectB[4])
				tmp->health--;
			if (detectB[8])
				tmp->health -= 4;
			if (tmp->health <= 0)
				tmp->exist = false;
		}
		else if (tmp->ani)
		{
			if (tmp->sn)
			{
				snd.play(180 + tmp->no, -100);
				tmp->sn = false;
			}
			if (tmp->dir == 1)
				tmp->ani = animate(23, tmp->no, 41, tmp->x-85, tmp->y, 1, 1);
			else
				tmp->ani = animate(23, tmp->no, 41, tmp->x+200, tmp->y, 1, -1);
			if (!tmp->ani)
				score += score / 25 + 50;
		}
		else
		{
			if (tmp->dir == 1)
				display(19, tmp->x-85, tmp->y);
			if (tmp->dir == -1)
				display(19, tmp->x+200, tmp->y,-1);
		}
		if ((detectB[2] || detectB[7])&&tDes.ticTic(750))
		{
			tDes.start();
			health -= 20;
		}
		tmp = tmp->next;
	}
}

void engine::intDes(int no, int x, int y)
{
	int i = 0,j=0;
	int noT = no;
	while (noT > 0)
	{
		noT /= 10;
		j++;
	}
	if (no == 0)
		display(20 + no % 10, x +15, y, 1.5);
	while (no>0)
	{
		display(20 + no % 10, x-(i-j)*19, y,1.5);
		i++;
		no /= 10;
	}
}

void engine::disHud()
{
	leftT.start();
	display(32, 68, 8, 1, 100, 13);
	for (int j = 7+40-healthTmp*40/100; j < 50; j++)
	{
		for (int i = 0; i < 100; i++)
		{
			if (gfxObject.GtPixel(i + 50, j) == 13)
				PutPixel(i + 50, j, 50, 50, 255);
		}
	}
	display(31, 0, -4);
	intDes(score, 1000, -2);
	intDes(timeLeft-leftT.elapsed()/1000, 1650, -4);
	intDes(level, 600, -4);
	leftT.start();
	tH.start();
	if (healthTmp>health&&tH.ticTic(0 / (healthTmp - health)))
	{
		healthTmp -= 2;
		snd.play(10, 0);
	}
	if (fireType == 1)
		display(54, 350, 0);
	else if (fireType == 2)
	{
		if (motaGola)
			display(55, 350, 2, 1, 101);
		else
			display(55, 350, 2);
	}
}

int engine::button(int a[])
{
	char* detectB = new char[256];
	if (a[8] >=1)
	{
		display(33, a[0], a[1], 1, 100, 0, detectB);
		if (detectB[2] || detectB[7])
		{
			if (detectB[7])
				tSit.start();
			if (tSit.ticTic(1000)==1)
				return 1;
		}
	}
	if (a[8] >=2)
	{
		display(34, a[2], a[3], 1, 100, 0, detectB);
		if (detectB[2] || detectB[7])
		{
			if (detectB[7])
				tSit.start();
			if (tSit.ticTic(1000)==1)
				return 2;
		}
	}
	if (a[8] >= 3)
	{
		display(35, a[4], a[5], 1, 100, 0, detectB);
		if (detectB[2] || detectB[7])
		{
			if (detectB[7])
				tSit.start();
			if (tSit.ticTic(1000)==1)
				return 3;
		}
	} 
	if (a[8] >= 4)
	{
		display(36, a[6], a[7], 1, 100, 0, detectB);
		if (detectB[2] || detectB[7])
		{
			if (detectB[7])
				tSit.start();
			if (tSit.ticTic(1000)==1)
				return 4;
		}
	}
	return 0;
}

void engine::reset()
{
	while (mine)
	{
		delete[]mine;
		mine = NULL;
	}
	while (mid)
	{
		delete[]mid;
		mid = NULL;
	}
	while (turr)
	{
		delete[]turr;
		turr = NULL;
	}
	while (eBeam)
	{
		delete[]eBeam;
		eBeam = NULL;
	}
	while (eLaser)
	{
		delete[]eLaser;
		eLaser = NULL;
	}
	while (heavy)
	{
		delete[]heavy;
		heavy = NULL;
	}
	while (hBeam)
	{
		delete[]hBeam;
		hBeam = NULL;
	}

}

void engine::pauseTimer()
{
	turrent* tmp1 = turr;
	while (tmp1)
	{
		tmp1->ti.pause();
		tmp1 = tmp1->next;
	}
	eLaserNode* tmp2 = eLaser;
	while (tmp2)
	{
		tmp2->on.pause();
		tmp2->off.pause();
		tmp2->r.pause();
		tmp2->r2.pause();
		tmp2 = tmp2->next;
	}
	heavyNode* tmp3 = heavy;
	while (tmp3)
	{
		tmp3->t.pause();
		tmp3 = tmp3->next;
	}
	tHero.pause();
	typeCng.pause();
	tDes.pause();
	tH.pause();
}

void engine::resumeTimer()
{
	turrent* tmp1 = turr;
	while (tmp1)
	{
		tmp1->ti.resume();
		tmp1 = tmp1->next;
	}
	eLaserNode* tmp2 = eLaser;
	while (tmp2)
	{
		tmp2->on.resume();
		tmp2->off.resume();
		tmp2->r.resume();
		tmp2->r2.resume();
		tmp2 = tmp2->next;
	}
	heavyNode* tmp3 = heavy;
	while (tmp3)
	{
		tmp3->t.resume();
		tmp3 = tmp3->next;
	}
	tHero.resume();
	typeCng.resume();
	tDes.resume();
	tH.resume();
}

int engine::paused()
{
	leftT.pause();
	pauseTimer();
	snd.play(11, 0);
	int xM = 800, yM = 400;
	char* detectB = new char[256];
	display(15, key('x'), key('y'), 1, 1, 1);
	for (int i = 0; i < 4; i++)
	{
		display(45 + i, xM, yM + i * 100, 1, 0, 0, detectB);
		if (detectB[1] == true)
		{
			display(43, xM, yM + i * 100 + 10);
			display(45 + i, xM - 10, yM - 10 + i * 100);
			if (key('l'))
			{
				snd.stop(11);
				resumeTimer();
				return i + 1;
			}
		}
		else
		{
			display(43, xM, yM + i * 100 + 5);
			display(45 + i, xM, yM + i * 100);
		}
	}
	display(44, key('x'), key('y'));
	return -1;
}

void engine::centralControl()
{
   	snd.play(12 + level % 6, -1000);
	if (firstQ)
	{
		static float tmpTran = 50;
		tmpTran += 0.5;
		display(70 + level, 0, 50, 1, 100);
		display(64, 500, 950, 1, (int)tmpTran%100);
		if (key(' '))
		{
			firstQ = false;
			lState->reset();
		}
	}
	else if ((key('q') || key('Q')) && !firstQ)
	{
		display(70 + level, 100, 50, 1, 100);
		pauseTimer();
		if (!rQ)
		{
			snd.stopa();
			for (int k = 1; k < 6; k++)
				snd.stop(11 + k);
		}
		rQ = true;
	}
	else if (rQ)
	{
		rQ = false;
		resumeTimer();
		snd.resume();
		for (int k = 1; k < 6; k++)
			snd.stop(11 + k);
	}
	else
	{
		display(110+level, 0, 0, 1, 100, 1);
		compileELaser();
		mainCharacter();
		compileELaser();
		compileHBeam(false);
		compileMid();
		compileHeavy();
		compileMine();
		compileHBeam();
		compileEBEAM();
		compileTurrent();
		answer=button(butPos);
	}
	disHud();
	display(44, key('x'), key('y'),1);
}

int engine::menu()
{
	snd.play(11, 0);
	int xM = 800, yM = 400;
	char* detectB = new char[256];
	display(15, key('x'), key('y'), 1,1, 1);
	for (int i = 0; i < 4; i++)
	{
		display(38 + i, xM, yM + i * 100,1,0,0,detectB);
		if (detectB[1]==true)
		{
			display(43, xM, yM + i * 100+10);
			display(38 + i, xM - 10, yM - 10 + i * 100);
			if (key('l'))
			{
				snd.stop(11);
				return i + 1;
			}
		}
		else
		{
			display(43, xM, yM + i * 100 + 5);
			display(38 + i, xM, yM + i * 100);			
		}
	}		
	animate(25, 0, 24, 300, 0);
	display(44, key('x'), key('y'));
	return 0;
}

int engine::recordedAns(int answer)
{
	if (answer != corAns)
	{
		display(67, 100, 200);
		return restart();
	}
	else
	{
		display(90 + level, 0, 0);
		if (key(' '))
		{
			answer = 0;
			level++;
			score += score*0.2;
			oldScore = score;
			intitLevel();
		}
		
	}
	return 0;
}

int engine::restart()
{

	char* detectB = new char[256];
	display(15, key('x'), key('y'), 1, 1, 1);
	display(38, 600, 900, 1, 0, 0, detectB);
	if (detectB[1] == true)
	{
		display(43, 600, 900 + 10);
		display(46, 600 - 10, 900 - 10);
		if (key('l'))
			return 1;
	}
	else
	{
		display(43, 600, 900 +  5);
		display(46, 600, 900);
	}
	display(38, 1000, 900, 1, 0, 0, detectB);
	if (detectB[1] == true)
	{
		display(43, 1000, 900 + 10);
		display(41, 1000-10, 900-10);
		if (key('l'))
			return 2;
	}
	else
	{
		display(43, 1000, 900 + 5);
		display(41, 1000, 900);
	}
	display(44, key('x'), key('y'));
}

void engine::intitLevel()
{
	lState->reset();
	score = oldScore;
	health = healthTmp = 100;
	reset();
	firstQ = true;
	pauseTimer();
	snd.stopa();
	for (int i = 1; i < 6; i++)
		snd.stop(11 + i);
	answer = 0;
	motaGola = false;
	laserDam = 10;
	switch (level)
	{
	case 1:
		chX = 200;
		chY = 800;
		timeLeft = 240;
		leftT.start();
		leftT.reset();

		//All enemies to be created here
		corAns = 2;//CorrectAnswer
		newTurrent(1, 20, 200, 3000, 10, 1);
		newELaser(430, 590, 1690, 1000, 3000, -1);
		newELaser(100, 250, 1600, 1000, 4000, -1);
		newMine(1, 200, 100, 1);
		newMine(2, 600, 100, 2);
		newMine(3, 200, 680, 2);
		butPos[0] = 1760;
		butPos[1] = 535;
		butPos[2] = 1790;
		butPos[3] = 190;
		butPos[4] = 0;
		butPos[5] = 0;
		butPos[6] = 0;
		butPos[7] = 0;
		butPos[8] = 2;
		break;
	case 2:
		chX = 100;
		chY = 200;
		timeLeft = 180;
		butPos[0] = 60;
		butPos[1] = 770;
		butPos[2] = 1350;
		butPos[3] = 760;
		butPos[4] = 1765;
		butPos[5] = 765;
		butPos[6] = 1765;
		butPos[7] = 180;
		butPos[8] = 4;
		corAns = 3;//CorrectAnswer
		newELaser(512, 782, 385, 5000, 3000, -1);
		newELaser(512, 782, 575, 5000, 3000, -1);
		newELaser(1650, 1920, 490, 5000, 3000);
		newTurrent(1, 18, 610, 3000, 2);
		newTurrent(2, 1450, 625, 3000, 2,-1);
		newMid(0,600,100,3);
		newHeavy(0, 1000, 100, 1000, 4);
		newMine(1, 1100, 800, 2);
		newMine(2, 950, 170, 3);
		newMine(3, 1200, 170, 2);
		leftT.start();
		leftT.reset();
		break;
	case 3:	chX = 100;
		chY = 100;
		butPos[0] = 100;
		butPos[1] = 950;
		butPos[2] = 1750;
		butPos[3] = 200;
		butPos[8] = 2;
		newELaser(1500, 1700, 435, 3000, 10000, 0);
		newELaser(925, 1265, 240, 1000, 500, 0);
		newELaser(330, 635, 820, 1000, 500, 0);
		newELaser(50, 250, 1550, 3000, 10000, -1);
		newHeavy(1, 1700, 90, 500, 2);
		newMid(1, 1000, 850, 3);
		newMine(1, 900, 900, 3);
		newMine(2, 700, 900, 3);
		corAns = 1;
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 4:
		chX = 1000;
		chY = 850;
		butPos[0] = 60;
		butPos[1] = 600;
		butPos[2] = 1800;
		butPos[3] = 610;
		butPos[4] = 1260;
		butPos[5] = 200;
		butPos[6] = 600;
		butPos[7] = 200;
		butPos[8] = 4;
		timeLeft = 180;
		newMine(1,600,720,2);
		newMine(2 , 1340, 720, 2);
		newELaser(845, 1115, 210, 3000, 3000, -1);
		newELaser(845, 1115, 1710, 3000, 4000, -1);
		newELaser(910, 1130, 500, 4000, 5000, 0);
		newHeavy(1,300,300,500,3);
		newHeavy(2, 1500, 300, 500, 3);
		newTurrent(1,1900,350,500,3,-1);
		newTurrent(1, 20, 350, 500, 3, 1);
		corAns = 3;
		leftT.start();
		leftT.reset();
		break;
	case 5:
		chX = 800;
		chY = 800;
		butPos[0] = 600;
		butPos[1] = 150;
		butPos[2] = 800;
		butPos[3] = 150;
		butPos[4] = 1100;
		butPos[5] = 150;
		butPos[6] = 1300;
		butPos[7] = 150;
		butPos[8] = 4;
		corAns = 4;
		newMine(1, 200, 100, 1);
		newMine(2, 600, 100, 2);
		newMine(3, 200, 680, 2);
		newTurrent(1, 20, 200, 3000, 10, 1);
		newELaser(430, 590, 1690, 1000, 3000, -1);
		newELaser(100, 250, 1600, 1000, 4000, -1);
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 6:
		chX = 900;
		chY = 425;
		butPos[0] = 400;
		butPos[1] = 140;
		butPos[2] = 950;
		butPos[3] = 140;
		butPos[8] = 2;
		corAns = 2;
		newTurrent(1,20,300,2000,2);
		newTurrent(1, 20, 300, 2000, 2);
		newTurrent(1, 520, 480, 2000, 2,-1);
		newMid(1, 900, 840, 4);
		newMid(2, 1000, 20, 4);
		newHeavy(1, 1000, 630, 1000, 2);
		newELaser(420, 600, 990, 1000, 3000, -1);
		newELaser(420, 600, 1215, 1000, 3000, -1);
		newELaser(240, 820, 825, 3000, 3000, -1);
		newELaser(240, 820, 1360, 3000, 3000, -1);
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 7:
		chX = 900;
		chY = 470;
		butPos[0] = 360;
		butPos[1] = 180;
		butPos[2] = 1800;
		butPos[3] = 940;
		butPos[8] = 2;
		corAns = 1;
		newELaser(15, 215, 250, 3000, 500, 0);
		newELaser(1540, 1900, 810, 3000, 500, 0);
		newMine(1, 500, 810, 2);
		newMine(2, 400, 250, 3);
		newMine(3, 900, 730, 3);
		newTurrent(1, 1900, 200, 750, 5, -1);
		newMid(1, 500, 280, 3);
		newHeavy(1, 900, 670, 1000, 2);
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 8:
		chX = 100;
		chY = 100;
		butPos[1] = 770;
		butPos[2] = 1350;
		butPos[3] = 760;
		butPos[4] = 1765;
		butPos[5] = 765;
		butPos[6] = 1765;
		butPos[7] = 180;
		butPos[8] = 4;
		corAns = 4;
		timeLeft = 180;
		newELaser(512, 782, 385, 5000, 3000, -1);
		newELaser(512, 782, 575, 5000, 3000, -1);
		newELaser(1650, 1920, 490, 5000, 3000);
		newTurrent(1, 18, 610, 3000, 2);
		newTurrent(2, 1450, 625, 3000, 2, -1);
		newMid(0, 600, 100, 3);
		newHeavy(0, 1000, 100, 1000, 4);
		newMine(1, 1100, 800, 2);
		newMine(2, 950, 170, 3);
		newMine(3, 1200, 170, 2);
		leftT.start();
		leftT.reset();
		break;
	case 9:
		chX = 1000;
		chY = 850;
		butPos[0] = 60;
		butPos[1] = 600;
		butPos[2] = 1800;
		butPos[3] = 610;
		butPos[4] = 1260;
		butPos[5] = 200;
		butPos[6] = 600;
		butPos[7] = 200;
		butPos[8] = 4;
		timeLeft = 180;
		newMine(1, 600, 720, 2);
		newMine(2, 1340, 720, 2);
		newELaser(845, 1115, 210, 3000, 3000, -1);
		newELaser(845, 1115, 1710, 3000, 4000, -1);
		newELaser(910, 1130, 500, 4000, 5000, 0);
		newHeavy(1, 300, 300, 500, 3);
		newHeavy(2, 1500, 300, 500, 3);
		newTurrent(1, 1900, 350, 500, 3, -1);
		newTurrent(1, 20, 350, 500, 3, 1);
		corAns = 3;
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 10:
		chX = 170;
		chY = 800;
		butPos[0] = 1000;
		butPos[1] = 150;
		butPos[2] = 400;
		butPos[3] = 150;
		butPos[4] = 1090;
		butPos[5] = 525;
		butPos[8] = 3;
		newTurrent(1, 20, 300, 2000, 2);
		newTurrent(1, 20, 300, 2000, 2);
		newTurrent(1, 520, 480, 2000, 2, -1);
		newMid(2, 1000, 20, 4);
		newHeavy(1, 1000, 600, 1000, 2);
		newELaser(420, 600, 990, 1000, 3000, -1);
		newELaser(420, 600, 1215, 1000, 3000, -1);
		newELaser(240, 820, 825, 3000, 3000, -1);
		newELaser(240, 820, 1360, 3000, 3000, -1);
		corAns = 3;
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 11:
		chX = 1780;
		chY = 850;
		butPos[0] = 160;
		butPos[1] = 140;
		butPos[2] = 880;
		butPos[3] = 140;
		butPos[4] = 1520;
		butPos[5] = 140;
		butPos[8] = 3;
		corAns = 2;
		newTurrent(1, 820, 100, 500, 4,-1);
		newTurrent(2, 20, 300, 500, 4);
		newTurrent(3, 20, 500, 500, 4);
		newTurrent(4, 20, 700, 500, 4);
		newTurrent(5, 20, 900, 500, 4);
		newTurrent(6, 1900, 100, 500, 4,-1);
		newTurrent(7, 1900, 300, 500, 4, -1);
		newTurrent(8, 1900, 500, 500, 4, -1);
		newTurrent(9, 1900, 700, 500, 4, -1);
		newMine(1, 200, 100, 2);
		newMine(2, 500, 800, 3);
		newMine(2, 1000, 800, 4);
		newMid(1, 500, 800, 1);
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 12:
		chX = 1780;
		chY = 850;
		butPos[0] = 160;
		butPos[1] = 140;
		butPos[2] = 630;
		butPos[3] = 140;
		butPos[4] = 1040;
		butPos[5] = 140;
		butPos[6] = 1540;
		butPos[7] = 140;
		butPos[8] = 4;
		corAns = 2;
		newTurrent(1, 560, 200, 500, 4, -1);
		newTurrent(2, 20, 300, 500, 4);
		newTurrent(3, 20, 500, 500, 4);
		newTurrent(4, 20, 700, 500, 4);
		newTurrent(5, 20, 900, 500, 4);
		newTurrent(6, 1900, 100, 500, 4, -1);
		newTurrent(7, 1900, 300, 500, 4, -1);
		newTurrent(8, 1900, 500, 500, 4, -1);
		newTurrent(9, 1900, 700, 500, 4, -1);
		newTurrent(10, 970, 200, 500, 4,-1);
		newTurrent(11, 1470, 200, 500, 4,-1);
		newMine(1, 200, 100, 2);
		newMine(2, 500, 800, 3);
		newMine(2, 1000, 800, 4);
		newMid(1, 500, 800, 1);
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	case 13:
		chX = 890;
		chY = 800;
		butPos[0] = 1100;
		butPos[1] = 930;
		butPos[2] = 700;
		butPos[3] = 930;
		butPos[4] = 400;
		butPos[5] = 930;
		butPos[6] = 1400;
		butPos[7] = 930;
		butPos[8] = 4;
		corAns = 2;
		newELaser(810, 1070, 800, 5000, 2000);
		newELaser(180, 820, 190, 10000, 2000, -1);
		newELaser(180, 820, 1685, 10000, 2000, -1);
		newMine(1, 250, 700, 4);
		newMine(2, 400, 500, 4);
		newMine(3, 500, 200, 4);
		newMine(4, 450, 700, 4);
		newMine(5, 600, 500, 4);
		newMine(6, 700, 200, 4);
		newMine(7, 1200, 700, 4);
		newMine(8, 1400, 500, 4);
		newMine(9, 1500, 200, 4);
		newMine(10, 1450, 700, 4);
		newMine(11, 1600, 500, 4);
		newMine(12, 1350, 200, 4);
		newMine(13, 400, 100, 4);
		newMine(14, 1350, 100, 4);
		newMid(1, 400, 200, 4);
		newMid(2, 500, 420, 4);
		newMid(3, 800, 620, 4);
		newMid(4, 500, 100, 5);
		newMid(5, 1300, 200, 4);
		newMid(6, 1500, 420, 4);
		newMid(7, 1400, 620, 4);
		newMid(8, 1500, 100, 5);
		timeLeft = 240;
		leftT.start();
		leftT.reset();
		break;
	case 14:
		chX = 1500;
		chY = 780;
		timeLeft = 180;
		butPos[0] = 60;
		butPos[1] = 770;
		butPos[2] = 1350;
		butPos[3] = 760;
		butPos[4] = 1765;
		butPos[5] = 765;
		butPos[6] = 1765;
		butPos[7] = 180;
		butPos[8] = 4;
		corAns = 4;//CorrectAnswer
		newELaser(512, 782, 385, 5000, 3000, -1);
		newELaser(512, 782, 575, 5000, 3000, -1);
		newELaser(1650, 1920, 490, 5000, 3000);
		newTurrent(1, 18, 610, 3000, 2);
		newTurrent(2, 1450, 625, 3000, 2, -1);
		newTurrent(3, 1900, 290, 500, 4, -1);
		newTurrent(4, 1900, 375, 500, 4, -1);
		newTurrent(5, 20, 290, 500, 4);
		newTurrent(6, 20, 375, 500, 4);
		newMid(0, 600, 100, 3);
		newHeavy(0, 1000, 100, 1000, 4);
		newHeavy(1, 1000, 650, 1000, 5);
		newHeavy(2, 1000, 100, 1000, 4);
		newMine(1, 1100, 800, 2);
		newMine(2, 950, 170, 3);
		newMine(3, 1200, 170, 2);
		newMine(4, 140, 750, 2);
		newMine(5, 200, 750, 3);
		newMine(6, 1200, 300, 2);
		newMine(7, 1000, 300, 4);
		leftT.start();
		leftT.reset();
		break;
	case 15:
		laserDam = 15;
		chX = 60;
		chY = 860;
		butPos[0] = 400;
		butPos[1] = 930;
		butPos[2] = 800;
		butPos[3] = 930;
		butPos[4] = 1400;
		butPos[5] = 930;
		butPos[6] = 1800;
		butPos[7] = 930;
		butPos[8] = 4;
		newELaser(180, 850, 180, 1000, 500, -1);
		newELaser(180, 1710, 180, 1000, 500);
		newELaser(440, 1900, 400, 1000, 500);
		newELaser(180, 1710, 620, 1000, 500);
		newTurrent(1, 1900, 100, 500, 8, -1);
		newTurrent(2, 200, 250, 500, 8, 1);
		newTurrent(3, 1900,500, 500, 8, -1);
		newTurrent(4, 200, 700, 500, 8, 1);
		newTurrent(5, 1900, 900, 500, 8, -1);
		newMid(1,700,700,5);
		newMid(2, 800, 800, 4);
		newMine(1, 900, 800, 4);
		corAns = 1;
		timeLeft = 180;
		leftT.start();
		leftT.reset();
		break;
	}
}