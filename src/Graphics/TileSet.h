#include "Sgl/Graphics/Texture2D.h"
#include <memory>
#include <vector>

namespace sgl {

	class TileSet {
		std::shared_ptr<Texture2D> tileImage;
		std::vector<Sprite> tiles;
	public:
		void Initialize(const std::string& url, int tileWidth, int tileHeight);
	};

}