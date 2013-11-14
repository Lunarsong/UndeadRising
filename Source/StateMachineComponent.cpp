//
//  StateMachineComponent.cpp
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "StateMachineComponent.h"
#include <Game/Entities/Entity.h>
#include <Core/Math/RandomNumGen.h>

namespace Engine
{
    StateMachineComponent::StateMachineComponent()
    {
        
    }
    
    StateMachineComponent::~StateMachineComponent()
    {
        
    }
    
    const HashedString& StateMachineComponent::GetType() const
    {
        static const HashedString g_hID( "StateMachine" );
        return g_hID;
    }
    
    void StateMachineComponent::VStart()
    {
        m_pSteering = m_pOwner->GetComponent<SteeringComponent>( "Steering" );
        if ( !m_pSteering )
        {
            m_pSteering = new SteeringComponent();
            m_pSteering->Release();
            
            m_pOwner->AddComponent( m_pSteering );
            m_pSteering->Start();
        }
    }
    
    void StateMachineComponent::VEnd()
    {
        
    }
    
    void StateMachineComponent::VUpdate( float fDeltaSeconds )
    {
        Vector4 vPosition = GetTransform().GetPosition();
        if ( vPosition.DistanceSQ( m_pSteering->GetTargetPosition() ) <= 1.0f )
        {
            float fRandom = g_RandomNumGen.RandomFloat( 0.0f, MATH_2PI );
            
            Vector4 vDirection( Math::Cos( fRandom ), 0.0f, Math::Sin( fRandom ) );
            vDirection.Normalize();
            m_pSteering->SetTargetPosition( vPosition + vDirection * g_RandomNumGen.RandomFloat( 10.0f, 20.0f ) );
        }
    }
    
    SteeringComponent* StateMachineComponent::GetSteering()
    {
        return m_pSteering;
    }
}