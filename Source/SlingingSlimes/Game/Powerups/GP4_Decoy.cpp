// Fill out your copyright notice in the Description page of Project Settings.


#include "GP4_Decoy.h"
#include "GP4_Powerup.h"
#include "GP4_Team1/Player/GP4_PlayerCharacter.h"
#include "GP4_Team1/Camera/GP4_CameraActor.h"

// Sets default values
AGP4_Decoy::AGP4_Decoy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGP4_Decoy::BeginPlay()
{
	Super::BeginPlay();
	FTimerHandle UnusedHandle;
	GetWorldTimerManager().SetTimer(UnusedHandle, this,
		&AGP4_Decoy::WaitForPlayerInstance, 0.2f, false);

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGP4_CameraActor::StaticClass(), FoundActors);
	if (FoundActors.Num() > 0)
	{
		CameraAct = Cast<AGP4_CameraActor>(FoundActors[0]);
	}
}

void AGP4_Decoy::WaitForPlayerInstance()
{
	if (Player && !bActive)
	{
		bActive = true;
		/*DecoyCharacter = GetWorld()->SpawnActor<AGP4_PlayerCharacter>(
			PlayerCharClass, GetActorLocation() * (Player->GetActorForwardVector() * Offset), GetActorRotation());
		*/
		DecoyAct = GetWorld()->SpawnActor<AActor>(
			PlayerCharClass, GetActorLocation() * (Player->GetActorForwardVector() * Offset), GetActorRotation());
		PlayerChar = Cast<AGP4_PlayerCharacter>(Player);
		//DecoyCharacter->AssignedTeam = PlayerChar->AssignedTeam;
		//DecoyCharacter->SetActorEnableCollision(false);
		FTimerHandle UnusedHandle;
		GetWorldTimerManager().SetTimer(UnusedHandle, this,
			&AGP4_Decoy::DeActivate_Implementation, Timer, false);
		if (CameraAct)
		{
			CameraAct->SetActors();
		}
	}
}

void AGP4_Decoy::MoveAroundTheDecoy()
{
	//MirrorPosition = (DecoyCharacter->GetActorLocation() + Player->GetActorLocation()) / 2;
	MirrorPosition = (DecoyAct->GetActorLocation() + Player->GetActorLocation()) / 2;
	
	FVector NewLoc = FVector(Player->GetActorLocation().X - MirrorPosition.X,
		Player->GetActorLocation().Y - MirrorPosition.Y,
		Player->GetActorLocation().Z); // -100 if using decoy AActor
		//(DecoyCharacter->GetActorForwardVector() * Offset);
	FRotator NewRot = FRotator(Player->GetActorRotation() * -1);
	//DecoyCharacter->SetActorLocationAndRotation(NewLoc, NewRot);
	DecoyAct->SetActorLocationAndRotation(NewLoc, NewRot);
}

// Called every frame
void AGP4_Decoy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bActive)
	{
		MoveAroundTheDecoy();
	}
}

void AGP4_Decoy::Activate_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Act imp decoy powerup"));
	
}

void AGP4_Decoy::DeActivate_Implementation()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("deact imp decoy powerup"));

	//DecoyCharacter->Destroy();
	DecoyAct->Destroy();
	Destroy();
}

