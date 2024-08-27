#pragma once

#include <functional>
#include <SDL.h>
#include "string"
#include "Graphics/TexturedRectangle.h"
#include "Physics/Vec2D.h"
#include "Core/GlobalResources.h"

class Button {
public:
	Button() : mnoptrTexture(nullptr), mnoptrPressableTexture(nullptr), mWidth(0), mHeight(0), mPosition(Vec2D::Zero) {};
	Button(const std::string& imagePath, int width, int height, const ImageFormat& imageFormat = FORMAT_PNG, float imageScale = SCALE);
	~Button();

	void Update();
	void Render(bool isStatic = true);
	void SetButtonFunction(std::function<void(void)> function);
	void SetPressableTexture(const std::string& path, const ImageFormat& imageFormat = FORMAT_PNG, float imageScale = SCALE);

	void SetPosition(float x, float y);
	void SetPosition(const Vec2D& position);
	void SetScale(float scale, bool isPressableButton = false);
	inline int GetWidth() const { return mWidth; }
	inline int GetHeight() const { return mHeight; }

	bool CanPressButton();
	inline void ExecuteButton() { mButtonFunction(); }

private:
	Vec2D mPosition;
	int mWidth, mHeight;
	TexturedRectangle* mnoptrTexture;
	TexturedRectangle* mnoptrPressableTexture;
	std::function<void(void)> mButtonFunction;
};