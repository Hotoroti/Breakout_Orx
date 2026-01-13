#include "Ball.h"
Ball::Ball(const orxSTRING configName) {
  orxConfig_Load("Ball.ini");

  m_Object = orxObject_CreateFromConfig(configName);
  orxDisplay_GetScreenSize(&m_ScreenWidth, &m_ScreenHeight);
}

Ball::~Ball() {
  if (m_Object) {
    orxObject_Delete(m_Object);
    m_Object = nullptr;
  }
}

void Ball::Update() {
  orxObject_GetWorldPosition(m_Object, &m_CurrentPos);
  if (!m_HasStarted && orxInput_HasBeenActivated("StartGame")) {
    Start();
  }  
  if (m_CurrentPos.fX > 0.5 * m_ScreenWidth || m_CurrentPos.fX < -0.5 * m_ScreenWidth) {
    m_Direction.fX *= -1;
  }

  if (m_CurrentPos.fY < -0.5 * m_ScreenHeight) {
    m_Direction.fY *= -1;
  }

  m_Speed.fX = m_Direction.fX * m_BALLSPEED;
  m_Speed.fY = m_Direction.fY * m_BALLSPEED;

  orxObject_SetSpeed(m_Object, &m_Speed);
}

void Ball::OnCollision() {
  m_Direction.fY *= -1;
}

void Ball::Start() {
  orxVector_Set(&m_Direction, 1, -1, 0);
  m_HasStarted = true;
}

void Ball::FollowPaddle(orxOBJECT* paddleObject) {
  if (m_HasStarted)
    return;

  orxVECTOR paddlePos = orxVECTOR_0;
  orxObject_GetWorldPosition(paddleObject, &paddlePos);

  orxVECTOR newPos = { paddlePos.fX, 350, m_CurrentPos.fZ };
  orxObject_SetWorldPosition(m_Object, &newPos);
}
