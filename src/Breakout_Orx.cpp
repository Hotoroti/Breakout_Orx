/**
 * @file Breakout_Orx.cpp
 * @date 13-Jan-2026
 */

#include "orx.h"
#include "orxExtensions.h"
#include "paddle/Paddle.h"
#include "ball/Ball.h"
#include "wall/Wall.h"

Paddle* m_paddle;
Ball* m_ball;
Wall* m_wall;

#ifdef __orxMSVC__

/* Requesting high performance dedicated GPU on hybrid laptops */
__declspec(dllexport) unsigned long NvOptimusEnablement        = 1;
__declspec(dllexport) int AmdPowerXpressRequestHighPerformance = 1;

#endif // __orxMSVC__

/** Update function, it has been registered to be called every tick of the core clock
 */
void orxFASTCALL Update(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{
  // Should quit?
  if(orxInput_HasBeenActivated("Quit"))
  {
    // Send close event
    orxEvent_SendShort(orxEVENT_TYPE_SYSTEM, orxSYSTEM_EVENT_CLOSE);
  }

  m_paddle->Update();
  m_ball->FollowPaddle(m_paddle->object);
  m_ball->Update();
}

/** Camera Update function, it has been registered to be called every tick of the core clock, after physics & objects have been updated
*/
void orxFASTCALL CameraUpdate(const orxCLOCK_INFO *_pstClockInfo, void *_pContext)
{
  // Get MainCamera proxy object
  orxConfig_PushSection("MainCamera");
  orxOBJECT *pstMainCamera = orxOBJECT(orxStructure_Get(orxConfig_GetU64("ID")));
  orxConfig_PopSection();
  if(pstMainCamera)
  {
    // Update & move the camera here
    // [...]

    // Round its position
    orxVECTOR vPosition;
    orxObject_SetPosition(pstMainCamera, orxVector_Round(&vPosition, orxObject_GetPosition(pstMainCamera, &vPosition)));
  }
}

orxSTATUS orxFASTCALL PhysicsEventHandler(const orxEVENT* _pstEvent)
{
  if (_pstEvent->eID == orxPHYSICS_EVENT_CONTACT_ADD) {
    orxPHYSICS_EVENT_PAYLOAD* payload =
      (orxPHYSICS_EVENT_PAYLOAD*)_pstEvent->pstPayload;

    orxOBJECT* pstRecipientObject, * pstSenderObject;

    pstSenderObject = orxOBJECT(_pstEvent->hSender);
    pstRecipientObject = orxOBJECT(_pstEvent->hRecipient);

    orxConfig_PushSection((orxSTRING)orxObject_GetName(pstSenderObject));
    orxSTRING senderObjectType = (orxSTRING)orxConfig_GetString("ObjectType");
    orxConfig_PopSection();

    orxSTRING recipientObjectName = (orxSTRING)orxObject_GetName(pstRecipientObject);

    if (orxString_Compare(senderObjectType, "wall") == 0) {
      m_wall->OnCollision(pstSenderObject,
        [ball = m_ball](orxFLOAT speedMod) {ball->IncreaseSpeed(speedMod); }
      );
      orxObject_SetLifeTime(pstSenderObject, 0);
    }

    if (orxString_Compare(recipientObjectName, "BallObject") == 0) {
      if (orxString_Compare(senderObjectType, "paddle") == 0) {
        m_ball->OnPaddleCollision(pstSenderObject);
        m_paddle->OnCollision();
      }
      else {
        m_ball->OnWallCollision(payload->vNormal);
      }
    }
  }
  return orxSTATUS_SUCCESS;
}


/** Init function, it is called when all orx's modules have been initialized
 */
orxSTATUS orxFASTCALL Init()
{
  // Init extensions
  InitExtensions();

  // Push [Main] as the default config section
  orxConfig_PushSection("Main");

  // Create the viewports
  for(orxS32 i = 0, iCount = orxConfig_GetListCount("ViewportList"); i < iCount; i++)
  {
    orxViewport_CreateFromConfig(orxConfig_GetListString("ViewportList", i));
  }

  // Register the Update & CameraUpdate functions to the core clock
  orxClock_Register(orxClock_Get(orxCLOCK_KZ_CORE), Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);
  orxClock_Register(orxClock_Get(orxCLOCK_KZ_CORE), CameraUpdate, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_LOWER);

  orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, PhysicsEventHandler);
    
  orxObject_CreateFromConfig("ArenaBackgroundObject");
  orxObject_CreateFromConfig("ScoreObject");
  orxObject_CreateFromConfig("LivesObject");
  
  m_paddle = new Paddle("PaddleObject");

  m_wall = new Wall();
  m_ball = new Ball("BallObject");

  // Done!
  return orxSTATUS_SUCCESS;
}

/** Run function, it should not contain any game logic
 */
orxSTATUS orxFASTCALL Run()
{
  // Return orxSTATUS_FAILURE to instruct orx to quit
  return orxSTATUS_SUCCESS;
}

/** Exit function, it is called before exiting from orx
 */
void orxFASTCALL Exit()
{
  // Exit from extensions
  ExitExtensions();

  // Let orx clean all our mess automatically. :)
}

/** Bootstrap function, it is called before config is initialized, allowing for early resource storage definitions
 */
orxSTATUS orxFASTCALL Bootstrap()
{
  // Bootstrap extensions
  BootstrapExtensions();

  // Return orxSTATUS_FAILURE to prevent orx from loading the default config file
  return orxSTATUS_SUCCESS;
}

/** Main function
 */
int main(int argc, char **argv)
{
  // Set the bootstrap function to provide at least one resource storage before loading any config files
  orxConfig_SetBootstrap(Bootstrap);

  // Execute our game
  orx_Execute(argc, argv, Init, Run, Exit);

  // Done!
  return EXIT_SUCCESS;
}
