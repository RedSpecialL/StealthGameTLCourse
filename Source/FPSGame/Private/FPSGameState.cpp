// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSGameState.h"

#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn* InstigatorPawn, bool bMissionSuccess)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		AFPSPlayerController* PC = Cast<AFPSPlayerController>(It->Get());
		if (PC != nullptr && PC->IsLocalController())
		{
			PC->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			// Disable input.
			APawn* MyPawn = PC->GetPawn();
			if (MyPawn != nullptr)
			{
				MyPawn->DisableInput(nullptr);
			}
		}
	}
}
