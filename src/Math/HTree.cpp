#include "HTree.h"

#include "../Renderer/Image.h"
#include "../Renderer/Sprite.h"
#include "../Renderer/Texture2D.h"
#include "../ResourceManager/ResourceManager.h"

#define IMAGE_SIZE 600

namespace Math {
	using namespace Renderer;

	HTree::HTree(unsigned int amountSteps, double lenghtRatio, double divisionRatio)
	: _viewPort({{0, 0}, {1, 1}})
	, _amountSteps(amountSteps)
	, _lenghtRatio(lenghtRatio)
	, _divisionRatio(divisionRatio)
	, _img(std::make_shared<Image>(IMAGE_SIZE, IMAGE_SIZE))
	, _sprite(nullptr) {
		makeFractal();
	}

	void HTree::render() {
        if (_sprite) {
            _sprite->render();
        }
    }

	void HTree::initSprite() {
        std::shared_ptr<Texture2D> texture = std::make_shared<Texture2D>(_img->width(),
                                                                         _img->height(),
                                                                         _img->data());
        const ResourceManager& res = ResourceManager::instance();
        _sprite = std::make_shared<Sprite>(texture, res.getShaderProgram("SpriteShader"),
                                           glm::vec2{0.f},
                                           (_sprite ? _sprite->size() : glm::vec2(IMAGE_SIZE)));
    }

    void HTree::makeFractal() {

    }
}