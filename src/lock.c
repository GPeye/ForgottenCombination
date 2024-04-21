#include "lock.h"
#include "game.h"
#include "time.h"

LCDBitmap* bgbitmap;
LCDBitmap* lockbitmap;
LCDBitmap* facebitmap;

LCDBitmap* knob1bitmap;
LCDBitmap* knob2bitmap;
LCDBitmap* knob3bitmap;
LCDBitmap* currentKnob;

#define SCREEN_WIDTH_CENTER 200
#define SCREEN_HEIGHT_CENTER 120

AudioSample* tick;
AudioSample* hitick;
AudioSample* extratick;

static float angle = 0.f;
static int knobShouldChange = 0;
static int playClick = 0;
static float movement = 0.f;
static int currentNumberOnDial = 0;
static int targetNumber = 35;

void InitLock(Lock* lock)
{
    const char* err;
    bgbitmap = gfx->loadBitmap("assets/lockback", &err);
    lockbitmap = gfx->loadBitmap("assets/lockbody", &err);
    facebitmap = gfx->loadBitmap("assets/lockface", &err);
    currentKnob = knob1bitmap = gfx->loadBitmap("assets/lockknob1", &err);
    knob2bitmap = gfx->loadBitmap("assets/lockknob2", &err);
    knob3bitmap = gfx->loadBitmap("assets/lockknob3", &err);

    tick = sound->sample->load("sound/clicklower");
    if (tick == NULL) {
        sys->logToConsole("failed to load tick");
    }
    hitick = sound->sample->load("sound/clickhi");
    if (tick == NULL) {
        sys->logToConsole("failed to load hitick");
    }
    extratick = sound->sample->load("sound/clickextra");
    if (tick == NULL) {
        sys->logToConsole("failed to load extratick");
    }

    srand(sys->getCurrentTimeMilliseconds);
}

void GenerateNewCodes(Lock* lock, int numberOfCodes)
{
    int i;
    for (i = 0; i < CODELEN; i++)
    {
        if (i < numberOfCodes) {
            lock->code[i] = rand() % 39;
        }
        else {
            lock->code[i] = 0;
        }
    }

}


static void drawBG(void) {
    gfx->drawBitmap(bgbitmap, 0, 0, kBitmapUnflipped);
    gfx->fillEllipse(SCREEN_WIDTH_CENTER - 107, SCREEN_HEIGHT_CENTER - 107, 214, 214, 0.f, 0.f, kColorBlack);
    gfx->fillTriangle(210,0,190,0,200,10,kColorWhite);
}

static void drawFace(void) {
    gfx->drawRotatedBitmap(facebitmap, SCREEN_WIDTH_CENTER, SCREEN_HEIGHT_CENTER, angle, 0.5f, 0.5f, 1.f, 1.f);
}

static int knobIndex = 0;
static void drawKnob(void) {
    if (knobShouldChange > 0) {
        knobShouldChange = 0;

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
            knobIndex = 2;
            break;
        }
    }
    gfx->drawBitmap(currentKnob, SCREEN_WIDTH_CENTER - 50, SCREEN_HEIGHT_CENTER - 47, kBitmapUnflipped);
}

void SetLockAngle(float a) {
    angle = a;
}

void SetLockAngleChange(float a) {
    movement += a;

    if (movement > 9.f) {
        movement -= 9.f;
        knobShouldChange = 1;
        playClick = 1;
    } else if (movement <= 0.f) {
        movement += 9.f;
        knobShouldChange = -1;
        playClick = 1;
    }
}

static void playSound(void) {
    if(playClick > 0) {
        playClick = 0;

        if (currentNumberOnDial == targetNumber) {
            sound->sampleplayer->setSample(Game.mSamplePlayer, hitick);
            sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
            //sound->sampleplayer->setSample(Game.mSamplePlayer, extratick);
            //sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
        }
        else {
            sound->sampleplayer->setSample(Game.mSamplePlayer, extratick);
            sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
        }
    }
}

static getCurrentNumber(){
    float num = 40.f - (angle / 9.f);
    sys->logToConsole("%d",(int)round(num));
    currentNumberOnDial = (int)round(num);
}

void DrawLock(Lock* lock) {
    drawBG();
    drawFace();
    drawKnob();
}

void UpdateLock(Lock* lock) {
    playSound();

    getCurrentNumber();
}