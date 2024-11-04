#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "TeleportActor.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class TAREA1_TSUBCLASSOFF_API ATeleportActor : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category="Teleport", meta=(AllowPrivateAccess=true))
	bool bTeleportingActor;

public:
	ATeleportActor();

	UPROPERTY(EditInstanceOnly, Category="Teleport")
	ATeleportActor* TeleportDestination;

	UPROPERTY(EditInstanceOnly, Category="Teleport")
	TArray<TSubclassOf<AActor>> ListTeleportClass;
	
	UFUNCTION(BlueprintCallable, Category="Teleport")
	void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category="Teleport")
	void BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UStaticMeshComponent* TeleportMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UArrowComponent* ArrowDirection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleport")
	USoundBase* SoundToPlay;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Teleport")
	UNiagaraSystem* NSTeleport;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};