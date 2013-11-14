//
//  Main.cpp
//  UndeadRising
//
//  Created by Shanee on 10/8/13.
//  Copyright (c) 2013 LunaEngine. All rights reserved.
//

#include "Main.h"
#include <Engine.h>
#include <Rendering/Interfaces/IRenderer.h>
#include <Game/Entities/Components/Rendering/FreeCameraComponent.h>
#include <Game/Entities/Components/Rendering/HeightmapComponent.h>
#include <Game/Entities/Components/Rendering/QuadComponent.h>
#include <Core/AssetManager/FolderAssetBundle.h>
#include <Core/AssetManager/Loaders/ImageAssetLoader.h>

#include <Core/Network/TCPSocket.h>
#include <Core/Network/SocketManager.h>

#include <Core/Threading/Multithreading.h>
#include <Core/Process/RealTimeProcess.h>

#include "GameProcess.h"

using namespace Engine;

FreeCameraComponent* pCamera = NULL;

class ServerTest : public RealTimeProcess
{
public:
    
    
    ServerTest() { }
    virtual ~ServerTest(void) { }
    
protected:
    TCPSocket* m_pSocket;
    void VThreadProc(void)
    {
        m_pSocket = new TCPSocket();
        if ( m_pSocket->VConnect( "127.0.0.1", 8000 ) == true )
        {
            while ( true )
            {
                m_pSocket->Send( "Hello", 5 );
                
                char buffer[200] = { '\0' };
                int iResult = m_pSocket->Receive( buffer, 200 );
                
                m_pSocket->Close();
                
                break;
            }
        }
        
        m_pSocket->Close();
        
        delete m_pSocket;
    }
};

TCPSocket* g_Server;
SocketManager* g_SocketManager;
void Start()
{
    /*g_SocketManager = new SocketManager();
    g_Server = new TCPSocket();
    g_Server->Listen( 8000, 2 );
    g_SocketManager->AddSocket( g_Server );
    g_Server->Release();
    
    g_SocketManager->SetCallbackOnMessage( [] ( BaseSocket* pSocket, const char* pBuffer, int iSize )
    {
        pSocket->Send( "Moo", 3 );
    }
    );
    
    ServerTest* pTest = new ServerTest();
    BaseApplication::Get()->AttachProcess( pTest );
    pTest->Release();*/
    ////
    
    FolderAssetBundle* pBundle = new FolderAssetBundle( FileUtils::GetWorkingFolder() );
	AssetManager::Get().AddAssetBundle( pBundle );
    
    AssetManager::Get().RegisterLoader( HashedString( "*.png" ), new ImageAssetLoader() );
    AssetManager::Get().RegisterLoader( HashedString( "*.jpg" ), new ImageAssetLoader() );
    
    GameProcess* pGame = new GameProcess();
    BaseApplication::Get()->AttachProcess( pGame );
    pGame->Release();
}

void Update( float fDeltaSeconds )
{
    
    //g_SocketManager->DoSelect();
}

void End()
{
    //delete g_SocketManager;
}