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
		m_bSteering = false;
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
		m_bSteering = true;
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
		if ( !m_bSteering )
			return;

        Transform& transform = GetTransform();
        Vector4 vPosition = transform.GetPosition();
        
        if ( vPosition.DistanceSQ( m_vTargetPosition ) > ( m_fDistanceTarget * m_fDistanceTarget ) )
        {
            Vector4 vDirection = vPosition.Direction( m_vTargetPosition );
            
            Vector4 vNewPosition = vPosition + vDirection * m_fSpeed * fDeltaSeconds;
            
            float fHeight = 0.0f;
            if ( SceneManager::Get()->VGetHeight( vNewPosition, fHeight ) )
            {
                vNewPosition.y = fHeight + m_fHeightOffset;
            }
            
            transform.SetPosition( vNewPosition );
        }

		else
		{
			m_bSteering = false;
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

	void SteeringComponent::SetHeightOffset( float fHeightOffset )
	{
		m_fHeightOffset = fHeightOffset;
	}

	float SteeringComponent::GetHeightOffset() const
	{
		return m_fHeightOffset;
	}

}