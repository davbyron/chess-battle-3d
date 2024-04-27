// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"
#include "Components/SceneComponent.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::DistributeCards(TArray<USceneComponent*> Hand, USceneComponent* NewCard)
{
	float OffsetYPerCard = 20.0;
	float RotateXPerCard = 5.0;

	int32 CardCount = Hand.Num();

	bool bCardCountInHandIsEven = CardCount % 2 == 0;

	for (int32 Index = 0; Index != CardCount; ++Index)
	{
		// If there's more than one card in-hand
		if (CardCount > 1)
		{
			FVector CardOffset(0.0f, 0.0f, 0.0f);
			FRotator CardRotation(0.0f, 0.0f, 0.0f);

			// If it's the newest card
			if (Index == CardCount - 1)
			{
				CardOffset.X = CardCount;

				int32 CardOffsetIfCountIsEven = CardCount - (CardCount / 2);
				int32 CardOffsetIfCountIsOdd = CardCount - ((CardCount + 1) / 2);

				if (bCardCountInHandIsEven)
				{
					CardOffset.Y = CardOffsetIfCountIsEven * OffsetYPerCard;
					CardRotation.Roll = CardOffsetIfCountIsEven * RotateXPerCard;

					Hand[Index]->AddLocalOffset(CardOffset);
					Hand[Index]->AddLocalRotation(CardRotation);
				}
				else
				{
					CardOffset.Y = CardOffsetIfCountIsOdd * OffsetYPerCard;
					CardRotation.Roll = CardOffsetIfCountIsOdd * RotateXPerCard;

					Hand[Index]->AddLocalOffset(CardOffset);
					Hand[Index]->AddLocalRotation(CardRotation);
				}
			}
			// If the card was already in-hand
			else
			{
				if ((bCardCountInHandIsEven && (Index + 1.0) <= (CardCount / 2.0)) || (!bCardCountInHandIsEven && (Index + 1.0) > (CardCount / 2.0)))
				{
					CardOffset.Y = OffsetYPerCard * -1;
					CardRotation.Roll = RotateXPerCard * -1;

					Hand[Index]->AddLocalOffset(CardOffset);
					Hand[Index]->AddLocalRotation(CardRotation);
				}
			}
		}
	}
}
