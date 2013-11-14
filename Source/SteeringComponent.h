//
//  SteeringComponent.h
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Game/Entities/Component.h>

namespace Engine
{
    class SteeringComponent : public Component
    {
    public:
        SteeringComponent();
        ~SteeringComponent();
        
        virtual const HashedString& GetType() const;
    
        static const HashedString g_hID;
        
        virtual void VStart();
        virtual void VUpdate( float fDeltaSeconds );
        
        void SetTargetPosition( const Vector4& vPosition );
        const Vector4& GetTargetPosition() const;
        
        void SetSpeed( float fSpeed );
        float GetSpeed() const;
        
    private:
        float   m_fSpeed;
        float   m_fHeightOffset;
        
        Vector4 m_vTargetPosition;
        float   m_fDistanceTarget;
    };
}