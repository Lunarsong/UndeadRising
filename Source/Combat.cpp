//
//  Combat.cpp
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "Combat.h"
#include <Core/Application/BaseApplication.h>

void Combat::InitiateCombat( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 )
{
    CombatProcess* pCombatProcess = new CombatProcess( pCamera, pEntity0, pEntity1 );
    BaseApplication::Get()->AttachProcess( pCombatProcess );
    pCombatProcess->Release();
}