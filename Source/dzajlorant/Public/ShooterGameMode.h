// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DZAJLORANT_API AShooterGameMode : public AGameModeBase
{
	GENERATED_BODY()

	public:
		virtual void PawnKilled(APawn* PawnKilled);
};
