////////////////////////////////////////////////////////////////////////////////
// Filename: bitmapclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BITMAPCLASS_H_
#define _BITMAPCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <d3dx10math.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: BitmapClass
////////////////////////////////////////////////////////////////////////////////
class BitmapClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	BitmapClass();
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool Initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, int, int);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();
	ID3D11ShaderResourceView** GetPTexture()
	{
		return m_Texture->GetPTexture();
	}
	bool getIsFill()
	{
		return m_isfill;
	}
	void setIsFill(bool is)
	{
		m_isfill = is;
	}
	void setIsFinish(bool is)
	{
		m_IsFinish = is;
	}
	int getX()
	{
		return m_X;
	}
	int getY()
	{
		return m_Y;
	}
	void setX(int x)
	{
		m_X = x;
	}
	void setY(int y)
	{
		m_Y = y;
	}
private:
	bool InitializeBuffers(ID3D11Device*);
	void ShutdownBuffers();
	bool UpdateBuffers(ID3D11DeviceContext*, int, int);
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass* m_Texture;
	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
	bool m_isfill;
	bool m_IsFinish;
	int m_X;
	int m_Y;
};

#endif