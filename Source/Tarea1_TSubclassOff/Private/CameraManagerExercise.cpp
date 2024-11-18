// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraManagerExercise.h"

void ACameraManagerExercise::StartFadeInFadeOut()
{
	if(FadeInOutActive) return;

	//FadeInOutActive = true;
	
	StartCameraFade(0.f, 1.f, 0.5f, FColor::Blue);
	StartCameraFade(1.f, 0.f, 0.5f, FColor::Blue);

	//FadeInOutActive = false;

	OnFadeTransitionFinished.Broadcast();
}
