#include "AreaToolsModule.h"
#include "AreaToolsUpdateCheck.h"

void FAreaToolsModule::StartupModule()
{
	// Non-blocking: logs when a newer GitHub release exists.
	FAreaToolsUpdateCheck::Run();
}

IMPLEMENT_MODULE(FAreaToolsModule, AreaTools)
