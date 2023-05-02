#pragma once

#include <memory>

#include "Geometry.h"

namespace Renderer {
	class Image;
	class Sprite;
	enum class Color;

	struct ViewPort {
        Math::Vector leftBottom;
        Math::Vector rightTop;
    };
}


namespace Math {
	class HTree {
	public:
		HTree(const HTree&) = delete;
		HTree& operator=(const HTree&) = delete;
		HTree& operator=(HTree&&) = delete;

	public:
		explicit HTree(unsigned int amountSteps, double lenghtRatio = 2.,
					   double divisionRatio = 1.);
		HTree(HTree&&) = default;

	public:
		void render();

		void setWH(unsigned int newWidth, unsigned int newHeight) noexcept;

	private:
		void initSprite();

		void makeFractal();

		void fillRectangle(Rectangle o, Renderer::Color color);

		void scaleRectangle(Rectangle& o) const noexcept;

	private:
		Renderer::ViewPort _viewPort;
		unsigned int _amountSteps;
		double _lenghtRatio;
		double _divisionRatio;
		std::shared_ptr<Renderer::Image> _img;
		std::shared_ptr<Renderer::Sprite> _sprite;
	};
}