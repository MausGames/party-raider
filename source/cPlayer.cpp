////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#include "main.h"


// ****************************************************************
CPlayer::CPlayer()noexcept
: m_iControl  (PLAYER_CONTROL_NONE)
, m_vOldPos   (coreVector2(FLT_MAX,FLT_MAX))
, m_vVelocity (coreVector2(0.0f,0.0f))
, m_vAim      (coreVector2(0.0f,0.0f))
, m_fCooldown (0.0f)
, m_iHealth   (PLAYER_HEALTH)
{
    this->DefineModel  ("default_cube.md3z");
    this->DefineTexture(0u, "default_white.webp");
    this->DefineProgram("object_program");

    this->ChangeType(TYPE_PLAYER);
}


// ****************************************************************
void CPlayer::Render()
{
    this->coreObject3D::Render();
}


// ****************************************************************
void CPlayer::Move()
{
    m_vOldPos = this->GetPosition().xy();
    m_fCooldown.UpdateMax(-PLAYER_SHOOT_RATE, 0.0f);

    coreVector2 vMove = coreVector2(0.0f,-1.0f);

    if((g_pGame->GetTime() < GAME_TIME) && (g_pGame->GetTime() > 0.0f))
    {
        bool        bShoot = false;
        coreVector2 vStick = coreVector2(0.0f,0.0f);

        if(m_iControl == 0u)
        {
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(D), CORE_INPUT_HOLD)) vMove.x += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(A), CORE_INPUT_HOLD)) vMove.x -= 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(W), CORE_INPUT_HOLD)) bShoot = true;

            if(Core::Input->GetJoystickButton(0u, 0u, CORE_INPUT_HOLD) || Core::Input->GetJoystickButton(0u, 1u, CORE_INPUT_HOLD)) bShoot = true;
            vStick = Core::Input->GetJoystickStickL(0u);

        }
        else if(m_iControl == 1u)
        {
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(RIGHT), CORE_INPUT_HOLD)) vMove.x += 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(LEFT),  CORE_INPUT_HOLD)) vMove.x -= 1.0f;
            if(Core::Input->GetKeyboardButton(CORE_INPUT_KEY(UP),    CORE_INPUT_HOLD)) bShoot = true;

            if(Core::Input->GetJoystickButton(1u, 0u, CORE_INPUT_HOLD) || Core::Input->GetJoystickButton(1u, 1u, CORE_INPUT_HOLD)) bShoot = true;
            vStick = Core::Input->GetJoystickStickL(1u);
        }

        vMove.x += vStick.x;
        if(!vStick.IsNull()) m_vAim = vStick.Normalized();   // not with keyboard :(

        if(bShoot && !m_fCooldown)
        {
            m_fCooldown = 1.0f;
            g_pGame->CreateBullet(this, this->GetPosition().xy(), m_vAim * PLAYER_SHOOT_POWER);
        }
    }

    m_vVelocity += vMove * (PLAYER_SPEED * PLAYER_ACCELERATION * TIME);
    if(!m_vVelocity.IsNull())
    {
        m_vVelocity.x *= POW(1.0f - PLAYER_BRAKE.x * (1.0f/60.0f), TIME * 60.0f);
        m_vVelocity.y *= POW(1.0f - PLAYER_BRAKE.y * (1.0f/60.0f), TIME * 60.0f);
    }

    coreVector2 vNewPos = this->GetPosition().xy() + m_vVelocity * TIME;

         if((vNewPos.x >  (FIELD_SPACE.x * 0.5f - this->GetSize().x * 0.75f)) && (m_vVelocity.x > 0.0f)) vNewPos.x -=  FIELD_SPACE.x;
    else if((vNewPos.x < -(FIELD_SPACE.x * 0.5f + this->GetSize().x * 0.75f)) && (m_vVelocity.x < 0.0f)) vNewPos.x -= -FIELD_SPACE.x;
         if((vNewPos.y >  (FIELD_SPACE.y * 0.5f - this->GetSize().y * 0.75f)) && (m_vVelocity.y > 0.0f)) vNewPos.y -=  FIELD_SPACE.y;
    else if((vNewPos.y < -(FIELD_SPACE.y * 0.5f + this->GetSize().y * 0.75f)) && (m_vVelocity.y < 0.0f)) vNewPos.y -= -FIELD_SPACE.y;

    this->SetPosition(coreVector3(vNewPos, 0.0f));
    this->SetSize    (coreVector3(1.0f,1.0f,1.0f) * (2.0f + 3.0f * (I_TO_F(m_iHealth) / I_TO_F(PLAYER_HEALTH))));

    this->coreObject3D::Move();
}


// ****************************************************************
bool CPlayer::TakeDamage(const coreInt8 iDamage)
{
    m_iHealth -= iDamage;
    return (m_iHealth <= 0);
}