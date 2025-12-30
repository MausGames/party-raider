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
CGame::CGame()noexcept
: m_apPlayer       {}
, m_apBullet       {}
, m_Interface      ()
, m_aiScore        {}
, m_iNumIteration  (0u)
, m_iLastIteration (0u)
, m_fTime          (GAME_TIME + GAME_COUNTDOWN + GAME_WAIT)
, m_bStarted       (false)
{
    this->StartIteration();
}


// ****************************************************************
CGame::~CGame()
{
    this->EndIteration();
}


// ****************************************************************
void CGame::Render()
{
    FOR_EACH(it, m_apPlayer)
    {
        const coreVector2 vPos = (*it)->GetPosition().xy();

        (*it)->Render();

        (*it)->SetPosition(coreVector3(vPos + FIELD_SPACE * coreVector2(1.0f,0.0f), 0.0f));
        (*it)->coreObject3D::Move();
        (*it)->Render();

        (*it)->SetPosition(coreVector3(vPos + FIELD_SPACE * coreVector2(0.0f,1.0f), 0.0f));
        (*it)->coreObject3D::Move();
        (*it)->Render();

        (*it)->SetPosition(coreVector3(vPos + FIELD_SPACE, 0.0f));
        (*it)->coreObject3D::Move();
        (*it)->Render();

        (*it)->SetPosition(coreVector3(vPos, 0.0f));
    }

    FOR_EACH(it, m_apBullet) (*it)->RenderStraw();
    FOR_EACH(it, m_apBullet) (*it)->Render();

    glCullFace(GL_FRONT);
    FOR_EACH(it, m_apBullet) (*it)->RenderGlass();

    glCullFace(GL_BACK);
    FOR_EACH(it, m_apBullet) (*it)->RenderGlass();

    glDisable(GL_DEPTH_TEST);
    m_Interface.Render();
    glEnable(GL_DEPTH_TEST);
}


// ****************************************************************
void CGame::Move()
{
    if(Core::Input->GetAnyButton(CORE_INPUT_PRESS) && !Core::Input->GetKeyboardButton(CORE_INPUT_KEY(SPACE), CORE_INPUT_PRESS))
    {
        m_bStarted = true;
    }

    if(m_bStarted)
    {
        m_fTime.Update(-1.0f);
    }

    FOR_EACH(it, m_apPlayer) (*it)->Move();
    FOR_EACH(it, m_apBullet) (*it)->Move();

    Core::Manager::Object->TestCollision(TYPE_PLAYER, TYPE_GROUND, [](CPlayer* OUTPUT pPlayer, coreObject3D* OUTPUT pGround, const coreVector3 vIntersection, const coreBool bFirstHit)
    {
        const coreFloat fThreshold = pGround->GetPosition().y + pGround->GetSize().y * 0.5f + pPlayer->GetSize().y * 0.5f;
        if(pPlayer->GetOldPos().y >= fThreshold)
        {
            if(pPlayer->GetVelocity().y < 0.0f)
            {
                pPlayer->SetVelocity(coreVector2(pPlayer->GetVelocity().x, 0.0f));
                pPlayer->SetPosition(coreVector3(pPlayer->GetPosition().x, fThreshold, 0.0f));
            }
        }
    });

    Core::Manager::Object->TestCollision(TYPE_BULLET, TYPE_GROUND, [](CBullet* OUTPUT pBullet, coreObject3D* OUTPUT pGround, const coreVector3 vIntersection, const coreBool bFirstHit)
    {
        const coreFloat fThreshold = pGround->GetPosition().y + pGround->GetSize().y * 0.5f;
        if(pBullet->GetOldPos().y >= fThreshold)
        {
            pBullet->SetVelocity(coreVector2(pBullet->GetVelocity().x, ABS(pBullet->GetVelocity().y)));
        }
    });

    Core::Manager::Object->TestCollision(TYPE_PLAYER, [](CPlayer* OUTPUT pPlayer1, CPlayer* OUTPUT pPlayer2, const coreVector3 vIntersection, const coreBool bFirstHit)
    {
        const coreVector2 vRange = pPlayer1->GetSize().xy() * 0.5f + pPlayer2->GetSize().xy() * 0.5f;
        const coreVector2 vDiff  = pPlayer1->GetPosition().xy()    - pPlayer2->GetPosition().xy();

        if((ABS(vDiff.x) < vRange.x) && (ABS(vDiff.y) < 0.1f))
        {
            const coreFloat fMove = (vRange.x - ABS(vDiff.x)) * SIGN(vDiff.x) * 0.51f;
            pPlayer1->SetPosition(pPlayer1->GetPosition() + coreVector3(fMove, 0.0f, 0.0f));
            pPlayer2->SetPosition(pPlayer2->GetPosition() - coreVector3(fMove, 0.0f, 0.0f));
        }
        else if(ABS(vDiff.y) < vRange.y)
        {
            const coreFloat fMove = vRange.y - ABS(vDiff.y);
            if(pPlayer1->GetPosition().y > pPlayer2->GetPosition().y)
            {
                if(pPlayer1->GetVelocity().y < 0.0f)
                {
                    pPlayer1->SetVelocity(coreVector2(pPlayer1->GetVelocity().x, 0.0f));
                    pPlayer1->SetPosition(pPlayer1->GetPosition() + coreVector3(0.0f, fMove, 0.0f));
                }
            }
            else
            {
                if(pPlayer2->GetVelocity().y < 0.0f)
                {
                    pPlayer2->SetVelocity(coreVector2(pPlayer2->GetVelocity().x, 0.0f));
                    pPlayer2->SetPosition(pPlayer2->GetPosition() + coreVector3(0.0f, fMove, 0.0f));
                }
            }
        }
    });

    Core::Manager::Object->TestCollision(TYPE_BULLET, TYPE_PLAYER, [this](CBullet* OUTPUT pBullet, CPlayer* OUTPUT pPlayer, const coreVector3 vIntersection, const coreBool bFirstHit)
    {
        if(pBullet->GetOwner()->GetControl() == pPlayer->GetControl())
            return;

        if(pPlayer->TakeDamage(1))
            this->DeletePlayer(pPlayer);

        this->DeleteBullet(pBullet);
    });

    for(coreUintW i = 0u; i < PLAYERS; ++i)
    {
        if(this->RetrievePlayerCount(i) == 0u)
        {
            for(coreUintW j = 0u; j < PLAYERS; ++j)
                if(i != j) ++m_aiScore[j];

            this->StartIteration();

            break;
        }
    }

    m_Interface.Move();
}


// ****************************************************************
void CGame::StartIteration()
{
    this->EndIteration();

    m_iLastIteration = (m_iNumIteration < 2u) ? (m_iNumIteration + GAME_LEVELS) : ((m_iLastIteration + Core::Rand->Uint(1u, GAME_LEVELS-1u)) % GAME_LEVELS);
    ++m_iNumIteration;

    if(m_iLastIteration < GAME_LEVELS)
    {
        for(coreUintW i = 0u; i < FIELD_GROUNDS; ++i)
            g_pField->EnableGround(i, false);
    }

    coreUint8 iCount;
    void (*nSetFunc)(CPlayer* OUTPUT, const coreUintW, const coreUintW);
    switch(m_iLastIteration)
    {
    case 0u:
        {
            g_pField->EnableGround(2u, true);
            g_pField->EnableGround(5u, true);

            iCount = 3u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(1u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 1u:
        {
            g_pField->EnableGround(3u, true);
            g_pField->EnableGround(4u, true);
            g_pField->EnableGround(6u, true);
            g_pField->EnableGround(7u, true);

            iCount = 2u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f) * ((iIndex == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(0u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 2u:
        {
            g_pField->EnableGround(2u, true);
            g_pField->EnableGround(3u, true);
            g_pField->EnableGround(4u, true);
            g_pField->EnableGround(6u, true);
            g_pField->EnableGround(7u, true);

            iCount = 3u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.3f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(1u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 3u:
        {
            g_pField->EnableGround(0u, true);
            g_pField->EnableGround(1u, true);
            g_pField->EnableGround(5u, true);

            iCount = 3u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.3f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(1u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 4u:
        {
            iCount = 5u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.25f * I_TO_F(2u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 5u:
        {
            g_pField->EnableGround(5u, true);
            g_pField->EnableGround(6u, true);
            g_pField->EnableGround(7u, true);

            iCount = 3u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f) * ((iIndex == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(1u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    default: UNREACHABLE
    case 6u:
        {
            iCount = 1u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;

    case 7u:
        {
            iCount = 3u;
            nSetFunc = [](CPlayer* OUTPUT pPlayer, const coreUintW iIndex, const coreUintW iType)
            {
                pPlayer->SetPosition(coreVector3((FIELD_SIZE.x * 0.5f - 6.0f) * ((iType == 0u) ? -1.0f : 1.0f), FIELD_SIZE.y * (0.5f * I_TO_F(1u-iIndex)) + pPlayer->GetSize().y * 0.5f + 8.0f, 0.0f));
            };
        }
        break;
    }

    for(coreUintW i = 0u; i < iCount; ++i)
    {
        CPlayer* pPlayer = this->CreatePlayer(COLOR_PLAYER_1, 0u);
        pPlayer->SetAim(coreVector2(1.5f, 0.5f).Normalized());

        nSetFunc(pPlayer, i, 0u);
    }

    for(coreUintW i = 0u; i < iCount; ++i)
    {
        CPlayer* pPlayer = this->CreatePlayer(COLOR_PLAYER_2, 1u);
        pPlayer->SetAim(coreVector2(-1.5f, 0.5f).Normalized());

        nSetFunc(pPlayer, i, 1u);
    }
}


// ****************************************************************
void CGame::EndIteration()
{
    FOR_EACH(it, m_apPlayer) MANAGED_DELETE(*it)
    FOR_EACH(it, m_apBullet) MANAGED_DELETE(*it)

    m_apPlayer.clear();
    m_apBullet.clear();
}


// ****************************************************************
RETURN_RESTRICT CPlayer* CGame::CreatePlayer(const coreVector3 vColor, const coreUint8 iControl)
{
    CPlayer* pPlayer = MANAGED_NEW(CPlayer);

    pPlayer->SetColor3 (vColor);
    pPlayer->SetControl(iControl);

    m_apPlayer.push_back(pPlayer);
    return pPlayer;
}


// ****************************************************************
void CGame::DeletePlayer(CPlayer* pPlayer)
{
    FOR_EACH(it, m_apPlayer)
    {
         if((*it) == pPlayer)
         {
             MANAGED_DELETE(pPlayer)
             m_apPlayer.erase(it);

             break;
         }
    }
}


// ****************************************************************
RETURN_RESTRICT CBullet* CGame::CreateBullet(CPlayer* pOwner, const coreVector2 vPosition, const coreVector2 vVelocity)
{
    CBullet* pBullet = MANAGED_NEW(CBullet);

    pBullet->SetPosition(coreVector3(vPosition, 0.0f));
    pBullet->SetOwner   (pOwner);
    pBullet->SetVelocity(vVelocity);

    m_apBullet.push_back(pBullet);
    return pBullet;
}


// ****************************************************************
void CGame::DeleteBullet(CBullet* pBullet)
{
    FOR_EACH(it, m_apBullet)
    {
         if((*it) == pBullet)
         {
             MANAGED_DELETE(pBullet)
             m_apBullet.erase(it);

             break;
         }
    }
}


// ****************************************************************
coreUint8 CGame::RetrievePlayerCount(const coreUintW iIndex)const
{
    coreUint8 iCount = 0u;

    FOR_EACH(it, m_apPlayer)
    {
         if((*it)->GetControl() == iIndex)
            ++iCount;
    }

    return iCount;
}