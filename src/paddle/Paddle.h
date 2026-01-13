#pragma once
#include  "orx.h"
class Paddle
{
public:
  Paddle(const orxSTRING connfigName);
  ~Paddle();

  void Update();

private:
  orxOBJECT* m_Object;
  orxVECTOR m_Direction;
  orxVECTOR m_Speed;
  orxFLOAT  m_PADDLESPEED = 50;
};


