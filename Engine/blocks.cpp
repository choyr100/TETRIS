#include "blocks.h"

Blocks::~Blocks()
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			delete[] m_Block[i][j];
		}
		delete[] m_Block[i];
	}
	delete[] m_Block;
}

void Blocks::Initialize(D3DClass* D3D,int screenWidth,int screenHeight,int type, TextureShaderClass* textureShader, InputClass* input, BitmapClass** map, bool* keydown, bool* tog, bool* ishard, cSound** _sound)
{
	iskeydown = keydown;
	toggle = tog;
	m_Map = map;
	m_Input = input;
	m_D3D = D3D;
	m_MoveX = 5;
	m_MoveY = -3;
	m_type = type;
	mapwidth = 15;
	mapheight = 30;
	screenWidth = 800;
	screenHeight = 600;
	size = 4;
	m_Num = 0;
	blocktypenum = 0;
	m_cur_ftime = 0.f;
	m_cur_time = 0.f;
	m_Ishard = ishard;
	m_IsEnd = false;
	m_IsSpeed = false;
	sound = _sound;
	m_Block = new BitmapClass**[size];
	for (int i = 0; i < size; i++)
	{
		m_Block[i] = new BitmapClass*[size];
	}
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j<size; j++) m_Block[i][j] = new BitmapClass[size];
	}
	WCHAR* str[6] = { L"data/1.jpg",
		L"data/2.jpg",
		L"data/3.jpg",
		L"data/4.jpg" ,
		L"data/5.jpg",
		L"data/fire.jpg" };
	srand((unsigned int)time(NULL));
	int color = rand() % 5;
	if (type == 11) color = 5;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				m_Block[i][j][k].Initialize(D3D->GetDevice(), screenWidth, screenHeight, str[color], 16, 16);
			}
		}
	}
	m_TextureShader = textureShader;
	switch (m_type)
	{
	case 0:
		for (int i = 0; i < size; i++)
		{
			m_Block[i][1][1].setIsFill(true);
			m_Block[i][2][1].setIsFill(true);
			m_Block[i][1][2].setIsFill(true);
			m_Block[i][2][2].setIsFill(true);
		}
		break;
	case 1:
		for (int i = 0; i < size; i++)
		{
			if (i % 2 == 0)
			{
				m_Block[i][0][1].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
			else
			{
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][2][3].setIsFill(true);
			}
		}
		break;
	case 2:
		for (int i = 0; i < size; i++)
		{
			if (i % 2 == 0)
			{
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else
			{
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
		}
		break;
	case 3:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else if(i==1)
			{
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
		}
		break;
	case 4:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
			else if (i == 1)
			{
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
		}
		break;
	case 5:
		for (int i = 0; i < size; i++)//반시계반향 대부분
		{
			if (i % 2 == 0)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
			else
			{
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
		}
		break;
	case 6:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
			else if (i == 1)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
			}
		}
		break;
	case 7:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
			else if (i == 1)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
		}
		break;
	case 8:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
			else if (i == 1)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][2][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
		}
		break;
	case 9:
		for (int i = 0; i < size; i++)
		{
			m_Block[i][2][1].setIsFill(true);
			m_Block[i][3][1].setIsFill(true);
			m_Block[i][1][1].setIsFill(true);
			m_Block[i][2][0].setIsFill(true);
			m_Block[i][2][2].setIsFill(true);
		}
		break;
	case 10:
		for (int i = 0; i < size; i++)
		{
			if (i == 0)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
			}
			else if (i == 1)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
			}
			else if (i == 2)
			{
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][1][1].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
			else if (i == 3)
			{
				m_Block[i][1][0].setIsFill(true);
				m_Block[i][2][0].setIsFill(true);
				m_Block[i][3][0].setIsFill(true);
				m_Block[i][1][2].setIsFill(true);
				m_Block[i][2][2].setIsFill(true);
				m_Block[i][3][2].setIsFill(true);
				m_Block[i][3][1].setIsFill(true);
			}
		}
		break;
	case 11:
		for (int i = 0; i < size; i++)
		{
			m_Block[i][1][1].setIsFill(true);
		}
		break;
	}
}

void Blocks::Shutdown()
{
}

void Blocks::Updated(int& movex, int& movey, int type, float time)
{

	BlockDownUpdated(time);

	if (m_Input->IsKeyDown(VK_SPACE) && !iskeydown[VK_SPACE])
	{
		iskeydown[VK_SPACE] = true;
		toggle[VK_SPACE] = !toggle[VK_SPACE];
		if (!m_IsSpeed)
		{
			if ((*sound) != nullptr) (*sound)->PLAYsound("speed");
			else
			{
				(*sound)->PLAYsound("speed");
			}
		}
		m_IsSpeed = true;
	}
	if (!m_Input->IsKeyDown(VK_SPACE) && iskeydown[VK_SPACE] || toggle[VK_SPACE])
	{
		iskeydown[VK_SPACE] = false;
		toggle[VK_SPACE] = !toggle[VK_SPACE];
	}

	if (m_Input->IsKeyDown(VK_UP) && !iskeydown[VK_UP] && !m_IsSpeed)
	{
		iskeydown[VK_UP] = true;
		toggle[VK_UP] = !toggle[VK_UP];
		blocktypenum++;

		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (m_Block[blocktypenum % 4][j][k].getIsFill())//4x4블락중에서 그려주고 있는 부분
				{
					if ((j + m_MoveX) < 0)
					{
						blocktypenum--;
						return;
					}
					if ((j + m_MoveX) >= 15)
					{
						blocktypenum--;
						return;
					}
					if ((k + m_MoveY) >= 30)
					{
						blocktypenum--;
						return;
					}
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if (m_Map[x][y].getIsFill())
							{
								if ((k + m_MoveY) == y && (j + m_MoveX) == x)
								{
									blocktypenum--;
								}
							}
						}
					}
				}
			}
		}
	}
	if (!m_Input->IsKeyDown(VK_UP) && iskeydown[VK_UP] && !m_IsSpeed)
	{
		iskeydown[VK_UP] = false;
	}
	if (m_Input->IsKeyDown(VK_LEFT) && !iskeydown[VK_LEFT] && !m_IsSpeed)
	{
		iskeydown[VK_LEFT] = true;
		toggle[VK_LEFT] = !toggle[VK_LEFT];
		m_MoveX--;
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (m_Block[blocktypenum % 4][j][k].getIsFill())
				{
					if ((j + m_MoveX) < 0)
					{
						m_MoveX++;
						return;
					}
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if (m_Map[x][y].getIsFill())
							{
								if ((k + m_MoveY) == y && (j + m_MoveX) == x)
								{
									m_MoveX++;
								}
							}
						}
					}
				}
			}
		}
	}
	if (!m_Input->IsKeyDown(VK_LEFT) && iskeydown[VK_LEFT] && !m_IsSpeed)
	{
		iskeydown[VK_LEFT] = false;
	}
	if (m_Input->IsKeyDown(VK_RIGHT) && !iskeydown[VK_RIGHT] && !m_IsSpeed)
	{
		iskeydown[VK_RIGHT] = true;
		toggle[VK_RIGHT] = !toggle[VK_RIGHT];
		m_MoveX++;
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (m_Block[blocktypenum % 4][j][k].getIsFill())
				{
					if ((j + m_MoveX) >= 15)
					{
						m_MoveX--;
						return;
					}
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if (m_Map[x][y].getIsFill())
							{
								if ((k + m_MoveY) == y && (j + m_MoveX) == x)
								{
									m_MoveX--;
								}
							}
						}
					}
				}
			}
		}
	}
	if (!m_Input->IsKeyDown(VK_RIGHT) && iskeydown[VK_RIGHT] && !m_IsSpeed)
	{
		iskeydown[VK_RIGHT] = false;
	}
	if (m_Input->IsKeyDown(VK_DOWN) && !iskeydown[VK_DOWN] && !m_IsSpeed)
	{
		iskeydown[VK_DOWN] = true;
		toggle[VK_DOWN] = !toggle[VK_DOWN];
		m_MoveY++;
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				if (m_Block[blocktypenum % 4][j][k].getIsFill())
				{
					if ((k + m_MoveY) >= 30)
					{
						m_MoveY--;
						return;
					}
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if (m_Map[x][y].getIsFill())
							{
								if ((k + m_MoveY) == y && (j + m_MoveX) == x)
								{
									m_MoveY--;
									m_IsEnd = true;
									return;
								}
							}
						}
					}
				}
			}
		}
	}
	if (!m_Input->IsKeyDown(VK_DOWN) && iskeydown[VK_DOWN] && !m_IsSpeed)
	{
		iskeydown[VK_DOWN] = false;
	}
	m_cur_ftime = time;
}
bool Blocks::Render(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix)
{

	for (int j = 0; j < size; j++)
	{
		for (int k = 0; k < size; k++)
		{
			if (m_Block[blocktypenum % 4][j][k].getIsFill())
			{
				m_Block[blocktypenum % 4][j][k].Render(m_D3D->GetDeviceContext(), (j + m_MoveX) * 16, (k + m_MoveY) * 16);
				m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Block[blocktypenum % 4][j][k].GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Block[blocktypenum % 4][j][k].GetTexture());
			}
		}
	}
	return true;
}

void Blocks::BlockDown()
{
	m_MoveY++;
	for (int j = 0; j < size; j++)
	{
		for (int k = 0; k < size; k++)
		{
			if (m_Block[blocktypenum % 4][j][k].getIsFill())//그려주는 부분이 
			{
				if ((k + m_MoveY) >= 30)
				{
					m_MoveY--;
					m_IsEnd = true;
					return;
				}
				for (int x = 0; x < mapwidth; x++)
				{
					for (int y = 0; y < mapheight; y++)
					{
						if (m_Map[x][y].getIsFill())
						{
							if ((k + m_MoveY) == y && (j + m_MoveX) == x)
							{
								m_MoveY--;
								m_IsEnd = true;
								return;
							}
						}
					}
				}
			}
		}
	}
}

void Blocks::BlockDownUpdated(float time)
{
	if (!*m_Ishard)
	{
		if ((((int)m_cur_time - (int)time) == -1) || m_IsSpeed)
		{
			BlockDown();
		}
	}
	else
	{
		if (!((m_cur_time - time) < 0.01f && (m_cur_time - time) > -0.01f) || m_IsSpeed)
		{
			BlockDown();
		}
	}
	m_cur_time = time;
}
