#include "TeleportActor.h"

#include "CameraManagerExercise.h"
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
	
	ArrowDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Direction"));
	ArrowDirection->SetupAttachment(TeleportMesh);
}

void ATeleportActor::SpawnNiagara() const
{
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
}

void ATeleportActor::SpawnSound() const
{
	if(SoundToPlay) UGameplayStatics::PlaySoundAtLocation(GetWorld(), SoundToPlay, GetActorLocation());
}

void ATeleportActor::SpawnFadeInOut(AActor& OtherActor) const
{
	if(const ACharacter* Character = Cast<ACharacter>(&OtherActor))
	{
		const int32 IndexPlayer = Cast<APlayerController>(Character->GetController())->GetLocalPlayer()->GetLocalPlayerIndex();
		
		if(ACameraManagerExercise* CameraManager = Cast<ACameraManagerExercise>(UGameplayStatics::GetPlayerCameraManager(GetWorld(), IndexPlayer) ))
		{
			CameraManager->StartFadeInFadeOut();
		}
	}
}
	

void ATeleportActor::DoTeleport(AActor& OtherActor) const
{
	TeleportDestination->SetCanTeleport(false);
	OtherActor.SetActorLocationAndRotation(TeleportDestination->GetActorLocation(), TeleportDestination->GetActorRotation());
	//OtherActor.DisableInput(0);
}

void ATeleportActor::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                              UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(!bCanTeleport) return;
	if(!TeleportDestination) return;
	if(AllowedActors.IsEmpty()) return;
	if(!AllowedActors.Contains(OtherActor->GetClass())) return;
	
	SpawnSound();
	
	SpawnNiagara();
	
	SpawnFadeInOut(*OtherActor);

	DoTeleport(*OtherActor);
	
}

void ATeleportActor::BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	SetCanTeleport(true);
}

void ATeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionBeginOverlap);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionEndOverlap);
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
			TeleportDestination->TeleportDestination=this;
		}
	}
}
#endif
