#include <kotek.core/include/kotek_main_manager.h>
#include <kotek.game/kotek_engine.h>

int main(int argc, char** argv)
{
	Kotek::Core::ktkMainManager main_manager(argc, argv);

	Kotek::Engine::InitializeEngine(main_manager);

	Kotek::Engine::ExecuteEngine(main_manager);

	Kotek::Engine::ShutdownEngine(main_manager);

	return 0;
}
