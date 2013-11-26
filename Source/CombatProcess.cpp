//
//  CombatProcess.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CombatProcess.h"
#include <Rendering/Scene/SceneManager.h>
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SpawnPositionProcessors.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SimulationProcessors.h>
#include <Game/Entities/Components/DurationComponent.h>

CombatProcess::CombatProcess( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 )
{
    m_pCamera = pCamera;
    m_pEntity0 = pEntity0;
    m_pEntity1 = pEntity1;
}

CombatProcess::~CombatProcess()
{
    
}

void CombatProcess::VOnInit(void)
{
    m_CombatData.pCombatant0 = (Character*)m_pEntity0->GetComponent( "Character" );
    m_CombatData.pCombatant1 = (Character*)m_pEntity1->GetComponent( "Character" );
    
    m_pEntity0->OnMessage( Combat::hMessageCombatStart, &m_CombatData );
    m_pEntity0->OnMessage( Combat::hMessageCombatStart, &m_CombatData );

    
    Vector4 vPosition = m_pEntity0->GetTransform().GetPosition();
    vPosition += -m_pEntity0->GetTransform().GetDirection() * 20.0f + Vector4( 0.0f, 15.0f, 0.0f );
    m_pCamera->SetPosition(  vPosition );
    //m_pCamera->LookAtTarget( m_pEntity0->GetTransform().GetPosition() );
    m_pCamera->SetDirection( (vPosition - m_pCamera->GetPosition()).Normalize() );
    
}

void CombatProcess::VOnUpdate( const float fDeltaSeconds )
{
    if ( m_CombatData.pCombatant0->GetHitPoints() == 0 )
    {
        OnVictory( m_pEntity1, m_pEntity0 );
    }
    
    else if ( m_CombatData.pCombatant1->GetHitPoints() == 0 )
    {
        OnVictory( m_pEntity0, m_pEntity1 );
    }
}

void CombatProcess::OnVictory( Entity* pVictor, Entity* pLoser )
{
    Succeed();
    
    pVictor->OnMessage( Combat::hMessageCombatWon, NULL );
    pVictor->OnMessage( Combat::hMessageCombatOver, NULL );
    
    pLoser->OnMessage( Combat::hMessageCombatLost, NULL );
    pLoser->OnMessage( Combat::hMessageCombatOver, NULL );
}