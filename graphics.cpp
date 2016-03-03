#include "graphics.h"
gfx::gfx(HWND hWnd,int xlen,int ylen,float sX,float sY)
	:
	pDeviceInterface(NULL),
	pDevice(NULL),
	pSurface(NULL),
	pDisBuffer(NULL)
{
	sizeX = sX;
	sizeY = sY;
	xLen = xlen;
	yLen = ylen;
	disBufferSize = xLen*yLen*sizeX*sizeY;
	pDisBuffer = new D3DCOLOR[disBufferSize];
	disClear = new D3DCOLOR[disBufferSize];
	resetColor = D3DCOLOR_XRGB(10, 150, 250);
	for (int i = 0; i < xLen*yLen; i++)
		disClear[i] = resetColor;
	bufferChk = new unsigned char[disBufferSize];
	pDeviceInterface = Direct3DCreate9(D3D_SDK_VERSION);
	D3DPRESENT_PARAMETERS para;
	ZeroMemory(&para, sizeof(para));
	para.Windowed = true;
	para.BackBufferFormat = D3DFMT_UNKNOWN;
	para.Flags = D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	para.SwapEffect = D3DSWAPEFFECT_DISCARD;
	para.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	pDeviceInterface->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING | D3DCREATE_PUREDEVICE, &para, &pDevice);
	pDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &pSurface);
	backRect.pBits = NULL;
}

gfx::~gfx()
{
	if (pDeviceInterface)
	{
		pDeviceInterface->Release();
		pDeviceInterface = NULL;
	}
	if (pDevice)
	{
		pDevice->Release();
		pDevice = NULL;
	}
	if (pSurface)
	{
		pSurface->Release();
		pDevice = NULL;
	}
	if (pDisBuffer)
	{
		delete pDisBuffer;
		pDisBuffer = NULL;		
	}

}

void gfx::BeginFrame(int level)
{	
	//These two methods of clearing the backBuffer reduced FPS by 7 and one is not good. That's why rejected.
	//resetColor = D3DCOLOR_XRGB(level*10,150+level*5,250-level*10);
	//for (int i = 0; i < xLen*yLen; i++)
	//	pDisBuffer[i] = resetColor;
	//memset(pDisBuffer, 200,sizeof(D3DCOLOR)*disBufferSize);
	memcpy(pDisBuffer, disClear, sizeof(D3DCOLOR)*disBufferSize);
	memset(bufferChk, 0, sizeof(unsigned char)*disBufferSize);
}

void gfx::EndFrame()
{
	pSurface->LockRect(&backRect, NULL, NULL);
	for (int y = 0; y < yLen; y++)
	{
		memcpy(&((BYTE*)backRect.pBits)[(backRect.Pitch)*y], &pDisBuffer[xLen*y], sizeof(D3DCOLOR)*xLen);
	} 
	pSurface->UnlockRect();
	pDevice->Present(NULL, NULL, NULL, NULL);
}

int gfx::mod(int x, int y)
{
	if (x > y)
		return x - y;
	else
		return y - x;
}


unsigned char gfx::PutPixel(int x, int y, int r, int g, int b, float trans,unsigned char sColor)
{
	x *= xLen/1920.0;
	y *= yLen / 1020.0;
	if (x >= 0 && x < xLen && y >= 0 && y < yLen)
	{
		if (trans != 1)
		{
			D3DCOLOR color;
			color = pDisBuffer[xLen*y + x];
			BYTE rC = (int)((color >> 16) & 0xFF);
			BYTE gC = (color >> 8) & 0xFF;
			BYTE bC = color & 0xFF;
			r = rC + (r - rC)*trans;
			g = gC + (g - gC)*trans;
			b = bC + (b - bC)*trans;
		}
		pDisBuffer[y*xLen + x] = D3DCOLOR_XRGB(r, g, b);
		if (sColor != 0&&trans!=0)
		{
			unsigned char ret = bufferChk[y*xLen + x];
			bufferChk[y*xLen + x] = sColor; //Color of the background buffer used for checking collisions
			return ret;
		}
		else
		{
			return bufferChk[y*xLen + x];
		}
	}
	return 0;
}

unsigned char gfx::GtPixel(int x, int y)
{
	x *= xLen / 1920.0;
	y *= yLen / 1020.0;
	if (x >= 0 && x < xLen && y >= 0 && y < yLen)
		return (bufferChk[y*xLen+x]);
	return 0;
}