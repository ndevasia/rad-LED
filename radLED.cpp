#include "radLED.h"
#include "input.h"

namespace LEDGameFrame
{
	int currCol = 0;

	LEDGameFrame::pixel pixelArray[64];

	LEDGameFrame::pixel[][] GameFrame(std::map map)
	{
		if (map[RIGHT].isHeld)
		{
			currCol += 1;
			
		}
		else if(map[LEFT].isHeld && currCol > 0)
		{
			currCol -= 1;
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