//
//  GameHUDComponent.h
//  UndeadRising
//
//  Created by Shanee on 11/25/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Game/Entities/Component.h>
#include <UI/UserInterface.h>
#include "Character.h"

using namespace Engine;

class GameHUDComponent : public Component
{
public:
    GameHUDComponent();
    ~GameHUDComponent();
    
    static const HashedString g_hID;
    virtual const HashedString& GetType() const;
    
    virtual void VStart();
    virtual void VEnd();
    
    virtual void VUpdate( float fDeltaSeconds );
    
    virtual void VOnMessage( const HashedString& hMessage, const void* pData );
    
private:
    UIElement* m_pHUD;
    SmartPtr<Character> m_pCharacter;
    
    Vector3 m_vHPSize;
    Vector3 m_vEnemyHPSize;
    
    void OnCombatButton( UIElement* pElement, void* pArgs );
    
    // CombatHUD
    SmartPtr<Character> m_pEnemyCharacter;
};