//�Q�l
//http://vivi.dyndns.org/tech/cpp/timeMeasurement.html

#ifndef __TIMER_H_INCLUDED__
#define __TIMER_H_INCLUDED__
#define NOMINMAX	//windows.h�̃}�N���̒�`�����
#include <windows.h>
class Timer
{
public:
    Timer();
    void  restart();	  // �v���J�n���Ԃ�ۑ�
    double  elapsed();    // ���X�^�[�g����̕b����Ԃ�

private:
    DWORD    m_start;    //  �v���J�n����
};
#endif

