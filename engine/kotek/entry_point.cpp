#include "../kotek.core/kotek_main_manager.h"
#include "../kotek.game/kotek_engine.h"

int main(int argc, char** argv)
{
	Kotek::Core::ktkMainManager main_manager(argc, argv);

	Kotek::Engine::initializeEngine(main_manager);

	Kotek::Engine::executeEngine(main_manager);

	Kotek::Engine::shutdownEngine(main_manager);

	return 0;
}
