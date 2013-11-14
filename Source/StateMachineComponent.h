//
//  StateMachineComponent.h
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Game/Entities/Component.h>
#include "SteeringComponent.h"

namespace Engine
{
    class StateMachineComponent : public Component
    {
    public:
        StateMachineComponent();
        ~StateMachineComponent();
        
        virtual const HashedString& GetType() const;
        
        virtual void VStart();
		virtual void VEnd();
        
		virtual void VUpdate( float fDeltaSeconds );
        
        SteeringComponent* GetSteering();
        
    private:
        SmartPtr<SteeringComponent> m_pSteering;
    };
    
    class StateMachineState
    {
    public:
        virtual ~StateMachineState() { }
        
        virtual void VOnUpdate( StateMachineComponent* pMachine, float fDeltaSeconds ) { }
        virtual void VOnStart( StateMachineComponent* pMachine ) { }
        virtual void VOnEnd( StateMachineComponent* pMachine ) { }
    };
}