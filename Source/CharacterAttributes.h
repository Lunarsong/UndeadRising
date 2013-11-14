//
//  CharacterAttributes.h
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

class CharacterAttributes
{
public:
    CharacterAttributes();
    ~CharacterAttributes();
    
    enum Attribute
    {
        HitPoints = 0,
        Mana,
        
        Strength,
        Magic,
        Agility,
        
        AttributeCount
    };
    
    int GetAttribute( Attribute eAttribute ) const;
    void SetAttribute( Attribute eAttribute, int iValue );
    
private:
    int m_Attributes[ AttributeCount ];
};