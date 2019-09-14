#include <unistd.h>
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "input.h"
#include "gamelogic.h"


int main()
{
    printf("Connecting to wiimotes...\n");

    // Connect to wiimotes
    while (!controllersConnected())
    {
        constexpr static unsigned ms = 10;
        usleep(ms * 1000);
    }

    printf("Connected to wiimotes!\n");

	srand(time(NULL));

	newGame();
}
