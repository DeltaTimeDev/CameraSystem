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
	void MoveUp(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	
};
