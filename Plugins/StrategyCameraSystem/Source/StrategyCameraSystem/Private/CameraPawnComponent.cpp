// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraPawnComponent.h"
#include "Components/InputComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

void UCameraPawnComponent::BeginPlay()
{
	Super::BeginPlay();
	APawn* Pawn = GetPawnChecked<APawn>();
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(Pawn->InputComponent);
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &UCameraPawnComponent::MoveUp);
}

void UCameraPawnComponent::MoveUp(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	UE_LOG(LogTemp, Warning, TEXT("MoveUp %f, %f"), MovementVector.X, MovementVector.Y);

	
	APawn* Pawn = GetPawnChecked<APawn>();


	if (Pawn->GetController() != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("valid"));


		// find out which way is forward
		const FRotator Rotation = Pawn->GetController()->GetControlRotation();
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
