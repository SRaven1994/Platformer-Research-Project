// Fill out your copyright notice in the Description page of Project Settings.


#include "StartTimerTrigger.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
AStartTimerTrigger::AStartTimerTrigger()
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
void AStartTimerTrigger::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AStartTimerTrigger::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AStartTimerTrigger::OnOverlapEnd);
	
}

// Called every frame
void AStartTimerTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AStartTimerTrigger::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When character collides the trigger, start the timer
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Char->StartTimer = true;
		}
	}
}

// collision functions
void AStartTimerTrigger::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

