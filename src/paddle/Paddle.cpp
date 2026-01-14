#include "Paddle.h"
Paddle::Paddle(const  orxSTRING configName) {
  orxConfig_Load("paddle.ini");

  object = orxObject_CreateFromConfig(configName);
  orxVector_Set(&m_Direction, 0, 0, 0);
  orxVector_Set(&m_Speed, 0, 0, 0);
}

Paddle::~Paddle() {
  if (object) {
    orxObject_Delete(object);
    object = nullptr;
  }
}

void Paddle::Update() {
  m_Direction.fX =
    (orxInput_IsActive("GoRight") ? 1.0f : 0.0f -
      (orxInput_IsActive("GoLeft") ? 1.0f : 0.0f));

  m_Speed.fX = m_Direction.fX * m_PADDLESPEED;
  orxObject_SetSpeed(object, &m_Speed);
}

