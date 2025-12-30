////////////////////////////////////////////////////////
//*--------------------------------------------------*//
//| Part of Party Raider (https://www.maus-games.at) |//
//*--------------------------------------------------*//
//| Copyright (c) 2019 Martin Mauersics              |//
//| Released under the zlib License                  |//
//*--------------------------------------------------*//
////////////////////////////////////////////////////////
#pragma once
#ifndef _PAR_GUARD_FIELD_H_
#define _PAR_GUARD_FIELD_H_


// ****************************************************************
class CField final : public coreObject2D
{
private:
    coreObject3D m_aGround[FIELD_GROUNDS];


public:
    CField()noexcept;

    DISABLE_COPY(CField)

    void Render()final;
    void Move  ()final;

    void EnableGround(const coreUintW iIndex, const coreBool bEnabled);
};


#endif // _PAR_GUARD_FIELD_H_