//
//  CombatProcess.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CombatProcess.h"
#include <Rendering/Scene/SceneManager.h>

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
    m_pCamera->SetPosition( m_pEntity0->GetTransform().GetPosition() + Vector3( 0.0f, 5.0f, -15.0f ) );
    m_pCamera->LookAtTarget( m_pEntity0->GetTransform().GetPosition() );
    
    m_pCombatScreen = UserInterface::AddScreenFromFile( "Combat", "CombatScreen.xml" );
    assert( m_pCombatScreen );
    
    
}

void CombatProcess::VOnUpdate( const float fDeltaSeconds )
{
    
}