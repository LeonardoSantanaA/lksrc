#pragma once

#include "TexturedRectangle.h"


class GameEntity {
public:
	GameEntity() {
		mSprite = nullptr;
		mRender = nullptr;
	}

	GameEntity(SDL_Renderer* render, const std::string& spritepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE) {
		mRender = render;
		mSprite = new TexturedRectangle(mRender, spritepath, format, scale);
	}

	~GameEntity() {
		delete mSprite;
	}

	void Update() {

	}

	void Render() {
		if (mSprite) {
			mSprite->Render(mRender);
		}
	}

	inline TexturedRectangle& GetTexturedRectangle() const{
		if (mSprite) {
			return *mSprite;
		}
		std::cout << "trying access a null pointer. GetTexturedRectangle()." << std::endl;
	}

	inline void SetPosition(int x, int y) {
		if (mSprite) {
			mSprite->SetPosition(x, y);
		}
		else {
			std::cout << "trying access a null pointer. SetPosition()." << std::endl;
		}
		
	}

	inline void SetDimensions(int w, int h, float scale = SCALE) {
		if (mSprite) {
			mSprite->SetDimensions(w, h, scale);
		}
		else {
			std::cout << "trying access a null pointer. SetPosition()." << std::endl;
		}
	}

	inline SDL_bool IsColliding(const GameEntity& otherEntity) {
		return this->GetTexturedRectangle().IsColliding(otherEntity.GetTexturedRectangle());
	}

private:
	TexturedRectangle* mSprite;
	SDL_Renderer* mRender;
};