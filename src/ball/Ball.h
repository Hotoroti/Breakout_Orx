#pragma once
#include  "orx.h"
class Ball
{
public:
  Ball(const orxSTRING configName);
  ~Ball();

  void Update();

  void OnCollision();

private:
  orxOBJECT* m_Object = nullptr;
  orxVECTOR m_Direction = orxVECTOR_0;
  orxVECTOR m_Speed = orxVECTOR_0;
  orxVECTOR m_CurrentPos = orxVECTOR_0;
  orxFLOAT  m_BALLSPEED = 200;
  orxFLOAT m_ScreenWidth = 0, m_ScreenHeight = 0;

  bool m_HasStarted = false;

  void Start();
};

