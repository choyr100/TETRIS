#pragma once

#include "lib/inc/fmod.hpp"		//fomd.hpp 추가
#include "lib/inc/fmod_errors.h"		//fomd.hpp 추가
#pragma comment(lib, "lib/fmodex_vc.lib")	//lib 링크
using namespace FMOD;			//FMOD 네임스페이스 사용


#include <stdio.h>
#include <Windows.h>
#include <string>

								//-----------------------------------해더파일 시작
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