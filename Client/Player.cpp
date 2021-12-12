#include "ResMng.h"
#include "Player.h"

Player* Player::GetInstance()
{
	static Player* instance = nullptr;
    if (!instance)
    {
        instance = new Player();
        instance->SetScale(1.5f);
    }
	return instance;
}

Player::Player(unsigned int coord)
{
    SetCoordPrev(GetCoord());
    SetCoord(coord);
}

int Player::GetId()
{
	WaitForSingleObject(mut_id, 0);
	return m_id;
}

int Player::GetCoordPrev()
{
	WaitForSingleObject(mut_coord, 0);
	return m_player_coordinates_prev;
}

void Player::SetId(int id_recv)
{
	WaitForSingleObject(mut_id, 0);
	m_id = id_recv;
}

void Player::SetCoordPrev(int prev_recv)
{
	WaitForSingleObject(mut_coord, 0);
	m_player_coordinates_prev = prev_recv;
}

void Player::SendPack(Commands command)
{
    int packet[2] = { command, GetId() };
    auto addr = ConnectManager::GetInstance()->GetAddr();
    sendto(ConnectManager::GetInstance()->GetSocket(), 
        (char*)packet, 
        sizeof(int) * 2, 
        0, 
        (sockaddr*)&addr, 
        sizeof(ConnectManager::GetInstance()->GetAddr())
    );
}

void Player::SetDirection(int id, int dir, int anim)
{
    int res_id;
    int color;
    switch (id)
    {
    case 1:
        color = RED;
        res_id = RES_SPRITE_PLAYER_00;
        break;
    case 2:
        color = BLUE;
        res_id = RES_SPRITE_PLAYER_01;
        break;
    case 3:
        color = GREEN;
        res_id = RES_SPRITE_PLAYER_02;
        break;
    case 4:
        color = YELLOW;
        res_id = RES_SPRITE_PLAYER_03;
        break;
    default:
        break;
    }
    switch (dir)
    {
    case UP:
        switch (anim)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_backward"), res_id, color);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_backward"), res_id, color);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_backward"), res_id, color);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case RIGHT:
        switch (anim)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_right"), res_id, color);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_right"), res_id, color);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_right"), res_id, color);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case LEFT:
        switch (anim)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_left"), res_id, color);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_left"), res_id, color);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_left"), res_id, color);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case DOWN:
        switch (anim)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_forward"), res_id, color);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_forward"), res_id, color);
            GetInstance()->SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_forward"), res_id, color);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    default:
        break;
    }
}

void Player::KeyProcessing(hgeKeyCode_t key)
{
	switch (key)
	{
	case HGEK_LEFT:
        SendPack(PACKET_LEFT);
		break;
	case HGEK_RIGHT:
        SendPack(PACKET_RIGHT);
		break;
	case HGEK_UP:
        SendPack(PACKET_UP);
		break;
	case HGEK_DOWN:
        SendPack(PACKET_DOWN);
		break;
	case HGEK_SPACE:
        SendPack(PACKET_BOMB);
		Sleep(100);
		break;
	default:
		break;
	}
}

void Player::Draw()
{
    auto id = GetId();
    if (id == 0)
    {
        return;
    }
    
    const float dist_x = 48.0f;
    const float dist_y = 48.0f;
    ResMng::GetInstance()->GetSprite(id)->RenderEx(
        dist_x * (GetCoord()%LINE_LENGTH) + SCREEN_MERGE,  
        dist_y * (floor(GetCoord() / LINE_LENGTH)) + SCREEN_MERGE, 
        0, 
        GetScale());
}

void Player::SetCoord(unsigned int coord)
{
    Object::SetCoord(coord);
}

unsigned int Player::GetCoord()
{
    auto ret = Object::GetCoord();
    return ret;
}