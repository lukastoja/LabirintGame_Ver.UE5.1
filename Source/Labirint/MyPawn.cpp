// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"
#include "Bullet.h"
#include "Classes/Components/InputComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "Classes/Components/CapsuleComponent.h"
#include "Classes/Components/BoxComponent.h"
#include "Classes/GameFramework/FloatingPawnMovement.h"
#include "Camera/CameraComponent.h"
#include "Classes/GameFramework/SpringArmComponent.h"
#include "Classes/GameFramework/PlayerController.h"
#include "Engine.h"
#include "Portal.h"
#include "GameFramework/InputSettings.h"
#include "Blueprint/UserWidget.h"
#include "Classes/Components/SceneComponent.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComoponent");
	StaticMeshFo = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshFoComoponent");
	Box = CreateDefaultSubobject<UBoxComponent>("BoxComponent");
	FloatingPawnMovement = CreateDefaultSubobject< UFloatingPawnMovement>("PawnMovement");
	MaterialPawn = CreateDefaultSubobject<UMaterial>("MaterialPawn");

	SetRootComponent(Box);
	StaticMesh->SetupAttachment(Box);
	StaticMeshFo->SetupAttachment(Box);

	StaticMeshFo->SetWorldLocation(FVector(50.f, 0.f, 0.f));
	StaticMeshFo->SetWorldRotation(FRotator(-90.f, 0.f, 0.f));

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(Box);
	//CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->AddRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	
	br_metaka = 10;
	max_metaka = 20;
	p = false;

	Rotacija_Y = 0.f;
	Rotacija_X = 0.f;
	X = 0.f;
	Y = 0.f;
	Z = 0.f;
	Lokacija_Metka = 100.f;
	MovementSpeed = 1.f;

	bUseControllerRotationYaw = true;

	Box->OnComponentEndOverlap.AddDynamic(this, &AMyPawn::OnOverlapEnd);
}

int AMyPawn::GetBr_metaka()
{
	return br_metaka;
}

void AMyPawn::Set_Material(UMaterial * materijal)
{
	MaterialPawn = materijal;
	StaticMesh->SetMaterial(0, MaterialPawn);
	StaticMeshFo->SetMaterial(0, MaterialPawn);
}

int AMyPawn::GetMax_metaka()
{
	return max_metaka;
}

void AMyPawn::UpdateBr_metaka(int metak)
{
	br_metaka = br_metaka + metak; 
	if (br_metaka <= 0)
	{
		br_metaka = 0;
	}
	if (br_metaka >= max_metaka)
	{
		br_metaka = max_metaka;
	}
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	if (OptionHUDClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);
	}

	
	if (PortalHUDClass != nullptr)
	{
		PortalWidget = CreateWidget<UUserWidget>(GetWorld(), PortalHUDClass);
	}

	StaticMesh->SetMaterial(0, MaterialPawn);
	StaticMeshFo->SetMaterial(0, MaterialPawn);
}

void AMyPawn::MoveForward(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorForwardVector() * Amount / MovementSpeed);
	//Rotacija_X = Rotacija_X + Amount * 10;
	//StaticMesh->SetWorldRotation(FRotator(Rotacija_X, Rotacija_Y, 0.f));
}

void AMyPawn::MoveRight(float Amount)
{
	FloatingPawnMovement->AddInputVector(GetActorRightVector() * Amount / MovementSpeed);
	Rotacija_Y = Rotacija_Y + Amount * 10;
	StaticMesh->SetWorldRotation(FRotator(Rotacija_X, Rotacija_Y, 0.f));
}

void AMyPawn::Turn(float Amount)
{
	AddControllerYawInput(Amount);
}

void AMyPawn::funkcija()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("RestartLevel");
}

void AMyPawn::Shoot()
{

	if (br_metaka <= 0)
	{

		br_metaka = 0;
		return;
	}
	if (BulletClass)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnParameters.bNoFail = true;
		SpawnParameters.Owner = this;
		SpawnParameters.Instigator = this;

		FTransform BulletSpawnTransform;
		BulletSpawnTransform.SetLocation(GetActorForwardVector() * Lokacija_Metka + GetActorLocation());
		BulletSpawnTransform.SetRotation(GetActorRotation().Quaternion());
		BulletSpawnTransform.SetScale3D(FVector(1.f));

		GetWorld()->SpawnActor<ABullet>(BulletClass, BulletSpawnTransform, SpawnParameters);
		UpdateBr_metaka(-1);
	}
}

void AMyPawn::CameraZoom(float Amount)
{
	CameraBoom->TargetArmLength = CameraBoom->TargetArmLength + Amount*3.5;
	if (CameraBoom->TargetArmLength >= 802)
	{
		CameraBoom->TargetArmLength = 800.f;
	}
	else if (CameraBoom->TargetArmLength <= 450)
	{
		CameraBoom->TargetArmLength = 450;
	}
}

void AMyPawn::CameraZoomIn()
{
	float Amount = -1;

	CameraBoom->TargetArmLength = CameraBoom->TargetArmLength + Amount*13;
	if (CameraBoom->TargetArmLength <= 450)
	{
		CameraBoom->TargetArmLength = 450;
	}
}

void AMyPawn::CameraZoomOut()
{
	float Amount = 1;

	CameraBoom->TargetArmLength = CameraBoom->TargetArmLength + Amount*13;
	if (CameraBoom->TargetArmLength >= 802)
	{
		CameraBoom->TargetArmLength = 800;
	}
}

void AMyPawn::ResetCamera()
{
	CameraBoom->TargetArmLength = 800;
}

void AMyPawn::TeleportNaPoziciju()
{
	if (TP)
	{
		FVector pozicija = FVector(X, Y, Z);
		Box->SetWorldLocation(pozicija);
	}
}

void AMyPawn::funkcija2()
{
	APlayerController* const MyPlayer = Cast<APlayerController>(GEngine->GetFirstLocalPlayerController(GetWorld()));
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	if (MyPlayer != NULL && p == false)
	{
		p = true;

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}

		if (PC)
		{
			PC->bShowMouseCursor = true;
			PC->bEnableClickEvents = true;
			PC->bEnableMouseOverEvents = true;
		}
	}
	else if (MyPlayer != NULL && p == true)
	{
		p = false;

		if (CurrentWidget != nullptr)
		{
			CurrentWidget->RemoveFromParent();
		}

		PC->bShowMouseCursor = false;
	}

	MyPlayer->SetPause(p);
}

void AMyPawn::Play_game()
{
	funkcija2();
}

void AMyPawn::Controls()
{
	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), OptionHUDClass);

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

void AMyPawn::Back_menu()
{
	UGameplayStatics::OpenLevel(this, "L_MainMenu");
}

void AMyPawn::Game_quit()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit");
}

void AMyPawn::Back_Pause()
{
	CurrentWidget->RemoveFromParent();
	CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PauseHUDClass);

	if (CurrentWidget != nullptr)
	{
		CurrentWidget->AddToViewport();
	}
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMyPawn::OnOverlapEnd(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
	TP = false;
	if (PortalWidget != nullptr)
	{
		PortalWidget->RemoveFromParent();
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("funkcija", IE_Pressed, this, &AMyPawn::funkcija);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &AMyPawn::Shoot);
	PlayerInputComponent->BindAction("funkcija2", IE_Pressed, this, &AMyPawn::funkcija2).bExecuteWhenPaused = true;
	PlayerInputComponent->BindAction("CameraZoomIn", IE_Pressed, this, &AMyPawn::CameraZoomIn);
	PlayerInputComponent->BindAction("CameraZoomOut", IE_Pressed, this, &AMyPawn::CameraZoomOut);
	PlayerInputComponent->BindAction("ResetCamera", IE_Pressed, this, &AMyPawn::ResetCamera);
	PlayerInputComponent->BindAction("TeleportNaPoziciju", IE_Pressed, this, &AMyPawn::TeleportNaPoziciju);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMyPawn::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyPawn::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &AMyPawn::Turn);
	PlayerInputComponent->BindAxis("CameraZoom", this, &AMyPawn::CameraZoom);
}

