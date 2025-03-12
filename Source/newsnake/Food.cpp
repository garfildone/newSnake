// Fill out your copyright notice in the Description page of Project Settings.


#include "Food.h"
#include "Engine/Classes/Components/StaticMeshComponent.h"
#include "SnakeBase.h"

// Sets default values
AFood::AFood()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFood::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	BufferTime += DeltaTime;
}

void AFood::Interact(AActor* Interactar, bool bIsHead)
{
	if (bIsHead)
	{
		auto Snake = Cast<ASnakeBase>(Interactar);
		if (IsValid(Snake))
		{
			Snake->AddSnakeElement();
			this->Destroy();
		}
	}
}

void AFood::CollectEeat()
{
	TArray<AActor*> CollectedActors;
	GetOverlappingActors(CollectedActors);

	for (int32 i = 0; i < CollectedActors.Num(); ++i)
	{
		ASnakeBase* const Test = Cast<ASnakeBase>(CollectedActors[i]);

		if (Test)
		{
			Test->VisibleBodyChanck++;
			Destroy(true, true);
			break;
		}
	}
}


