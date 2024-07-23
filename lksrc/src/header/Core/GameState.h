#pragma once

#include <SDL.h>
#include <string>

class GameState {
public:
	virtual bool Init() = 0;
	virtual bool Exit() = 0;
	virtual ~GameState() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;

	inline bool IsPop() const { return isPop; }
	inline std::string GetID() const { return id; }
	
protected:
	SDL_Renderer* mRender;
	std::string id;
	bool isPop = false;
	friend class Engine;
};