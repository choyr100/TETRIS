#pragma once

#include "lib/inc/fmod.hpp"		//fomd.hpp �߰�
#include "lib/inc/fmod_errors.h"		//fomd.hpp �߰�
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib ��ũ
using namespace FMOD;			//FMOD ���ӽ����̽� ���


#include <stdio.h>
#include <Windows.h>
#include <string>

								//-----------------------------------�ش����� ����
#pragma once

class cSound
{

public:
	cSound(void);
	~cSound(void);

	void LOADSoundAll();
	void ERRCHECK(FMOD_RESULT result);
	void PLAYsound(const std::string& sound_name);
	void DeleteSound();

	void offBGM()
	{
		initSound->release();
	}

public:
	FMOD::System   * System;

private:
	FMOD::Sound   * initSound;
	FMOD::Sound   * Stage_1_Sound;
	FMOD::Sound   * fireSound;
	FMOD::Sound   * laserSound;
	FMOD::Sound   * DestroySound;
	FMOD::Sound   * explosionSound;
	FMOD::Channel  * channel;
};