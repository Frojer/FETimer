#pragma once

#ifndef _FE_TIME
#define _FE_TIME

#include "FEDefine.h"

#include <chrono>

//----------------------------------------------------------------------------------------------------------------------------------------
// Ÿ�̸� ���� �帧
//----------------------------------------------------------------------------------------------------------------------------------------
// otp = _offsetTP, to = timeOffset;
//  otp           to          otp           otp
//   |              |          |             |
//   |--------------___________--------------++++++++++++++++++|
// start          pause     start        timeScale            stop
// 
// ex) Start() -> Pause() -> Start() -> SetTimeScale() -> Stop()
//
// Start() �Լ��� ȣ��Ǹ鼭 _offsetTP�� Start() �Լ��� ȣ������� �˴ϴ�.
// Pause() �Լ��� ȣ��Ǹ鼭 _offsetTP�� Pause() �Լ��� ȣ����� ������ ���� _timeOffset�� �����ݴϴ�.
// �ٽ� Start() �Լ��� ȣ�� �Ǹ鼭 _offsetTP�� ������ Start() �Լ��� ȣ��������� �ٲ�ϴ�.
// SetTimeScale() �Լ� ȣ��� timeScale�� ����� �������� ����� ��ȭ�� �ʿ��ϹǷ�
// _offsetTP�� SetTimeScale() �Լ��� ȣ����� ������ ���� _timeOffset�� �����ְ� _offsetTP�� ������ SetTimeScale() �Լ��� ȣ��������� �ٲ�ϴ�.
// Stop() �Լ��� ȣ��Ǹ鼭 _offsetTP���� Stop() ȣ�� ���������� �ð��� _timeOffset�� �����ָ鼭 Ÿ�̸��� ���� ����ð��� _timeOffset�� �˴ϴ�.
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

	// ���� ������ ���� �� �׻� 0.0f ��ȯ�մϴ�.
	FE::FLOAT GetElapseTime();

	void SetTimeScale(FE::FLOAT i_timeScale);

	FE::FLOAT GetTimeScale() const;
	STATE GetState() const;

private:
	std::chrono::time_point<std::chrono::high_resolution_clock> _offsetTP;
	FE::FLOAT _timeScale;	// �⺻�� : 1.0f

	// _offsetTP�� ����ǰų�(Pause or Stop or SetTimeScale), GetElapseTime()�� ȣ���Ͽ� _timeOffset�� ���ϰ��� �ϴ°�쿡�� _timeOffset�� �������ݴϴ�.
	FE::FLOAT _timeOffset;
	STATE _state;	// �⺻�� : STOP
};

#endif