#include "input/Input.h"
#include "raylib.h"

bool Input::MoveUp()    { return IsKeyDown(KEY_W); }
bool Input::MoveDown()  { return IsKeyDown(KEY_S); }
bool Input::MoveLeft()  { return IsKeyDown(KEY_A); }
bool Input::MoveRight() { return IsKeyDown(KEY_D); }
