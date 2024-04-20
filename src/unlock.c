#include "unlock.h"

LCDBitmap* bgbitmap;
LCDBitmap* lockbitmap;
LCDBitmap* facebitmap;

LCDBitmap* knob1bitmap;
LCDBitmap* knob2bitmap;
LCDBitmap* knob3bitmap;
LCDBitmap* currentKnob;

AudioSample* tick;

#define SCREEN_WIDTH_CENTER 200
#define SCREEN_HEIGHT_CENTER 120

static int changeKnob = 0;
static float crankMovement = 0.f;

void initLockSceneData(void) {
    const char* err;
    bgbitmap = gfx->loadBitmap("assets/lockback", &err);
    lockbitmap = gfx->loadBitmap("assets/lockbody", &err);
    facebitmap = gfx->loadBitmap("assets/lockface", &err);
    currentKnob = knob1bitmap = gfx->loadBitmap("assets/lockknob1", &err);
    knob2bitmap = gfx->loadBitmap("assets/lockknob2", &err);
    knob3bitmap = gfx->loadBitmap("assets/lockknob3", &err);

    tick = sound->sample->load("sound/click");
    if(tick == NULL){
        sys->logToConsole("failed to load tick");
    }
    
}

static void drawBG(void) {
    gfx->drawBitmap(bgbitmap,0,0,kBitmapUnflipped);
    //gfx->drawBitmap(lockbitmap,SCREEN_WIDTH_CENTER-107,SCREEN_HEIGHT_CENTER-107,kBitmapUnflipped);
    gfx->fillEllipse(SCREEN_WIDTH_CENTER-107,SCREEN_HEIGHT_CENTER-107,214,214,0.f,0.f,kColorBlack);
}

static int knobIndex = 0;
static void drawKnob(void) {
    if(changeKnob > 0){
        changeKnob = 0;

        sound->sampleplayer->setSample(Game.mSamplePlayer,tick);
        sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);

        switch (knobIndex) {
            case 2:
                currentKnob = knob2bitmap;
                knobIndex--;
                break;
            case 1:
                currentKnob = knob3bitmap;
                knobIndex--;
                break;
            case 0:
                currentKnob = knob1bitmap;
                knobIndex=2;
                break;
        }
    }
    gfx->drawBitmap(currentKnob,SCREEN_WIDTH_CENTER-50,SCREEN_HEIGHT_CENTER-47,kBitmapUnflipped);
}

static float angle = 0.f;
static int faceCenterX = SCREEN_WIDTH_CENTER-104;
static int faceCenterY = SCREEN_HEIGHT_CENTER-104;

static void drawFace(void) {
    //gfx->drawBitmap(facebitmap,faceCenterX,faceCenterY,kBitmapUnflipped);
    gfx->drawRotatedBitmap(facebitmap,SCREEN_WIDTH_CENTER, SCREEN_HEIGHT_CENTER, angle, 0.5f, 0.5f,1.f,1.f);
}

static void handleCrankRotate(void) {
    angle = sys->getCrankAngle();
    crankMovement += sys->getCrankChange();

    if (crankMovement > 5.f || crankMovement < -5.f) {
        crankMovement = 0.f;
        changeKnob = 1;
    }
}

void updateUnlock(void) {
    drawBG();
    handleCrankRotate();
    drawKnob();
    drawFace();
}