#include "TAttributeComponent.h"

UTAttributeComponent::UTAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

template <typename T>
TAttributeExercise<T>::TAttributeExercise(T InValue, const FName InAttributeName)
{
	Value = InValue;
	AttributeName = InAttributeName;
}

void UTAttributeComponent::GetAttribute(const FName& InAttributeName, float& OutValue) const
{
	if(!InAttributeName.IsValid()) return;
	
	for(auto Attribute : FloatAttributes)
	{
		if(Attribute.GetAttributeName().Compare(InAttributeName))
		{
			OutValue = Attribute.GetAttributeValue();
			return;
		}
	}
}

void UTAttributeComponent::AddAttribute(const FName& InAttributeName, const float InValue)
{
	if(!InAttributeName.IsValid()) return;
	if(InValue == -1.0f) return; //Al compilar da un warning indica que INDEX_NONE esta deprecado para floats

	if(HasAttribute(InAttributeName)) return; 
	
	const TAttributeExercise<float> Attribute = TAttributeExercise<float>(InValue, InAttributeName);
	FloatAttributes.Add(Attribute);

}

bool UTAttributeComponent::HasAttribute(const FName& InAttributeName)
{
	if(!InAttributeName.IsValid()) return false;
	
	for(auto Attribute : FloatAttributes)
	{
		if(Attribute.GetAttributeName().Compare(InAttributeName))
		{
			return true;
		}
	}
	return false;
}

void UTAttributeComponent::ModifyAttribute(const FName& InAttributeName, const float InValue)
{
	if(!InAttributeName.IsValid()) return;
	if(InValue == -1.0f) return; //Al compilar da un warning indica que INDEX_NONE esta deprecado para floats

	for(TAttributeExercise<float> Attribute : FloatAttributes)
	{
		if(Attribute.GetAttributeName().Compare(InAttributeName))
		{
			Attribute.SetAttributeName(InAttributeName);
			Attribute.SetAttributeValue(InValue);
			break;
		}
	}	
}