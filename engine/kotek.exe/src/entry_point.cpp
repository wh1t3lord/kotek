#include <kotek.core.main_manager/include/kotek_core_main_manager.h>
#include <kotek.game/include/kotek_engine.h>

int main(int argc, char** argv)
{
	Kotek::Core::ktkMainManager main_manager;

	Kotek::Engine::InitializeEngine(&main_manager);
	Kotek::Engine::ExecuteEngine(&main_manager);
	Kotek::Engine::ShutdownEngine(&main_manager);

	return 0;
}
