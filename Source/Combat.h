//
//  Combat.h
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include "CharacterAttributes.h"
#include "Character.h"
#include "CombatAbility.h"

class Combat
{
public:
    static void InitiateCombat( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 );
    
    static void ProcessAbility( const CombatAbility& ability, Entity* pUser, Entity* pTarget );
    static void ResolveEffect( const CombatEffect& effect, Entity* pUser, Entity* pTarget );
    
    static const HashedString hMessageCombatStart;
    static const HashedString hMessageCombatOver;
    static const HashedString hMessageCombatWon;
    static const HashedString hMessageCombatLost;
    
    struct CombatStartData
    {
        Character* pCombatant0;
        Character* pCombatant1;
    };
};

#include "CombatProcess.h"