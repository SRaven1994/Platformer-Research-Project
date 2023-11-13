// Fill out your copyright notice in the Description page of Project Settings.


#include "LadderV2.h"
#include "Components/BoxComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
ALadderV2::ALadderV2()
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
void ALadderV2::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ALadderV2::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ALadderV2::OnOverlapEnd);
	
}

// Called every frame
void ALadderV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// collision functions
void ALadderV2::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When character collides with ladder, begin accend
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Char->OnLadder = true;
		}
	}
}

void ALadderV2::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// When character stop collides with ladder, stop accend
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Char->OnLadder = false;
		}
	}
}

