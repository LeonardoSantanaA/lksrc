#include "Camera.h"
#include "Engine.h"

Camera* Camera::mInstance = nullptr;

Camera::Camera()
:mTarget(nullptr) {
	mViewBox = { 0, 0, Engine::GetInstance()->GetWidth(), Engine::GetInstance()->GetHeight() };
}

void Camera::Clean() {
	if (mInstance) {
		delete mInstance;
		mInstance = nullptr;
	}

	if (mTarget) {
		mTarget = nullptr;
	}
}

Camera* Camera::GetInstance() {
	if (!mInstance) {
		mInstance = new Camera;
	}
	return mInstance;
}

void Camera::Update() {
	if (mTarget) {
		mViewBox.x = mTarget->x - Engine::GetInstance()->GetWidth() / 2;
		mViewBox.y = mTarget->y - Engine::GetInstance()->GetHeight() / 2;

		if (mViewBox.x < 0) {
			mViewBox.x = 0;
		}
		if (mViewBox.y < 0) {
			mViewBox.y = 0;
		}

		if (mViewBox.x > (2 * Engine::GetInstance()->GetWidth() - mViewBox.w)) {
			mViewBox.x = (2 * Engine::GetInstance()->GetWidth() - mViewBox.w);
		}
		if (mViewBox.y > (2 * Engine::GetInstance()->GetHeight() - mViewBox.h)) {
			mViewBox.y = (2 * Engine::GetInstance()->GetHeight() - mViewBox.h);
		}

		mPosition = Vec2D(mViewBox.x, mViewBox.y);
	}
}