// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GP4_Powerup.h"
#include "GP4_Decoy.generated.h"

class AGP4_PlayerCharacter;
class AGP4_CameraActor;

UCLASS()
class GP4_TEAM1_API AGP4_Decoy : public AActor, public IPowerup
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		float Timer = 5.0f;

	UPROPERTY(EditAnywhere)
		bool bActive = false;

	UPROPERTY(EditAnywhere)
	int32 Offset = 500;
	UPROPERTY(VisibleAnywhere)
		AGP4_PlayerCharacter* PlayerChar;

	/*UPROPERTY(VisibleAnywhere)
	AGP4_PlayerCharacter* DecoyCharacter;*/

	UPROPERTY(VisibleAnywhere)
		AActor* DecoyAct;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<AActor> PlayerCharClass;

	UPROPERTY(VisibleAnywhere)
	FVector MirrorPosition;

	UPROPERTY(VisibleAnywhere)
		AGP4_CameraActor* CameraAct = nullptr;

public:	
	// Sets default values for this actor's properties
	AGP4_Decoy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void WaitForPlayerInstance();
	UFUNCTION()
		void MoveAroundTheDecoy();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate_Implementation() override;

	virtual void DeActivate_Implementation() override;

};
