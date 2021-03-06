#include "stdafx.h"
#include "ULib_OpenGLCanvas.hpp"
#include "ULib_D3D9Canvas.hpp"
#include "ULib_VideoCanvas.hpp"
#include "ULib_BaseCanvas.hpp"

ULib_BaseCanvas* ULib_BaseCanvas::CreateInstance(CONST CHAR *device, int index)
{
	if (!ppULib_BaseCanvas)
	{
		ppULib_BaseCanvas = new (ULib_BaseCanvas *[MAX_SF_SIZE]);
		for(int i = 0; i < MAX_SF_SIZE; ++i) ppULib_BaseCanvas[i] = NULL;
	}
	if (ppULib_BaseCanvas[index])
	{
		delete ppULib_BaseCanvas[index];
	}
	if (0 == strcmp("opengl", device))
	{
		return ppULib_BaseCanvas[index] = new ULib_OpenGLCanvas ();
	}
	else if(0 == strcmp("dx9", device))
	{
		return ppULib_BaseCanvas[index] = new ULib_D3D9Canvas ();
	}
	else if (0 == strcmp("directdraw", device))
	{
		return ppULib_BaseCanvas[index] = new ULib_VideoCanvas();
	}
	else
	{
		// Not supported.
		return NULL;
	}
}

ULib_BaseCanvas* ULib_BaseCanvas::Instance(int index)
{
	if (ppULib_BaseCanvas && ppULib_BaseCanvas[index])
	{
		return ppULib_BaseCanvas[index];
	}else
	{
		return NULL;
	}
}

HRESULT ULib_BaseCanvas::DestoryInstance(int index)
{
	if (ppULib_BaseCanvas[index])
	{
		ppULib_BaseCanvas[index]->Release();
		delete ppULib_BaseCanvas[index];
		ppULib_BaseCanvas[index] = NULL;
		return S_OK;
	}else
	{
		return E_FAIL;
	}
}

ULib_BaseCanvas **ppULib_BaseCanvas = NULL;