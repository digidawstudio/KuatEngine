#include "Core.h"


#pragma once
namespace KuatEngine{

	class KUATENGINE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApp();
}

