#include <thread>
#include <unistd.h>
#include <map>
#include <cstring>
#include "input.h"
#include "wiiuse.h"

using std::thread;
using std::map;
using std::array;

wiimote** wiimotes;

InputState inputState;

thread pollingThread;
bool running;
bool wiimotesConnected = false;

void connectToControllers()
{
	int found, connected;
	wiimotes = wiiuse_init(1);

	while (1) {
		printf("[WII-INFO] Searching for wiimotes, enter discovery now\n");
		found = wiiuse_find(wiimotes, 1, 5);
		if (!found) {
			printf("[WII-ERR] Found %i wiimotes out of 1 expected...\n", found);
			exit(1); }

		connected = wiiuse_connect(wiimotes, 1);
		if (connected == 1) {
			printf("[WII-INFO] Connected to all wiimotes!\n"); break; }
		else {
			printf("[WII-ERR] Failed to connect\n"); exit(1); }}
	
	wiiuse_set_leds(wiimotes[0], WIIMOTE_LED_1);
	wiiuse_set_leds(wiimotes[1], WIIMOTE_LED_4);
	wiiuse_rumble(wiimotes[0], 1);
	wiiuse_rumble(wiimotes[1], 1);
	usleep(2000000);
	wiiuse_rumble(wiimotes[0], 0);
	wiiuse_rumble(wiimotes[1], 0);

	wiimotesConnected = true;
}

void startInputPolling()
{
    pollingThread = thread([]()
    {
        connectToControllers();

        running = true;

        while (running)
        {
            if (wiiuse_poll(wiimotes, 1) && wiimotes[0]->event == WIIUSE_EVENT)
            {
                static map<WiiButton, int> buttonNames
                {
                    {UP, WIIMOTE_BUTTON_RIGHT},
                    {RIGHT, WIIMOTE_BUTTON_DOWN},
                    {DOWN, WIIMOTE_BUTTON_LEFT},
                    {LEFT, WIIMOTE_BUTTON_UP},
                    {A, WIIMOTE_BUTTON_A},
                    {B, WIIMOTE_BUTTON_B},
                    {ONE, WIIMOTE_BUTTON_ONE},
                    {TWO, WIIMOTE_BUTTON_TWO},
                };
                
                for (const auto entry : buttonNames)
                {
                    inputState[entry.first].isPressed = IS_PRESSED(wiimotes[0], entry.second);
                    inputState[entry.first].isHeld = IS_HELD(wiimotes[0], entry.second);
                }
            }
        }
    });
}

bool controllersConnected()
{
    return wiimotesConnected;
}

InputState getButtonStates()
{
    return inputState;
}

void stopInputPolling()
{
    running = false;
}
