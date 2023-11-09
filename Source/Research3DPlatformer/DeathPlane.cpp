// Fill out your copyright notice in the Description page of Project Settings.


#include "DeathPlane.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Research3DPlatformerGameMode.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ADeathPlane::ADeathPlane()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ADeathPlane::BeginPlay()
{
	Super::BeginPlay();
	
	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADeathPlane::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADeathPlane::OnOverlapEnd);
}

// Called every frame
void ADeathPlane::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Collision functions
void ADeathPlane::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// On collision with player character, subtract a life
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char->Checkpoint == 0)
		{
			AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
			GameState->SpawnPoint1Player = true;
			Char->LoseLife();
		}
		else if (Char->Checkpoint == 1)
		{
			Char->LoseLife();
		}
	}
}

void ADeathPlane::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

