#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TAttributeComponent.generated.h"


template<typename T>
class TAttributeExercise
{
public:
	TAttributeExercise(T InValue = 0, const FName InAttributeName = TEXT("NONE") );
	
	T GetAttributeValue() const { return Value; }
	void SetAttributeValue(const T& InValue) { Value = InValue; }

	const FName& GetAttributeName() const { return AttributeName; }
	void SetAttributeName(const FName& InAttributeName ) { AttributeName = InAttributeName; }

private:
	T Value;
	FName AttributeName;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TAREA1_TSUBCLASSOFF_API UTAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	
	TArray<TAttributeExercise<float>> FloatAttributes;

public:
	UTAttributeComponent();

	UFUNCTION(CallInEditor, BlueprintCallable) //no consigo devolver en el output un TAttributeExercise<float>&, ¿se puede?
	void GetAttribute(const FName& InAttributeName, float& OutValue) const;	
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void AddAttribute(const FName& InAttributeName, const float InValue);
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	bool HasAttribute(const FName& InAttributeName);
	
	UFUNCTION(CallInEditor, BlueprintCallable)
	void ModifyAttribute(const FName& InAttributeName, const float InValue);
};
