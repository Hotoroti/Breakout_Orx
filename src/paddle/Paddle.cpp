#include "Paddle.h"
Paddle::Paddle(const  orxSTRING configName) {
  m_Object = orxObject_CreateFromConfig(configName);
  orxVector_Set(&m_Direction, 0, 0, 0);
}

Paddle::~Paddle() {
  if (m_Object) {
    orxObject_Delete(m_Object);
    m_Object = nullptr;
  }
}

void Paddle::Update() {
  m_Direction.fX =
    (orxInput_IsActive("GoRight") ? 1.0f : 0.0f -
      (orxInput_IsActive("GoLeft") ? 1.0f : 0.0f));

  m_Direction.fX *= m_PADDLESPEED;

  orxObject_SetSpeed(m_Object, &m_Direction);
}

