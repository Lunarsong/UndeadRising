//
//  Character.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "Character.h"

const HashedString Character::g_hID( "Character" );

Character::Character()
{
    m_iHitPoints = m_Attributes.GetAttribute( CharacterAttributes::HitPoints );
    m_iMana = m_Attributes.GetAttribute( CharacterAttributes::Mana );
}

Character::~Character()
{
    
}

const CharacterAttributes& Character::GetAttributes() const
{
    return m_Attributes;
}

const HashedString& Character::GetType() const
{
	return g_hID;
}

