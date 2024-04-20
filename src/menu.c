#include "game.h"
#include "menu.h"

int x = (400-86)/2;
int y = (240-16)/2;

void updateMenu(void) {
    gfx->clear(kColorWhite);
	gfx->setFont(Game.font);
	gfx->drawText("Hello, World", strlen("Hello, World"), kASCIIEncoding, x, y);
}