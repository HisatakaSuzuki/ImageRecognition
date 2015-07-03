//参考
//http://vivi.dyndns.org/tech/cpp/timeMeasurement.html

#ifndef __TIMER_H_INCLUDED__
#define __TIMER_H_INCLUDED__
#define NOMINMAX	//windows.hのマクロの定義を回避
#include <windows.h>
class Timer
{
public:
    Timer();
    void  restart();	  // 計測開始時間を保存
    double  elapsed();    // リスタートからの秒数を返す

private:
    DWORD    m_start;    //  計測開始時間
};
#endif

