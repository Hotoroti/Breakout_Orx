#include "Wall.h"

Wall::Wall() {
  orxConfig_Load("Wall.ini");

  Init();
}

Wall::~Wall() {

}

void Wall::Init() {
  orxVECTOR placePosition = orxVECTOR_0;
  orxVECTOR startPosition = orxVECTOR_0;
  orxVECTOR spacing = orxVECTOR_0;
  orxOBJECT* tempObject = nullptr;

  orxConfig_PushSection("Grid");

  orxConfig_GetVector("StartPos", &startPosition);
  orxConfig_GetVector("Spacing", &spacing);
  orxU32 countX = orxConfig_GetU32("CountX");
  orxU32 countY = orxConfig_GetU32("CountY");

  orxConfig_PopSection();
  // 🔹 Auto-center on X
  orxFLOAT totalWidth = (countX > 1)
    ? (spacing.fX * (countX - 1))
    : 0.0f;

  orxFLOAT startX = -totalWidth * 0.5f;


  for (orxU32 x = 0; x < countX; x++) {
    placePosition.fX = startX + (spacing.fX * x);
    for (orxU32 y = 0; y < countY; y++) {

      placePosition.fY = startPosition.fY + (spacing.fY * y);

      orxOBJECT* tempObject = orxObject_CreateFromConfig("RedWallObject");
      orxObject_SetPosition(tempObject, &placePosition);
    }
  }


}

orxU32 Wall::GetGridValue(const orxSTRING key) {
  orxU32 tempValue = 0;

  orxConfig_PushSection("Grid");
  tempValue = orxConfig_GetU32(key);
  orxConfig_PopSection();

  return tempValue;
}

void Wall::Update() {

}

void Wall::OnCollision() {

}
