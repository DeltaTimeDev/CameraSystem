// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/PawnComponent.h"
#include "InputActionValue.h"
#include "CameraPawnComponent.generated.h"

/**
 * 
 */
UCLASS()
class STRATEGYCAMERASYSTEM_API UCameraPawnComponent : public UPawnComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;
	void Move(const FInputActionValue& Value);
	void Rotate(const FInputActionValue& Value);
	void Zoom(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class APawn* Pawn;

	class UCameraComponent* CameraComponent;
	class USpringArmComponent* SpringArmComponent;

private:
	float ZoomDistance;
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	float StartDistance = 900.0f;
};
