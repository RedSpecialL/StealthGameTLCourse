// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"

#include "FPSCharacter.h"
#include "FPSGameMode.h"

#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	OverlapComponent = CreateDefaultSubobject<UBoxComponent>(FName("OverlapComponent"));
	OverlapComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapComponent->SetBoxExtent(FVector(200.0f));
	RootComponent = OverlapComponent;

	OverlapComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap);

	OverlapComponent->SetHiddenInGame(false);

	DecalComponents = CreateDefaultSubobject<UDecalComponent>(FName("DecalComponent"));
	DecalComponents->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComponents->SetupAttachment(RootComponent);
}

void AFPSExtractionZone::HandleOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		return;
	}

	if(MyPawn->bIsCarryingObjective)
	{

		AFPSGameMode* GameMode = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());

		if (GameMode != nullptr)
		{
			GameMode->CompleteMission(MyPawn, true);
		}
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	UE_LOG(LogTemp, Warning, TEXT("Overlapped with extraction zone!"));
}

