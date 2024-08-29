#include "Managers/TextureManager.h"
#include "Managers/ResourceManager.h"
#include "Core/Engine.h"
#include "Camera/Camera.h"

TextureManager* TextureManager::mInstance = nullptr;

TextureManager* TextureManager::GetInstance() {
	if (!mInstance) {
		mInstance = new TextureManager;
	}
	return mInstance;
}

auto TextureDeleter = [](SDL_Texture* texture) {
	if (texture) {
		SDL_DestroyTexture(texture);
	}
	};


bool TextureManager::Load(const std::string& id, const std::string& path) {
	std::shared_ptr<SDL_Surface> surface = ResourceManager::GetInstance()->GetSurface(path, FORMAT_PNG);
	if (!surface) {
		SDL_Log("failed to get surface in texturemanager: %s", SDL_GetError());
		return false;
	}

	std::shared_ptr<SDL_Texture> texture(
		SDL_CreateTextureFromSurface(Engine::GetInstance()->GetRender(), surface.get()),
		TextureDeleter
	);
	mTextureMap[id] = texture;

	return true;
}


void TextureManager::Drop(const std::string& id) {
	auto it = mTextureMap.find(id);
	if (it != mTextureMap.end()) {
		mTextureMap.erase(it);
	}
	else {
		SDL_Log("texture with ID '%s' not found", id.c_str());
	}
}

void TextureManager::Clean() {
    mTextureMap.clear();

    if (mInstance) {
        delete mInstance;
        mInstance = nullptr;
    }
}


void TextureManager::Render(const std::string& id, int x, int y, int w, int h, float scaleX, float scaleY, float scrollRatio, bool loop, const SDL_RendererFlip& flip) {
	SDL_Rect srcRect = { 0, 0, w, h };
	Camera* camera = Camera::GetInstance();
	Vec2D cam = camera->GetPosition() * scrollRatio;
	SDL_Renderer* renderer = Engine::GetInstance()->GetRender();

	int scaledW = static_cast<int>((w * scaleX) * camera->GetZoom());
	int scaledH = static_cast<int>((h * scaleY) * camera->GetZoom());

	int startX = static_cast<int>((x - cam.x) * camera->GetZoom());
	int startY = static_cast<int>((y - cam.y) * camera->GetZoom());

	if (loop) {
		int firstX = startX % scaledW;
		int secondX = firstX + scaledW;

		SDL_Rect dstRect1 = { firstX, startY, scaledW, scaledH };
		SDL_Rect dstRect2 = { secondX, startY, scaledW, scaledH };

		SDL_RenderCopyEx(renderer, mTextureMap[id].get(), &srcRect, &dstRect1, 0, nullptr, flip);
		SDL_RenderCopyEx(renderer, mTextureMap[id].get(), &srcRect, &dstRect2, 0, nullptr, flip);


		if (firstX + scaledW <= 0) {
			firstX = secondX + scaledW;
		}
		if (secondX + scaledW <= 0) {
			secondX = firstX + scaledW;
		}

	}
	else {
		//render without loop
		SDL_Rect dstRect = { startX, startY, scaledW, scaledH };
		SDL_RenderCopyEx(renderer, mTextureMap[id].get(), &srcRect, &dstRect, 0, nullptr, flip);
	}
}

void TextureManager::RenderFrame(const std::string& id, int x, int y, int w, int h, int row, int frame, const SDL_RendererFlip& flip) {
	SDL_Rect srcRect = { w * frame, h * row, w, h };
	Camera* camera = Camera::GetInstance();
	Vec2D cam = camera->GetPosition();
	SDL_Rect dstRect = { static_cast<int>((x - cam.x) * camera->GetZoom()), static_cast<int>((y - cam.y) * camera->GetZoom()), static_cast<int>(w * camera->GetZoom()), static_cast<int>(h * camera->GetZoom()) };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), mTextureMap[id].get(), &srcRect, &dstRect, 0, nullptr, flip);
}

void TextureManager::RenderTile(const std::string& tilesetID, int tileSize, int x, int y, int row, int frame, const SDL_RendererFlip& flip) {
	SDL_Rect srcRect = { tileSize * frame, tileSize * (row), tileSize, tileSize };
	Camera* camera = Camera::GetInstance();
	Vec2D cam = camera->GetPosition();
	SDL_Rect dstRect = { static_cast<int>((x - cam.x) * camera->GetZoom()), static_cast<int>((y - cam.y) * camera->GetZoom()), static_cast<int>(tileSize * camera->GetZoom()), static_cast<int>(tileSize * camera->GetZoom()) };
	SDL_RenderCopyEx(Engine::GetInstance()->GetRender(), mTextureMap[tilesetID].get(), &srcRect, &dstRect, 0, 0, flip);
}