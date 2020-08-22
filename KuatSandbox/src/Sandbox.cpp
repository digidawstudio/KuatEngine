#include <KuatEngine.h>

class Sandbox : public KuatEngine::Application {
public:
	Sandbox(){}
	~Sandbox(){}
};

KuatEngine::Application* KuatEngine::CreateApp() {
	return new Sandbox();
}