// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint2.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerGameMode.h"
#include "Research3DPlatformerCharacter.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASpawnPoint2::ASpawnPoint2()
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
void ASpawnPoint2::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint2::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ASpawnPoint2::OnOverlapEnd);
	
}

// Called every frame
void ASpawnPoint2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameState->SpawnPoint2Player == true)
	{
		MovePlayer();
	}

}

// Collision functions
void ASpawnPoint2::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASpawnPoint2::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

// Move player to the spawn point in the world
void ASpawnPoint2::MovePlayer()
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* MyPawn = MyController->GetPawn();
	AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(MyPawn);
	if (Char != nullptr)
	{
		FVector Location = GetActorLocation();
		Char->SetActorLocation(Location, false);
		AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
		GameState->SpawnPoint2Player = false;
	}
}

