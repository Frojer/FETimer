#pragma once

#ifndef _FE_TIME
#define _FE_TIME

#include "FEDefine.h"

#include <chrono>

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
	// otp = _offsetTP, to = timeOffset;
	//  otp           to          otp
	//   |              |          |
	//   |--------------___________--------------++++++++++++++++++|
	// start          pause     start        timeScale            stop
	// otp가 갱신되면 to에 지금까지의 흐른 시간을 저장합니다. 그 후 새로운 otp부터 now() 사이의 값을 더해 타이머의 값 구합니다.
	// timeScale에서 offsetTime을 변경해주는 이유는 변경하지 않으면 offsetTime이 가리키는 것부터 지금까지로 timeScale이 적용되기 때문입니다.
	std::chrono::time_point<std::chrono::high_resolution_clock> _offsetTP;
	FE::FLOAT _timeScale;
	FE::FLOAT _timeOffset;
	STATE _state;
};

#endif