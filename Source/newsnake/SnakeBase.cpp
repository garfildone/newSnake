// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeBase.h"
#include "SnakeElementBase.h"
#include "Interactable.h"

// Sets default values
ASnakeBase::ASnakeBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ElementSize = 100.f;
	MovementSpeed = 0.5;
	LastMoveDirection = EMovementDirection::DOWN;

	StepDelay = 2.f;
	BufferTime = 0;
}

// Called when the game starts or when spawned
void ASnakeBase::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(MovementSpeed);
	AddSnakeElement(5);
}

// Called every frame
void ASnakeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

	BufferTime += DeltaTime;
	if (BufferTime >= StepDelay)
	{
		SetActorTickInterval(MovementSpeed);
		BufferTime = 0;
	}
}

void ASnakeBase::AddSnakeElement(int ElementsNum)
{
	for (int i = 0; i < ElementsNum; ++i)
	{
		FVector NewLocation = FVector(SnakeElements.Num() * ElementSize, 0, 0);
		FTransform NewTransform(NewLocation);
		ASnakeElementBase* NewSnakeElem = GetWorld()->SpawnActor<ASnakeElementBase>(SnakeElementClass, NewTransform);
		NewSnakeElem->SnakeOwner = this;
		SnakeElements.Add(NewSnakeElem);

		int32 ElemIndex = SnakeElements.Find(NewSnakeElem);
		if (ElemIndex == 0)
		{
			NewSnakeElem->SetFirstElementType();

		}
		NewSnakeElem->SetLastElementSnake(SnakeElements, ChangesMesh);

	}
}

void ASnakeBase::Move()
{
	FVector MovementVector(ForceInitToZero);
	FRotator NewRotator;

	float M_Speed = ElementSize;

	switch (LastMoveDirection)
	{
	case EMovementDirection::UP:
		MovementVector.X += MovementSpeed;
		MovementVector.Rotation() = FRotator(0.f, -90.f, 0.f);
		break;
	case EMovementDirection::DOWN:
		MovementVector.X -= MovementSpeed;
		MovementVector.Rotation() = FRotator(0.f, 90.f, 0.f);
		break;
	case EMovementDirection::LEFT:
		MovementVector.Y += MovementSpeed;
		MovementVector.Rotation() = FRotator(90.f, -90.f, 0.f);
		break;
	case EMovementDirection::RIGHT:
		MovementVector.Y -= MovementSpeed;
		MovementVector.Rotation() = FRotator(-90.f, -90.f, 0.f);
		break;
	}

	//AddActorLocalOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();

	for (int i = SnakeElements.Num() - 1; i > 0; i--)
	{
		auto CurrentElement = SnakeElements[i];
		auto PrevElement = SnakeElements[i - 1];

		FVector PrevLocation = PrevElement->GetActorLocation();
		CurrentElement->SetActorLocation(PrevLocation);
	}

	SnakeElements[0]->AddActorWorldOffset(MovementVector);
	SnakeElements[0]->ToggleCollision();
}

void ASnakeBase::SnakeElementOverlap(ASnakeElementBase* OverlappedElement, AActor* Other)
{
	if (IsValid(OverlappedElement))
	{
		int32 ElemIndex;
		SnakeElements.Find(OverlappedElement, ElemIndex);
		bool bIsFirst = ElemIndex == 0;
		IInteractable* InteractebleInterface = Cast<IInteractable>(Other);
		if (InteractebleInterface)
		{
			InteractebleInterface->Interact(this, bIsFirst);
		}
	}
}

