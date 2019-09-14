#pragma once
/* this is input.h, Jake's header file for input */
#ifndef INPUT_H 
#define INPUT_H  
#include <map>   
enum WiiButton {    
	UP = 0,    
	RIGHT,    
	DOWN,   
	LEFT,   
	A,    
	B,    
	ONE,    
	TWO,    
	LENGTH  // DO NOT USE, strictly for my implementation
};  

struct ButtonState {    
	bool isPressed;    
	bool isHeld; 
}; 

void start(); 
bool controllersConnected(); 
std::array getButtonStates(); 
void stop();  
#endif
/* END OF INPUT.H */