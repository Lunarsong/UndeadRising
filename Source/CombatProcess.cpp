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
    Vector4 vPosition = m_pEntity0->GetTransform().GetPosition();
    vPosition += -m_pEntity0->GetTransform().GetDirection() * 20.0f + Vector4( 0.0f, 15.0f, 0.0f );
    m_pCamera->SetPosition(  vPosition );
    //m_pCamera->LookAtTarget( m_pEntity0->GetTransform().GetPosition() );
    m_pCamera->SetDirection( (vPosition - m_pCamera->GetPosition()).Normalize() );
    
    m_pCombatScreen = UserInterface::AddScreenFromFile( "Combat", "CombatScreen.xml" );
    assert( m_pCombatScreen );
    
    
}

void CombatProcess::VOnUpdate( const float fDeltaSeconds )
{
    
}