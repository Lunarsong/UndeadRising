//
//  CharacterInterface.cpp
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CharacterInterface.h"

namespace Engine
{
    CharacterInterface::CharacterInterface()
    {
        m_pMenu = UserInterface::AddScreenFromFile( "Character", "CharacterMenu.xml" );
    }
    
    CharacterInterface::~CharacterInterface()
    {
        
    }
    
}