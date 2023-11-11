// Fill out your copyright notice in the Description page of Project Settings.


#include "EnergyItem.h"
#include "Components/SphereComponent.h"
#include "Research3DPlatformerCharacter.h"

// Sets default values
AEnergyItem::AEnergyItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set collision 
	CollisionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionVolume"));

	RootComponent = CollisionVolume;

	// Set mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(GetRootComponent());

	// Set rotation
	bRotate = true;

	RotationRate = 90;

}

// Called when the game starts or when spawned
void AEnergyItem::BeginPlay()
{
	Super::BeginPlay();

	// Add collision
	CollisionVolume->OnComponentBeginOverlap.AddDynamic(this, &AEnergyItem::OnOverlapBegin);
	CollisionVolume->OnComponentEndOverlap.AddDynamic(this, &AEnergyItem::OnOverlapEnd);
	
}

// Called every frame
void AEnergyItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Rotate object
	if (bRotate)
	{
		FRotator Rotation = GetActorRotation();
		Rotation.Yaw += RotationRate * DeltaTime;
		SetActorRotation(Rotation);
	}

}

// Collision functions
void AEnergyItem::OnOverlapBegin(UPrimitiveComponent* newComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// When character collides with energy, set dash energy to near max
	if (Cast<AResearch3DPlatformerCharacter>(OtherActor))
	{
		AResearch3DPlatformerCharacter* Char = Cast<AResearch3DPlatformerCharacter>(OtherActor);
		if (Char)
		{
			Char->GainEnergy();
			Destroy();
		}
	}
}

void AEnergyItem::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

