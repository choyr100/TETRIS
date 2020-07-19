#pragma once

#include "bitmapclass.h"
#include "D3DClass.h"
#include "inputclass.h"
#include "TextureShaderClass.h"

#include "cSound.h"

#include <cstdlib>
#include <ctime>

class Blocks
{
public:
	void Initialize(D3DClass*, int, int, int, TextureShaderClass*, InputClass*, BitmapClass**, bool*, bool*, bool*,cSound**);
	void Shutdown();
	void Updated(int&,int&, int, float);
	bool Render(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);
	bool getIsEnd()
	{
		return m_IsEnd;
	}
	int getMoveX()
	{
		return m_MoveX;
	}
	int getMoveY()
	{
		return m_MoveY;
	}
	void addMoveY()
	{
		++m_MoveY;
	}
	int getBlockType()
	{
		return blocktypenum;
	}
	BitmapClass*** getBlock()
	{
		return m_Block;
	}
	void setMoveX(int x)
	{
		m_MoveX = x;
	}
	void setMoveY(int x)
	{
		m_MoveY = x;
	}
	bool getIsSpeed()
	{
		return m_IsSpeed;
	}
private:
	BitmapClass*** m_Block;
	BitmapClass** m_Map;
	D3DClass* m_D3D;
	TextureShaderClass* m_TextureShader;
	int m_type;
	int size;
	int m_MoveX;
	int m_MoveY;
	int m_Num;
	int mapwidth;
	int mapheight;
	int screenWidth;
	int screenHeight;
	int m_NumX;
	int m_NumY;
	bool* iskeydown;
	bool* toggle;
	int blocktypenum;
	bool* m_Ishard;
	InputClass* m_Input;
	float m_cur_ftime;
	int m_cur_time;
	bool m_IsEnd;
	bool m_IsSpeed;
	cSound** sound;
};