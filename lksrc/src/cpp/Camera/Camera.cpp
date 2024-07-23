#include "Camera/Camera.h"
#include "Core/Engine.h"

Camera* Camera::mInstance = nullptr;

Camera::Camera()
:mTarget(nullptr), mZoom(1), mCameraWidth(Engine::GetInstance()->GetWidth()),mCameraHeight(Engine::GetInstance()->GetHeight()), mSceneHeight(Engine::GetInstance()->GetHeight()), mSceneWidth(Engine::GetInstance()->GetWidth())  {
	mViewBox = { 0, 0, mCameraWidth, mCameraHeight };
}

void Camera::Reset() {
	mTarget = nullptr;
	SetZoom(1);
	mPosition = Vec2D(0, 0);
	mViewBox.w = Engine::GetInstance()->GetWidth();
	mViewBox.h = Engine::GetInstance()->GetHeight();
	
	mCameraWidth = Engine::GetInstance()->GetWidth();
	mCameraHeight = Engine::GetInstance()->GetHeight();
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


void Camera::SetZoom(float zoom) {
	mZoom = zoom;
	mCameraWidth = static_cast<int>(Engine::GetInstance()->GetWidth() / mZoom);
	mCameraHeight = static_cast<int>(Engine::GetInstance()->GetHeight() / mZoom);
	mViewBox.w = mCameraWidth;
	mViewBox.h = mCameraHeight;
}

void Camera::Update() {
	if (mTarget) {
		mViewBox.x = static_cast<int>(mTarget->x) - mCameraWidth / 2;
		mViewBox.y = static_cast<int>(mTarget->y) - mCameraHeight / 2;

		if (mViewBox.x < 0) {
			mViewBox.x = 0;
		}
		if (mViewBox.y < 0) {
			mViewBox.y = 0;
		}

		if (mViewBox.x > mSceneWidth - mCameraWidth) {
			mViewBox.x = mSceneWidth - mCameraWidth;
		}
		if (mViewBox.y > mSceneHeight - mCameraHeight) {
			mViewBox.y = mSceneHeight - mCameraHeight;
		}

		mPosition = Vec2D(static_cast<int>(mViewBox.x), static_cast<int>(mViewBox.y));
	}
}

void Camera::Reload() {
	mCameraWidth = static_cast<int>(Engine::GetInstance()->GetWidth() / static_cast<int>(mZoom));
	mCameraHeight = static_cast<int>(Engine::GetInstance()->GetHeight() / static_cast<int>(mZoom));
	mViewBox.w = mCameraWidth;
	mViewBox.h = mCameraHeight;
}