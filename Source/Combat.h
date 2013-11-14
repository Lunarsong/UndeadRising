//
//  Combat.h
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include "CombatProcess.h"
#include "CharacterAttributes.h"
#include "Character.h"
#include "CombatAbility.h"

class Combat
{
public:
    static void InitiateCombat( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 );
};