#pragma once

#include <Game/Entities/Component.h>

namespace Engine
{
	class InteractableComponent : public Component
	{
	public:
		InteractableComponent(void);
		virtual ~InteractableComponent(void);

		virtual const HashedString& GetType() const;

		virtual void VOnInteract( Entity* pEntity )=0;

		static const HashedString g_hID;
	};

}
