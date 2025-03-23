// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include "Actordethzone.generated.h"

class UStaticMeshComponent;

UCLASS()
class NEWSNAKE_API AActordethzone : public AActor, public IInteractable
{
	GENERATED_BODY()
	

public:	
	// Sets default values for this actor's properties
	AActordethzone();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		UStaticMeshComponent* MeshComponent;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactar, bool bIsHead) override;
};
