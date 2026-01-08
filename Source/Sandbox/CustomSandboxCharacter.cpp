// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSandboxCharacter.h"

// Sets default values
ACustomSandboxCharacter::ACustomSandboxCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(FName("First Person Camera"));
	check(FirstPersonCamera != nullptr);
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(FName("First Person Mesh"));
	check(FirstPersonMesh != nullptr);
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
	FirstPersonCamera->SetupAttachment(FirstPersonMesh, FName("head"));
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;

	FirstPersonAnimation = CreateDefaultSubobject<UAnimBlueprint>(FName("First Person Animation"));
	check(FirstPersonAnimation != nullptr);
	FirstPersonCamera->bEnableFirstPersonScale = true;
	FirstPersonCamera->FirstPersonScale = FirstPersonScale;
	FirstPersonCamera->SetRelativeLocationAndRotation(FirstPersonCameraOffset, FRotator(0.0f, 0.0f, 0.0f));
}

// Called when the game starts or when spawned
void ACustomSandboxCharacter::BeginPlay()
{
	Super::BeginPlay();
	FirstPersonMesh->SetOnlyOwnerSee(true);
	FirstPersonMesh->SetAnimInstanceClass(FirstPersonAnimation->GeneratedClass);

	if (const auto PlayerController = Cast<APlayerController>(Controller))
	{
		if (const auto System = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			System->AddMappingContext(InputContext, 0);
		}
	}
}

// Called every frame
void ACustomSandboxCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACustomSandboxCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (const auto EnhancedInput = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomSandboxCharacter::Look);
	}
}

void ACustomSandboxCharacter::Look(const FInputActionValue &Value)
{
	const auto Vector = Value.Get<FVector2D>();
	GEngine->AddOnScreenDebugMessage(0, 0.5, FColor::Cyan, FString::Printf(TEXT("MouseInput: %s"), *Vector.ToString()));
	if (Controller)
	{
		AddControllerYawInput(Vector.X);
		AddControllerPitchInput(Vector.Y);
	}
}

