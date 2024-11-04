#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TeleportActor.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class TAREA1_TSUBCLASSOFF_API ATeleportActor : public AActor
{
	GENERATED_BODY()

public:
	ATeleportActor();

	UPROPERTY(EditInstanceOnly, Category="Teleport")
	ATeleportActor* TeleportDestination;
	
	UFUNCTION(BlueprintCallable, Category="Teleport")
	void BoxCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                              const FHitResult& SweepResult);
	
	UFUNCTION(BlueprintCallable, Category="Teleport")
	void BoxCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	bool bTeleportingActor;
	
protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UStaticMeshComponent* TeleportMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Teleport")
	UArrowComponent* ArrowDirection;
	
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
};
