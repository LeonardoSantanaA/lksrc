#include "Camera/Camera.h"
#include "Core/Engine.h"
#include "Managers/Utils.h"
#include <cstdlib> 
#include <random>

Camera* Camera::mInstance = nullptr;

Camera::Camera()
:mTarget(nullptr), mZoom(1), mCameraWidth(Engine::GetInstance()->GetWidth()),mCameraHeight(Engine::GetInstance()->GetHeight()), mSceneHeight(Engine::GetInstance()->GetHeight()), mSceneWidth(Engine::GetInstance()->GetWidth()), mScreenShakeDuration(0.0f), mScreenShakeMagnetude(0.0f){
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

		if (mScreenShakeDuration > 0.0f) {
			mScreenShakeDuration--;

			std::random_device rseed;
			int minRange = -mScreenShakeMagnetude, maxRange = mScreenShakeMagnetude;

			std::mt19937 rng(rseed());
			std::uniform_real_distribution<float> randomX(minRange, maxRange);
			std::uniform_real_distribution<float> randomY(minRange, maxRange);

			float shakeX = randomX(rng);
			float shakeY = randomY(rng);

			mViewBox.x += shakeX;
			mViewBox.y += shakeY;
		}



		mPosition = Vec2D(static_cast<int>(mViewBox.x), static_cast<int>(mViewBox.y));
	}
}

bool Camera::IsInCamera(GameEntity& entity, int xOffset, int yOffset) {
	SDL_Rect cameraCollider = { mViewBox.x - xOffset, mViewBox.y - yOffset, mViewBox.w + (xOffset * 2), mViewBox.h + (yOffset * 2) };

	return SDL_HasIntersection(entity.GetCollider2D(0)->GetColliderBoundingBox(), &cameraCollider);
}

bool Camera::IsInCamera(const SDL_Rect& rect, int xOffset, int yOffset) {
	SDL_Rect cameraCollider = { mViewBox.x - xOffset, mViewBox.y - yOffset, mViewBox.w + xOffset, mViewBox.h + yOffset };

	return SDL_HasIntersection(&rect, &cameraCollider);
}

void Camera::Screenshake(float magnetude, float duration) {
	mScreenShakeDuration = duration;
	mScreenShakeMagnetude = magnetude;
}

void Camera::Reload() {
	mCameraWidth = static_cast<int>(Engine::GetInstance()->GetWidth() / static_cast<int>(mZoom));
	mCameraHeight = static_cast<int>(Engine::GetInstance()->GetHeight() / static_cast<int>(mZoom));
	mViewBox.w = mCameraWidth;
	mViewBox.h = mCameraHeight;
}