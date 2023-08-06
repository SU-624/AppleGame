#include "AppleGame.h"
#include "define.h"

/// <summary>
/// FMOD�� �̿��� �ܼ��� �Ҹ� ��Ʈ�� �Լ��� ����
/// �뷡 index ������ channel ���ڷ� ��Ʈ��.
/// 2021.10.28 woodpie9 �ۼ�
/// 2021.11.18 Win32 ������Ʈ �̽�, ������Ʈ
/// </summary>
//System* pSystem;
Sound* pSound[10];
Channel* pChannel[1];
Channel* pEffect[1];
ChannelControl* pVolume;
float volume_ch[5] = {0.5f, 0.5f, 0.5f, 0.5f, 0.5f};
int channel_count;

/// <summary>
/// ���� ����� �غ��ϱ� ���� �Լ�.
/// ���α׷����� �� �ѹ� ����Ǿ�� ��
/// 
/// </summary>
void SoundSystem(int max_chanel_count=10)
{
	// �Ҹ��� ����� ä���� ��. �����Ӱ� ���� ����
	channel_count = max_chanel_count;

	System_Create(&pSystem);
	pSystem->init(channel_count, FMOD_INIT_NORMAL, NULL);

	// �뷡 ���� �̸�, �ݺ����� (LOOP_NORMAL�� �ݺ�. DEFAULT�� 1ȸ), Ȯ������ (�̻��), �Ҹ��� index

	// �ݺ��Ǵ� �Ҹ� (�������) �߰��κ�
	pSystem->createSound("../../../4_Resources/Sound/17. The White Lady.mp3",
		FMOD_LOOP_NORMAL, NULL, &pSound[0]);
	pSystem->createSound("../../../4_Resources/Sound/My Mistake.mp3",
		FMOD_LOOP_NORMAL, NULL, &pSound[1]); // ���� �����
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
/// ���ϴ� �Ҹ��� ���ϴ� ä�ο��� ����Ѵ�.
/// </summary>
/// <param name="Sound_num"> ����Ϸ��� �Ҹ��� index </param>
/// <param name="Channel_num"> ����Ϸ��� ä���� ���� </param>
void Sound_Play(int Sound_num, int Channel_num)
{
	pSystem->playSound(pSound[Sound_num], NULL, 0, &pChannel[Channel_num]);
//	Sound_Set(Channel_num);
}

/// <summary>
/// ���ϴ� ä���� �Ҹ��� ������Ų��.
/// </summary>
void Sound_Stop(int Channel_num)
{
	pChannel[Channel_num]->stop();
}

/// <summary>
/// ���ϴ� ä���� �Ҹ��� ������Ų��. �ִ� 1
/// </summary>
void Sound_UP(int Channel_num)
{
	volume_ch[Channel_num] += 0.1f;
	if (volume_ch[Channel_num] >= 1.0) volume_ch[Channel_num] = 1.0;
	Sound_Set(Channel_num);
}

/// <summary>
/// ���ϴ� ä���� �Ҹ��� ���ҽ�Ų��. �ּ� 0
/// </summary>
void Sound_Down(int Channel_num)
{
	volume_ch[Channel_num] -= 0.1f;
	if (volume_ch[Channel_num] <= 0) volume_ch[Channel_num] = 0;
	Sound_Set(Channel_num);
}

/// <summary>
/// ���ϴ� ä���� �Ҹ��� ����� �Ҹ��� ũ��� �����Ѵ�.
/// ȭ��(cpp����)�� �ٲ�� �Ҹ������� �ʱ�ȭ �Ǵµ�, �װ� �����ϱ� ����
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

// BGM Ű�� ȭ�� ��ȯ ���� ����Ѵ�.
// ������ �����ص� �Ҹ� ũ�⸦ ������
void Sound_BGM_ON(int Sound_num)
{
	Sound_Play(Sound_num, Channel_BGM);
	Sound_Set(Channel_BGM);
}

// ��� ä���� �Ҹ��� ����.
// BGM�� �ٲ�� ȭ���� ��ȯ��ų �� ����Ѵ�.
void Sound_All_OFF()
{
	for (int i = 0; i < channel_count; i++)
	{
		Sound_Stop(i);
	}
}