#include <stdio.h>
#include <stdlib.h>

#include "pd_api.h"
#include "game.h"

#ifdef _WINDLL
__declspec(dllexport)
#endif
int eventHandler(PlaydateAPI* pd, PDSystemEvent event, uint32_t arg)
{
	if ( event == kEventInit )
	{
		InitGame(pd);
		pd->system->setUpdateCallback(Update, pd);
	}
	
	return 0;
}