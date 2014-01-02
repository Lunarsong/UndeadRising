//
//  SkillTreeItem.h
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <vector>
#include <Core/Resources/ISerializable.h>

namespace Engine
{
    class SkillTreeItem : public IXMLResource
    {
    public:
        SkillTreeItem();
        ~SkillTreeItem();
        
        virtual tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
        virtual bool VFromXML( tinyxml2::XMLElement* pData );
        
    private:
        std::string m_Name;
        
        std::vector< SkillTreeItem > m_pChildren;
    };
}