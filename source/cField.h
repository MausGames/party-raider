////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Released under the zlib License                  |//
//| More information available in the readme file    |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_FIELD_H_
#define _PAR_GUARD_FIELD_H_


// ****************************************************************
class cField final : public coreObject2D
{
private:
    coreObject3D m_aGround[FIELD_GROUNDS];


public:
    cField()noexcept;

    DISABLE_COPY(cField)

    void Render()final;
    void Move  ()final;

    void EnableGround(const coreUintW iIndex, const coreBool bEnabled);
};


#endif // _PAR_GUARD_FIELD_H_