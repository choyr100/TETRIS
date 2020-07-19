////////////////////////////////////////////////////////////////////////////////
// Filename: textclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_

///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "fontclass.h"
#include "fontshaderclass.h"

#include <sstream>
////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
	};

	struct VertexType
	{
		D3DXVECTOR3 position;
	    D3DXVECTOR2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass&);
	~TextClass();

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX);
	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, HWND, int, int, D3DXMATRIX, int , char* , float, float, float,int,int);
	void Shutdown();
	bool Render(ID3D11DeviceContext*, D3DXMATRIX, D3DXMATRIX);
	bool RenderText(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);
	bool RenderTime(ID3D11DeviceContext* deviceContext, D3DXMATRIX worldMatrix, D3DXMATRIX orthoMatrix);
	bool SetFps(int fps, ID3D11DeviceContext* deviceContext);
	bool SetCpu(int cpu, ID3D11DeviceContext* deviceContext);
	bool SetTime(float time, ID3D11DeviceContext* deviceContext);
	bool SetScore(int cpu, ID3D11DeviceContext* deviceContext, int x, int y);
	bool SetRankScore(int rank, int score, ID3D11DeviceContext* deviceContext, int x, int y);
	bool SetText(string text, ID3D11DeviceContext* deviceContext, int x, int y,float , float, float);

	int getRank()
	{
		return m_Rank;
	}
	int getScore()
	{
		return m_Score;
	}
	void setRank(int r)
	{
		m_Rank = r;
	}
	void setScore(int s)
	{
		m_Score = s;
	}

private:
	bool InitializeSentence(SentenceType**, int, ID3D11Device*);
	bool UpdateSentence(SentenceType*, char*, int, int, float, float, float, ID3D11DeviceContext*);
	void ReleaseSentence(SentenceType**);
	bool RenderSentence(ID3D11DeviceContext*, SentenceType*, D3DXMATRIX, D3DXMATRIX);

private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	D3DXMATRIX m_baseViewMatrix;
	SentenceType* m_sentence1;
	SentenceType* m_sentence2;

	int m_Rank;
	int m_Score;

};

#endif