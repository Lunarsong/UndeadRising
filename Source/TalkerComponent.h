#pragma once
#include "interactablecomponent.h"
#include <Game/Dialogue/DialogueTree.h>

namespace Engine
{
	class TalkerComponent :
		public InteractableComponent
	{
	public:
		TalkerComponent( const std::string& strDialogue );
		virtual ~TalkerComponent(void);

		virtual void VOnInteract( Entity* pEntity );

	private:
		SmartPtr<DialogueTree> m_pDialogue;
	};

}
