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
	UFUNCTION(CallInEditor, BlueprintCallable)
	void GetAttribute(const FName& InAttributeName, UAttributeExercise* &InAttribute) const;
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void AddAttribute(const FName& InAttributeName, float InValue);
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	bool HasAttribute(const FName& InAttributeName) const;
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void ModifyAttribute(const FName& InAttributeName, const float InValue);
};
