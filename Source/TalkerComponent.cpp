#include "TalkerComponent.h"
#include <Game/Dialogue/DialogueXmlParser.h>
#include <Game/Dialogue/UI/DialogueInterface.h>
#include <Core/Application/BaseApplication.h>

namespace Engine
{
	TalkerComponent::TalkerComponent( const std::string& strDialogue )
	{
		DialogueTree* pTree = DialogueXmlParser::FromFile( strDialogue.c_str() );
		if ( pTree )
		{
			m_pDialogue = pTree;
			pTree->Release();
		}
	}


	TalkerComponent::~TalkerComponent(void)
	{
	}

	void TalkerComponent::VOnInteract( Entity* pEntity )
	{
		if ( m_pDialogue )
		{
			DialogueInterface* pDialogueInterface = (DialogueInterface*)BaseApplication::Get()->GetProcessManager().GetProcessByName( "Dialogue" );
			if ( pDialogueInterface )
			{
				pDialogueInterface->SetDialogueTree( m_pDialogue );
			}
		}
	}

}
