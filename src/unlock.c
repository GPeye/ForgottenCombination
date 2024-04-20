#include "unlock.h"
#include "math.h"
#include "lock.h"

/*
Unlock controls the level / tells the lock what to do / reacts to changes in state

*/


#define SCREEN_WIDTH_CENTER 200
#define SCREEN_HEIGHT_CENTER 120

static int changeKnob = 0;
static float crankMovement = 0.f;

static float targetAngle = 45.f;

static float angle = 0.f;

Lock lock;

void initLockSceneData(void) {

    InitLock(&lock);

    GenerateNewCodes(&lock, 3);
}

static void handleCrankRotate(void) {
    SetLockAngle(sys->getCrankAngle());
    SetLockAngleChange(sys->getCrankChange());
    //angle = sys->getCrankAngle();
    /*crankMovement += sys->getCrankChange();

    if (crankMovement > 5.f || crankMovement < -5.f) {
        crankMovement = 0.f;
        changeKnob = 1;
    }*/
}

void updateUnlock(void) {
    //drawBG();
    DrawLock(&lock);
    handleCrankRotate();
    //drawKnob();
    //drawFace();
}