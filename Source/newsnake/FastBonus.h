// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "FastBonus.generated.h"

class UStaticMeshComponent;

UCLASS()
class NEWSNAKE_API AFastBonus : public ABonusBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFastBonus();

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
		float IncreaseSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interactar, bool bIsHead) override;

};
