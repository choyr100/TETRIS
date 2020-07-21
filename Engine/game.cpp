#include "game.h"

void Game::Initialize()
{
	sound = 0;
	m_Text = 0;
	m_MoveX = 0;
	m_MoveY = 0;
	mapwidth = 15;
	mapheight = 30;
	screenWidth = 800;
	screenHeight = 600;
	m_ftime = 0.f;
	hard = false;
	blocktypenum = 0;
	m_BlockCount = 0;
	m_EndBlocks = 0;
	m_IsEnd = false;
	m_IsPrev = false;
	m_IsStop = false;
	m_StopText = false;
	m_cur_ftime = m_end_time;
	m_Bitmap = 0;
	m_Text = 0;
	m_Item = 0;
	m_IsEraserSound = false;
	m_Bitmap = new BitmapClass*[mapwidth];
	int arraysize = m_ArrayBlocks.size();
	for(int i=0; i<arraysize;i++) m_ArrayBlocks.erase(m_ArrayBlocks.begin());
	for (int i = 0; i < mapwidth; i++)
	{
		m_Bitmap[i] = new BitmapClass[mapheight];
	}
	for (int i = 0; i < mapwidth; i++)
	{
		for (int j = 0; j < mapheight; j++)
		{
			m_Bitmap[i][j].Initialize(m_D3D->GetDevice(), screenWidth, screenHeight, L"data/0.jpg", 16, 16);
		}
	}
	
	m_Text = new TextClass;

	for (int i = 0; i < 10; i++)
	{
		m_Rank[i] = new TextClass;
		m_Rank[i]->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), *m_hwnd, screenWidth, screenHeight, baseViewMatrix);

		if (i < 5)
		{
			m_UIText[i] = new TextClass;
			switch (i)
			{
			case 0:
				m_UIText[i]->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), *m_hwnd, screenWidth, screenHeight, baseViewMatrix, 128, "Mode: Easy", 1.f, 1.f, 1.f, 400, 300);
				break;
			case 1:
				m_UIText[i]->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), *m_hwnd, screenWidth, screenHeight, baseViewMatrix, 128, "Enter: Stop, ESC: esc , R: restart", 1.f, 1.f, 1.f, 600, 400);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			default:
				break;
			}
		}
	}

	// Initialize the text object.
	m_Text->Initialize(m_D3D->GetDevice(), m_D3D->GetDeviceContext(), *m_hwnd, screenWidth, screenHeight, baseViewMatrix);

	std::srand((unsigned int)time(NULL));
	m_ArrayBlocks.push_back(new Blocks());
	if (!hard) blocklimitnum = 5;
	else blocklimitnum = 11;
	sound = new cSound;
	m_ArrayBlocks[0]->Initialize(m_D3D, screenWidth, screenHeight, rand() % blocklimitnum, m_TextureShader,m_Input,m_Bitmap, iskeydown, toggle,&hard, &sound);
	m_MainBlocks = m_ArrayBlocks[0];

	fileLoad();
	

}

void Game::Initialize(bool isresound)
{
	m_MoveX = 0;
	m_MoveY = 0;
	mapwidth = 15;
	mapheight = 30;
	screenWidth = 800;
	screenHeight = 600;
	m_ftime = 0.f;
	hard = false;
	blocktypenum = 0;
	m_BlockCount = 0;
	m_EndBlocks = 0;
	m_IsEnd = false;
	m_IsPrev = false;
	m_IsStop = false;
	m_StopText = false;
	m_cur_ftime = m_end_time;
	m_Item = 0;
	m_IsEraserSound = false;
	int arraysize = m_ArrayBlocks.size();
	for (int i = 0; i < arraysize; i++)
	{
		delete m_ArrayBlocks[0];
		m_ArrayBlocks.erase(m_ArrayBlocks.begin());
	}
	m_ArrayBlocks.clear();
	for (int i = 0; i < mapwidth; i++)
	{
		for (int j = 0; j < mapheight; j++)
		{
			m_Bitmap[i][j].setIsFill(false);
			m_Bitmap[i][j].setIsFinish(false);
		}
	}
	m_UIText[0]->SetText("Mode: Easy", m_D3D->GetDeviceContext(), 400, 300, 1.0f, 0.0f, 1.0f);

	std::srand((unsigned int)time(NULL));
	m_ArrayBlocks.push_back(new Blocks());
	if (!hard) blocklimitnum = 5;
	else blocklimitnum = 11;
	sound->PLAYsound("bgm");
	m_ArrayBlocks[0]->Initialize(m_D3D, screenWidth, screenHeight, rand() % blocklimitnum, m_TextureShader, m_Input, m_Bitmap, iskeydown, toggle, &hard, &sound);
	m_MainBlocks = m_ArrayBlocks[0];

	fileLoad();



}

void Game::Shutdown()
{
	for (int i = 0; i < mapwidth; i++)
	{
		for (int j = 0; j < mapheight; j++)
		{
			m_Bitmap[i][j].Shutdown();
		}
	}
}

void Game::GetTime()
{
	if (timeGetTime() >= (m_cur_ftime + 500))
	{
		m_ftime += 0.5f;
		m_cur_ftime = timeGetTime();
	}
}

void Game::Update(float _time)
{
	if(!m_IsStop && !m_IsEnd) GetTime();
	if (m_ftime - m_end_time > 100) hard = true; // ���̵� �ð�

	if (!hard)
	{
		blocklimitnum = 5;
		m_UIText[0]->SetText("Mode: Easy", m_D3D->GetDeviceContext(), 400, 300, 1.0f, 1.0f, 1.0f);
		if ((((int)m_cur_ftime - (int)m_ftime) == -1))
		{
			
		}
	}
	else
	{
		blocklimitnum = 11;
		m_UIText[0]->SetText("Mode: Hard", m_D3D->GetDeviceContext(), 400, 300, 1.0f, 0.0f, 0.0f);
		if (!((m_cur_ftime - m_ftime) < 0.01f && (m_cur_ftime - m_ftime) > -0.01f))
		{
			
		}
	}

	m_UIText[1]->SetTime(m_ftime, m_D3D->GetDeviceContext());

	if (m_Input->IsKeyDown(VK_RETURN) && !iskeydown[VK_RETURN])
	{
		iskeydown[VK_RETURN] = true;
		toggle[VK_RETURN] = !toggle[VK_RETURN];
		m_IsStop = !m_IsStop;
	}
	if (!m_Input->IsKeyDown(VK_RETURN) && iskeydown[VK_RETURN])
	{
		iskeydown[VK_RETURN] = false;
	}


	if (m_Input->IsKeyDown(0x52) && !iskeydown[0x52] && m_IsEnd) //R��ư
	{
		iskeydown[0x52] = true;
		toggle[0x52] = !toggle[0x52];
		m_end_time = m_cur_ftime;
		m_Score = 0;
		m_IsEnd = false;
		Initialize(true);
	}
	if (!m_Input->IsKeyDown(0x52) && iskeydown[0x52])
	{
		iskeydown[0x52] = false;
	}
	
	if (m_IsStop)
	{
		m_UIText[0]->SetText("- Stop -", m_D3D->GetDeviceContext(), 400, 300, 1.0f, 0.0f, 1.0f);
		return;
	}

	m_Text->SetScore(m_Score, m_D3D->GetDeviceContext(), 300, 20);

	if (!m_IsPrev)
	{
		std::srand(_time);
		m_PrvBlocks = new Blocks;
		m_PrvBlocks->Initialize(m_D3D, screenWidth, screenHeight, rand() % blocklimitnum, m_TextureShader, m_Input, m_Bitmap, iskeydown, toggle,&hard, &sound);
		m_PrvBlocks->setMoveX(20);
		m_PrvBlocks->setMoveY(26);
		m_IsPrev = true;
	}

	if (m_IsEnd)
	{
		m_UIText[0]->SetText("- End -", m_D3D->GetDeviceContext(), 400, 300, 1.0f, 0.0f, 0.0f);
		return;
	}
	m_MainBlocks->Updated(m_MoveX,m_MoveY,blocktypenum, _time);
	if(m_Item!=0) m_Item->BlockDownUpdated(_time);

	if (m_Item != 0)
	{
		if (m_Item->getIsEnd())
		{
			delete m_Item;
			m_Item = 0;
			Initialize(false);
		}
	}

	if (m_MainBlocks->getIsEnd())
	{
		int movex, movey, type;
		m_EndBlocks = m_MainBlocks;
		movex = m_EndBlocks->getMoveX();
		movey = m_EndBlocks->getMoveY();
		type = m_EndBlocks->getBlockType() % 4;
		for (int i = 0; i < 4; i++) 
		{
			for (int j = 0; j < 4; j++)
			{
				if (m_EndBlocks->getBlock()[type][i][j].getIsFill())//4x4������ �׷��ְ� �ִ� ���� ã�Ƽ�
				{
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if ((j + movey == y) && (i + movex == x))//�ش� ���� �ش��ϴ� ���� ��ǥ�� ����á�ٰ� true�� �ٲ��ش�.
							{
								m_Bitmap[x][y].setIsFill(true);
							}
							else if ((j + movey) < 0)
							{
								m_IsEnd = true;
								sound->offBGM();
								sound->PLAYsound("end");

								fileSave();
								fileLoad();
								return;
							}
						}
					}
				}
			}
		}

		//int rowY = 0;
		//for (int y = 0; y < mapheight; y++)
		//{
		//	int fillcount = 0;
		//	for (int x = 0; x < mapwidth; x++)
		//	{
		//		if (m_Bitmap[x][y].getIsFill())
		//		{
		//			fillcount++;
		//			if (fillcount == mapwidth)//y�� �ش����� ��������
		//			{
		//				rowY = y;
		//				m_Score++;
		//				for (int z = 0; z < mapwidth; z++)//y�� �ش��ϴ� ���� �ʿ� ����ٰ� false�� �־��ش�. �� �׸��� �ʿ��� ���ִ°͵鵵 ��ĭ�� ��������Ѵ�. �׳� �� �ʱ�ȭ�ϰ� �ٽ� ä��°�? ���������� �� ����
		//				{
		//					m_Bitmap[z][rowY].setIsFill(false);
		//				}
		//				for (int i = 0; i < m_ArrayBlocks.size(); i++)//���� ���鿡�� y�ٿ� �ش��ϴ� ������ ã�ƾ��Ѵ�.ã�Ƽ� ��������ϴµ�?�׸��°� �� �׸��� false�ϰ� <- �ð��Ǹ� ������ �ִϸ��̼�
		//				{											  //y�� ���� �ִ°͵��� ��ĭ�� ��������Ѵ�.
		//					movex = m_ArrayBlocks[i]->getMoveX();
		//					movey = m_ArrayBlocks[i]->getMoveY();
		//					type = m_ArrayBlocks[i]->getBlockType() % 4;
		//					for (int j = 0; j < 4; j++) // ���� �Ʒ����� �˻��ϴ°� ���� ���� �� �Ƴ� ������ ������
		//					{
		//						for (int k = 0; k < 4; k++)
		//						{
		//							if (m_ArrayBlocks[i]->getBlock()[type][k][j].getIsFill())
		//							{
		//								if ((j + movey) == rowY)
		//								{
		//									m_ArrayBlocks[i]->getBlock()[type][k][j].setIsFill(false);
		//									m_ArrayBlocks[i]->getBlock()[type][k][j].setIsFinish(true);
		//								}
		//							}
		//							//?
		//						}
		//					}
		//				}
		//			}
		//		}
		//	}
		//} // ���� ������ ���� ���� ���� ������ �ȳ�����



		int rowY = 0;
		for (int y = 0; y < mapheight; y++)
		{
			int fillcount = 0;
			for (int x = 0; x < mapwidth; x++)
			{
				if (m_Bitmap[x][y].getIsFill())
				{
					fillcount++;
					if (fillcount == mapwidth)//y�� �ش����� ��������
					{
						rowY = y;
						m_Score+=10;
						if (!m_IsEraserSound)
						{
							sound->PLAYsound("eraser");
							m_IsEraserSound = true;
						}
						for (int z = 0; z < mapwidth; z++)//y�� �ش��ϴ� ���� �ʿ� ����ٰ� false�� �־��ش�. �� �׸��� �ʿ��� ���ִ°͵鵵 ��ĭ�� ��������Ѵ�. �׳� �� �ʱ�ȭ�ϰ� �ٽ� ä��°�? ���������� �� ����
						{
							m_Bitmap[z][rowY].setIsFill(false);//??? �̰͵� ���̶� ���� �ʳ�?? �� �����غ��� rowY�� �����
						}
						for (int u = rowY; u > 0; --u)// �� rowY�����߾�? ��������� ���� rowY�ݾ�?? �� �¾� �׷� �� ���� �ִ°� �Ʒ��� ��ĭ���� �ű�� ���ݾ�? // ���� �Ųٷ� �ؾ��ϳ� �ȱ׷��� ���� ������
						{
							for (int z = 0; z < mapwidth; z++) // �ٺ��� ���ִ°͸� �ϸ� ���ݾ�
							{
								if (m_Bitmap[z][u-1].getIsFill())
								{
									m_Bitmap[z][u].setIsFill(true);
									m_Bitmap[z][u - 1].setIsFill(false);
								}
							}
						}
						for (int i = 0; i < m_ArrayBlocks.size(); i++)//���� ���鿡�� y�ٿ� �ش��ϴ� ������ ã�ƾ��Ѵ�.ã�Ƽ� ��������ϴµ�?�׸��°� �� �׸��� false�ϰ� <- �ð��Ǹ� ������ �ִϸ��̼�
						{											  //y�� ���� �ִ°͵��� ��ĭ�� ��������Ѵ�.
							movex = m_ArrayBlocks[i]->getMoveX();
							movey = m_ArrayBlocks[i]->getMoveY();
							type = m_ArrayBlocks[i]->getBlockType() % 4;
							if ((3 + movey) < rowY) // 4x4 ������ ���� �ؿ� �ִ°� �����ϳ�?? �׷� �� �����̳�
							{
								m_ArrayBlocks[i]->addMoveY();
							}
							else if(((0 + movey) <= rowY )&&((3 + movey) >= rowY))//4x4 �� ������� �� �ؿ� �ִ� �ֵ� �𿩺� // �ƴ� �Ḹ �ؿ� �ִ� �ֵ��� �������ݾ� // �� �ٿ� �ִ� �ֵ鸸 �ѹ� �� �Ÿ���
							{
								for (int k = 0; k < 4; k++) // ��������� �ֵ���� ����� ����
								{
									if (m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].getIsFill())
									{
										m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].setIsFill(false);
										m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].setIsFinish(true);
									}
								}

								for (int j = (rowY - movey); j > 0; --j) // ������� �� ���� �׷� rowY - movey �̰ų�?? �׷� rowY - movey �̰� �� ������ �ֵ��� �� �ϸ� �ǰڴ�.
								{
									for (int k = 0; k < 4; k++)
									{
										if (m_ArrayBlocks[i]->getBlock()[type][k][j - 1].getIsFill())//�ؿ������� ���ܿ;��� ������ ������ �����Ͱ� �������
										{
											m_ArrayBlocks[i]->getBlock()[type][k][j].setIsFill(true); //�ڱ� ������� ������ �Űܾ��ϴϱ� false��
											m_ArrayBlocks[i]->getBlock()[type][k][j - 1].setIsFill(false); // ������ �Ű����ϱ� true
										}
										//? �ȰŰ���?? ���� �� ���� ���� �ִ�. �� ����ִ��� Ȯ�� ��

									}
								}
							}
						}
					}
				}
			}
		}
		
		m_IsEraserSound = false;
		m_BlockCount++;
		m_ArrayBlocks.push_back(m_PrvBlocks);
		m_MainBlocks = m_ArrayBlocks[m_BlockCount];
		m_MainBlocks->setMoveX(5);
		m_MainBlocks->setMoveY(-3);
		if (rand() % 50 == 0 && m_Item==0) // Ȯ�� ������ Ȯ��
		{
 			m_Item = new Blocks;
			m_Item->Initialize(m_D3D, screenWidth, screenHeight, 11, m_TextureShader, m_Input, m_Bitmap, iskeydown, toggle, &hard, &sound);
		}
		m_IsPrev = false;
		//std::srand((unsigned int)time(NULL));
		//m_MainBlocks->Initialize(m_D3D, screenWidth, screenHeight, rand() % 5, m_TextureShader, m_Input, m_Bitmap, iskeydown, toggle);
	}
	//if (m_Input->IsKeyDown(VK_DOWN))
	//{
	//	m_MoveY++;
	//}
}

void Game::IskeyToggle(unsigned int key,int &i)
{

}

bool Game::Render(D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix, D3DXMATRIX orthoMatrix)
{
	bool result;
	// Put the bitmap vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//result = m_Bitmap->Render(m_D3D->GetDeviceContext(), 100, 100);
	//if (!result)
	//{
	//	return false;
	//}

	//// Render the bitmap with the texture shader.
	//result = m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap->GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}

	for (int i = 0; i < mapwidth; i++)
	{
		for (int j = 0; j < mapheight; j++)
		{
			//if (!m_Bitmap[i][j].getIsFill())
			{
				m_Bitmap[i][j].Render(m_D3D->GetDeviceContext(), i * 16, j * 16);
				m_TextureShader->Render(m_D3D->GetDeviceContext(), m_Bitmap[i][j].GetIndexCount(), worldMatrix, viewMatrix, orthoMatrix, m_Bitmap[i][j].GetTexture());
			}
		}
	}

	if (!m_IsEnd)
	{
		m_MainBlocks->Render(worldMatrix, viewMatrix, orthoMatrix);
		for (int i = 0; i < m_ArrayBlocks.size(); i++)
		{
			m_ArrayBlocks[i]->Render(worldMatrix, viewMatrix, orthoMatrix);
		}
	}

	if (m_IsPrev)
	{
		m_PrvBlocks->Render(worldMatrix, viewMatrix, orthoMatrix);
	}

	m_D3D->TurnOnAlphaBlending();
	m_Text->RenderText(m_D3D->GetDeviceContext(),worldMatrix,orthoMatrix);
	for (int i = 0; i < 10; i++)
	{
		if(m_IsEnd) m_Rank[i]->RenderText(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
		if(i<2) m_UIText[i]->RenderText(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	}
	m_UIText[1]->RenderTime(m_D3D->GetDeviceContext(), worldMatrix, orthoMatrix);
	m_D3D->TurnOffAlphaBlending();

	m_D3D->TurnOnAlphaBlending(1.f,1.f,1.f);
	if (m_Item != 0)
	{
		m_Item->Render(worldMatrix, viewMatrix, orthoMatrix);
	}
	m_D3D->TurnOffAlphaBlending(1.f, 1.f, 1.f);

	return true;
}
