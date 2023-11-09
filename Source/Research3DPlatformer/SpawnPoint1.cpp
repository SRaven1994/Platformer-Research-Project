// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint1.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerGameMode.h"
#include "Research3DPlatformerCharacter.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ASpawnPoint1::ASpawnPoint1()
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
void ASpawnPoint1::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ASpawnPoint1::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ASpawnPoint1::OnOverlapEnd);
	
}

// Called every frame
void ASpawnPoint1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (GameState->SpawnPoint1Player == true)
	{
		MovePlayer();
	}

}

// Collision functions
void ASpawnPoint1::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ASpawnPoint1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void ASpawnPoint1::MovePlayer()
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* MyPawn = MyController->GetPawn();
	AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(MyPawn);
	if (Char != nullptr)
	{
		FVector Location = GetActorLocation();
		Char->SetActorLocation(Location, false);
		AResearch3DPlatformerGameMode* GameState = Cast<AResearch3DPlatformerGameMode>(GetWorld()->GetAuthGameMode());
		GameState->SpawnPoint1Player = false;
	}
}

