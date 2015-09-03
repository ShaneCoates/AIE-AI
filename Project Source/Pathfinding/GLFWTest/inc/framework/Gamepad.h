/*-----------------------------------------------------------------------------

		Author:			Shane Coates
		Description:	Gamepad class
						Used to receive commands from a gamepad/controller

-----------------------------------------------------------------------------*/

#ifndef GAMEPAD_H
#define	GAMEPAD_H

#include <Windows.h>
#include <Xinput.h>

// XInput Button values
static const WORD XINPUT_Buttons[] = {
      XINPUT_GAMEPAD_A,
      XINPUT_GAMEPAD_B,
      XINPUT_GAMEPAD_X,
      XINPUT_GAMEPAD_Y,
      XINPUT_GAMEPAD_DPAD_UP,
      XINPUT_GAMEPAD_DPAD_DOWN,
      XINPUT_GAMEPAD_DPAD_LEFT,
      XINPUT_GAMEPAD_DPAD_RIGHT,
      XINPUT_GAMEPAD_LEFT_SHOULDER,
      XINPUT_GAMEPAD_RIGHT_SHOULDER,
      XINPUT_GAMEPAD_START,
      XINPUT_GAMEPAD_BACK,
	  XINPUT_GAMEPAD_LEFT_THUMB,
      XINPUT_GAMEPAD_RIGHT_THUMB
     
};
 
// XInput Button IDs
struct XButtonIDs
{
      // Public variables
 
      int A,B,X,Y; // 'Action' buttons
 
      // Directional Pad (D-Pad)
      struct DirectionalPad
      {
            int Up,Down,Left,Right;
      }DPad;
 
      // Shoulder ('Bumper') buttons
      int LShoulder, RShoulder;
 
      // Thumbstick buttons
      int LThumbstick, RThumbstick;
 
      int Start; // 'START' button
      int Back;  // 'BACK' button
 
      // Function prototypes
 
      XButtonIDs(); // Default constructor
};

class Gamepad
{
public:
	//constructors
	Gamepad();								//Default constructor
	Gamepad(int a_iIndex);					//Overload constructor

	void Update();							//Update gamepad state
	void RefreshState();					// Update button states for next frame

	 // Thumbstick functions
    bool LStick_InDeadzone();				// Return true if left stick is inside its deadzone
    bool RStick_InDeadzone();				// Return true if right stick is inside its deadzone
 
    float LeftStick_X();					// Return the X axis of the left stick
    float LeftStick_Y();					// Return the Y axis of the left stick
    float RightStick_X();					// Return the X axis of the right stick
    float RightStick_Y();					// Return the Y axis of the right stick

	// Trigger functions
    float LeftTrigger();					// Return value of the left trigger
    float RightTrigger();					// Return value of the right trigger

	// Button functions
    bool ButtonPressed(int a_iButton);		// Return true if button is pressed
	// Frame-specific version of 'ButtonPressed'
    bool ButtonDown(int a_iButton);
 

	//Utility functions
	XINPUT_STATE GetState();				//Return gamepad State
	int GetIndex();							//Return gamepad index
	bool Connected();						//Return true if gamepad is connected	
	
	// Vibrate the gamepad
    void Rumble(float a_fLeftMotor = 0.0f, float a_fRightMotor = 0.0f);
private:
	XINPUT_STATE State;						//Current gamepad state
	int GamepadIndex;						//Gamepad index (eg. 1, 2, 3, 4)

	static const int ButtonCount = 14;		// Total gamepad buttons
    bool bPrev_ButtonStates[ButtonCount];	// Previous frame button states
    bool bButtonStates[ButtonCount];		// Current frame button states
 
    bool bGamepad_ButtonsDown[ButtonCount]; // Buttons pressed on current frame
};

#endif

// Externally define the 'XButtonIDs' struct as 'XButtons'
extern XButtonIDs XButtons;