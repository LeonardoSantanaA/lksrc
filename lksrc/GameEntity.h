#pragma once

#include "TexturedRectangle.h"
#include <vector>
#include "Collider2D.h"
#include "Layer.h"

class GameEntity {
public:
	GameEntity();
	GameEntity(const std::string& name, SDL_Renderer* render);


	~GameEntity();

	void Update();

	void Render();

	void AddTexturedRectangleComponent(std::string filepath, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);
	void AddTexturedRectangleComponent(std::string filepath, int red, int green, int blue, const ImageFormat& format = FORMAT_BMP, float scale = SCALE);

	void AddCollider2D();

	SDL_bool IsColliding(const GameEntity& otherEntity, size_t index, size_t otherIndex);

	void SetPosition(int x, int y, int indexCollision = 0, int xoffsetCollision = 0, int yoffsetCollision = 0);
	void SetDimensions(int w, int h, float scale = SCALE);

	inline TexturedRectangle& GetTexturedRectangle() const{
		if (mnoptrSprite) {
			return *mnoptrSprite;
		}
		std::cout << "trying access a nullptr. gameentity::gettexturedrectangle()." << std::endl;
	}

	inline Collider2D* GetCollider2D(size_t index) {
		if (mnoptrColliders[index]) {
			return mnoptrColliders[index];
		}
		std::cout << "trying access a nullptr. gameentity::getcollider2D(), index: " << index << std::endl;
		return nullptr;
	}

	inline int GetX() { if (mnoptrSprite) { return mnoptrSprite->GetX(); } std::cout << "getx() from nullptr sprite." << std::endl;  return -1; }
	inline int GetY() { if (mnoptrSprite) { return mnoptrSprite->GetY(); } std::cout << "gety() from nullptr sprite." << std::endl;  return -1; }
	inline int GetWidth() { if (mnoptrSprite) { return mnoptrSprite->GetWidth(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }
	inline int GetHeight() { if (mnoptrSprite) { return mnoptrSprite->GetHeight(); } std::cout << "getwidth() from nullptr sprite." << std::endl;  return -1; }
	inline void SetDebugMode(bool debugMode) { mDebugMode = debugMode; }
	inline Layer GetLayer() const { return mLayer; }
	inline void SetLayer(Layer layer) { mLayer = layer; }


private:
	std::string mName;
	Layer mLayer;
	TexturedRectangle* mnoptrSprite;
	std::vector<Collider2D*> mnoptrColliders;
	SDL_Renderer* mRender;

	bool mDebugMode;
};