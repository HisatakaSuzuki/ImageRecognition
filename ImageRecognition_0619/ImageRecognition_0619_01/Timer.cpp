#include "Timer.h";
#pragma comment(lib, "winmm.lib")// timeGetTime() ���g�������Ԍv���^�C�}�[ �N���X
Timer::Timer() { restart(); }
void  Timer::restart()
{
    m_start = timeGetTime();        // �v���J�n���Ԃ�ۑ�
}
double  Timer::elapsed()    // ���X�^�[�g����̕b����Ԃ�
{
    DWORD end = timeGetTime();
    return (double)(end - m_start) / 1000;	//�b�Ƃ��ĕԂ�
}
