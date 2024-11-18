// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/PlayerCameraManager.h"
#include "CameraManagerExercise.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFadeTransitionFinished);
/**
 * 
 */
UCLASS()
class TAREA1_TSUBCLASSOFF_API ACameraManagerExercise : public APlayerCameraManager
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
	FOnFadeTransitionFinished OnFadeTransitionFinished;

	UFUNCTION(BlueprintCallable)
	virtual void StartFadeInFadeOut();
	
	UFUNCTION(BlueprintCallable)
	bool GetFadeInOutActive() const { return FadeInOutActive; }

private:
	
	bool FadeInOutActive = false;
	
};
