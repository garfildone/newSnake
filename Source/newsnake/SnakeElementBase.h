// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interactable.h"
#include <newsnake/SnakeBase.h>
#include <newsnake/PlayerPawnBase.h>
#include "SnakeElementBase.generated.h"

class UStaticMeshComponent;

UCLASS()
class NEWSNAKE_API ASnakeElementBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeElementBase();

	UPROPERTY(VisibleAnyWhere, BlueprintReadOnly)
		UStaticMeshComponent* MeshComponent;

	UPROPERTY()
		ASnakeBase* SnakeOwner;

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeBase> SnakeActorClass;

	//A range for Creating Food/Bonus by Y
	UPROPERTY(EditAnyWhere)
		float MinY = -1350.f; float MaxY = 1340.f;
	//A range for Creating Food/Bonus by X
	UPROPERTY(EditAnyWhere)
		float MinX = -1330.f; float MaxX = 1320.f;
	// Creating Foot by Z
	UPROPERTY()
		float SpawnZ = 2.f;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintNativeEvent)
		void SetFirstElementType();
	    void SetFirstElementType_Implementation();

		virtual void Interact(AActor* Interactor, bool bIsHead);

		UFUNCTION()
			void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
				AActor* OtherActor,
				UPrimitiveComponent* OtherComp,
				int32 OtherBodyIndex,
				bool bFromSweep,
				const FHitResult& SweepResult);

		UFUNCTION()
			void ToggleCollision();
};
