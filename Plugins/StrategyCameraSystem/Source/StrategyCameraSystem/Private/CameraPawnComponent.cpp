// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawnComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void UCameraPawnComponent::BeginPlay()
{
	Super::BeginPlay();
	Pawn = GetPawnChecked<APawn>();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(Pawn->InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UCameraPawnComponent::Move);
	EnhancedInputComponent->BindAction(RotateAction, ETriggerEvent::Triggered, this, &UCameraPawnComponent::Rotate);
	EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Triggered, this, &UCameraPawnComponent::Zoom);


	CameraComponent = Pawn->FindComponentByClass<UCameraComponent>();
	SpringArmComponent = Pawn->FindComponentByClass<USpringArmComponent>();

	ZoomDistance = StartDistance;
	SpringArmComponent->TargetArmLength = ZoomDistance;

}

void UCameraPawnComponent::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();	

	if (Pawn->GetController() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("valid"));


		// find out which way is forward
		//const FRotator Rotation = Pawn->GetController()->GetControlRotation();
		const FRotator Rotation = Pawn->GetActorRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		Pawn->AddMovementInput(ForwardDirection, MovementVector.Y);
		Pawn->AddMovementInput(RightDirection, MovementVector.X);
	}

}

void UCameraPawnComponent::Rotate(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	//float AxisValue = Value.Get<FVector2D>();
	Pawn->AddActorWorldRotation(FRotator(0, AxisValue, 0));
}

void UCameraPawnComponent::Zoom(const FInputActionValue& Value)
{
	float AxisValue = Value.Get<float>();
	ZoomDistance += AxisValue;

	SpringArmComponent->TargetArmLength = ZoomDistance;
}
