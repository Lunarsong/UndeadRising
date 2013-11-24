//
//  CombatProcess.cpp
//  UndeadRising
//
//  Created by Shanee on 11/11/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "CombatProcess.h"
#include <Rendering/Scene/SceneManager.h>
#include <Game/Game.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SpawnPositionProcessors.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SimulationProcessors.h>
#include <Game/Entities/Components/DurationComponent.h>
#include "Combat.h"

void CombatProcess::OnCombatButton( UIElement* pElement, void* pArgs )
{
	Character* pCharacter = (Character*)m_pEntity0->GetComponent( "Character" );
    if ( pCharacter )
    {
        unsigned int uiSize = pCharacter->GetNumAbilities();
        if ( (unsigned int)pArgs < uiSize )
        {
            const CombatAbility& ability = pCharacter->GetAbility( (unsigned int)pArgs );
            Combat::ProcessAbility( ability, m_pEntity0, m_pEntity1 );
        }
        
        else
        {
            throw "Ability button pressed without ability";
        }
    }
    
    return;
    
    const Transform& transform = m_pEntity0->GetTransform();

	Entity* pEntity = Game::CreateEntity( transform );
	ParticleEmitter* pSystem = new ParticleEmitter();
    pEntity->AddComponent( pSystem );
    pSystem->Start();
    pSystem->SetTexture( "explosion.png" );
                    
    EmitterProcessor* pPositionProcessor = new SphericalSpawnPositionProcessor( 1.0f );
    pSystem->AddProcessor( pPositionProcessor );
    pPositionProcessor->Release();
                    
	pPositionProcessor = new ColorOverAgeProcessor( new CurveModifier( Vector3::ZERO, Vector3( 227.0f/255.0f, 140.0f/255.0f, 45.0f/255.0f ), Vector3( 219.0f/255.0f, 76.0f/255.0f, 44.0f/255.0f ), Vector3( 1.0f, 1.0f, 1.0f ) ) );
	pSystem->AddProcessor( pPositionProcessor );
	pPositionProcessor->Release();

	pPositionProcessor = new AlphaOverAgeProcessor( new CurveModifier( Vector3::ZERO, Vector3( 0.25f ), Vector3( 0.0f ), Vector3::ZERO ) );
	pSystem->AddProcessor( pPositionProcessor );
	pPositionProcessor->Release();

	pPositionProcessor = new SizeOverAgeProcessor( new CurveModifier( Vector3::ZERO, Vector3::ONE * 50.0f, Vector3::ONE * 50.0f, Vector3::ONE * 0.0f ) );
	pSystem->AddProcessor( pPositionProcessor );
	pPositionProcessor->Release();

	/*CubicBezierCurve curve0( Vector3(0.0f, 0.0f, 0.0f ), Vector3( 0.0f, 0.5f, 1.0f ) * 5.0f, Vector3( 0.0f, -0.5f, 1.0f ) * 5.0f, Vector3( -5.0f, -5.0f, 5.0f ) );
	CubicBezierCurve curve1( Vector3(0.0f, 0.0f, 0.0f ), Vector3( 0.0f, -0.5f, 1.0f ) * 5.0f, Vector3( 0.0f, 0.5f, 1.0f ) * 5.0f, Vector3( 5.0f, 5.0f, 5.0f ) );
	pPositionProcessor = new VelocityOverAgeProcessor( new RandomCurveModifier( curve0, curve1 ) );
	pPositionProcessor->Release();

	CubicBezierCurve curve2( Vector3(0.0f, 0.0f, 0.0f ), Vector3( 1.0f, 0.0f, 0.0f ) * 5.0f, Vector3( -1.0f, 0.0f, 0.0f ) * 5.0f, Vector3( 0.0f, 0.0f, 5.0f ) );
	CubicBezierCurve curve3( Vector3(0.0f, 0.0f, 0.0f ), Vector3( -1.0f, 0.0f, 0.0f ) * 5.0f, Vector3( 1.0f, 0.0f, 0.0f ) * 5.0f, Vector3( 0.0f, 0.0f, 5.0f ) );
	pPositionProcessor = new VelocityOverAgeProcessor( new RandomCurveModifier( curve2, curve3, InterpolationUtils::Half ) );
	pSystem->AddProcessor( pPositionProcessor );
	pPositionProcessor->Release();*/

	pPositionProcessor = new VelocityOverAgeProcessor( Vector3::ZERO, Vector3::FORWARD * 20.0f );
	pSystem->AddProcessor( pPositionProcessor );
	pPositionProcessor->Release();


    pPositionProcessor = new SpawnPositionProcessor( Vector3( 0.0f, 0.5f, 0.0f ) );
    pSystem->AddProcessor( pPositionProcessor );
    pPositionProcessor->Release();
    /*                
    //pPositionProcessor = new VelocityOverAgeProcessor( new CurveModifier( Vector3( 0.0f, 2.0f, 0.0f ) * 5.0f, Vector3( 1.0f, 2.0f, 1.0f ) * 5.0f, Vector3( -1.0f, 2.0f, -1.0f ) * 5.0f, Vector3( 1.0f, 2.0f, 1.0f ) * 5.0f ) );
    pPositionProcessor = new VelocityOverAgeProcessor( new ConstantEmitterModifier( Vector3::UP * 5.0f ) );
    pSystem->AddProcessor( pPositionProcessor );
    pPositionProcessor->Release();
                    
    pPositionProcessor = new RadialVelocityProcessor( Vector3( 1.0f, 1.0f, 1.0f ) * 20.0f );
    pSystem->AddProcessor( pPositionProcessor );
    pPositionProcessor->Release();
                    
    pPositionProcessor = new ColorOverAgeProcessor( new CurveModifier( Vector3::ZERO, Vector3( 1.0f, 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ), Vector3( 0.0f, 0.0f, 1.0f ) ) );
    pSystem->AddProcessor( pPositionProcessor );
    pPositionProcessor->Release();*/
                    
    pSystem->Release();
	
	DurationComponent* pDuration = new DurationComponent( 5.0f );
	pEntity->AddComponent( pDuration );
	pDuration->Start();
	pDuration->Release();

}

CombatProcess::CombatProcess( Camera* pCamera, Entity* pEntity0, Entity* pEntity1 )
{
    m_pCamera = pCamera;
    m_pEntity0 = pEntity0;
    m_pEntity1 = pEntity1;
}

CombatProcess::~CombatProcess()
{
    
}

void CombatProcess::VOnInit(void)
{
    Vector4 vPosition = m_pEntity0->GetTransform().GetPosition();
    vPosition += -m_pEntity0->GetTransform().GetDirection() * 20.0f + Vector4( 0.0f, 15.0f, 0.0f );
    m_pCamera->SetPosition(  vPosition );
    //m_pCamera->LookAtTarget( m_pEntity0->GetTransform().GetPosition() );
    m_pCamera->SetDirection( (vPosition - m_pCamera->GetPosition()).Normalize() );
    
    m_pCombatScreen = UserInterface::AddScreenFromFile( "Combat", "CombatScreen.xml" );
    assert( m_pCombatScreen );
    
	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_bottomright" ))->SetCallbackArgs( 0 );
	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_bottomright" ))->SetCallbackFunction( std::bind( &CombatProcess::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );

	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_bottomleft" ))->SetCallbackArgs( (void*)1 );
	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_bottomleft" ))->SetCallbackFunction( std::bind( &CombatProcess::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );

	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_topright" ))->SetCallbackArgs( (void*)2 );
	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_topright" ))->SetCallbackFunction( std::bind( &CombatProcess::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );

	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_topleft" ))->SetCallbackArgs( (void*)3 );
	((UIButtonImage*)m_pCombatScreen->GetElement( "btn_action_topleft" ))->SetCallbackFunction( std::bind( &CombatProcess::OnCombatButton, this, std::placeholders::_1, std::placeholders::_2 ) );
    
    
    Character* pCharacter = (Character*)m_pEntity0->GetComponent( "Character" );
    if ( pCharacter )
    {
        UILabel* pLabels[4];
        pLabels[0] = ((UILabel*)m_pCombatScreen->GetElement( "lbl_ability_br" ));
        pLabels[1] = ((UILabel*)m_pCombatScreen->GetElement( "lbl_ability_bl" ));
        pLabels[2] = ((UILabel*)m_pCombatScreen->GetElement( "lbl_ability_tr" ));
        pLabels[3] = ((UILabel*)m_pCombatScreen->GetElement( "lbl_ability_tl" ));
        
        unsigned int uiSize = pCharacter->GetNumAbilities();
        for ( unsigned int i = 0; i < 4; ++i )
        {
            if ( i >= uiSize )
                break;
            
            const CombatAbility& ability = pCharacter->GetAbility( i );
            pLabels[i]->SetString( ability.GetName().getStr() );
        }
    }
    

    UIColor* pHP = (UIColor*)m_pCombatScreen->GetElement( "player_hitpoints" );
    if ( pHP )
    {
        m_vHPSize = pHP->GetSize().GetCoordinates();
    }
    
    UIColor* pEnemyHP = (UIColor*)m_pCombatScreen->GetElement( "enemy_hitpoints" );
    if ( pEnemyHP )
    {
        m_vEnemyHPSize = pEnemyHP->GetSize().GetCoordinates();
    }
}

void CombatProcess::VOnUpdate( const float fDeltaSeconds )
{
    Character* pCharacter = (Character*)m_pEntity0->GetComponent( "Character" );
    UIColor* pHP = (UIColor*)m_pCombatScreen->GetElement( "player_hitpoints" );
    if ( pHP && pCharacter )
    {
        float fSizePercent = (float)pCharacter->GetHitPoints() / (float)pCharacter->GetAttributes().GetAttribute( CharacterAttributes::HitPoints );
        pHP->SetSize( m_vHPSize.x * fSizePercent, m_vHPSize.y );
    }
    
    Character* pEnemyCharacter = (Character*)m_pEntity1->GetComponent( "Character" );
    UIColor* pEnemyHP = (UIColor*)m_pCombatScreen->GetElement( "enemy_hitpoints" );
    if ( pEnemyHP && pEnemyCharacter )
    {
        float fSizePercent = (float)pEnemyCharacter->GetHitPoints() / (float)pEnemyCharacter->GetAttributes().GetAttribute( CharacterAttributes::HitPoints );
        pEnemyHP->SetSize( m_vEnemyHPSize.x * fSizePercent, m_vEnemyHPSize.y );
    }
}
