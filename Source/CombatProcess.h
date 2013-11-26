//
//  CombatProcess.h
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once


#include <Core/Process/Process.h>
#include <Game/Entities/Entity.h>
#include <UI/UserInterface.h>
#include "Character.h"
#include "Combat.h"

using namespace Engine;

class CombatProcess : public Process
{
public:
    CombatProcess( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 );
    ~CombatProcess();
    
    void VOnInit(void);
    void VOnUpdate( const float fDeltaSeconds );
    
private:
    Camera*             m_pCamera;

    SmartPtr<Entity>    m_pEntity0;
    SmartPtr<Entity>    m_pEntity1;

    Combat::CombatStartData m_CombatData;
    
    void OnVictory( Entity* pVictor, Entity* pLoser );
};