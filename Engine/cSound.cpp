#include "cSound.h"


cSound::cSound(void)
{
	System = NULL;
	initSound = NULL;
	Stage_1_Sound = NULL;
	fireSound = NULL;
	laserSound = NULL;
	DestroySound = NULL;
	explosionSound = NULL;
	channel = NULL;
	LOADSoundAll();//sound loading 클래스 생성시 한번만 호출

	FMOD_RESULT  result;
	result = System->playSound(FMOD_CHANNEL_FREE, initSound, FALSE, &channel);
	channel->setVolume(0.5f);
	ERRCHECK(result);
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
cSound::~cSound(void)
{
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------//사운드를 로드시켜 줌. 메쉬 모델을 로드시켜주는 것과 같은 맥락.
void cSound::LOADSoundAll()
{
	FMOD_RESULT result;

	result = FMOD::System_Create(&System);
	ERRCHECK(result);

	result = System->init(100, FMOD_INIT_NORMAL, 0);
	ERRCHECK(result);

	result = System->createSound("data/01 Welcome to PUYOTETRIS!!.mp3", FMOD_LOOP_NORMAL, 0, &initSound);
	ERRCHECK(result);

	result = System->createSound("data/PPT-Tetris-Hold-Varoop.oga", FMOD_DEFAULT, 0, &Stage_1_Sound);
	ERRCHECK(result);

	result = System->createSound("data/WINFANF.wav", FMOD_DEFAULT, 0, &fireSound);
	ERRCHECK(result);

	result = System->createSound("data/13.wav", FMOD_DEFAULT, 0, &laserSound);
	ERRCHECK(result);

	result = System->createSound("../data/sound/Destroy.wav", FMOD_DEFAULT, 0, &DestroySound);
	ERRCHECK(result);

	result = System->createSound("../data/sound/Stage2.wav", FMOD_DEFAULT, 0, &explosionSound);
	ERRCHECK(result);
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//사운드 파일이 없거나 잘못된 파일이 아닌지 에러체크를 해주는 함수. 검사해보고 잘못된 파일이거나 사운드 파일이 없으면
//창에 메시지 출력. 
void cSound::ERRCHECK(FMOD_RESULT result)
{
	if (result != FMOD_OK)
	{
		char str[256];
		sprintf(str, "FMOD error! ( %d ) %s\n", result, FMOD_ErrorString(result));
		//MessageBox(NULL, str, "", MB_OK);
	}
}
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------
//함수 인자로 문자열을 입력하면 상황에 따른 사운드를 재생.
void cSound::PLAYsound(const std::string& sound_name)
{
	FMOD_RESULT result;
	if (sound_name == "bgm")
	{
		//initSound->release();
		result = System->playSound(FMOD_CHANNEL_FREE, initSound, FALSE, &channel);
		channel->setVolume(1.f);
	}
	else if (sound_name == "speed")
	{
		//initSound->release();
		result = System->playSound(FMOD_CHANNEL_FREE, Stage_1_Sound, FALSE, &channel);
		channel->setVolume(1.f);
		ERRCHECK(result);
	}

	else if (sound_name == "end")
	{
		result = System->playSound(FMOD_CHANNEL_FREE, fireSound, FALSE, &channel);
		channel->setVolume(0.5f);
		ERRCHECK(result);
	}

	else if (sound_name == "eraser")
	{
		result = System->playSound(FMOD_CHANNEL_FREE, laserSound, FALSE, &channel);
		channel->setVolume(2.5f);
		ERRCHECK(result);
	}

	else if (sound_name == "destroy")
	{
		result = System->playSound(FMOD_CHANNEL_FREE, DestroySound, FALSE, &channel);
		channel->setVolume(0.25f);
		ERRCHECK(result);
	}

	else if (sound_name == "explosion_sound")
	{
		result = System->playSound(FMOD_CHANNEL_FREE, explosionSound, FALSE, &channel);
		channel->setVolume(1.f);
		ERRCHECK(result);
	}
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void cSound::DeleteSound()
{
	//if (initSound) { SAFE_DELETE(initSound); }
	//if (Stage_1_Sound) { SAFE_DELETE(Stage_1_Sound); }
	//if (fireSound) { SAFE_DELETE(fireSound); }
	//if (laserSound) { SAFE_DELETE(laserSound); }
	//if (DestroySound) { SAFE_DELETE(DestroySound); }
	//if (explosionSound) { SAFE_DELETE(explosionSound); }
	//if (System) { SAFE_DELETE(System); }
}