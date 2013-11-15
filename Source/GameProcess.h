//
//  GameProcess.h
//  UndeadRising
//
//  Created by Shanee on 10/30/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#pragma once

#include <Engine.h>
#include <Rendering/Interfaces/IRenderer.h>
#include <Game/Entities/Components/Rendering/FreeCameraComponent.h>
#include <Game/Entities/Components/Rendering/HeightmapComponent.h>
#include <Game/Entities/Components/Rendering/QuadComponent.h>

#include <Core/Process/Process.h>
#include <Game/Entities/Components/Rendering/SkyBox.h>
#include <Game/Entities/Components/Rendering/MeshComponent.h>
#include <Game/Entities/Components/Rendering/AtmosphericScattering.h>
#include "IslandData.h"
#include <Core/Input/InputManager.h>
#include "SteeringComponent.h"

using namespace Engine;

class GameProcess : public Process, public IMouseHandler, public ITouchHandler
{
public:
    GameProcess();
    ~GameProcess();
    
    virtual void VOnInit(void);
    virtual void VOnUpdate( const float fDeltaSeconds );
    virtual void VOnSuccess(void);
    virtual void VOnFail(void);
    virtual void VOnAbort(void);
    
    virtual bool VOnMouseMove( const Vector3& vPosition, const Vector3& vDeltaPosition );
    virtual bool VOnMouseButtonDown( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonUp( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseButtonDClick( const int iButtonIndex, const Vector3& vPosition );
    virtual bool VOnMouseWheel( const Vector3& vPosition, const Vector3& vDelta );
    
    virtual bool VOnTouchStart( const int iTouchIndex, const Vector2& vPosition, const int iPressure );
    virtual bool VOnTouchEnd( const int iTouchIndex, const Vector2& vPosition, const int iPressure );
    virtual bool VOnTouchCancel( const int iTouchIndex, const Vector2& vPosition, const int iPressure );
    virtual bool VOnTouchMove( const int iTouchIndex, const Vector2& vPosition, const Vector2& vDeltaPosition, const int iPressure );

private:
    IslandData m_IslandData;
    
    HeightmapComponent* m_pHeightMapEntity;
    FreeCameraComponent* m_pCamera;
    
    Entity* m_pMrBitey;
    SteeringComponent* m_pSteering;
    
    AtmosphericScattering* m_pAtmosphere;
};