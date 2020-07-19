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
	//	while (!ifile.eof()) //������ ������ ����
	//	{
	//		ifile >> str;//������ str�� �־��ش�.
	//		scorereal = stof(str); // ���ڿ��� ���� ���� float ������ ��ȯ���ش�.
	//		add(new Node(realname, realdep, scorereal));
	//	}
	//	ifile.close();

	//}
	//void fileSave(string filename)
	//{
	//	ofstream ofile;
	//	ofile.open(filename.c_str());
	//	if (!ofile)//���н� �����Ų��.
	//	{
	//		cout << "�������� �� �����ϴ�" << endl;
	//		exit(0);
	//	}
	//	Node* temp = header->getNextNode();//List���� ���� printAll�� ���� �Ȱ��� ���ư���. ������ ������ ofile �� �Է��Ͽ� �����Ѵ�.
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