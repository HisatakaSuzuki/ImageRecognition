#include "Timer.h";
#pragma comment(lib, "winmm.lib")// timeGetTime() を使った時間計測タイマー クラス
Timer::Timer() { restart(); }
void  Timer::restart()
{
    m_start = timeGetTime();        // 計測開始時間を保存
}
double  Timer::elapsed()    // リスタートからの秒数を返す
{
    DWORD end = timeGetTime();
    return (double)(end - m_start) / 1000;	//秒として返す
}
