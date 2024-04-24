#include <stdio.h>
#include "eventA.h"
#include "event_handlers.h"
EventHandler  g_EventHandlers[256];
int main(int argc, char *argv[])
{
	printf("for test eventc\n");
	g_EventHandlers[0x01]();
	return 0;
}
