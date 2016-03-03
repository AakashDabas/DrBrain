#pragma once
#include<d3d9.h>
#pragma comment(lib,"d3d9.lib")
class gfx
{
public:
	gfx(HWND hwnd,int,int,float,float);
	~gfx();
	void BeginFrame(int level);
	void EndFrame();
	unsigned char PutPixel(int, int, int, int, int, float trans = 1,unsigned char sColor=0);
	unsigned char GtPixel(int x, int y);
	int mod(int, int);
private:
	IDirect3D9 *pDeviceInterface;
	IDirect3DDevice9 *pDevice;
	IDirect3DSurface9 *pSurface;
	D3DLOCKED_RECT backRect;//To get access to the GPU's RAM which contains the buffer to be displayed
	D3DCOLOR* pDisBuffer,*disClear;//The temporary buffer which stores the whole screen output
	D3DCOLOR resetColor;
	unsigned char* bufferChk;
	unsigned long disBufferSize;
	int xLen, yLen;
	float sizeX, sizeY;
};