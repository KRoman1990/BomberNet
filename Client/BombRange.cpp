#include "BombRange.h"
#include "ResMng.h"

void BombRange::Draw()
{
    const float dist_x = 48.0f;
    const float dist_y = 48.0f;
    ResMng* rmng = ResMng::GetInstance();
    rmng->GetSprite(RES_SPRITE_BOMBRANGE)->RenderEx(dist_x * (GetCoord() % LINE_LENGTH) + SCREEN_MERGE, dist_y * (floor(GetCoord() / LINE_LENGTH)) + SCREEN_MERGE, 0, GetScale());
}