//
//  CombatAbility.cpp
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CombatAbility.h"
#include <assert.h>

CombatAbility::CombatAbility()
{
    
}

CombatAbility::~CombatAbility()
{
    
}

int CombatAbility::GetNumEffects() const
{
    return m_Effects.size();
}

const HashedString& CombatAbility::GetName() const
{
    return m_Name;
}

const CombatEffect& CombatAbility::GetEffect( unsigned int uiIndex ) const
{
    assert( "Requested index larger than container!" && uiIndex < m_Effects.size() );
    
    return m_Effects[ uiIndex ];
}

void CombatAbility::AddEffect( const CombatEffect& effect )
{
    m_Effects.push_back( effect );
}

tinyxml2::XMLElement* CombatAbility::VToXML( tinyxml2::XMLElement* pTo ) const
{
    throw "Unimplemented";

    return pTo;
}

bool CombatAbility::VFromXML( tinyxml2::XMLElement* pData )
{
    const char* pName = pData->Attribute( "Name" );
    if ( pName )
    {
        m_Name = HashedString( pName );
    }
    
    pData->QueryFloatAttribute( "Range", &m_fRange );
    const char* pTarget = pData->Attribute( "Target" );
    if ( pTarget )
    {
        m_eTarget = TargetFromString( pTarget );
    }
    
    tinyxml2::XMLElement* pCombatEffect = pData->FirstChildElement( "CombatEffect" );
    while ( pCombatEffect )
    {
        CombatEffect effect;
        if ( effect.VFromXML( pCombatEffect ) )
        {
            m_Effects.push_back( effect );
        }
        
        pCombatEffect = pCombatEffect->NextSiblingElement( "CombatEffect" );
    }
    
    return true;
}

void CombatAbility::VSerialize( std::ostream &out ) const
{
    throw "Unimplemented!";
}

void CombatAbility::VDeserialize( std::istream& in )
{
    throw "Unimplemented!";
}

void CombatEffect::VSerialize( std::ostream &out ) const
{
    throw "Unimplemented!";
}

void CombatEffect::VDeserialize( std::istream& in )
{
    throw "Unimplemented!";
}

tinyxml2::XMLElement* CombatEffect::VToXML( tinyxml2::XMLElement* pTo ) const
{
    throw "Unimplemented!";
    
    return pTo;
}

bool CombatEffect::VFromXML( tinyxml2::XMLElement* pData )
{
    const char* pType = pData->Attribute( "Type" );
    if ( !pType )
    {
        throw  "Missing CombatEffect Type";
        
        return false;
    }
    eType = TypeFromString( pType );
    
    const char* pTarget = pData->Attribute( "Target" );
    if ( !pTarget )
    {
        throw  "Missing CombatEffect Target";
        
        return false;
    }
    eTarget = EffectTargetFromString( pTarget );
    
    pData->QueryIntAttribute( "Min", &iMin );
    pData->QueryIntAttribute( "Max", &iMax );
    
    pData->QueryFloatAttribute( "Radius", &fRadius );
    
    return true;
}

CombatEffect::Type CombatEffect::TypeFromString( const char* pString )
{
    std::string inputString = pString;
    std::transform( inputString.begin(), inputString.end(), inputString.begin(), ::tolower );
    
    if ( inputString == "physical" )
        return Physical;
    
    if ( inputString == "fire" )
        return Fire;
    
    if ( inputString == "frost" )
        return Frost;
    
    if ( inputString == "poison" )
        return Poison;
    
    if ( inputString == "arcane" )
        return Arcane;
    
    if ( inputString == "divine" )
        return Divine;
    
    if ( inputString == "dark" )
        return Dark;
    
    if ( inputString == "electricity" )
        return Electricity;
    
    if ( inputString == "healing" )
        return Healing;
    
    if ( inputString == "undefined" )
        return Undefined;
    
    throw "Unknown type";
    
    return Undefined;
}

CombatAbility::Target CombatAbility::TargetFromString( const char* pString )
{
    std::string inputString = pString;
    std::transform( inputString.begin(), inputString.end(), inputString.begin(), ::tolower );
    
    if ( inputString == "self" )
        return Self;
    
    if ( inputString == "entity" )
        return Entity;
    
    if ( inputString == "area" )
        return Area;
    
    if ( inputString == "position" )
        return Position;
    
    throw "Unknown target option";
    
    return Entity;
}

CombatEffect::EffectTarget CombatEffect::EffectTargetFromString( const char* pString )
{
    std::string inputString = pString;
    std::transform( inputString.begin(), inputString.end(), inputString.begin(), ::tolower );
    
    if ( inputString == "self" )
        return Self;
    
    if ( inputString == "other" )
        return Other;
    
    if ( inputString == "area" )
        return Area;
    
    if ( inputString == "position" )
        return Position;
    
    throw "Unknown target option";
    
    return Other;
}