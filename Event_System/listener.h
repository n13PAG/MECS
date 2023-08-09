#pragma once

#include "event.h"

namespace MECS {
	class IListener
	{
	public:
		virtual void Listen(Event& event) = 0;
	};

}