#include "lock.h"
#include "game.h"

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

    srand(time(NULL));
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
        sys->logToConsole("%d ", lock->code[i]);
    }

}


static void drawBG(void) {
    gfx->drawBitmap(bgbitmap, 0, 0, kBitmapUnflipped);
    gfx->fillEllipse(SCREEN_WIDTH_CENTER - 107, SCREEN_HEIGHT_CENTER - 107, 214, 214, 0.f, 0.f, kColorBlack);
}

static void drawFace(void) {
    gfx->drawRotatedBitmap(facebitmap, SCREEN_WIDTH_CENTER, SCREEN_HEIGHT_CENTER, angle, 0.5f, 0.5f, 1.f, 1.f);
}

static int knobIndex = 0;
static void drawKnob(void) {
    if (changeKnob > 0) {
        changeKnob = 0;

        float diff = fabsf(fmod(targetAngle - angle, 360.f));

        if (diff < 3.f) {
            sound->sampleplayer->setSample(Game.mSamplePlayer, hitick);
            sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
            //sound->sampleplayer->setSample(Game.mSamplePlayer, extratick);
            //sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
        }
        else {
            sound->sampleplayer->setSample(Game.mSamplePlayer, extratick);
            sound->sampleplayer->play(Game.mSamplePlayer, 1, 1.f);
        }


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

void SetLockAngleChange(float a)
{

}

void DrawLock(Lock* lock)
{
    drawBG();
    drawFace();
}