#pragma once
#include "CoreMinimal.h"
#include "ATAreaSelection.generated.h"

// Polygon (XY) + min/max Z. A building is inside when its centre is.
USTRUCT(BlueprintType)
struct AREATOOLS_API FATAreaSelection
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite) TArray<FVector> Corners;
	UPROPERTY(BlueprintReadWrite) bool bUseMinZ = false;
	UPROPERTY(BlueprintReadWrite) bool bUseMaxZ = false;
	UPROPERTY(BlueprintReadWrite) float MinZ = 0.f;
	UPROPERTY(BlueprintReadWrite) float MaxZ = 0.f;
	UPROPERTY(BlueprintReadWrite) bool bAllMap = false;

	bool Contains(const FVector& P) const;
	void Clear() { *this = FATAreaSelection(); }
};
