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
    if (m_upg == 1)
    {
        packet[1] += BLOCK_UPGRADE1;
    }
    auto addr = ConnectManager::GetInstance()->GetAddr();
    sendto(ConnectManager::GetInstance()->GetSocket(), 
        (char*)packet, 
        sizeof(int) * 2, 
        0, 
        (sockaddr*)&addr, 
        sizeof(ConnectManager::GetInstance()->GetAddr())
    );
}

void Player::SetDirection(int dir)
{
    switch (dir)
    {
    case UP:
        switch (animation_state)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_backward", m_id), m_id);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_backward", m_id), m_id);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_backward", m_id), m_id);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case RIGHT:
        switch (animation_state)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_right", m_id), m_id);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_right", m_id), m_id);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_right", m_id), m_id);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case LEFT:
        switch (animation_state)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_left", m_id), m_id);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_left", m_id), m_id);
            SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_left", m_id), m_id);
            SetAnim(WALK1);
            break;
        default:
            break;
        }
        break;
    case DOWN:
        switch (animation_state)
        {
        case STILL:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("still_forward", m_id), m_id);
            SetAnim(WALK1);
            break;
        case WALK1:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk1_forward", m_id), m_id);
            GetInstance()->SetAnim(WALK2);
            break;
        case WALK2:
            ResMng::GetInstance()->SetEnt(ResMng::GetInstance()->GetPlayerTex("walk2_forward", m_id), m_id);
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
        SetDirection(LEFT);
        SendPack(PACKET_LEFT);
		break;
	case HGEK_RIGHT:
        SetDirection(RIGHT);
        SendPack(PACKET_RIGHT);
		break;
	case HGEK_UP:
        SetDirection(UP);
        SendPack(PACKET_UP);
		break;
	case HGEK_DOWN:
        SetDirection(DOWN);
        SendPack(PACKET_DOWN);
		break;
	case HGEK_SPACE:
        SendPack(PACKET_BOMB);
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