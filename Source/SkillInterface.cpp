//
//  SkillInterface.cpp
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "SkillInterface.h"

namespace Engine
{
    SkillInterface::SkillInterface()
    {
        m_pMenu = UserInterface::AddScreenFromFile( "Skills", "SkillMenu.xml" );
    }
    
    SkillInterface::~SkillInterface()
    {
        
    }
}