#include "Bomb.h"
#include "ResMng.h"

void Bomb::Draw()
{
    const float dist_x = 48.0f;
    const float dist_y = 48.0f;
    ResMng* rmng = ResMng::GetInstance();
    rmng->GetSprite(GetSprId())->RenderEx(dist_x * (GetCoord() % LINE_LENGTH) + SCREEN_MERGE, dist_y * (floor(GetCoord() / LINE_LENGTH)) + SCREEN_MERGE, 0, GetScale());
}

int Bomb::GetSprId()
{
    return spr_id;
}