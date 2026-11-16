#include "ATAreaSelection.h"

bool FATAreaSelection::Contains(const FVector& P) const
{
	if (bUseMinZ && P.Z < MinZ) return false;
	if (bUseMaxZ && P.Z > MaxZ) return false;
	if (bAllMap) return true;
	const int32 N = Corners.Num();
	if (N < 3) return false;
	// Even-odd ray cast. Crossing (non-simple) polygons give odd results by design.
	bool bInside = false;
	for (int32 i = 0, j = N - 1; i < N; j = i++)
	{
		const FVector& A = Corners[i];
		const FVector& B = Corners[j];
		if ((A.Y > P.Y) != (B.Y > P.Y) &&
			P.X < (B.X - A.X) * (P.Y - A.Y) / (B.Y - A.Y) + A.X)
		{
			bInside = !bInside;
		}
	}
	return bInside;
}
