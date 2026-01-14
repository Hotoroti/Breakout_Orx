#pragma once
#include "orx.h"
#include <functional>

class Wall {
public:
  Wall();
  ~Wall();
  void Update();
  void OnCollision(orxOBJECT* wallOBJ, std::function<void(orxFLOAT)> increaseSpeed, std::function<void(orxFLOAT)> increaseScore);

private:
  orxU32 m_wallCount = 0;
  void Init();
  orxU32 GetGridValue(const orxSTRING key);
};
