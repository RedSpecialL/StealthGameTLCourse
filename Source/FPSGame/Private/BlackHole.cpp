// Fill out your copyright notice in the Description page of Project Settings.


#include "BlackHole.h"
#include "Components/SphereComponent.h"
//#include "Kismet/GameplayStatics.h"

// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh")); \
	RootComponent = Mesh;
	//Mesh->AttachTo(RootComponent);
	
	PullingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PullingSphere"));
	PullingSphere->AttachTo(Mesh);

	DestroyingSphere = CreateDefaultSubobject<USphereComponent>(TEXT("DestroyingSphere"));
	DestroyingSphere->AttachTo(Mesh);
	//DestroyingSphere->

}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappedActors;
	PullingSphere->GetOverlappingActors(OverlappedActors);


	for (auto Actor : OverlappedActors)
	{
		if (Actor != nullptr)
		{
			


			UStaticMeshComponent* Temp = Cast<UStaticMeshComponent>(Actor->GetRootComponent());
			if (Temp != nullptr)
			{
				Temp->AddRadialForce(GetActorLocation(), PullingSphere->GetScaledSphereRadius(), -(ForceApplied * Temp->GetMass()), ERadialImpulseFalloff::RIF_Linear);
				//Temp->AddForce
			}

			//AddForce
			//Actor->AddForce();
		}
	}

	
	DestroyingSphere->GetOverlappingActors(OverlappedActors);
	for (auto Actor : OverlappedActors)
	{
		if (Actor == this)
		{
			continue;
		}

		if (Actor != nullptr)
		{
			Actor->Destroy();
		}
	}
}

