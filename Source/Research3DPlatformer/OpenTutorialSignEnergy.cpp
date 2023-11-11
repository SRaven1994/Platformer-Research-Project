// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenTutorialSignEnergy.h"
#include "Components/SphereComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
AOpenTutorialSignEnergy::AOpenTutorialSignEnergy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));
	RootComponent = CollisionVolume;

	// Set mesh
	Sign = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SignMesh"));
	Sign->SetupAttachment(RootComponent);

	Post = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PostMesh"));
	Post->SetupAttachment(Sign);
}

// Called when the game starts or when spawned
void AOpenTutorialSignEnergy::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AOpenTutorialSignEnergy::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AOpenTutorialSignEnergy::OnOverlapEnd);
	
}

// Called every frame
void AOpenTutorialSignEnergy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);



}

// Collision Functions
void AOpenTutorialSignEnergy::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void AOpenTutorialSignEnergy::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

