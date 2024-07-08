#include "Button.h"
#include "Engine.h"
#include "Input.h"

Button::Button(const std::string& imagePath, int width, int height, const ImageFormat& imageFormat, float imageScale) 
: mWidth(width), mHeight(height), mPosition(Vec2D::Zero), mnoptrPressableTexture(nullptr){
	mnoptrTexture = new TexturedRectangle(imagePath, imageFormat, imageScale);
	mnoptrTexture->SetDimensions(width, height, imageScale);
}

Button::~Button() {
	if (mnoptrTexture) {
		delete mnoptrTexture;
		mnoptrTexture = nullptr;
	}
	if (mnoptrPressableTexture) {
		delete mnoptrPressableTexture;
		mnoptrPressableTexture = nullptr;
	}
}

void Button::Update() {
	if (CanPressButton() && Input::GetInstance()->GetMouseButtonPress(SDL_BUTTON_LEFT)) {
		mButtonFunction();
	}
}

void Button::SetButtonFunction(std::function<void(void)> function) {
	mButtonFunction = function;
}

void Button::Render() {
	if (mnoptrPressableTexture && CanPressButton()) {
		mnoptrPressableTexture->Render();
	}
	else {
		if (mnoptrTexture) {
			mnoptrTexture->Render();
		}
	}
}

void Button::SetPressableTexture(const std::string& path, const ImageFormat& imageFormat, float imageScale) {
	mnoptrPressableTexture = new TexturedRectangle(path, imageFormat, imageScale);
	Vec2D pressableTexturePos = { static_cast<float>(mnoptrTexture->GetX()), static_cast<float>(mnoptrTexture->GetY()) };
	mnoptrPressableTexture->SetDimensions(mWidth, mHeight, imageScale);
	mnoptrPressableTexture->SetPosition(pressableTexturePos);
}

void Button::SetPosition(float x, float y) {
	Vec2D newPos = { x, y };
	mPosition = newPos;
	if (mnoptrTexture) {
		mnoptrTexture->SetPosition(newPos);
	}
	if (mnoptrPressableTexture) {
		mnoptrPressableTexture->SetPosition(newPos);
	}
}

void Button::SetPosition(const Vec2D& position) {
	mPosition = position;
	if (mnoptrTexture) {
		mnoptrTexture->SetPosition(position);
	}
	if (mnoptrPressableTexture) {
		mnoptrPressableTexture->SetPosition(position);
	}
}

void Button::SetScale(float scale, bool isPressableButton) {
	if (isPressableButton && mnoptrPressableTexture) {
		mnoptrPressableTexture->SetDimensions(mnoptrPressableTexture->GetWidth(), mnoptrPressableTexture->GetHeight(), scale);
	}
	if (isPressableButton && !mnoptrPressableTexture) {
		std::cout << "button::setscale(): pressable texture is nullptr." << std::endl;
	}
	if (!isPressableButton && mnoptrTexture) {
		mnoptrTexture->SetDimensions(mnoptrTexture->GetWidth(), mnoptrTexture->GetHeight(), scale);
	}
	if (!isPressableButton && !mnoptrPressableTexture) {
		std::cout << "button::setscale(): button texture is nullptr." << std::endl;
	}
}

bool Button::CanPressButton() {
	if (Engine::GetInstance()->GetMouseX() >= mnoptrTexture->GetX() && Engine::GetInstance()->GetMouseX() <= mnoptrTexture->GetX() + mnoptrTexture->GetWidth()) {
		if (Engine::GetInstance()->GetMouseY() >= mnoptrTexture->GetY() && Engine::GetInstance()->GetMouseY() <= mnoptrTexture->GetY()  + mnoptrTexture->GetHeight()) {
			return true;
		}
	}
	return false;
}