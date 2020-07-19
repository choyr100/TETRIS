#pragma once

#include <windows.h>
#include "d3dclass.h"
#include "bitmapclass.h"
#include "inputclass.h"
#include "textureshaderclass.h"
#include "blocks.h"
#include "textclass.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "cSound.h"

using namespace std;

class Game
{
public:
	Game()
	{
		for (int i = 0; i < 256; i++)
		{
			iskeydown[i] = false;
			toggle[i] = false;
		}
		m_end_time = 0.f;
		m_Score = 0;
		m_IsEraserSound = false;
		sound = 0;
	}
	Game(D3DClass* D3D, BitmapClass* Bitmap)
	{

	}
	void Initialize();
	void Initialize(bool);
	void Shutdown();
	void setD3D(D3DClass* D3D)
	{
		m_D3D = D3D;
	}
	void setInputClass(InputClass* input)
	{
		m_Input = input;
	}
	void setTexture(ID3D11ShaderResourceView** texture)
	{
		m_texture = texture;
	}
	void setHwnd(HWND* hwnd)
	{
		m_hwnd = hwnd;
	}
	void setTextureShaderClass(TextureShaderClass* TextureShader)
	{
		this->m_TextureShader = TextureShader;
	}
	int getMoveX()
	{
		return m_MoveX;
	}
	int getMoveY()
	{
		return m_MoveY;
	}
	void setBaseViewMatrix(D3DXMATRIX m)
	{
		baseViewMatrix = m;
	}
	void IskeyToggle(unsigned int,int&);
	void Update(float);
	bool Render(D3DXMATRIX, D3DXMATRIX, D3DXMATRIX);

	bool getIsStop()
	{
		return m_IsStop;
	}

	void fileLoad()
	{
		ifstream ifile;
		string filename = "rank.txt";
		string str;
		int _scorereal;
		int _count=0;
		ifile.open(filename.c_str());
		if (!ifile)
		{
			exit(0);
		}
		while (!ifile.eof()) //파일이 끝날때 까지
		{
			ifile >> str;//줄줄이 str에 넣어준다.
			_scorereal = stoi(str); // 문자열로 얻은 값을 float 값으로 변환해준다.

			m_Rank[_count]->SetRankScore(_count + 1, _scorereal, m_D3D->GetDeviceContext(), 400, 20 * (_count + 1));
			_count++;
		}
		ifile.close();

	}

	void fileSave()
	{
		string filename = "rank.txt";
		ofstream ofile;
		ofile.open(filename.c_str());
		if (!ofile)//실패시 종료시킨다.
		{
			cout << "파일을열 수 없습니다" << endl;
			exit(0);
		}
		bool score = false;
		for (int i = 0; i < 10; i++)
		{
			if (m_Rank[i]->getScore()>=m_Score)
			{
				ofile << m_Rank[i]->getScore() << endl;
			}
			else
			{
				if (!score)
				{
					ofile << m_Score << endl;
					score = true;
				}
				else
				{
					ofile << m_Rank[i-1]->getScore() << endl;
				}
			}
		}

		ofile.close();
	}

private:
	InputClass* m_Input;
	D3DClass* m_D3D;
	BitmapClass** m_Bitmap;
	TextureShaderClass* m_TextureShader;
	ID3D11ShaderResourceView** m_texture;
	HWND* m_hwnd;
	bool iskeydown[256];
	bool toggle[256];
	int m_MoveX;
	int m_MoveY;
	int mapwidth;
	int mapheight;
	int screenWidth;
	int screenHeight;
	bool hard;
	int blocktypenum;
	int blocklimitnum;
	Blocks* m_MainBlocks;
	Blocks* m_PrvBlocks;
	Blocks* m_EndBlocks;
	vector<Blocks*> m_ArrayBlocks;
	int m_BlockCount;
	int m_Score;

	cSound* sound;

	TextClass* m_Rank[10];

	TextClass* m_Text;

	TextClass* m_UIText[5];

	bool m_IsEnd;

	bool m_IsPrev;

	bool m_IsStop;

	bool m_StopText;

	float m_cur_ftime;

	float m_end_time;

	D3DXMATRIX baseViewMatrix;

	Blocks* m_Item;

	bool m_IsEraserSound;

};