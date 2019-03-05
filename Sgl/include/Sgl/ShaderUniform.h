#pragma once
#include <string>

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

	struct UniformDeclaration {
		unsigned int offset;
		UniformType type;
		std::string name;
	};
}