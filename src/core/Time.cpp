#include "core/Time.h"
#include "raylib.h"

float Time::DeltaTime()
{
    return GetFrameTime();
}
