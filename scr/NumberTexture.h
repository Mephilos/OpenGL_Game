#ifndef NUMBER_TEXTURE_H_
#define NUMBER_TEXTURE_H_

#include <gslib.h>
#include <string>

class NumberTexture {
public:
	// コンストラクタ
	NumberTexture(GSint texture, int width, int height);
	// 描画
	void draw(const GSvector2& position, int num, int digit, char fill = '0', const GScolor* color = 0) const;
	// 描画
	void draw(const GSvector2& position, int num, const GScolor* color = 0) const;
	// 描画
	void draw(const GSvector2& position, const std::string& num, const GScolor* color = 0) const;

private:
	// テクスチャ
	GSint	texture_;
	// 幅
	int		width_;
	// 高さ
	int		height_;
};

#endif

