//
//  GameProcess.cpp
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "GameProcess.h"
#include "StateMachineComponent.h"
#include <Game/Entities/Components/Rendering/Particles/ParticleEmitter.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SpawnPositionProcessors.h>
#include <Game/Entities/Components/Rendering/Particles/Processors/SimulationProcessors.h>
#include "Combat.h"
#include <Game/Dialogue/UI/DialogueInterface.h>
#include "TalkerComponent.h"
#include "CombatAbility.h"
#include "GameHUDComponent.h"
#include <Game/Entities/Components/Rendering/WaterPlane.h>
#include <Game/Entities/Components/Rendering/Particles/ParticleProcessorFactory.h>
#include "SkillInterface.h"

SkillInterface* pSkillInterface;
GameProcess::GameProcess()
{
    InputManager::Get()->AddMouseHandler( this );
    InputManager::Get()->AddTouchHandler( this );
    
    ParticleProcessorFactory::Initialize();
}

GameProcess::~GameProcess()
{
    InputManager::Get()->RemoveMouseHandler( this );
    InputManager::Get()->RemoveTouchHandler( this );
    
    //delete pSkillInterface;
}

void GameProcess::VOnInit(void)
{
    //pSkillInterface =  new SkillInterface();
    
	DialogueInterface* pDialogue = new DialogueInterface( NULL, "DialogueInterface.xml", "Dialogue.xml" );
	pDialogue->SetName( "Dialogue" );
	BaseApplication::Get()->AttachProcess( pDialogue );
	pDialogue->Release();

    Entity* pEntity = Game::CreateEntity();
    ThirdPersonCamera* pCamera = new ThirdPersonCamera();
    pCamera->SetDistanceMax( 50.0f );
    m_pCamera = pCamera;
    pEntity->AddComponent( pCamera );
    pCamera->SetClearColor( ColorF::BLACK );
    pCamera->Release();
    pCamera->SetPosition( Vector4( 2000.0f, 30.0f, 2000.0f ) );
    pCamera->SetDirection( Vector4( 0.0f, 0.0f, 1.0f ) );
    pCamera->Start();
    
    pEntity = Game::CreateEntity();
    
    
    int iWorldSize = 512;
    m_IslandData.Generate( iWorldSize, iWorldSize );
    HeightmapComponent* pComponent = new HeightmapComponent( iWorldSize, iWorldSize, m_IslandData );
    m_pHeightMapEntity = pComponent;
    //pComponent->SetTexture( "sketch.png" );
    m_IslandData.GenerateBiomes();
    ColorF* pColors = new ColorF[ iWorldSize * iWorldSize ];
    for ( int i = 0; i < iWorldSize; ++i )
    {
        for ( int j = 0; j < iWorldSize; ++j )
        {
            ColorF color;
            IslandData::Biome eBiome = m_IslandData.GetBiome( i, j );
            
            if ( eBiome == IslandData::SeaWater )
            {
                color = Color::BLUE;
            }
            
            else if ( eBiome == IslandData::FreshWater )
            {
                color = Color( 0, 191, 255 );
            }
            
            else if ( eBiome == IslandData::Grassland )
            {
                color = Color( 195, 211, 170, 255 );
            }
            
            else if ( eBiome == IslandData::Snow )
            {
                color = Color::WHITE;
            }
            
            else if ( eBiome == IslandData::Bare )
            {
                color = Color( 200, 200, 200, 255 );
            }
            
            else if ( eBiome == IslandData::Scorched )
            {
                color = Color::GREY;
            }
            
            else if ( eBiome == IslandData::Tundra )
            {
                color = Color( 220, 220, 186, 255 );
            }
            
            else if ( eBiome == IslandData::Taiga )
            {
                color = Color( 203, 211, 186, 255 );
            }
            
            else if ( eBiome == IslandData::Shrubland )
            {
                color = Color( 195, 203, 186, 255 );
            }
            
            else if ( eBiome == IslandData::TemperateDesert )
            {
                color = Color( 227, 231, 201, 255 );
            }
            
            else if ( eBiome == IslandData::TemperateRainForest )
            {
                color = Color( 163, 195, 167, 255 );
            }
            
            else if ( eBiome == IslandData::TemperateDecidousForest )
            {
                color = Color( 180, 200, 168, 255 );
            }
            
            else if ( eBiome == IslandData::TropicalRainForest )
            {
                color = Color( 155, 186, 168, 255 );
            }
            
            else if ( eBiome == IslandData::TropicalSeasonalForest )
            {
                color = Color( 168, 203, 163, 255 );
            }
            
            else if ( eBiome == IslandData::SubtropicalDesert )
            {
                color = Color( 232, 220, 198, 255 );
            }
            
            else if ( eBiome == IslandData::Unassigned )
            {
                throw "Whoops";
            }
            
            else
            {
                throw "Unhandled biome";
            }
            
            pColors[ j * iWorldSize + i ] = color;
        }
    }
    
    pComponent->GenerateHeightMap( iWorldSize, iWorldSize, m_IslandData, pColors );
    delete [] pColors;
    pEntity->AddComponent( pComponent );
    pComponent->Release();
    pComponent->Start();
    
    // Generate blend map for splatting
    unsigned int* pBlendMap = new unsigned int[ iWorldSize * iWorldSize ];
    for ( int i = 0; i < iWorldSize; ++i )
    {
        for ( int j = 0; j < iWorldSize; ++j )
        {
            Color color;
            IslandData::Biome eBiome = m_IslandData.GetBiome( i, j );
            
            if ( eBiome == IslandData::SeaWater )
            {
                color = Color::BLUE;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::FreshWater )
            {
                color = Color::BLUE;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::Grassland )
            {
                color = Color::GREEN;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::Snow )
            {
                color = Color( 0, 0, 0, 255 );
            }
            
            else if ( eBiome == IslandData::Bare )
            {
                color = Color( 0, 0, 0 ,0 );
            }
            
            else if ( eBiome == IslandData::Scorched )
            {
                color = Color( 0, 0, 0 ,0 );
            }
            
            else if ( eBiome == IslandData::Tundra )
            {
                color = Color( 0, 0, 0 ,255 );
            }
            
            else if ( eBiome == IslandData::Taiga )
            {
                color = Color::BLACK;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::Shrubland )
            {
                color = Color::BLACK;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::TemperateDesert )
            {
                color = Color::RED;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::TemperateRainForest )
            {
                color = Color::GREEN;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::TemperateDecidousForest )
            {
                color = Color::GREEN;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::TropicalRainForest )
            {
                color = Color::GREEN;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::TropicalSeasonalForest )
            {
                color = Color::GREEN;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::SubtropicalDesert )
            {
                color = Color::RED;
                color.Alpha = 0;
            }
            
            else if ( eBiome == IslandData::Unassigned )
            {
                throw "Whoops";
            }
            
            else
            {
                throw "Unhandled biome";
            }
            
            pBlendMap[ j * iWorldSize + i ] = color.RGBA;
        }
    }
    
    ITexture* pBlendMapTexture = IRenderer::CreateTexture();
    pBlendMapTexture->VCreate( iWorldSize, iWorldSize, 4, (char*)pBlendMap );

    delete [] pBlendMap;
    
    StructuredMaterial<Vector4>* pSplattingMaterial = new StructuredMaterial<Vector4>();
    pSplattingMaterial->GetBuffer()->VAddProperty( "u_vLightDirection", BufferProperty::BP_VECTOR3 );
    
    IShaderProgram* pProgram = IRenderer::CreateShaderProgram();
    IVertexShader* pVertexShader = IRenderer::CreateVertexShader();
    IPixelShader* pPixelShader = IRenderer::CreatePixelShader();
    
    BinaryResource* pVertexResource = AssetManager::Get().GetAsset< BinaryResource >( "Terrain.vert" );
    BinaryResource* pPixelResource = AssetManager::Get().GetAsset< BinaryResource >( "Terrain.frag" );
    
    if ( pVertexShader->VCreateFromMemory( pVertexResource->Buffer(), pVertexResource->Size() ) == false )
        throw "Error";
    
    if ( pPixelShader->VCreateFromMemory( pPixelResource->Buffer(), pPixelResource->Size() ) == false )
        throw "error";
    
    pProgram->VSetPixelShader( pPixelShader );
    pProgram->VSetVertexShader( pVertexShader );
    pVertexShader->VAddAttribute( "u_vPosition", Position_VertexData );
    pVertexShader->VAddAttribute( "u_vTexCoords", UV_VertexData );
    pVertexShader->VAddAttribute( "u_vNormal", Normal_VertexData );
    pVertexShader->VAddAttribute( "u_vColor", Color_VertexData );
    pProgram->VLink();
    
    pSplattingMaterial->SetShaderProgram( pProgram );
    pSplattingMaterial->AddTextureRegister( "Desert" );
    pSplattingMaterial->AddTextureRegister( "Grass" );
    pSplattingMaterial->AddTextureRegister( "Water" );
    pSplattingMaterial->AddTextureRegister( "Snow" );
    pSplattingMaterial->AddTextureRegister( "Rock" );
    pSplattingMaterial->AddTextureRegister( "BlendMap" );
    
    ITexture* pTexture = AssetManager::Get().GetAsset<ITexture>( "Desert.png" );
    pSplattingMaterial->SetTexture( 0, pTexture );
    
    pTexture = AssetManager::Get().GetAsset<ITexture>( "Grass.png" );
    pSplattingMaterial->SetTexture( 1, pTexture );
    
    pTexture = AssetManager::Get().GetAsset<ITexture>( "Water.png" );
    pSplattingMaterial->SetTexture( 2, pTexture );
    
    pTexture = AssetManager::Get().GetAsset<ITexture>( "Snow.png" );
    pSplattingMaterial->SetTexture( 3, pTexture );
    
    pTexture = AssetManager::Get().GetAsset<ITexture>( "Rock.png" );
    pSplattingMaterial->SetTexture( 4, pTexture );
    
    pSplattingMaterial->SetTexture( 5, pBlendMapTexture );
    
    
    
    m_pHeightMapEntity->SetMaterial( pSplattingMaterial );
    pSplattingMaterial->Release();
    pProgram->Release();
    pPixelShader->Release();
    pVertexShader->Release();
    
    
    pBlendMapTexture->Release();
    
    /*pEntity = Game::CreateEntity();
    SkyBox* pSkyBox = new SkyBox();
    pEntity->AddComponent( pSkyBox );
    pSkyBox->Start();
    pSkyBox->Release();*/
    
    
    Matrix mat;
    MeshComponent* pMeshComponent = NULL;
    Mesh* pMesh = NULL;
    
    
    pMesh = Mesh::CreateBox();
    mat.BuildScale( Vector4::ONE * 2.0f );
    mat.SetPosition( Vector4( 1900.0f, 0.0f, 1900.0f ) );
	mat.SetPosition( Vector4( 0.0f, 0.0f, 0.0f ) );
    pEntity = Game::CreateEntity( mat );
    pMeshComponent = new MeshComponent();
//    pEntity->AddComponent( pMeshComponent );
    pMeshComponent->SetMesh( pMesh );
    pMesh->Release();
    pMeshComponent->Start();
    pMeshComponent->Release();
    m_pSteering = new SteeringComponent();
    pEntity->AddComponent( m_pSteering );
    m_pSteering->SetSpeed( 15.0f );
	m_pSteering->SetHeightOffset( 1.0f );
    m_pSteering->Start();
    m_pSteering->Release();
    
    Character* pCharacter = new Character();
    XmlResource* pResource = AssetManager::Get().GetAsset<XmlResource>( "CombatAbilities.xml" );
    if ( pResource )
    {
        auto pElement = pResource->GetRoot()->FirstChildElement();
        
        while ( pElement )
        {
            CombatAbility ability;
            ability.VFromXML( pElement );
            pCharacter->AddAbility( ability );
            
            pElement = pElement->NextSiblingElement( "Ability" );
        }
    }
    
    pEntity->AddComponent( pCharacter );
    pCharacter->Release();
    
    GameHUDComponent* pGameHud = new GameHUDComponent();
    pEntity->AddComponent( pGameHud );
    pGameHud->Start();
    pGameHud->Release();
    
    m_pMrBitey = pEntity;
    
    pEntity = Game::CreateEntity();
    m_pAtmosphere = new AtmosphericScattering();
    pEntity->AddComponent( m_pAtmosphere );
    m_pAtmosphere->Start();
	m_pAtmosphere->Release();

	Transform waterPosition;
	waterPosition.SetPosition( 0.0f, 5.0f, 0.0f );
	pEntity = Game::CreateEntity( waterPosition );
	WaterPlane* pWater = new WaterPlane();
	pEntity->AddComponent( pWater );
	pWater->Start();
	pWater->Release();
}

void GameProcess::VOnUpdate( const float fDeltaSeconds )
{
    const Transform& matTransform = m_pMrBitey->GetTransform();
    Vector4 vPosition = matTransform.GetPosition();
    Vector4 vForward = matTransform.GetDirection().Normalize();
    Vector4 vCameraPosition = vPosition - vForward * 10.0f + Vector4( 0.0f, 5.0f, 0.0f );
//    m_pCamera->SetPosition( vCameraPosition );
//    m_pCamera->SetDirection( vForward );
    Vector3 vResolution( (float)IRenderer::Get()->VGetScreenWidth(), (float)IRenderer::Get()->VGetScreenHeight(), 1.0f );
    
    Vector3 vRayPos, vRayDir;
    Matrix::Unproject( InputManager::Get()->GetMousePos(), vResolution, m_pCamera->GetProjection(), m_pCamera->GetView(), vRayPos, vRayDir );
    
    float fDistance = 0.0f;
    if ( m_pHeightMapEntity->VPick( vRayPos, vRayDir, &fDistance ) )
    {
        Matrix matTransform;
        matTransform.BuildScale( Vector4::ONE * 2.0f );
        vRayDir.Normalize();
        matTransform.SetPosition( vRayPos + vRayDir * fDistance + Vector4( 0.0f, 0.0f, 0.0f ) );
        //m_pMrBitey->SetTransform( matTransform );
    }
    
    ((StructuredMaterial<Vector4>*)m_pHeightMapEntity->GetMaterial())->GetData() = m_pAtmosphere->GetAtmosphericSettings().v3LightPos;

	m_pCamera->SetTarget( m_pMrBitey->GetTransform().GetPosition() );

	Vector4 vAngles;
	if ( InputManager::Get()->GetKeyState( KEY_D ) != NONE_KEYSTATE )
	{
		vAngles.y -= 1.0f;
	}

	if ( InputManager::Get()->GetKeyState( KEY_A ) != NONE_KEYSTATE )
	{
		vAngles.y += 1.0f;
	}

	if ( InputManager::Get()->GetKeyState( KEY_W ) != NONE_KEYSTATE )
	{
		vAngles.x += 1.0f;
	}

	if ( InputManager::Get()->GetKeyState( KEY_S ) != NONE_KEYSTATE )
	{
		vAngles.x -= 1.0f;
	}

	m_pCamera->SetAngleDelta( vAngles * fDeltaSeconds );
	m_pCamera->SetDistanceDelta(- InputManager::Get()->GetMouseWheelDelta().y );
    
    static const float speed = 1000.0f;
    
    if (InputManager::Get()->GetKeyState( KEY_UPARROW ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(Vector3::FORWARD * fDeltaSeconds * speed);
    }
    
    if (InputManager::Get()->GetKeyState( KEY_RIGHTARROW ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(Vector3::RIGHT * fDeltaSeconds * speed);
    }
    
    if (InputManager::Get()->GetKeyState( KEY_DOWNARROW ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(-Vector3::FORWARD * fDeltaSeconds * speed);
    }
    
    if (InputManager::Get()->GetKeyState( KEY_LEFTARROW ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(-Vector3::RIGHT * fDeltaSeconds * speed);
    }
    
    if (InputManager::Get()->GetKeyState( KEY_SPACE ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(Vector3::UP * fDeltaSeconds * speed);
    }
    
    if (InputManager::Get()->GetKeyState( KEY_X ) != NONE_KEYSTATE )
    {
        m_pMrBitey->GetTransform().Move(-Vector3::UP * fDeltaSeconds * speed);
    }
}

void GameProcess::VOnSuccess(void)
{
    
}

void GameProcess::VOnFail(void)
{
    
}

void GameProcess::VOnAbort(void)
{
    
}

bool GameProcess::VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition )
{
    return false;
}

bool GameProcess::VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool GameProcess::VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition )
{
    Vector3 vResolution( IRenderer::Get()->VGetScreenWidth(), IRenderer::Get()->VGetScreenHeight(), 1.0f );
    
    Vector3 vRayPos, vRayDir;
    Matrix::Unproject( vPosition, vResolution, m_pCamera->GetProjection(), m_pCamera->GetView(), vRayPos, vRayDir );
    
    float fDistance = 0.0f;

    if ( iButtonIndex == 0 )
    {
        if ( m_pHeightMapEntity->VPick( vRayPos, vRayDir, &fDistance ) )
        {
            if ( fDistance < 0.0f )
                fDistance = -fDistance;
            
            Transform& transform = m_pMrBitey->GetTransform();

			if ( InputManager::Get()->GetKeyState( KEY_T ) == HELD_KEYSTATE )
			{
				transform.SetPosition( vRayPos + vRayDir * fDistance + Vector3::UP );
			}
			else
			{
				Vector4 vTarget = vRayPos + vRayDir * fDistance + Vector3( 0.0f, 1.0f, 0.0f );
				m_pSteering->SetTargetPosition( vTarget );
			}            
            
            return false;
        }
    }
    
    else if ( iButtonIndex == 1 )
    {
        SceneNode* pSceneNode = SceneManager::Get()->VPickAndReturnClosest( vRayPos, vRayDir, &fDistance );
        if ( pSceneNode )
        {
            Entity* pEntity = pSceneNode->VGetEntity();
            if ( pEntity )
            {
                if ( pEntity != m_pHeightMapEntity->GetOwner() )
                {
                    Transform& matTransform = m_pMrBitey->GetTransform();
					Vector4 vPosition( pEntity->GetTransform().GetPosition() - Vector4( Vector4( 0.0f, 0.0f, -20.0f ) ) );                    
                    m_pHeightMapEntity->GetHeight( vPosition.x, vPosition.z, vPosition.y );
                    matTransform.SetPosition( vPosition );

					InteractableComponent* pInteractable = (InteractableComponent*)pEntity->GetComponent( InteractableComponent::g_hID );
					if ( pInteractable )
					{
						pInteractable->VOnInteract( m_pMrBitey );
					}

                    Combat::InitiateCombat( m_pCamera, m_pMrBitey, pEntity );
                }
                
                else
                {
                    Matrix matTransform;
                    matTransform.BuildScale( Vector4::ONE * 2.0f );
                    vRayDir.Normalize();
                    matTransform.SetPosition( vRayPos + vRayDir * fDistance + Vector4( 0.0f, 1.0f, 0.0f ) );
                    
                    Entity* pEntity = Game::CreateEntity( matTransform );
                    MeshComponent* pMeshComponent = new MeshComponent();
                    pEntity->AddComponent( pMeshComponent );
                    Mesh* pMesh = Mesh::CreateBox();
                    pMeshComponent->SetMesh( pMesh );
                    pMesh->Release();
                    pMeshComponent->Start();
                    pMeshComponent->Release();

					TalkerComponent* pTalker = new TalkerComponent( "Dialogue.xml" );
					pEntity->AddComponent( pTalker );
					pTalker->Start();
					pTalker->Release();
                    
                    StateMachineComponent* pStateMachine = new StateMachineComponent();
                    pEntity->AddComponent( pStateMachine );
                    //pStateMachine->Start();
                    pStateMachine->Release();
                    
                    Character* pCharacter = new Character();
                    XmlResource* pResource = AssetManager::Get().GetAsset<XmlResource>( "CombatAbilities.xml" );
                    if ( pResource )
                    {
                        auto pElement = pResource->GetRoot()->FirstChildElement();
                        
                        while ( pElement )
                        {
                            CombatAbility ability;
                            ability.VFromXML( pElement );
                            pCharacter->AddAbility( ability );
                            
                            pElement = pElement->NextSiblingElement( "Ability" );
                        }
                    }
                    
                    pEntity->AddComponent( pCharacter );
                    pCharacter->Release();
                    
                    /*ParticleEmitter* pSystem = new ParticleEmitter();
                    pEntity->AddComponent( pSystem );
                    pSystem->Start();
                    pSystem->SetTexture( "explosion.png" );
                    
                    EmitterProcessor* pPositionProcessor = new SphericalSpawnPositionProcessor( 0.5f );
                    pSystem->AddProcessor( pPositionProcessor );
                    pPositionProcessor->Release();
                    
                    pPositionProcessor = new SpawnPositionProcessor( Vector3( 0.0f, 2.0f, 0.0f ) );
                    pSystem->AddProcessor( pPositionProcessor );
                    pPositionProcessor->Release();
                    
                    //pPositionProcessor = new VelocityOverAgeProcessor( new CurveModifier( Vector3( 0.0f, 2.0f, 0.0f ) * 5.0f, Vector3( 1.0f, 2.0f, 1.0f ) * 5.0f, Vector3( -1.0f, 2.0f, -1.0f ) * 5.0f, Vector3( 1.0f, 2.0f, 1.0f ) * 5.0f ) );
                    pPositionProcessor = new VelocityOverAgeProcessor( new ConstantEmitterModifier( Vector3::UP * 5.0f ) );
                    pSystem->AddProcessor( pPositionProcessor );
                    pPositionProcessor->Release();
                    
                    pPositionProcessor = new RadialVelocityProcessor( Vector3( 1.0f, 1.0f, 1.0f ) * 20.0f );
                    pSystem->AddProcessor( pPositionProcessor );
                    pPositionProcessor->Release();
                    
                    pPositionProcessor = new ColorOverAgeProcessor( new CurveModifier( Vector3::ZERO, Vector3( 1.0f, 0.0f, 0.0f ), Vector3( 0.0f, 1.0f, 0.0f ), Vector3( 0.0f, 0.0f, 1.0f ) ) );
                    pSystem->AddProcessor( pPositionProcessor );
                    pPositionProcessor->Release();
                    
                    pSystem->Release();*/
                }
            }
        }
    }
    
    return false;
}

bool GameProcess::VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition )
{
    return false;
}

bool GameProcess::VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta )
{
    return false;
}

bool GameProcess::VOnTouchStart( const int iTouchIndex, const Vector2& vPosition, const int iPressure )
{
    
    return false;
}

bool GameProcess::VOnTouchEnd( const int iTouchIndex, const Vector2& vPosition, const int iPressure )
{
    return false;
}

bool GameProcess::VOnTouchCancel( const int iTouchIndex, const Vector2& vPosition, const int iPressure )
{
    return false;
}

bool GameProcess::VOnTouchMove( const int iTouchIndex, const Vector2& vPosition, const Vector2& vDeltaPosition, const int iPressure )
{
    Vector4 vCameraPosition = m_pCamera->GetPosition();
    vCameraPosition.x -= vDeltaPosition.x;
    vCameraPosition.z += vDeltaPosition.y;
    
    if ( m_pHeightMapEntity->GetHeight( vCameraPosition.x, vCameraPosition.z, vCameraPosition.y ) )
    {
        vCameraPosition.y += 10.0f;
    }
    
    m_pCamera->SetPosition( vCameraPosition );
    
    return false;
}