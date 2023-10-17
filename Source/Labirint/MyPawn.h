// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

UCLASS()
class LABIRINT_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

	UPROPERTY(EditAnywhere, Category = "Material")
	class UMaterial* MaterialPawn;

	UPROPERTY()
	class UUserWidget* PortalWidget;

	UPROPERTY()
	bool TP = false;

	UPROPERTY()
	float Rotacija_Y;

	UPROPERTY()
	float Rotacija_X;

	UPROPERTY(EditAnywhere, Category = "Components")
	float MovementSpeed;

	UPROPERTY(EditAnywhere, Category = "Components")
	float X;

	UPROPERTY(EditAnywhere, Category = "Components")
	float Y;

	UPROPERTY(EditAnywhere, Category = "Components")
	float Z;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int br_metaka;

	UPROPERTY(EditAnywhere, Category = "Shooting")
	int max_metaka;

	UPROPERTY()
	bool p; //pause

	UPROPERTY(EditAnywhere, Category = "Components")
	class UBoxComponent* Box;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, Category = "Components")
	UStaticMeshComponent* StaticMeshFo;

	UFUNCTION(BlueprintPure, Category = "Br_metaka")
	int GetBr_metaka();

	UFUNCTION(BlueprintCallable, Category = "MaterialPawn")
	void Set_Material(UMaterial* materijal);

	UFUNCTION(BlueprintPure, Category = "Br_metaka")
	int GetMax_metaka();

	/**Updates the player current number of amo
	*	@param metak This is the amount to change the players current amo
	*
	*/

	UFUNCTION(BlueprintCallable, Category = "Br_metaka")
	void UpdateBr_metaka(int metak);

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Play_game();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Controls();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Back_menu();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Game_quit();

	UFUNCTION(BlueprintCallable, Category = "MainMenu")
	void Back_Pause();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float Amount);
	void MoveRight(float Amount);
	void Turn(float Amount);
	void funkcija2();
	void funkcija();
	void Shoot();
	void CameraZoom(float Amount);
	void CameraZoomIn();
	void CameraZoomOut();
	void ResetCamera();
	void TeleportNaPoziciju();

	UPROPERTY(EditAnywhere, Category = "Shooting")
	TSubclassOf<class ABullet> BulletClass;

	class UFloatingPawnMovement* FloatingPawnMovement;


	UPROPERTY(EditAnywhere, Category = "Shooting")
	float Lokacija_Metka;


	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character **/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PauseHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> OptionHUDClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MainMenu", Meta = (BlueprintProtected = "true"))
	TSubclassOf<class UUserWidget> PortalHUDClass;

	UPROPERTY()
	class UUserWidget* CurrentWidget;



public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
