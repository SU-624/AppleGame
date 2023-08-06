#pragma once
#include <stdlib.h>
#include"fmod.hpp"
#include"fmod_errors.h"

using namespace FMOD;

void SoundSystem(int max_chanel_count);
void Sound_Play(int Sound_num, int Channel_num);
void Sound_Stop(int Chanul_num);
void Sound_UP(int Channel_num);
void Sound_Down(int Channel_num);
void Sound_Set(int Channel_num);
void Sound_BGM_ON(int Sound_num);
void Sound_All_OFF();
void PlayEffect();
void Sound_VOL_Set(int Channel_num, float Volume);