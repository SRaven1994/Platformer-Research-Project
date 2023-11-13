// Fill out your copyright notice in the Description page of Project Settings.


#include "NextLevelTrigger.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ANextLevelTrigger::ANextLevelTrigger()
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
void ANextLevelTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ANextLevelTrigger::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ANextLevelTrigger::OnOverlapEnd);
	
}

// Called every frame
void ANextLevelTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// collision functions
void ANextLevelTrigger::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}


void ANextLevelTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

