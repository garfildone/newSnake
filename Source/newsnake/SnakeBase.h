// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeBase.generated.h"

class ASnakeElementBase;

UENUM()
enum class EMovementDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

UCLASS()
class NEWSNAKE_API ASnakeBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASnakeBase();

	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<ASnakeElementBase> SnakeElementClass;

	UPROPERTY(EditDefaultsOnly)
		float ElementSize;

	UPROPERTY(EditDefaultsOnly)
		float MovementSpeed;

	UPROPERTY();
	TArray<ASnakeElementBase*> SnakeElements;

	UPROPERTY()
		EMovementDirection LastMoveDirection;

	//For any Bounus speed
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "How long is any bonus valid")
		float StepDelay;
	UPROPERTY()
		float BufferTime;

	//For method SetLastElementSnale in SnakeElementBase
	UPROPERTY(EditAnyWhere, BlueprintReadWrite, Category = "LastElement")
		UStaticMesh* ChangesMesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void AddSnakeElement(int ElementsNum = 1);

	UFUNCTION(BlueprintCallable)
		void Move();

	UFUNCTION()
		void SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other);

	UPROPERTY(EditAnywhere) int32 VisibleBodyChanck = 3;
};
