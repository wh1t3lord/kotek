#pragma once

#include "../kotek.core/kotek_std.h"

namespace Kotek
{
	namespace Render
	{
		class kotek_gltf_accessor
		{
		public:
			kotek_gltf_accessor(void) :
				m_count(0), m_stride(0), m_dimension(0), m_type(0),
				m_p_data(nullptr), m_min(0.0f, 0.0f, 0.0f, 0.0f),
				m_max(0.0f, 0.0f, 0.0f, 0.0f)
			{
			}

			~kotek_gltf_accessor(void) {}

			const float* get(int index) const
			{
				if (index >= this->m_count)
				{
					index = this->m_count - 1;
				}

				return this->m_p_data + this->m_stride * index;
			}

			int findClosestFloatIndex(float val) const
			{
				int ini = 0;
				int fin = this->m_count - 1;

				while (ini <= fin)
				{
					int mid = (ini + fin) / 2;
					float v = *(this->get(mid));

					if (val < v)
					{
						fin = mid - 1;
					}
					else if (val > v)
					{
						ini = mid + 1;
					}
					else
					{
						return mid;
					}
				}

				return fin;
			}

			int getCount(void) const noexcept { return this->m_count; }
			void setCount(int count) noexcept { this->m_count = count; }

			int getStride(void) const noexcept { return this->m_stride; }
			void setStride(int value) noexcept { this->m_stride = value; }

			int getDimension(void) const noexcept { return this->m_dimension; }
			void setDimension(int value) noexcept { this->m_dimension = value; }

			int getType(void) const noexcept { return this->m_type; }
			void setType(int value) noexcept { this->m_type = value; }

			void setData(const float* p_data) noexcept
			{
				this->m_p_data = p_data;
			}

			const ktk::math::vec4_t& getMin(void) const noexcept
			{
				return this->m_min;
			}
			void setMin(const ktk::math::vec4_t& vec) noexcept { this->m_min = vec; }

			const ktk::math::vec4_t& getMax(void) const noexcept
			{
				return this->m_max;
			}
			void setMax(const ktk::math::vec4_t& vec) noexcept { this->m_max = vec; }

		private:
			int m_count;
			int m_stride;
			int m_dimension;
			int m_type;
			const float* m_p_data;
			ktk::math::vec4_t m_min;
			ktk::math::vec4_t m_max;
		};

		class kotek_gltf_primitives
		{
		public:
			kotek_gltf_primitives(void) :
				m_center(0.0f, 0.0f, 0.0f, 0.0f),
				m_radius(0.0f, 0.0f, 0.0f, 0.0f)
			{
			}
			~kotek_gltf_primitives(void) {}

			const ktk::math::vec4_t& getCenter(void) const noexcept
			{
				return this->m_center;
			}
			void setCenter(const ktk::math::vec4_t& vec) noexcept
			{
				this->m_center = vec;
			}

			const ktk::math::vec4_t& getRadius(void) const noexcept
			{
				return this->m_radius;
			}
			void setRadius(const ktk::math::vec4_t& vec) noexcept
			{
				this->m_radius = vec;
			}

		private:
			ktk::math::vec4_t m_center;
			ktk::math::vec4_t m_radius;
		};

		class kotek_gltf_mesh
		{
		public:
			kotek_gltf_mesh(void) {}
			~kotek_gltf_mesh(void) {}

			void addPrimitive(const kotek_gltf_primitives& data) noexcept
			{
				this->m_storage_primitives.push_back(data);
			}

			const ktk::vector<kotek_gltf_primitives>& getPrimitives(
				void) const noexcept
			{
				return this->m_storage_primitives;
			}

		private:
			ktk::vector<kotek_gltf_primitives> m_storage_primitives;
		};

		class kotek_gltf_transform
		{
		public:
			kotek_gltf_transform(void) :
				m_rotation(ktk::mat4x4_t()),
				m_translation(0.0f, 0.0f, 0.0f, 0.0f),
				m_scale(1.0f, 1.0f, 1.0f, 0.0f)
			{
			}
			~kotek_gltf_transform(void) {}

			const ktk::mat4x4_t& getRotation(void) const noexcept
			{
				return this->m_rotation;
			}
			void setRotation(const ktk::mat4x4_t& data) noexcept
			{
				this->m_rotation = data;
			}

			const ktk::math::vec4_t& getTranslation(void) const noexcept
			{
				return this->m_translation;
			}
			void setTranslation(const ktk::math::vec4_t& data) noexcept
			{
				this->m_translation = data;
			}

			const ktk::math::vec4_t& getScale(void) const noexcept
			{
				return this->m_scale;
			}
			void setScale(const ktk::math::vec4_t& data) noexcept
			{
				this->m_scale = data;
			}

		private:
			ktk::mat4x4_t m_rotation;
			ktk::math::vec4_t m_translation;
			ktk::math::vec4_t m_scale;
		};

		class kotek_gltf_node
		{
		public:
			kotek_gltf_node(void) :
				m_is_joint(false), m_skin_index(-1), m_mesh_index(-1),
				m_channel(-1)
			{
			}
			~kotek_gltf_node(void) {}

			bool isJoint(void) const noexcept { return this->m_is_joint; }
			void setJoint(bool value) noexcept { this->m_is_joint = value; }

			int getSkinIndex(void) const noexcept { return this->m_skin_index; }
			void setSkinIndex(int value) noexcept
			{
				this->m_skin_index = value;
			}

			int getMeshIndex(void) const noexcept { return this->m_mesh_index; }
			void setMeshIndex(int value) noexcept
			{
				this->m_mesh_index = value;
			}

			int getChannel(void) const noexcept { return this->m_channel; }
			void setChannel(int value) noexcept { this->m_channel = value; }

			const ktk::string& getName(void) const noexcept
			{
				return this->m_name;
			}
			void setName(const ktk::string& name) noexcept
			{
				this->m_name = name;
			}

			const kotek_gltf_transform& getTransform(void) const noexcept
			{
				return this->m_transform;
			}
			void setTransform(const kotek_gltf_transform& data) noexcept
			{
				this->m_transform = data;
			}

		private:
			bool m_is_joint;
			int m_skin_index;
			int m_mesh_index;
			int m_channel;
			ktk::string m_name;
			kotek_gltf_transform m_transform;
		};

		class kotek_gltf_scene
		{
		public:
			kotek_gltf_scene(void) {}
			~kotek_gltf_scene(void) {}

			const ktk::vector<int>& getNodes(void) const noexcept
			{
				return this->m_nodes;
			}
			void setNodes(const ktk::vector<int>& data) noexcept
			{
				this->m_nodes = data;
			}

		private:
			ktk::vector<int> m_nodes;
		};

#pragma region Animation
		class kotek_gltf_skins
		{
		public:
			kotek_gltf_skins(void) : m_p_skeleton(nullptr) {}
			~kotek_gltf_skins(void) {}

			kotek_gltf_node* getSkeleton(void) const noexcept
			{
				return this->m_p_skeleton;
			}
			void setSkeleton(kotek_gltf_node* p_node) noexcept
			{
				this->m_p_skeleton = p_node;
			}

			const ktk::vector<int>& getJointsNodeIndex(void) const noexcept
			{
				return this->m_joints_node_index;
			}
			void setJointsNodeIndex(const ktk::vector<int>& data) noexcept
			{
				this->m_joints_node_index = data;
			}

			const kotek_gltf_accessor& getInverseBindMatrices(
				void) const noexcept
			{
				return this->m_inverse_bind_matrices;
			}
			void setInverseBindMatrices(
				const kotek_gltf_accessor& data) noexcept
			{
				this->m_inverse_bind_matrices = data;
			}

		private:
			kotek_gltf_node* m_p_skeleton;
			ktk::vector<int> m_joints_node_index;
			kotek_gltf_accessor m_inverse_bind_matrices;
		};
#pragma endregion

		class kotek_gltf_light
		{
		public:
			kotek_gltf_light(void) :
				m_light_type(kLightType_Directional), m_range(0.0f),
				m_intensity(0.0f), m_inner_cone_angle(0.0f),
				m_outer_cone_angle(0.0f), m_color(1.0f, 1.0f, 1.0f, 1.0f)
			{
			}
			~kotek_gltf_light(void) {}

			enum light_type_t : int
			{
				kLightType_Directional,
				kLightType_PointLight,
				kLightType_SpotLight
			};

			light_type_t getLightType(void) const noexcept
			{
				return this->m_light_type;
			}
			void setLightType(light_type_t type) noexcept
			{
				this->m_light_type = type;
			}

			float getRange(void) const noexcept { return this->m_range; }
			void setRange(float value) noexcept { this->m_range = value; }

			float getIntensity(void) const noexcept
			{
				return this->m_intensity;
			}
			void setIntensity(float value) noexcept
			{
				this->m_intensity = value;
			}

			float getInnerConeAngle(void) const noexcept
			{
				return this->m_inner_cone_angle;
			}
			void setInnerConeAngle(float value) noexcept
			{
				this->m_inner_cone_angle = value;
			}

			float getOuterConeAngle(void) const noexcept
			{
				return this->m_outer_cone_angle;
			}
			void setOuterConeAngle(float value) noexcept
			{
				this->m_outer_cone_angle = value;
			}

			const ktk::math::vec4_t& getColor(void) const noexcept
			{
				return this->m_color;
			}
			void setColor(const ktk::math::vec4_t& data) noexcept
			{
				this->m_color = data;
			}

		private:
			light_type_t m_light_type;
			float m_range;
			float m_intensity;
			float m_inner_cone_angle;
			float m_outer_cone_angle;
			ktk::math::vec4_t m_color;
		};

		class kotek_gltf_light_instance
		{
		public:
			kotek_gltf_light_instance(void) : m_light_id(-1), m_node_index(-1)
			{
			}
			~kotek_gltf_light_instance(void) {}

			int getLightID(void) const noexcept { return this->m_light_id; }
			void setLightID(int value) noexcept { this->m_light_id = value; }

			int getNodeIndex(void) const noexcept { return this->m_node_index; }
			void setNodeIndex(int value) noexcept
			{
				this->m_node_index = value;
			}

		private:
			int m_light_id;
			int m_node_index;
		};

		class kotek_gltf_camera
		{
		public:
			kotek_gltf_camera(void) :
				m_node_index(-1), m_camera_type(kCameraType_Perspective),
				m_fov(60.0f), m_plane_near(0.1f), m_plane_far(1000.0f)
			{
			}

			enum camera_type_t : int
			{
				kCameraType_Perspective
			};

			int getNodeIndex(void) const noexcept { return this->m_node_index; }
			void setNodeIndex(int value) noexcept
			{
				this->m_node_index = value;
			}

			camera_type_t getCameraType(void) const noexcept
			{
				return this->m_camera_type;
			}
			void setCameraType(camera_type_t value) noexcept
			{
				this->m_camera_type = value;
			}

			float getFOV(void) const noexcept { return this->m_fov; }
			void setFOV(float value) noexcept { this->m_fov = value; }

			float getPlaneNear(void) const noexcept
			{
				return this->m_plane_near;
			}
			void setPlaneNear(float value) noexcept
			{
				this->m_plane_near = value;
			}

			float getPlaneFar(void) const noexcept { return this->m_plane_far; }
			void setPlaneFar(float value) noexcept
			{
				this->m_plane_far = value;
			}

		private:
			int m_node_index;
			camera_type_t m_camera_type;
			float m_fov;
			float m_plane_near;
			float m_plane_far;
		};
	} // namespace Render
} // namespace Kotek