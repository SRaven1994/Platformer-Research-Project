// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleporter1.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Research3DPlatformerGameMode.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ATeleporter1::ATeleporter1()
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
void ATeleporter1::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ATeleporter1::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ATeleporter1::OnOverlapEnd);
	
}

// Called every frame
void ATeleporter1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Collision functions
void ATeleporter1::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// On collision with player character, subtract a life
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
			GameState->SpawnPoint3Player = true;
		}
	}
}

void ATeleporter1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

