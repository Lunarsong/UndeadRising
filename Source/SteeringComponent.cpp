//
//  SteeringComponent.cpp
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "SteeringComponent.h"
#include <Rendering/Scene/SceneManager.h>

namespace Engine
{
    const HashedString SteeringComponent::g_hID( "Steering" );
    
    SteeringComponent::SteeringComponent()
    {
        m_fSpeed = 4.5f;
        m_fDistanceTarget = 1.0f;
        m_fHeightOffset = 0.0f;
    }
    
    SteeringComponent::~SteeringComponent()
    {
        
    }
    
    const HashedString& SteeringComponent::GetType() const
    {
        return g_hID;
    }
    
    void SteeringComponent::SetTargetPosition( const Vector4& vPosition )
    {
        m_vTargetPosition = vPosition;
    }
    
    const Vector4& SteeringComponent::GetTargetPosition() const
    {
        return m_vTargetPosition;
    }
    
    void SteeringComponent::VStart()
    {
        m_vTargetPosition = GetTransform().GetPosition();
    }
    
    void SteeringComponent::VUpdate( float fDeltaSeconds )
    {
        Matrix matTransform = GetTransform();
        Vector4 vPosition = matTransform.GetPosition();
        
        if ( vPosition.DistanceSQ( m_vTargetPosition ) > ( m_fDistanceTarget * m_fDistanceTarget ) )
        {
            Vector4 vDirection = vPosition.Direction( m_vTargetPosition );
            
            Vector4 vNewPosition = vPosition + vDirection * m_fSpeed * fDeltaSeconds;
            
            float fHeight = 0.0f;
            if ( SceneManager::Get()->VGetHeight( vNewPosition, fHeight ) )
            {
                vNewPosition.y = fHeight + m_fHeightOffset;
            }
            
            matTransform.SetPosition( vNewPosition );
            
            SetTransform( matTransform );
        }
    }
    
    void SteeringComponent::SetSpeed( float fSpeed )
    {
        m_fSpeed = fSpeed;
    }
    
    float SteeringComponent::GetSpeed() const
    {
        return m_fSpeed;
    }
}