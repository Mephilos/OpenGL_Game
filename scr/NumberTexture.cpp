#include "NumberTexture.h"
#include <sstream>
#include <iomanip>

// ƒRƒ“ƒXƒgƒ‰ƒNƒ^
NumberTexture::NumberTexture(GSint texture, int width, int height) :
	texture_(texture),
	width_(width),
	height_(height) {
}

// •`‰æ
void NumberTexture::draw(const GSvector2 & position, int num, int digit, char fill, const GScolor* color) const {
	std::stringstream ss;
	ss << std::setw(digit) << std::setfill(fill) << num;
	draw(position, ss.str(), color);
}

// •`‰æ
void NumberTexture::draw(const GSvector2 & position, int num, const GScolor* color) const {
	draw(position, std::to_string(num), color);
}

// •`‰æ
void NumberTexture::draw(const GSvector2 & position, const std::string & num, const GScolor* color) const {
	for (int i = 0; i < (int)num.size(); ++i) {
		if (num[i] == ' ') continue;
		const int n = num[i] - '0';
		const GSrect rect(n * width_, 0.0f, (n * width_) + width_, height_);
		const GSvector2 pos(position.x + i * width_, position.y);
		gsDrawSprite2D(texture_, &pos, &rect, NULL, color, NULL, 0);
	}
}
