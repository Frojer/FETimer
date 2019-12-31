#include "FETimer.h"

using namespace std;
using namespace chrono;

FETimer::FETimer(FE::FLOAT t_timeScale)
	: _timeScale(t_timeScale), _timeOffset(0.0f), _state(STATE::STOP)
{
}

void FETimer::Start()
{
	if (_state == STATE::RUNNING)
		return;

	_state = STATE::RUNNING;
	_offsetTP = high_resolution_clock::now();
}

FE::FLOAT FETimer::Pause()
{
	if (_state != STATE::RUNNING)
		return _timeOffset;

	_state = STATE::PAUSE;

	// 일시정지시 시작점이 쓸모가 없어지므로 지금까지 진행된 경과시간을 저장합니다.
	auto t = _offsetTP;
	_offsetTP = high_resolution_clock::now();

	// 일시정지된 시점에서 시작했던 시점 사이의 시간을 경과시간에 더해줍니다. (처음 일시정지 했던 경우가 아니라면, _timeOffset에 일시정지 하기 전까지의 경과시간이 저장되어있음)
	_timeOffset += _timeScale * static_cast<duration<float>>(_offsetTP - t).count();

	return _timeOffset;
}

FE::FLOAT FETimer::Stop()
{
	if (_state != STATE::RUNNING)
		return _timeOffset;

	_state = STATE::STOP;

	// 타이머 종료시 지금까지의 경과시간을 구합니다.
	// _timeOffset(_offsetTP가 바뀐적이 있다면 그 이전의 경과시간을 담고있다,) + 시작시점부터 지금까지의 경과시간
	FE::FLOAT t = _timeOffset + _timeScale * static_cast<duration<float>>(high_resolution_clock::now() - _offsetTP).count();

	_timeOffset = 0.0f;

	return t;
}

FE::FLOAT FETimer::GetElapseTime()
{
	if (_state != STATE::RUNNING)
		return _timeOffset;

	return _timeOffset + _timeScale * static_cast<duration<float>>(high_resolution_clock::now() - _offsetTP).count();
}

void FETimer::SetTimeScale(FE::FLOAT i_timeScale)
{
	if (_state == STATE::RUNNING)
	{
		auto t = _offsetTP;
		_offsetTP = high_resolution_clock::now();

		_timeOffset += _timeScale * static_cast<duration<float>>(_offsetTP - t).count();
	}
	
	// 타이머가 동작 중이 아니라면, _offsetTP는 Start()에서 지정되므로 _timeScale만 바꿔줘도 됩니다.
	_timeScale = i_timeScale;
}

FE::FLOAT FETimer::GetTimeScale() const
{
	return _timeScale;
}

FETimer::STATE FETimer::GetState() const
{
	return _state;
}