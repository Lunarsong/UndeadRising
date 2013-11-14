//
//  CombatAbility.cpp
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CombatAbility.h"
#include <assert.h>

CombatAbility::CombatAbility()
{
    
}

CombatAbility::~CombatAbility()
{
    
}

int CombatAbility::GetNumEffects() const
{
    return m_Effects.size();
}

const CombatEffect& CombatAbility::GetEffect( unsigned int uiIndex ) const
{
    assert( "Requested index larger than container!" && uiIndex < m_Effects.size() );
    
    return m_Effects[ uiIndex ];
}

void CombatAbility::AddEffect( const CombatEffect& effect )
{
    m_Effects.push_back( effect );
}