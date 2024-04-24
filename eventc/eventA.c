#include "eventA.h"


EVENT_DECLARE(initEventA)

void processEventA() {
	printf("process EventA\n");
}
static void initEventA() {
	REGISTER_EVENT_HANDLE(0x01, processEventA);
}


