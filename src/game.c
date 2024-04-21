#include "game.h"
#include "menu.h"
#include "unlock.h"

const struct playdate_graphics* gfx = NULL;
const struct playdate_sys* sys = NULL;
const struct playdate_display* display = NULL;
const struct playdate_file* file = NULL;
const struct playdate_sound* sound = NULL;

GameStruct Game;

AudioSample* music;

static void initFonts(void) {
    const char* fontpath = "fonts/midnight45";
    const char* err;
	Game.font = gfx->loadFont(fontpath, &err);
	if (Game.font == NULL)
		sys->error("%s:%i Couldn't load font %s: %s", __FILE__, __LINE__, fontpath, err);
}

void InitGame(PlaydateAPI* pd)
{
    pd->display->setRefreshRate(30);
    //Game.gState = State_Menu;
    Game.gState = State_InGame;
    Game.gPd = pd;
    gfx = Game.gPd->graphics;
	sys = Game.gPd->system;
	display = Game.gPd->display;
	file = Game.gPd->file;
	sound = Game.gPd->sound;

    Game.mSamplePlayer = Game.gPd->sound->sampleplayer->newPlayer();
	Game.musicPlayer = Game.gPd->sound->fileplayer->newPlayer();
	Game.gPd->sound->fileplayer->loadIntoPlayer(Game.musicPlayer, "sound/suped.mp3");

    initFonts();

    initLockSceneData();

	//sound->fileplayer->play(Game.musicPlayer, 0);
}

int Update(void* userdata) {
    switch (Game.gState)
	{
	case State_Menu:
		updateMenu();
		break;
	case State_InGame:
		updateUnlock();
		break;
	default:
		break;
	}

    return 1;
}