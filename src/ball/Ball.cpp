#include "Ball.h"
Ball::Ball(const orxSTRING configName, orxOBJECT* levelsObject) {
  orxConfig_Load("Ball.ini");

  m_Object = orxObject_CreateFromConfig(configName);
  m_levelsObject = levelsObject;
  orxDisplay_GetScreenSize(&m_ScreenWidth, &m_ScreenHeight);

  m_CurrentBallSpeed = m_BASEBALLSPEED;
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

  if (m_CurrentPos.fY > 0.5 * m_ScreenHeight) {
    orxConfig_PushSection("PointValues");

    orxFLOAT livesValue = orxConfig_GetFloat("Lives") - 1;
    orxConfig_SetFloat("Lives", livesValue);

    orxCHAR text[64];
    orxString_NPrint(text, sizeof(text), "Score: %0.0f", livesValue);
    orxObject_SetTextString(m_levelsObject, text);

    orxConfig_PopSection();

    m_HasStarted = false;
  }

  m_Speed.fX = m_Direction.fX * m_CurrentBallSpeed;
  m_Speed.fY = m_Direction.fY * m_CurrentBallSpeed;

  orxObject_SetSpeed(m_Object, &m_Speed);
}

void Ball::OnWallCollision(orxVECTOR collisionNormal) {
  if (orxMath_Abs(collisionNormal.fX) > orxMath_Abs(collisionNormal.fY)) {
    m_Direction.fX *= -1;
  }
  else {
    m_Direction.fY *= -1;
  }
}

void Ball::OnPaddleCollision(orxOBJECT* paddleOBJ)
{
  orxVECTOR ballPos, paddlePos;
  orxObject_GetWorldPosition(m_Object, &ballPos);
  orxObject_GetWorldPosition(paddleOBJ, &paddlePos);

  orxOBOX box;
  orxObject_GetBoundingBox(paddleOBJ, &box);

  orxFLOAT paddleHalfWidth = box.vX.fX;

  orxFLOAT hit =
    (ballPos.fX - paddlePos.fX) / paddleHalfWidth;

  hit = orxCLAMP(hit, -1.0f, 1.0f);

  orxFLOAT maxAngle = orxMATH_KF_PI * 0.33f;
  orxFLOAT angle = hit * maxAngle;

  m_Direction.fX = orxMath_Sin(angle);
  m_Direction.fY = -orxMath_Cos(angle);

  orxVector_Normalize(&m_Direction, &m_Direction);
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

  orxVECTOR newPos = { paddlePos.fX, paddlePos.fY -50, m_CurrentPos.fZ };
  orxObject_SetWorldPosition(m_Object, &newPos);
}

void Ball::IncreaseSpeed(orxFLOAT speedMod) {
  orxConfig_PushSection("BallSettings");
  if (m_CurrentBallSpeed < orxConfig_GetFloat("BallMaxSpeed")) {
    m_CurrentBallSpeed += speedMod;
    orxLOG("Current speed: %f", m_CurrentBallSpeed);
  }
  orxConfig_PopSection();
}
