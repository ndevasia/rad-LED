#include "radLED.h"
#include "input.h"
#include "character.h"
#include <map>

namespace LEDGameFrame
{
	LEDGameFrame::pixel pixelArray[64];

	LEDGameFrame::pixel[][] GameFrame(std::map map, Character *player, Character[] enemies)
	{
		if (map[RIGHT].isHeld)
		{
			player.location += 1;
			
		}
		else if(map[LEFT].isHeld && currCol > 0)
		{
			player.location -= 1;
		}

		if (map[TWO].isPressed)
		{
			//attacking code
		}
		else if (map[B].isHeld) 
		{
			//recharge code
		}
		pixelArray[currCol] = { 0, 255, 0 };
		return pixelArray; 
	}

}