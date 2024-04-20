#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include "pd_api.h"


#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 240

extern const struct playdate_graphics *gfx;
extern const struct playdate_sys *sys;
extern const struct playdate_display *display;
extern const struct playdate_file *file;
extern const struct playdate_sound *sound;

typedef enum
{
    State_SplashScreen,
    State_Menu,
    State_InGame,
    State_Scoreboard,
    State_Tutorial
} GameScene;

typedef struct {
    PlaydateAPI *gPd;
    GameScene gState;

    const char* fontpath;
    LCDFont* font;
    
    SamplePlayer* mSamplePlayer;


    FilePlayer* musicPlayer;

    struct {
        float time;
    } GameScore;

} GameStruct;

extern GameStruct Game;

void InitGame(PlaydateAPI *pd);
int Update(void *userdata);

#endif