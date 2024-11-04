#include "TeleportActor.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "Tarea1_TSubclassOff/Tarea1_TSubclassOffCharacter.h"


ATeleportActor::ATeleportActor()
{
	PrimaryActorTick.bCanEverTick = true;

	TeleportMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Teleport Mesh"));	
	// TeleportMesh->SetWorldRotation(FRotator{90.f,0.f,0.f});
	RootComponent = TeleportMesh;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetupAttachment(TeleportMesh);
	
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionBeginOverlap);	
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ATeleportActor::BoxCollisionEndOverlap);
	
	ArrowDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Direction"));
	ArrowDirection->SetupAttachment(TeleportMesh);
}

void ATeleportActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATeleportActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATeleportActor::BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(bTeleportingActor) return;
	
	UE_LOG(LogTemp, Display, TEXT("ORIGEN TEST1"));
	if(ATarea1_TSubclassOffCharacter* Character = Cast<ATarea1_TSubclassOffCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT("ORIGEN TEST2"));
		if(TeleportDestination)
		{
			UE_LOG(LogTemp, Display, TEXT("ORIGEN TEST3"));
			if(!bTeleportingActor)
			{
				bTeleportingActor = true;
				Character->SetActorLocationAndRotation(TeleportDestination->GetActorLocation(), TeleportDestination->GetActorRotation());
			}
		}
	}
}

void ATeleportActor::BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Display, TEXT("DESTINO TEST1"));
	if(ATarea1_TSubclassOffCharacter* Character = Cast<ATarea1_TSubclassOffCharacter>(OtherActor))
	{
		UE_LOG(LogTemp, Display, TEXT("DESTINO TEST2"));
		bTeleportingActor = false;
	}
}
