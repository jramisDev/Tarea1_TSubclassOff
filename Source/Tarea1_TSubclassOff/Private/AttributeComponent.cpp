#include "AttributeComponent.h"

#include "AttributeExercise.h"

UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UAttributeExercise* UAttributeComponent::GetAttribute(const FName& InAttributeName) const
{
	if(!InAttributeName.IsValid()) return nullptr;
	
	for(const auto Attribute : Attributes)
	{
		if(Attribute->GetAttributeName().Compare(InAttributeName))
		{
			return Attribute;
		}
	}
	return nullptr;
}

void UAttributeComponent::AddAttribute(const FName& InAttributeName, const float InValue)
{
	if(!InAttributeName.IsValid()) return;
	if(InValue == -1.0f) return; //Al compilar da un warning indica que INDEX_NONE esta deprecado para floats

	if(HasAttribute(InAttributeName)) return; 
	
	UAttributeExercise* Attr = NewObject<UAttributeExercise>(this, StaticClass());
	Attr->SetAttributeName(InAttributeName);
	Attr->SetAttributeValue(InValue);
	
	Attributes.Add(Attr);	
}

bool UAttributeComponent::HasAttribute(const FName& InAttributeName) const
{
	if(!InAttributeName.IsValid()) return false;
	
	for(const auto Attribute : Attributes)
	{
		if(Attribute->GetAttributeName().Compare(InAttributeName))
		{
			return true;
		}
	}
	return false;
}

void UAttributeComponent::ModifyAttribute(const FName& InAttributeName, const float InValue)
{
	if(!InAttributeName.IsValid()) return;
	if(InValue == -1.0f) return; //Al compilar da un warning indica que INDEX_NONE esta deprecado para floats
		
	for(const auto Attribute : Attributes)
	{
		if(Attribute->GetAttributeName().Compare(InAttributeName))
		{
			Attribute->SetAttributeName(InAttributeName);
			Attribute->SetAttributeValue(InValue);
			break;
		}
	}	
}