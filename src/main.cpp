#include <unistd.h>
#include "input.h"
#include "gamelogic.h"

int main()
{
    printf("Connecting to wiimotes...\n");

    startInputPolling();

    // Connect to wiimotes
    while (!controllersConnected())
    {
        constexpr static unsigned ms = 10;
        usleep(ms * 1000);
    }

    printf("Connected to wiimotes!\n");

	newGame();

    stopInputPolling();
}
