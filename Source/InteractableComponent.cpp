#include "InteractableComponent.h"

namespace Engine
{
	const HashedString InteractableComponent::g_hID( "Interactable" );

	InteractableComponent::InteractableComponent(void)
	{
	}


	InteractableComponent::~InteractableComponent(void)
	{
	}

	const HashedString& InteractableComponent::GetType() const
	{
		return g_hID;
	}

}
