#pragma once
#include <string>
#include <vector>
#include <cstring>
#include "glm/glm.hpp"

namespace sgl
{
	enum UniformType {
		Int,
		Float,
		Vec2,
		Vec3,
		Vec4,
		Mat3,
		Mat4
	};

	class UniformHandler {
	public:
		template <class T>
		struct Uniform {
			const char* name;
			T data;
		};

		struct UniformDeclaration {
			UniformType type;
			std::size_t offset;
		};

	private:

		constexpr static std::size_t UniformMaxSize = 300;
		constexpr static std::size_t UniformMaxCount = 20;

		std::vector<UniformDeclaration> declarations;
		std::vector<std::uint8_t> uniformVector;
		std::size_t offset;

	public:

		UniformHandler()
			: uniformVector(UniformMaxSize), offset(0)
		{
			declarations.reserve(UniformMaxCount);
		}

		template <class T>
		void AddUniform(const Uniform<T>& value)
		{
			if (std::is_same<T, int>::value)
				declarations.emplace_back(UniformDeclaration{ UniformType::Int, offset });
			else if (std::is_same<T, float>::value)
				declarations.emplace_back(UniformDeclaration{ UniformType::Float, offset });
			else if (std::is_same<T, glm::mat4>::value)
				declarations.emplace_back(UniformDeclaration{ UniformType::Mat4, offset });
			else if (std::is_same<T, glm::vec3>::value)
				declarations.emplace_back(UniformDeclaration{ UniformType::Vec3, offset });

			std::memcpy(&uniformVector[offset], &value, sizeof(Uniform<T>));
			offset += sizeof(Uniform<T>);
		}

		std::vector<UniformDeclaration>::iterator begin()
		{
			return declarations.begin();
		}

		std::vector<UniformDeclaration>::iterator end()
		{
			return declarations.end();
		}

		std::size_t Count()
		{
			return declarations.size();
		}

		template <class T>
		T GetValue(const UniformDeclaration& ud)
		{
			const Uniform<T>* temp = reinterpret_cast<Uniform<T>*>(&uniformVector[ud.offset]);
			return temp->data;
		}

		template <class T>
		const char* GetName(const UniformDeclaration& ud)
		{
			const Uniform<T>* temp = reinterpret_cast<Uniform<T>*>(&uniformVector[ud.offset]);
			return temp->name;
		}

	};
}