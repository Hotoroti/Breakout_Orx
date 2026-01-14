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

void Paddle::OnCollision()
{
  orxConfig_PushSection("PaddleSettings");
  orxVECTOR position;
  orxObject_GetPosition(object, &position);
  if (position.fY > orxConfig_GetFloat("BaseYPosition")) {
    position.fY = orxConfig_GetFloat("BaseYPosition");
  }
  orxConfig_PopSection();
  orxObject_SetPosition(object, &position);
}

void Paddle::Update() {
  m_Direction.fX =
    (orxInput_IsActive("GoRight") ? 1.0f : 0.0f -
      (orxInput_IsActive("GoLeft") ? 1.0f : 0.0f));

  m_Speed.fX = m_Direction.fX * m_PADDLESPEED;
  orxObject_SetSpeed(object, &m_Speed);
}

