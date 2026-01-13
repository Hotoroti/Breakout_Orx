#pragma once
#include "orx.h"

class Wall {
public:
  Wall();
  ~Wall();
  void Update();
  void OnCollision();

private:
  orxFLOAT m_wallCount = 0;
  void Init();
  orxU32 GetGridValue(const orxSTRING key);
};
