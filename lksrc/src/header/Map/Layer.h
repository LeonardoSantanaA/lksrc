#pragma once

class Layer {
public:
	virtual ~Layer() = default;
	virtual void Update() = 0;
	virtual void Render() = 0;
};