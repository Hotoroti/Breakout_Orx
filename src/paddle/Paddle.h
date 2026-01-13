#pragma once
#include  "orx.h"
class Paddle
{
public:
  Paddle(const orxSTRING connfigName);
  ~Paddle();

  void Update();

private:
  orxOBJECT* m_Object = nullptr;
  orxVECTOR m_Direction = orxVECTOR_0;
  orxVECTOR m_Speed = orxVECTOR_0;
  orxFLOAT  m_PADDLESPEED = 200;
  orxBOOL m_CanMove = false;
};


