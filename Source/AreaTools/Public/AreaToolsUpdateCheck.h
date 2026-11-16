#pragma once
#include "CoreMinimal.h"

// In-game update notice. Does not download or replace files:
// installing is done through the Satisfactory Mod Manager / ficsit.app.
struct FAreaToolsUpdateCheck
{
	static void Run();
};
