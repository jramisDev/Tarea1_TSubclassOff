#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttributeExercise.generated.h"

UCLASS(Blueprintable)
class TAREA1_TSUBCLASSOFF_API UAttributeExercise : public UObject
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;

	UPROPERTY()
	float Value = 0;

public:

	UFUNCTION(BlueprintCallable)
	const FName& GetAttributeName() const { return Name; }

	UFUNCTION(BlueprintCallable)
	void SetAttributeName(const FName& InName) { Name = InName; }

	UFUNCTION(BlueprintCallable)
	float GetAttributeValue() const { return Value; }

	UFUNCTION(BlueprintCallable)
	void SetAttributeValue(const float InValue) { Value = InValue; }
};