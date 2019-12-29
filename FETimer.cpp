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

	auto t = _offsetTP;
	_offsetTP = high_resolution_clock::now();

	_timeOffset += _timeScale * static_cast<duration<float>>(_offsetTP - t).count();

	return _timeOffset;
}

FE::FLOAT FETimer::Stop()
{
	_state = STATE::STOP;

	if (_state != STATE::RUNNING)
		return _timeOffset;

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