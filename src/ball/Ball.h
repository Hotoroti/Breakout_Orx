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
  orxOBJECT* m_Object;
  orxVECTOR m_Direction;
  orxVECTOR m_Speed;
  orxFLOAT  m_BALLSPEED = 200;

  bool m_HasStarted;

  void Start();
};

