#include "Graphics/PlayerGUI.h"
#include "Managers/EntityManager.h"
#include "Entities/Player.h"

PlayerGUI::PlayerGUI()
{
	//life
	mnoptrLifeMold = std::make_unique<TexturedRectangle>("assets/images/player/lifeStatusMold.png", FORMAT_PNG);
	mnoptrLifeMold->SetDimensions(100, 12, 3.0f);
	mnoptrLifeMold->SetPosition(Vec2D(10.0f, 10.0f));

	mnoptrLifeBar = std::make_unique<TexturedRectangle>("assets/images/player/lifeStatusBar.png", FORMAT_PNG);
	mnoptrLifeBar->SetPosition(Vec2D(10.0f, 10.0f));

	//stamina
	mnoptrStaminaMold = std::make_unique<TexturedRectangle>("assets/images/player/staminaStatusMold.png", FORMAT_PNG);
	mnoptrStaminaMold->SetDimensions(80, 10, 3.0f);
	mnoptrStaminaMold->SetPosition(Vec2D(10.0f, 50.0f));

	mnoptrStaminaBar = std::make_unique<TexturedRectangle>("assets/images/player/staminaStatusBar.png", FORMAT_PNG);
	mnoptrStaminaBar->SetPosition(Vec2D(10.0f, 50.0f));
}

void PlayerGUI::Render() {
	std::shared_ptr<Player> player = EntityManager::GetInstance()->GetEntityRef<Player>("PLAYER");

	mnoptrLifeBar->SetDimensions(player->GetLife(), 12.0f, 3.0f);
	mnoptrLifeBar->Render(true);
	mnoptrLifeMold->Render(true);

	mnoptrStaminaBar->SetDimensions(player->GetStamina(), 10.0f, 3.0f);
	mnoptrStaminaBar->Render(true);
	mnoptrStaminaMold->Render(true);
}