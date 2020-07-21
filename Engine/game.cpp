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
	if (m_ftime - m_end_time > 100) hard = true; // 난이도 시간

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


	if (m_Input->IsKeyDown(0x52) && !iskeydown[0x52] && m_IsEnd) //R버튼
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
				if (m_EndBlocks->getBlock()[type][i][j].getIsFill())//4x4블럭에서 그려주고 있는 블럭을 찾아서
				{
					for (int x = 0; x < mapwidth; x++)
					{
						for (int y = 0; y < mapheight; y++)
						{
							if ((j + movey == y) && (i + movex == x))//해당 블럭에 해당하는 맵의 좌표에 가득찼다고 true로 바꿔준다.
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
		//			if (fillcount == mapwidth)//y가 해당줄이 가득찬거
		//			{
		//				rowY = y;
		//				m_Score++;
		//				for (int z = 0; z < mapwidth; z++)//y에 해당하는 줄의 맵에 비었다고 false를 넣어준다. 아 그리고 맵에서 차있는것들도 한칸씩 내려줘야한다. 그냥 다 초기화하고 다시 채우는건? 무식하지만 난 편함
		//				{
		//					m_Bitmap[z][rowY].setIsFill(false);
		//				}
		//				for (int i = 0; i < m_ArrayBlocks.size(); i++)//끝난 블럭들에서 y줄에 해당하는 블럭들을 찾아야한다.찾아서 뭐해줘야하는데?그리는거 못 그리게 false하고 <- 시간되면 터지는 애니메이션
		//				{											  //y줄 위에 있는것들을 한칸씩 내려줘야한다.
		//					movex = m_ArrayBlocks[i]->getMoveX();
		//					movey = m_ArrayBlocks[i]->getMoveY();
		//					type = m_ArrayBlocks[i]->getBlockType() % 4;
		//					for (int j = 0; j < 4; j++) // 왠지 아래부터 검사하는게 좋아 보여 응 아냐 위에서 부터해
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
		//} // 무슨 아이템 쓴거 마냥 블럭이 밑으로 안내려옴



		int rowY = 0;
		for (int y = 0; y < mapheight; y++)
		{
			int fillcount = 0;
			for (int x = 0; x < mapwidth; x++)
			{
				if (m_Bitmap[x][y].getIsFill())
				{
					fillcount++;
					if (fillcount == mapwidth)//y가 해당줄이 가득찬거
					{
						rowY = y;
						m_Score+=10;
						if (!m_IsEraserSound)
						{
							sound->PLAYsound("eraser");
							m_IsEraserSound = true;
						}
						for (int z = 0; z < mapwidth; z++)//y에 해당하는 줄의 맵에 비었다고 false를 넣어준다. 아 그리고 맵에서 차있는것들도 한칸씩 내려줘야한다. 그냥 다 초기화하고 다시 채우는건? 무식하지만 난 편함
						{
							m_Bitmap[z][rowY].setIsFill(false);//??? 이것도 밑이랑 같지 않냐?? 잘 생각해보자 rowY는 상수야
						}
						for (int u = rowY; u > 0; --u)// 왜 rowY까지했어? 사라져야할 줄이 rowY잖아?? 응 맞어 그럼 그 위에 있는건 아래로 한칸씩만 옮기면 되잖아? // 뭐야 거꾸로 해야하네 안그러면 값이 덮어짐
						{
							for (int z = 0; z < mapwidth; z++) // 바보야 차있는것만 하면 되잖아
							{
								if (m_Bitmap[z][u-1].getIsFill())
								{
									m_Bitmap[z][u].setIsFill(true);
									m_Bitmap[z][u - 1].setIsFill(false);
								}
							}
						}
						for (int i = 0; i < m_ArrayBlocks.size(); i++)//끝난 블럭들에서 y줄에 해당하는 블럭들을 찾아야한다.찾아서 뭐해줘야하는데?그리는거 못 그리게 false하고 <- 시간되면 터지는 애니메이션
						{											  //y줄 위에 있는것들을 한칸씩 내려줘야한다.
							movex = m_ArrayBlocks[i]->getMoveX();
							movey = m_ArrayBlocks[i]->getMoveY();
							type = m_ArrayBlocks[i]->getBlockType() % 4;
							if ((3 + movey) < rowY) // 4x4 블럭에서 가장 밑에 있는거 멀쩡하냐?? 그럼 넌 정상이네
							{
								m_ArrayBlocks[i]->addMoveY();
							}
							else if(((0 + movey) <= rowY )&&((3 + movey) >= rowY))//4x4 블럭 사라지는 줄 밑에 있는 애들 모여봐 // 아니 잠만 밑에 있는 애들은 멀쩡하잖아 // 그 줄에 있는 애들만 한번 더 거르자
							{
								for (int k = 0; k < 4; k++) // 사라져야할 애들부터 지우고 보자
								{
									if (m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].getIsFill())
									{
										m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].setIsFill(false);
										m_ArrayBlocks[i]->getBlock()[type][k][rowY - movey].setIsFinish(true);
									}
								}

								for (int j = (rowY - movey); j > 0; --j) // 사라져야 할 줄은 그럼 rowY - movey 이거네?? 그럼 rowY - movey 이거 전 까지만 애들을 잘 하면 되겠다.
								{
									for (int k = 0; k < 4; k++)
									{
										if (m_ArrayBlocks[i]->getBlock()[type][k][j - 1].getIsFill())//밑에서부터 땡겨와야해 위에서 내리면 데이터가 덮어씌여져
										{
											m_ArrayBlocks[i]->getBlock()[type][k][j].setIsFill(true); //자긴 사라지고 밑으로 옮겨야하니깐 false로
											m_ArrayBlocks[i]->getBlock()[type][k][j - 1].setIsFill(false); // 밑으로 옮겼으니깐 true
										}
										//? 된거겠지?? 젭라 아 위에 문제 있다. 맵 비어있는지 확인 좀

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
		if (rand() % 50 == 0 && m_Item==0) // 확률 아이템 확률
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
