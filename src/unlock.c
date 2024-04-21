#include "unlock.h"
#include "math.h"
#include "lock.h"

/*
Unlock controls the level / tells the lock what to do / reacts to changes in state

*/

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
    handleCrankRotate();
    DrawLock(&lock);
    UpdateLock(&lock);
    //drawKnob();
    //drawFace();
}