#include <thread>
#include <unistd.h>
#include <map>
#include "input.h"
#include "wiiuse.h"

using std::map;
using std::array;

wiimote** wiimotes;

bool controllersConnected()
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

	return true;
}

InputState getButtonStates()
{
    static array<ButtonState, LENGTH> lastResult;
    array<ButtonState, LENGTH> result;

    if (wiiuse_poll(wiimotes, 1) && wiimotes[0]->event == WIIUSE_EVENT)
    {
        static map<WiiButton, int> buttonNames
        {
            {UP, WIIMOTE_BUTTON_UP},
            {RIGHT, WIIMOTE_BUTTON_RIGHT},
            {DOWN, WIIMOTE_BUTTON_DOWN},
            {LEFT, WIIMOTE_BUTTON_LEFT},
            {A, WIIMOTE_BUTTON_A},
            {B, WIIMOTE_BUTTON_B},
            {ONE, WIIMOTE_BUTTON_ONE},
            {TWO, WIIMOTE_BUTTON_TWO},
        };
        
        for (const auto entry : buttonNames)
        {
            if (IS_PRESSED(wiimotes[0], entry.second))
            {
                result[entry.first].isPressed = true;
                
                if (lastResult[entry.first].isPressed)
                {
                    result[entry.first].isHeld = true;
                }
            }
        }
    }

    lastResult = result;

    return result;
}
