#include "HTree.h"

#include <iostream>

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
	, _img(std::make_shared<Image>(IMAGE_SIZE, IMAGE_SIZE, 1))
	, _sprite(nullptr) {
		// @TODO УДАЛИТЬ ЭТО!!!
		_amountSteps = 1;
		_lenghtRatio = 2.;
		_divisionRatio = 1.;
		//--------------------
		makeFractal();
	}

	void HTree::render() {
        if (_sprite) {
            _sprite->render();
        }
    }

    void HTree::setWH(const unsigned int newWidth, const unsigned int newHeight) noexcept {
        _sprite->setSize(glm::vec2(newWidth, newHeight));
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
    	// @TODO Метод не дописан
    	double width = static_cast<double>(_img->width());
    	double height = static_cast<double>(_img->height());
    	Line startLine {{width / 4, height / 2},
    					{3 * width / 4, height / 2}};
		drawLine(startLine, 3, Color::BLACK);
		initSprite();
    }

    void HTree::drawLine(Line o, unsigned int thickness, Renderer::Color color) {
        Rectangle rectangle = genRectangle(o, thickness);
        fillRectangle(rectangle, color);
    }

    Rectangle HTree::genRectangle(Line o, unsigned int thickness) {
        Rectangle result;
        if (thickness % 2 == 0) {
            thickness++;
        }
        if (o.first.y == o.second.y) {
            if (o.first.x > o.second.x) {
            std::swap(o.first, o.second);        
            }
            result = {{o.first.x, o.first.y - thickness / 2},
                      {o.second.x, o.second.y + thickness / 2}};
        } else {
            if (o.first.y < o.second.y) {
                std::swap(o.first, o.second);
            }
            result = {{o.second.x - thickness / 2, o.second.y},
                      {o.first.x + thickness / 2, o.first.y}};
        }
        return result;
    }

    void HTree::fillRectangle(Rectangle o, Color color) {
    	scaleRectangle(o);
    	int minX = ceil(std::min(o.leftBottom.x, o.rightTop.x));
    	int minY = ceil(std::min(o.leftBottom.y, o.rightTop.y));
    	int maxX = ceil(std::max(o.leftBottom.x, o.rightTop.x));
    	int maxY = ceil(std::max(o.leftBottom.y, o.rightTop.y));
    	for (unsigned int x = minX; x <= maxX and x < _img->width(); x++) {
    		for (unsigned int y = minY; y <= maxY and y < _img->height(); y++) {
    			_img->setColor(x, y, color);
    		}
    	}
    }

    void HTree::scaleRectangle(Rectangle& o) const noexcept {
    	auto crop = [](Vector&& o) -> Vector {
            o.x = o.x < 0 ? 0 : o.x;
            o.y = o.y < 0 ? 0 : o.y;
            return o;
        };
        auto temp = _viewPort.leftBottom;
        temp.scale(_img->width(), _img->height());
        o.leftBottom = crop(o.leftBottom - temp);
        o.rightTop = crop(o.rightTop - temp);
        auto diff = _viewPort.rightTop - _viewPort.leftBottom;
        double scaleCoefX = diff.x > 0 ? 1. / diff.x : 0.;
        double scaleCoefY = diff.y > 0 ? 1. / diff.y : 0.;
        o.scale(scaleCoefX, scaleCoefY);
    }
}