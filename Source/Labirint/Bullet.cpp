// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet.h"
#include "Engine.h"
#include "Classes/GameFramework/ProjectileMovementComponent.h"
#include "Goal.h"
#include "Zamka1.h"
#include "MyPawn.h"
#include "Classes/GameFramework/Actor.h"
#include "Classes/Materials/Material.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>("BulletMesh");
	SetRootComponent(BulletMesh);

	BulletMovement = CreateDefaultSubobject<UProjectileMovementComponent>("BulletMovement");
	BulletMovement->InitialSpeed = 3500.f;
	BulletMovement->MaxSpeed = 3500.f;

	MaterialBullet = CreateDefaultSubobject<UMaterial>("MaterialBullet");

	OnActorHit.AddDynamic(this, &ABullet::OnBulletHit);

}

void ABullet::Set_Material(UMaterial* materijal)
{
	MaterialBullet = materijal;
	BulletMesh->SetMaterial(0, MaterialBullet);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	AActor* mojLik = GetOwner();

	if (Cast<AMyPawn>(mojLik) != __nullptr)
	{
		Set_Material(Cast<AMyPawn>(mojLik)->MaterialPawn);
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnBulletHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	if(Cast<AZamka1>(OtherActor) != nullptr)
	{
		return;
	}
	if (Cast<AMyPawn>(OtherActor) != nullptr)
	{
		Destroy();
		Cast<AMyPawn>(OtherActor)->UpdateBr_metaka(1);
		return;
	}
	Destroy();
}

