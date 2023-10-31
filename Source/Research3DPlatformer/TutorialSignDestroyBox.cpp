// Fill out your copyright notice in the Description page of Project Settings.


#include "TutorialSignDestroyBox.h"
#include "Components/SphereComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ATutorialSignDestroyBox::ATutorialSignDestroyBox()
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
void ATutorialSignDestroyBox::BeginPlay()
{
	Super::BeginPlay();
	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ATutorialSignDestroyBox::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ATutorialSignDestroyBox::OnOverlapEnd);
	
}

// Called every frame
void ATutorialSignDestroyBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Collision functions
void ATutorialSignDestroyBox::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

void ATutorialSignDestroyBox::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

