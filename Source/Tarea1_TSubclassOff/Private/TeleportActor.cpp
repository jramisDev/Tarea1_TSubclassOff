﻿#include "TeleportActor.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tarea1_TSubclassOff/Tarea1_TSubclassOffCharacter.h"


ATeleportActor::ATeleportActor()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleport Mesh"));	
	RootComponent = TeleportMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(TeleportMesh);
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionBeginOverlap);	
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionEndOverlap);
	
	ArrowDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Direction"));
	ArrowDirection->SetupAttachment(TeleportMesh);
}

void ATeleportActor::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bTeleportingActor) return;
	if(!TeleportDestination) return;
	if(ListTeleportClass.IsEmpty()) return;
	if(!ListTeleportClass.Contains(OtherActor->GetClass())) return;
	
	bTeleportingActor = true;

	if(SoundToPlay) UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation());
	
	if(NSTeleport)
	{
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAttached(
											NSTeleport,
											TeleportMesh,
											NAME_None,
											FVector(0.f),
											FRotator(0.f),
											EAttachLocation::Type::KeepRelativeOffset,
											true);
	}

	if(const ATarea1_TSubclassOffCharacter* Character = Cast<ATarea1_TSubclassOffCharacter>(OtherActor))
	{
		Character->FadeInOutCamera();
	}
	
	OtherActor->SetActorLocationAndRotation(TeleportDestination->GetActorLocation(), TeleportDestination->GetActorRotation());
}

void ATeleportActor::BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bTeleportingActor = false;
}

#if WITH_EDITOR
void ATeleportActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	if(PropertyChangedEvent.GetPropertyName().IsEqual(GET_MEMBER_NAME_CHECKED(ATeleportActor, TeleportDestination)))
	{
		if(TeleportDestination)
		{
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TeleportDestination->GetActorLocation()));
			TeleportDestination->SetActorRotation(UKismetMathLibrary::FindLookAtRotation(TeleportDestination->GetActorLocation(), GetActorLocation()));
		}
	}
}
#endif
