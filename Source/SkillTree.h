//
//  SkillTree.h
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Core/Resources/ISerializable.h>
#include "SkillTreeItem.h"

namespace Engine
{
    class SkillTree : public IXMLResource
    {
    public:
        SkillTree();
        ~SkillTree();
        
        virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
        virtual bool VFromXML( tinyxml2::XMLElement* pData );
        
    private:
        std::string m_Name;
        
        std::vector< SkillTreeItem > m_Children;
        
    };
}