//
//  CombatAbility.h
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <vector>

struct CombatEffect
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
        
        TypeCount
    };
    
    enum Target
    {
        Self = 0,
        Entity,
        Area,
        Position,
        
        TargetCount
    };
    
    int iMin;
    int iMax;
    
    float fRange;
    float fRadius;
    
    Type eType;
    Target eTarget;
};

class CombatAbility
{
public:
    CombatAbility();
    ~CombatAbility();
    
    int GetNumEffects() const;
    const CombatEffect& GetEffect( unsigned int uiIndex ) const;
    void AddEffect( const CombatEffect& effect );
    
private:
    std::vector< CombatEffect > m_Effects;
    
};