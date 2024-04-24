#ifndef EVENT_HANDLERS_H
#define EVENT_HANDLERS_H

typedef void (*EventHandler)(void);
extern EventHandler  g_EventHandlers[256];

#define REGISTER_EVENT_HANDLE(eventId, handler) do { \
 if ((eventId) < sizeof(g_EventHandlers) / sizeof(g_EventHandlers[0])) { \
	g_EventHandlers[(eventId)] = (handler); \
 }\
} while (0)

#define EVENT_DECLARE(name) \
static void name() __attribute__((constructor));
#endif // EVENT_HANDLERS_H
