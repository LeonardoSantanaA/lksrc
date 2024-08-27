#include <memory>
#include "Graphics/TexturedRectangle.h"

class PlayerGUI {
public:
	PlayerGUI();
	void Render();

private:
	std::unique_ptr<TexturedRectangle> mnoptrLifeMold;
	std::unique_ptr<TexturedRectangle> mnoptrLifeBar;
	std::unique_ptr<TexturedRectangle> mnoptrStaminaMold;
	std::unique_ptr<TexturedRectangle> mnoptrStaminaBar;
};