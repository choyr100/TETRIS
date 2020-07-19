////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _GRAPHICSCLASS_H_
#define _GRAPHICSCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "d3dclass.h"
#include "cameraclass.h"
#include "textureshaderclass.h"
#include "bitmapclass.h"
#include "game.h"
#include "textclass.h"

/////////////
// GLOBALS //
/////////////
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


////////////////////////////////////////////////////////////////////////////////
// Class name: GraphicsClass
////////////////////////////////////////////////////////////////////////////////
class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool Initialize(int, int, HWND);
	bool Initialize(int screenWidth, int screenHeight, HWND hwnd, Game* game);
	void Shutdown();
	bool Frame(int, int ,float);

	//void fileLoad()
	//{
	//	ifstream ifile;
	//	string filename = "list.txt";
	//	string str;
	//	float scorereal;
	//	ifile.open(filename.c_str());
	//	if (!ifile)
	//	{
	//		exit(0);
	//	}
	//	while (!ifile.eof()) //파일이 끝날때 까지
	//	{
	//		ifile >> str;//줄줄이 str에 넣어준다.
	//		scorereal = stof(str); // 문자열로 얻은 값을 float 값으로 변환해준다.
	//		add(new Node(realname, realdep, scorereal));
	//	}
	//	ifile.close();

	//}
	//void fileSave(string filename)
	//{
	//	ofstream ofile;
	//	ofile.open(filename.c_str());
	//	if (!ofile)//실패시 종료시킨다.
	//	{
	//		cout << "파일을열 수 없습니다" << endl;
	//		exit(0);
	//	}
	//	Node* temp = header->getNextNode();//List에서 만든 printAll와 거의 똑같이 돌아간다. 하지만 값들을 ofile 에 입력하여 저장한다.
	//	while (temp != tailer)
	//	{
	//		ofile << temp->getName() << " " << temp->getDepartment() << " " << temp->getScore() << endl;
	//		temp = temp->getNextNode();
	//	}

	//	ofile.close();
	//}

private:
	bool Render(float);

private:
	D3DClass* m_D3D;
	CameraClass* m_Camera;
	TextureShaderClass* m_TextureShader;
	BitmapClass* m_Bitmap;
	BitmapClass* test;
	Game* m_game;
	TextClass* m_Text;

	int m_TimeCount;
	int m_TimeFrame;
};

#endif