#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AttributeExercise.generated.h"

UCLASS(Blueprintable)
class TAREA1_TSUBCLASSOFF_API UAttributeExercise : public UObject
{
	GENERATED_BODY()

	FName Name;
	float Value = -1.0f; //Al compilar da un warning indica que INDEX_NONE esta deprecado para floats

public:
	UAttributeExercise(){}
	UAttributeExercise(const FName& InName, const float InValue)
	{
		Name = InName;
		Value = InValue;
	}
	
	const FName& GetAttributeName() const { return Name; }
	void SetAttributeName(const FName& InName) { Name = InName; }

	float GetAttributeValue() const { return Value; }
	void SetAttributeValue(const float InValue) { Value = InValue; }
};
