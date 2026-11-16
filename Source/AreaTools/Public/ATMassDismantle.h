#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ATAreaSelection.h"
#include "ATMassDismantle.generated.h"

UCLASS()
class AREATOOLS_API UATMassDismantle : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Dismantles every buildable whose centre is inside Area. Refunds go to the player.
	// Returns number dismantled.
	UFUNCTION(BlueprintCallable, Category = "AreaTools", meta = (WorldContext = "WorldContext"))
	static int32 DismantleArea(UObject* WorldContext, class AFGCharacterPlayer* Player, const FATAreaSelection& Area);
};
