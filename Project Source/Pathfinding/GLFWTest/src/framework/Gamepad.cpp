#include "Gamepad.h"


// Define the 'XButtonIDs' struct as 'XButtons'
XButtonIDs XButtons;

// 'XButtonIDs' - Default constructor
XButtonIDs::XButtonIDs()
{
      // These values are used to index the XINPUT_Buttons array,
      // accessing the matching XINPUT button value
 
      A = 0;
      B = 1;
      X = 2;
      Y = 3;
 
      DPad.Up    = 4;
      DPad.Down  = 5;
      DPad.Left  = 6;
      DPad.Right = 7;
 
      LShoulder = 8;
      RShoulder = 9;
 
      Start = 10;
      Back  = 11;
 
      LThumbstick = 12;
      RThumbstick = 13;
}

//Default constructor
Gamepad::Gamepad()
{

}

// Overloaded constructor
Gamepad::Gamepad(int a_iIndex)
{
    // Set gamepad index
    GamepadIndex = a_iIndex - 1;
 
    // Iterate through all gamepad buttons
    for (int i = 0; i < ButtonCount; i++)
    {
          bPrev_ButtonStates[i]   = false;
          bButtonStates[i]        = false;
          bGamepad_ButtonsDown[i] = false;
    }
}

// Update gamepad state
void Gamepad::Update()
{
	State = GetState(); // Obtain current gamepad state
 
    // Iterate through all gamepad buttons
    for (int i = 0; i < ButtonCount; i++)
    {
          // Set button state for current frame
          bButtonStates[i] = (State.Gamepad.wButtons &
             XINPUT_Buttons[i]) == XINPUT_Buttons[i];
 
          // Set 'DOWN' state for current frame
          bGamepad_ButtonsDown[i] = !bPrev_ButtonStates[i] &&
            bButtonStates[i];
    }
}

// Update button states for next frame
void Gamepad::RefreshState()
{
       memcpy(bPrev_ButtonStates, bButtonStates,
         sizeof(bPrev_ButtonStates));
}

// Return true if the left stick is inside its deadzone
bool Gamepad::LStick_InDeadzone()
{
       // Obtain the X & Y axes of the stick
       short sX = State.Gamepad.sThumbLX;
       short sY = State.Gamepad.sThumbLY;
 
       if (sX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
           sY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
           sX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE ||
           sY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
       {
           return false; // The stick is outside of its deadzone
       }
 
       return true; // The stick is inside its deadzone
}
 
// Return true if the right stick is inside its deadzone
bool Gamepad::RStick_InDeadzone()
{
       // Obtain the X & Y axes of the stick
       short sX = State.Gamepad.sThumbRX;
       short sY = State.Gamepad.sThumbRY;
 
       if (sX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
           sY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
           sX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE ||
           sY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
       {
           return false; // The stick is outside of its deadzone
       }
 
       return true; // The stick is inside its deadzone
}

// Return the X axis of the left stick
float Gamepad::LeftStick_X()
{
        // Obtain the X axis of the left stick
        short sX = State.Gamepad.sThumbLX;
 
        // Convert the value to a float
        float fX = (static_cast<float>(sX) / 32768.0f);
 
        return fX;
}
 
// Return the Y axis of the left stick
float Gamepad::LeftStick_Y()
{
        // Obtain the Y axis of the left stick
        short sY = State.Gamepad.sThumbLY;
 
        // Convert the value to a float
        float fY = (static_cast<float>(sY) / 32768.0f);
 
        return fY;
}
 
// Return the X axis of the right stick
float Gamepad::RightStick_X()
{
        // Obtain the X axis of the right stick
        short sX = State.Gamepad.sThumbRX;
 
        // Convert the value to a float
        float fX = (static_cast<float>(sX) / 32768.0f);
 
        return fX;
}
 
// Return the Y axis of the right stick
float Gamepad::RightStick_Y()
{
        // Obtain the Y axis of the left stick
        short sY = State.Gamepad.sThumbRY;
 
        // Convert the value to a float
        float fY = (static_cast<float>(sY) / 32768.0f);
 
        return fY;
}

// Return value of the left trigger
float Gamepad::LeftTrigger()
{
        // Obtain value of the trigger
        BYTE Trigger = State.Gamepad.bLeftTrigger;
 
        if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
              return Trigger / 255.0f;
 
        return 0.0f; // Trigger was not pressed
}
 
// Return value of the right trigger
float Gamepad::RightTrigger()
{
        // Obtain value of the trigger
        BYTE Trigger = State.Gamepad.bRightTrigger;
 
        if (Trigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD)
              return Trigger / 255.0f;
 
        return 0.0f; // Trigger was not pressed
}

// Return true if button is pressed
bool Gamepad::ButtonPressed(int a_iButton)
{
      if (State.Gamepad.wButtons & XINPUT_Buttons[a_iButton])
      {
            return true; // The button is pressed
      }
 
      return false; // The button is not pressed
}

// Frame-specific version of 'ButtonPressed' function
bool Gamepad::ButtonDown(int a_iButton)
{
       return bGamepad_ButtonsDown[a_iButton];
}

// Return gamepad state
XINPUT_STATE Gamepad::GetState()
{
      // Temporary XINPUT_STATE to return
      XINPUT_STATE GamepadState;
 
      // Zero memory
      ZeroMemory(&GamepadState, sizeof(XINPUT_STATE));
 
      // Get the state of the gamepad
      XInputGetState(GamepadIndex, &GamepadState);
 
      // Return the gamepad state
      return GamepadState;
}

// Return gamepad index
int Gamepad::GetIndex()
{
      return GamepadIndex;
}

// Return true if the gamepad is connected
bool Gamepad::Connected()
{
      // Zero memory
      ZeroMemory(&State, sizeof(XINPUT_STATE));
 
      // Get the state of the gamepad
      DWORD Result = XInputGetState(GamepadIndex, &State);
 
      if (Result == ERROR_SUCCESS)
            return true;  // The gamepad is connected
      else
            return false; // The gamepad is not connected
}

// Vibrate the gamepad (values of 0.0f to 1.0f only)
void Gamepad::Rumble(float a_fLeftMotor, float a_fRightMotor)
{
       // Vibration state
       XINPUT_VIBRATION VibrationState;
 
       // Zero memory
       ZeroMemory(&VibrationState, sizeof(XINPUT_VIBRATION));
 
       // Calculate vibration values
       int iLeftMotor  = int(a_fLeftMotor * 65535.0f);
       int iRightMotor = int(a_fRightMotor * 65535.0f);
 
       // Set vibration values
       VibrationState.wLeftMotorSpeed  = iLeftMotor;
       VibrationState.wRightMotorSpeed = iRightMotor;
 
       // Set the vibration state
       XInputSetState(GamepadIndex, &VibrationState);
}