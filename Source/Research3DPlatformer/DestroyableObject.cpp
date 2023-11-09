// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyableObject.h"
#include "Components/SphereComponent.h"
#include "Research3DPlatformerCharacter.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ADestroyableObject::ADestroyableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	Active = false;



}

// Called when the game starts or when spawned
void ADestroyableObject::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &ADestroyableObject::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &ADestroyableObject::OnOverlapEnd);
	
}

// Called every frame
void ADestroyableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active == true)
	{
		DestroyObject();
	}
}

// Collision functions
void ADestroyableObject::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When character collides with object, can destroy
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Active = true;
		}
	}
}

void ADestroyableObject::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// When character collides no longer with object, cannot destroy
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Active = false;
		}
	}
}

void ADestroyableObject::DestroyObject()
{
	APlayerController* MyController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	APawn* MyPawn = MyController->GetPawn();
	AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(MyPawn);
	if (Char != nullptr && Char->IsAttacking == true)
	{
		Destroy();
	}
}

