#include "ATMassDismantle.h"
#include "Buildables/FGBuildable.h"
#include "FGCharacterPlayer.h"
#include "FGInventoryComponent.h"
#include "FGPlayerState.h"
#include "FGDismantleInterface.h"
#include "EngineUtils.h"

int32 UATMassDismantle::DismantleArea(UObject* WorldContext, AFGCharacterPlayer* Player, const FATAreaSelection& Area)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
	if (!World || !Player || !Player->HasAuthority()) return 0;

	TArray<AFGBuildable*> Targets;
	for (TActorIterator<AFGBuildable> It(World); It; ++It)
	{
		AFGBuildable* B = *It;
		if (B && Area.Contains(B->GetActorLocation())) Targets.Add(B);
	}

	int32 Count = 0;
	for (AFGBuildable* B : Targets)
	{
		if (!IsValid(B)) continue;
		TArray<FInventoryStack> Refund;
		B->GetDismantleRefund_Implementation(Refund, false);
		if (UFGInventoryComponent* Inv = Player->GetInventory())
		{
			for (const FInventoryStack& S : Refund) Inv->AddStack(S, true);
		}
		B->Dismantle_Implementation();
		++Count;
	}
	return Count;
}
