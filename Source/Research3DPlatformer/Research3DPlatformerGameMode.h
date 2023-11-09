// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Research3DPlatformerGameMode.generated.h"

UCLASS(minimalapi)
class AResearch3DPlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AResearch3DPlatformerGameMode();


	// Spawn Player to states
	bool SpawnPoint1Player { false };

	bool SpawnPoint2Player { false };

	bool SpawnPoint3Player { false };

};



