#pragma once

#ifndef _FE_TIME
#define _FE_TIME

#include "FEDefine.h"

#include <chrono>

//----------------------------------------------------------------------------------------------------------------------------------------
// 타이머 동작 흐름
//----------------------------------------------------------------------------------------------------------------------------------------
// otp = _offsetTP, to = timeOffset;
//  otp           to          otp           otp
//   |              |          |             |
//   |--------------___________--------------++++++++++++++++++|
// start          pause     start        timeScale            stop
// 
// ex) Start() -> Pause() -> Start() -> SetTimeScale() -> Stop()
//
// Start() 함수가 호출되면서 _offsetTP는 Start() 함수의 호출시점이 됩니다.
// Pause() 함수가 호출되면서 _offsetTP와 Pause() 함수의 호출시점 사이의 값을 _timeOffset에 더해줍니다.
// 다시 Start() 함수가 호출 되면서 _offsetTP의 시점이 Start() 함수의 호출시점으로 바뀝니다.
// SetTimeScale() 함수 호출시 timeScale이 변경된 시점부터 배속의 변화가 필요하므로
// _offsetTP와 SetTimeScale() 함수의 호출시점 사이의 값을 _timeOffset에 더해주고 _offsetTP의 시점이 SetTimeScale() 함수의 호출시점으로 바뀝니다.
// Stop() 함수가 호출되면서 _offsetTP부터 Stop() 호출 시점사이의 시간을 _timeOffset에 더해주면서 타이머의 최종 경과시간이 _timeOffset이 됩니다.
//----------------------------------------------------------------------------------------------------------------------------------------

class FETimer final
{
public:
	enum class STATE : FE::UINT8
	{
		STOP,
		RUNNING,
		PAUSE
	};
	FETimer(FE::FLOAT t_timeScale = 1.0f);
	~FETimer() = default;

	void Start();
	FE::FLOAT Pause();
	FE::FLOAT Stop();

	// 동작 중이지 않을 때 항상 0.0f 반환합니다.
	FE::FLOAT GetElapseTime();

	void SetTimeScale(FE::FLOAT i_timeScale);

	FE::FLOAT GetTimeScale() const;
	STATE GetState() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _offsetTP;
	FE::FLOAT _timeScale;	// 기본값 : 1.0f

	// _offsetTP가 변경되거나(Pause or Stop or SetTimeScale), GetElapseTime()을 호출하여 _timeOffset을 구하고자 하는경우에만 _timeOffset을 갱신해줍니다.
	FE::FLOAT _timeOffset;
	STATE _state;	// 기본값 : STOP
};

#endif