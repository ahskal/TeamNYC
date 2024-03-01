// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase/ItemBase.h"
#include "Item/ItemBase/ItemDataStructs.h"

UItemBase::UItemBase()) :
	bIsCopy(false), bIsPickup(false)
{
}

void UItemBase::ResetItemFlags()
{
}

UItemBase* UItemBase::CreateItemCopy() const
{
	return nullptr;
}

void UItemBase::SetQuantity(const int32 NewQuantity)
{
}
