/* TODO: delete
#include "kotek_callbacks.h"
#include "kotek_factory.h"
#include "kotek_game.h"
#include "kotek_scene.h"
#include "kotek_system_camera.h"
*/

/* TODO: delete
#pragma region Systems
namespace Kotek
{
	namespace Game
	{
		void updateComponent_Camera(Core::ktkMainManager& main_manager,
			kotek_component_camera* p_component_camera)
		{
			KOTEK_ASSERT(p_component_camera,
				"you can't receive here an invalid component");

			Core::ktkInput* p_input = main_manager.GetInput();

			float xoffset = p_input->GetMouseX() - p_input->GetMouseLastX();
			float yoffset = p_input->GetMouseLastY() - p_input->GetMouseY();

			xoffset *= p_input->GetMouseSensitivity();
			yoffset *= p_input->GetMouseSensitivity();

			float yaw = p_component_camera->getYaw();
			yaw += xoffset;

			float pitch = p_component_camera->getPitch();
			pitch += yoffset;

			if (pitch > 89.0f)
			{
				pitch = 89.0f;
			}
			else if (pitch < -89.0f)
			{
				pitch = -89.0f;
			}

			p_component_camera->setYaw(yaw);
			p_component_camera->setPitch(pitch);

			ktk::vec3_t direction;
			direction.x =
				cos(ktk::math::radians(yaw)) * cos(ktk::math::radians(pitch));
			direction.y = sin(ktk::math::radians(pitch));
			direction.z =
				sin(ktk::math::radians(yaw)) * cos(ktk::math::radians(pitch));

			p_component_camera->setFront(ktk::math::normalize(direction));
		}

		void updateSystems(Core::ktkMainManager& main_manager)
		{
			kotek_scene* p_scene = g_manager_game_factory.getCurrentScene();

			KOTEK_ASSERT(p_scene, "can't be, invalid scene");

			updateComponent_Camera(main_manager,
				g_manager_game_factory.get<kotek_component_camera>(
					p_scene->getActor()));
		}

		void updateRender(Core::ktkMainManager& main_manager)
		{
			main_manager.getRenderer()->draw();
		}
	} // namespace Game
} // namespace Kotek
#pragma endregion
*/

namespace Kotek
{
	namespace Game
	{
		bool ExecuteModule_Game(Core::ktkMainManager* main_manager, float dt)
		{
			return true;
		}

		bool serializeModule_Game(void) { return true; }

		bool deserializeModule_Game(void) { return true; }
	} // namespace Game
} // namespace Kotek
