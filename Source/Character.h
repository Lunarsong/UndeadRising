//
//  Character.h
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Game/Entities/Component.h>
#include "CharacterAttributes.h"

using namespace Engine;

class Character : public Component
{
public:
    Character();
    ~Character();
    
	virtual const HashedString& GetType() const;

	static const HashedString g_hID;

    const CharacterAttributes& GetAttributes() const;
    
private:
    int m_iHitPoints;
    int m_iMana;
    
    CharacterAttributes m_Attributes;
    
};