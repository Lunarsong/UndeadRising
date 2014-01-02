//
//  CombatAbility.h
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <vector>
#include <Core/Resources/ISerializable.h>
#include <Externals/HashedString/HashedString.h>

struct CombatEffect : public Engine::IXMLResource, public Engine::ISerializable
{
    enum Type
    {
        Physical = 0,
        Fire,
        Frost,
        Poison,
        Arcane,
        Divine,
        Dark,
        Electricity,
        Healing,
        Undefined,
        
        TypeCount
    };
    
    enum EffectTarget
    {
        Self = 0,
        Other,
        Area,
        Position,
        
        EffectTargetCount
    };
    
    int iMin;
    int iMax;

    float fRadius;
    
    Type eType;
    EffectTarget eTarget;
    
    std::string strParticles;
    
    void VSerialize( std::ostream &out ) const;
    void VDeserialize( std::istream& in );
    
    tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
    bool VFromXML( tinyxml2::XMLElement* pData );
    
    static Type TypeFromString( const char* pString );
    static EffectTarget EffectTargetFromString( const char* pString );
};

class CombatAbility : public Engine::IXMLResource, public Engine::ISerializable
{
public:
    CombatAbility();
    ~CombatAbility();
    
    const HashedString& GetName() const;
    
    int GetNumEffects() const;
    const CombatEffect& GetEffect( unsigned int uiIndex ) const;
    void AddEffect( const CombatEffect& effect );
    
    void VSerialize( std::ostream &out ) const;
    void VDeserialize( std::istream& in );
    
    tinyxml2::XMLElement* VToXML( tinyxml2::XMLElement* pTo ) const;
    bool VFromXML( tinyxml2::XMLElement* pData );

    enum Target
    {
        Self = 0,
        Entity,
        Area,
        Position,
        
        TargetCount
    };
    
    static Target TargetFromString( const char* pString );
    
private:
    HashedString    m_Name;
    float           m_fRange;
    Target          m_eTarget;
    
    std::vector< CombatEffect > m_Effects;
    
};