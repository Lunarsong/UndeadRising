//
//  SkillInterface.h
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <UI/UserInterface.h>

namespace Engine
{
    class SkillInterface
    {
    public:
        SkillInterface();
        ~SkillInterface();
        
    private:
        UIElement* m_pMenu;
    };
}