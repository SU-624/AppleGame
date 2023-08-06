#include "AppleGame.h"
#include "define.h"

/// <summary>
/// FMOD를 이용한 단순한 소리 컨트롤 함수를 정의
/// 노래 index 순서와 channel 숫자로 컨트롤.
/// 2021.10.28 woodpie9 작성
/// 2021.11.18 Win32 프로젝트 이식, 업데이트
/// </summary>
//System* pSystem;
Sound* pSound[10];
Channel* pChannel[1];
Channel* pEffect[1];
ChannelControl* pVolume;
float volume_ch[5] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
int channel_count;

/// <summary>
/// 사운드 출력을 준비하기 위한 함수.
/// 프로그램에서 딱 한번 실행되어야 함
/// 
/// </summary>
void SoundSystem(int max_chanel_count=10)
{
	// 소리를 출력할 채널의 수. 자유롭게 증감 가능
	channel_count = max_chanel_count;

	System_Create(&pSystem);
	pSystem->init(channel_count, FMOD_INIT_NORMAL, NULL);

	// 노래 파일 이름, 반복여부 (LOOP_NORMAL은 반복. DEFAULT는 1회), 확장정보 (미사용), 소리의 index

	// 반복되는 소리 (배경음악) 추가부분
	pSystem->createSound("../../../4_Resources/Sound/17. The White Lady.mp3",
		FMOD_LOOP_NORMAL, NULL, &pSound[0]);
	pSystem->createSound("../../../4_Resources/Sound/My Mistake.mp3",
		FMOD_LOOP_NORMAL, NULL, &pSound[1]); // 현재 사용중
	pSystem->createSound("../../../4_Resources/Sound/Fat Cat.mp3",
		FMOD_LOOP_NORMAL, NULL, &pSound[2]);

	//Effect
	pSystem->createSound("../../../4_Resources/Sound/clear.wav",
		FMOD_DEFAULT, NULL, &pSound[3]);
	
}

void PlayEffect()
{
	pSystem->playSound(pSound[3], NULL, 0, pEffect);
	pEffect[0]->setVolume(volume_ch[0]);
}


/// <summary>
/// 원하는 소리를 원하는 채널에서 출력한다.
/// </summary>
/// <param name="Sound_num"> 출력하려는 소리의 index </param>
/// <param name="Channel_num"> 출력하려는 채널을 선택 </param>
void Sound_Play(int Sound_num, int Channel_num)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel[Channel_num]);
//	Sound_Set(Channel_num);
}

/// <summary>
/// 원하는 채널의 소리를 중지시킨다.
/// </summary>
void Sound_Stop(int Channel_num)
{
	pChannel[Channel_num]->stop();
}

/// <summary>
/// 원하는 채널의 소리를 증가시킨다. 최대 1
/// </summary>
void Sound_UP(int Channel_num)
{
	volume_ch[Channel_num] += 0.1f;
	if (volume_ch[Channel_num] >= 1.0) volume_ch[Channel_num] = 1.0;
	Sound_Set(Channel_num);
}

/// <summary>
/// 원하는 채널의 소리를 감소시킨다. 최소 0
/// </summary>
void Sound_Down(int Channel_num)
{
	volume_ch[Channel_num] -= 0.1f;
	if (volume_ch[Channel_num] <= 0) volume_ch[Channel_num] = 0;
	Sound_Set(Channel_num);
}

/// <summary>
/// 원하는 채널의 소리를 저장된 소리의 크기로 변경한다.
/// 화면(cpp파일)이 바뀌면 소리설정이 초기화 되는데, 그걸 유지하기 위함
/// </summary>
void Sound_Set(int Channel_num)
{
	pChannel[Channel_num]->setVolume(volume_ch[Channel_num]);
}

void Sound_VOL_Set(int Channel_num, float Volume)
{
	volume_ch[Channel_num] = Volume;
	if (volume_ch[Channel_num] >= 1.0) volume_ch[Channel_num] = 1.0;
	if (volume_ch[Channel_num] <= 0) volume_ch[Channel_num] = 0;

	pChannel[Channel_num]->setVolume(volume_ch[Channel_num]);
}

// BGM 키기 화면 전환 이후 사용한다.
// 이전에 설정해둔 소리 크기를 유지함
void Sound_BGM_ON(int Sound_num)
{
	Sound_Play(Sound_num, Channel_BGM);
	Sound_Set(Channel_BGM);
}

// 모든 채널의 소리를 끈다.
// BGM이 바뀌며 화면을 전환시킬 때 사용한다.
void Sound_All_OFF()
{
	for (int i = 0; i < channel_count; i++)
	{
		Sound_Stop(i);
	}
}