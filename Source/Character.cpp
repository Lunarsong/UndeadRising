//
//  Character.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "Character.h"
#include "Combat.h"
#include <Game/Game.h>

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

void Character::AddAbility( const CombatAbility& ability )
{
    m_Abilities.push_back( ability );
}

const CombatAbility& Character::GetAbility( unsigned int uiIndex ) const
{
    assert( uiIndex < m_Abilities.size() && "Index larger than container!" );
    return m_Abilities[ uiIndex ];
}

unsigned int Character::GetNumAbilities() const
{
    return m_Abilities.size();
}

int Character::OnDamage( int iDamage, CombatEffect::Type eType )
{
    switch ( eType )
    {
        case CombatEffect::Healing:
            m_iHitPoints += iDamage;
            break;
            
        default:
            m_iHitPoints -= iDamage;
            break;
    }
    
    m_iHitPoints = std::min( m_iHitPoints, m_Attributes.GetAttribute( CharacterAttributes::HitPoints ) );
    m_iHitPoints = std::max( m_iHitPoints, 0 );
    
    return iDamage;
}

void Character::VOnMessage( const HashedString &hMessage, const void *pData )
{
    if ( hMessage == Combat::hMessageCombatLost )
    {
        if ( m_pOwner->GetComponent( "GameHUD" ) == NULL )
        {
            Game::DestroyEntity( m_pOwner );
        }
    }
}