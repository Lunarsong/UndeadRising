//
//  CharacterAttributes.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CharacterAttributes.h"
#include <assert.h>

CharacterAttributes::CharacterAttributes()
{
    for ( int i = 0; i < AttributeCount; ++i )
    {
        m_Attributes[ i ] = 10;
    }
}

CharacterAttributes::~CharacterAttributes()
{
    
}

int CharacterAttributes::GetAttribute( Attribute eAttribute ) const
{
    assert( "Invalid attribute" && eAttribute < AttributeCount && eAttribute >= 0 );
    
    return m_Attributes[ eAttribute ];
}

void CharacterAttributes::SetAttribute( Attribute eAttribute, int iValue )
{
    assert( "Invalid attribute" && eAttribute < AttributeCount && eAttribute >= 0 );
    
    m_Attributes[ eAttribute ] = iValue;
}