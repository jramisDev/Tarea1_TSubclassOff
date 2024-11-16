#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"

class UAttributeExercise;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA1_TSUBCLASSOFF_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Attributes")
	TArray<UAttributeExercise*> Attributes;
	
public:
	UAttributeComponent();

	/* Con UObject */
	UAttributeExercise* GetAttribute(const FName& InAttributeName) const;
	void AddAttribute(const FName& InAttributeName, float InValue);
	bool HasAttribute(const FName& InAttributeName) const;
	void ModifyAttribute(const FName& InAttributeName, const float InValue);
};
