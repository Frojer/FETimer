# FETimer

## 멤버 함수
* public
  ### void Start();
  * 타이머를 시작한다.
  * 타이머가 돌아가는 중에 다시 하면 아무 일도 일어나지 않는다.
  * 다시 시작하고 싶다면 Stop()을 먼저 호출해주자.
  * 타이머의 상태가 RUNNING 상태가 된다.

  ### FE::FLOAT Pause()
  * 타이머를 일시 정지한다.
  * 반환값은 일시 정지했을 때까지의 경과시간을 반환한다.
  * 타이머의 상태가 PAUSE 상태가 된다.

  ### FE::FLOAT Stop();
  * 타이머를 멈춘다.
  * 반환값은 멈춘 순간의 경과시간을 반환한다.
  * 타이머의 상태가 STOP 상태가 된다.

  ### FE::FLOAT GetElapseTime();
  * 경과시간을 얻어온다.

  ### void SetTimeScale(FE::FLOAT i_timeScale);
  * _timeScale을 변경한다.

  ### FE::FLOAT GetTimeScale() const;
  * _timeScale을 얻어온다.
  * 개체 생성 시의 기본값은 1.0f이다.

  ### STATE GetState() const;
  * 현재 타이머의 상태를 얻어온다.
  * 타이머의 상태로는 RUN, PAUSE, STOP이 있다.
  * 개체 생성 시의 기본값은 STOP이다.