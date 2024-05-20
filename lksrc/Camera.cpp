#include "Camera.h"
#include "Engine.h"

Camera* Camera::mInstance = nullptr;

Camera::Camera()
:mTarget(nullptr), mZoom(1), mCameraWidth(Engine::GetInstance()->GetWidth()),mCameraHeight(Engine::GetInstance()->GetHeight())  {
	mViewBox = { 0, 0, mCameraWidth, mCameraHeight };
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
		mViewBox.x = mTarget->x - mCameraWidth / 2.0f;
		mViewBox.y = mTarget->y - mCameraHeight / 2.0f;

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

		mPosition = Vec2D(mViewBox.x, mViewBox.y);
	}
}

void Camera::Reload() {
	mCameraWidth = static_cast<int>(Engine::GetInstance()->GetWidth() / mZoom);
	mCameraHeight = static_cast<int>(Engine::GetInstance()->GetHeight() / mZoom);
	mViewBox.w = mCameraWidth;
	mViewBox.h = mCameraHeight;
}