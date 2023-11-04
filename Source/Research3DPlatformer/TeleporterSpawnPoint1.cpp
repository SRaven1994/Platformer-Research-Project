// Fill out your copyright notice in the Description page of Project Settings.


#include "TeleporterSpawnPoint1.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ATeleporterSpawnPoint1::ATeleporterSpawnPoint1()
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
void ATeleporterSpawnPoint1::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ATeleporterSpawnPoint1::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ATeleporterSpawnPoint1::OnOverlapEnd);
	
}

// Called every frame
void ATeleporterSpawnPoint1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Collision functions
void ATeleporterSpawnPoint1::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void ATeleporterSpawnPoint1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

