//
//  SkillTree.cpp
//  UndeadRising
//
//  Created by Shanee on 11/28/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "SkillTree.h"

namespace Engine
{
    SkillTree::SkillTree()
    {
        
    }
    
    SkillTree::~SkillTree()
    {
        
    }
    
    tinyxml2::XMLElement* SkillTree::VToXML( tinyxml2::XMLElement* pTo ) const
    {
        throw "Unimplemented";
        
        return NULL;
    }
    
    bool SkillTree::VFromXML( tinyxml2::XMLElement* pData )
    {
        const char* pName = pData->Attribute( "Name" );
        if ( pName )
        {
            m_Name = pName;
        }
        
        tinyxml2::XMLElement* pSkillElement = pData->FirstChildElement( "Skill" );
        while ( pSkillElement )
        {
            SkillTreeItem skill;
            skill.VFromXML( pSkillElement );
            m_Children.push_back( skill );
            
            pSkillElement = pSkillElement->NextSiblingElement( "Skill" );
        }
        
        return true;
    }

}