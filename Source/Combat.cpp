//
//  Combat.cpp
//  UndeadRising
//
//  Created by Shanee on 11/12/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "Combat.h"
#include <Core/Application/BaseApplication.h>
#include <Game/Entities/Components/Rendering/Particles/ParticleEmitter.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SimulationProcessors.h>
#include <Game/Game.h>

void Combat::InitiateCombat( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 )
{
    CombatProcess* pCombatProcess = new CombatProcess( pCamera, pEntity0, pEntity1 );
    BaseApplication::Get()->AttachProcess( pCombatProcess );
    pCombatProcess->Release();
}

void Combat::ProcessAbility( const CombatAbility& ability, Entity* pUser, Entity* pTarget )
{
    unsigned int uiNumEffects = ability.GetNumEffects();
    for ( unsigned int i = 0; i < uiNumEffects; ++i )
    {
        const CombatEffect& effect = ability.GetEffect( i );
        ResolveEffect( effect, pUser, pTarget );
    }
}

void Combat::ResolveEffect( const CombatEffect& effect, Entity* pUser, Entity* pTarget )
{
    Character* pUserCharacter = (Character*)pUser->GetComponent( "Character" );
    Character* pTargetCharacter = (Character*)pTarget->GetComponent( "Character" );
    
    int iRand = g_RandomNumGen.RandomInt( effect.iMin, effect.iMax );
    
    switch ( effect.eTarget )
    {
        case CombatEffect::Self:
        {
            pUserCharacter->OnDamage( iRand, effect.eType );
        } break;
            
        case CombatEffect::Other:
        {
            pTargetCharacter->OnDamage( iRand, effect.eType );
            
            if ( effect.strParticles.size() )
            {
                ParticleEmitterData* pParticleData = new ParticleEmitterData();
                pParticleData->VFromXML( AssetManager::Get().GetAsset<XmlResource>( effect.strParticles )->GetRoot() );
                ParticleEmitter* pEmitter = new ParticleEmitter();
                pEmitter->SetData( pParticleData );
                
                const Transform& userTransform = pUser->GetTransform();
                const Transform& targetTransform = pTarget->GetTransform();
                Entity* pEmitterEntity = Game::CreateEntity( userTransform );
                pEmitterEntity->AddComponent( pEmitter );
                pEmitter->Start();
                pEmitter->Release();
                
                Vector3 vDirection = userTransform.GetPosition().Direction( targetTransform.GetPosition() );
                VelocityDirectionProcessor* pVelocityDirectionProc = new VelocityDirectionProcessor( vDirection );
                pEmitter->AddProcessor( pVelocityDirectionProc );
                pVelocityDirectionProc->Release();
            }
            
        } break;
            
        case CombatEffect::Position:
            
            break;
            
        case CombatEffect::Area:
            
            break;
            
        default:
            throw "Unhandled effect target";
            break;
    }
}

const HashedString Combat::hMessageCombatStart( "CombatStart" );
const HashedString Combat::hMessageCombatOver( "CombatOver" );
const HashedString Combat::hMessageCombatWon( "CombatWon" );
const HashedString Combat::hMessageCombatLost( "CombatLost" );