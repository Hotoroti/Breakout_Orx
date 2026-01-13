#include "Ball.h"
Ball::Ball(const orxSTRING configName) {
  m_Object = orxObject_CreateFromConfig(configName);
  orxVector_Set(&m_Direction, 0, 0, 0);
  orxVector_Set(&m_Speed, 0, 0, 0);
  m_HasStarted = false;
}

Ball::~Ball() {
  if (m_Object) {
    orxObject_Delete(m_Object);
    m_Object = nullptr;
  }
}

void Ball::Update() {
  if (!m_HasStarted && orxInput_HasBeenActivated("StartGame")) {
    Start();
  }

  m_Speed.fX = m_Direction.fX * m_BALLSPEED;
  m_Speed.fY = m_Direction.fY * m_BALLSPEED;

  orxObject_SetSpeed(m_Object, &m_Speed);
}

void Ball::OnCollision() {
  m_Direction.fY *= -1;
}

void Ball::Start() {
  orxVector_Set(&m_Direction, 0, -1, 0);
  m_HasStarted = true;
}
