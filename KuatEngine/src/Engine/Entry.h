#pragma once
#ifdef KE_PLATFORM_WINDOWS
extern KuatEngine::Application* KuatEngine::CreateApp();
int main(int argc, char** argv) {
	printf("Starting Engine...");
	auto app = KuatEngine::CreateApp();
	app->Run();
	
	delete app;
}
#endif // KE_PLATFORM_WINDOWS
