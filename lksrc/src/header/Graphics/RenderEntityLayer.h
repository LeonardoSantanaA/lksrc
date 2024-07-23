#pragma once

//layers to control which entity will render first.
enum class RenderEntityLayer {
	BACKGROUND = 0,
	MIDDLEGROUND,
	FOREGROUND,
	END
};