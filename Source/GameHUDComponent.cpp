//
//  GameHUDComponent.cpp
//  UndeadRising
//
//  Created by Shanee on 11/25/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "GameHUDComponent.h"
#include <Game/Entities/Entity.h>
#include "Combat.h"
#include <Game/Entities/Components/Rendering/Particles/ParticleEmitter.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SimulationProcessors.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SpawnPositionProcessors.h>
#include <Game/Entities/Components/DurationComponent.h>
#include <Game/Game.h>

GameHUDComponent::GameHUDComponent()
{
    
}

GameHUDComponent::~GameHUDComponent()
{
    
}

const HashedString GameHUDComponent::g_hID( "GameHUD" );
const HashedString& GameHUDComponent::GetType() const
{
    return g_hID;
}

void GameHUDComponent::VStart()
{
    m_pHUD = UserInterface::AddScreenFromFile( "GameHUD", "GameHUD.xml" );
    assert( m_pHUD );
    
    m_pHUD->SetVisible( false );
    
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_bottomright" ))->SetCallbackArgs( 0 );
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_bottomright" ))->SetCallbackFunction( std::bind( &GameHUDComponent::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );
    
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_bottomleft" ))->SetCallbackArgs( (void*)1 );
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_bottomleft" ))->SetCallbackFunction( std::bind( &GameHUDComponent::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );
    
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_topright" ))->SetCallbackArgs( (void*)2 );
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_topright" ))->SetCallbackFunction( std::bind( &GameHUDComponent::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );
    
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_topleft" ))->SetCallbackArgs( (void*)3 );
	((UIButtonImage*)m_pHUD->GetElement( "btn_action_topleft" ))->SetCallbackFunction( std::bind( &GameHUDComponent::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );
    
    
    m_pCharacter = (Character*)m_pOwner->GetComponent( "Character" );
    if ( m_pCharacter )
    {
        UILabel* pLabels[4];
        pLabels[0] = ((UILabel*)m_pHUD->GetElement( "lbl_ability_br" ));
        pLabels[1] = ((UILabel*)m_pHUD->GetElement( "lbl_ability_bl" ));
        pLabels[2] = ((UILabel*)m_pHUD->GetElement( "lbl_ability_tr" ));
        pLabels[3] = ((UILabel*)m_pHUD->GetElement( "lbl_ability_tl" ));
        
        unsigned int uiSize = m_pCharacter->GetNumAbilities();
        for ( unsigned int i = 0; i < 4; ++i )
        {
            if ( i >= uiSize )
                break;
            
            const CombatAbility& ability = m_pCharacter->GetAbility( i );
            pLabels[i]->SetString( ability.GetName().getStr() );
        }
    }
    
    
    UIColor* pHP = (UIColor*)m_pHUD->GetElement( "player_hitpoints" );
    if ( pHP )
    {
        m_vHPSize = pHP->GetSize().GetCoordinates();
    }
    
    UIColor* pEnemyHP = (UIColor*)m_pHUD->GetElement( "enemy_hitpoints" );
    if ( pEnemyHP )
    {
        m_vEnemyHPSize = pEnemyHP->GetSize().GetCoordinates();
    }

}

void GameHUDComponent::VEnd()
{
    
}

void GameHUDComponent::VUpdate( float fDeltaSeconds )
{
    UIColor* pHP = (UIColor*)m_pHUD->GetElement( "player_hitpoints" );
    if ( pHP && m_pCharacter )
    {
        float fSizePercent = (float)m_pCharacter->GetHitPoints() / (float)m_pCharacter->GetAttributes().GetAttribute( CharacterAttributes::HitPoints );
        pHP->SetSize( m_vHPSize.x * fSizePercent, m_vHPSize.y );
    }
    
    UIColor* pEnemyHP = (UIColor*)m_pHUD->GetElement( "enemy_hitpoints" );
    if ( pEnemyHP )
    {
        if ( m_pEnemyCharacter )
        {
            float fSizePercent = (float)m_pEnemyCharacter->GetHitPoints() / (float)m_pEnemyCharacter->GetAttributes().GetAttribute( CharacterAttributes::HitPoints );
            pEnemyHP->SetSize( m_vEnemyHPSize.x * fSizePercent, m_vEnemyHPSize.y );
            pEnemyHP->SetVisible( true );
        }
        
        else
        {
            pEnemyHP->SetVisible( false );
        }
    }

}

void GameHUDComponent::VOnMessage( const HashedString& hMessage, const void* pData )
{
    if ( hMessage == Combat::hMessageCombatStart )
    {
        if ( pData )
        {
            m_pHUD->SetVisible( true );
            const Combat::CombatStartData* pCombatData = (Combat::CombatStartData*)pData;
            if ( pCombatData->pCombatant0 != m_pCharacter )
            {
                m_pEnemyCharacter = pCombatData->pCombatant0;
            }
            
            else
            {
                m_pEnemyCharacter = pCombatData->pCombatant1;
            }
        }
    }
    
    else if ( hMessage == Combat::hMessageCombatLost )
    {
        m_pHUD->SetVisible( false );
        m_pEnemyCharacter = NULL;
    }
    
    else if ( hMessage == Combat::hMessageCombatWon )
    {
        m_pHUD->SetVisible( false );
        m_pEnemyCharacter = NULL;
    }
}

void GameHUDComponent::OnCombatButton( UIElement* pElement, void* pArgs )
{
    if ( m_pCharacter && m_pEnemyCharacter )
    {
        unsigned int uiSize = m_pCharacter->GetNumAbilities();
        if ( (unsigned int)pArgs < uiSize )
        {
            const CombatAbility& ability = m_pCharacter->GetAbility( (unsigned int)pArgs );
            Combat::ProcessAbility( ability, m_pCharacter->GetOwner(), m_pEnemyCharacter->GetOwner() );
        }
        
        else
        {
            throw "Ability button pressed without ability";
        }
    }    
}
