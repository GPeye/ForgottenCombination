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

static char* score;
static int ww = 0;
int scorewidth = 0;
static void displayScore(void) {
    gfx->setFont(Game.font);
    ww = sys->formatString(&score, "%d", 12);
    scorewidth = gfx->getTextWidth(Game.font, score, strlen(score), kASCIIEncoding, 0);
    gfx->setDrawMode(kDrawModeCopy);
    gfx->drawText(score, strlen(score), kASCIIEncoding, 20, 20);
    gfx->setDrawMode(kDrawModeCopy);
    sys->realloc(score, 0);
}

void updateUnlock(void) {
    //drawBG();
    handleCrankRotate();
    DrawLock(&lock);
    UpdateLock(&lock);

    displayScore();
    //drawKnob();
    //drawFace();
}