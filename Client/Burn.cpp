#include "Burn.h"
#include "ResMng.h"

void Burn::Draw()
{
    const float dist_x = 48.0f;
    const float dist_y = 48.0f;
    ResMng* rmng = ResMng::GetInstance();
    rmng->GetSprite(RES_SPRITE_BURN_1)->RenderEx(dist_x * (GetCoord() % LINE_LENGTH) + SCREEN_MERGE, dist_y * (floor(GetCoord() / LINE_LENGTH)) + SCREEN_MERGE, 0, GetScale());
}