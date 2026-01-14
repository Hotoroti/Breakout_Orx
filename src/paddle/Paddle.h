#pragma once
#include  "orx.h"
class Paddle
{
public:
  orxOBJECT* object = nullptr;

  Paddle(const orxSTRING connfigName);
  ~Paddle();

  void Update();

private:  
  orxVECTOR m_Direction = orxVECTOR_0;
  orxVECTOR m_Speed = orxVECTOR_0;
  orxFLOAT  m_PADDLESPEED = 700;
  orxBOOL m_CanMove = false;
};


