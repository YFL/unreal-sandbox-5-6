// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "CustomSandboxCharacter.generated.h"

class UInputMappingContext;
class UInputAction;

UCLASS(Blueprintable, BlueprintType)
class SANDBOX_API ACustomSandboxCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACustomSandboxCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Mesh")
	TObjectPtr<USkeletalMeshComponent> FirstPersonMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
	TObjectPtr<UAnimBlueprint> FirstPersonAnimation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= "Camera")
	TObjectPtr<UCameraComponent> FirstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float FirstPersonScale = 0.6f;

	// Offset for the first-person camera
	UPROPERTY(EditAnywhere, Category = "Camera")
	FVector FirstPersonCameraOffset = FVector(2.0f, 5.9f, 0.0f);

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> LookAction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	void Look(const FInputActionValue &Value);
};
