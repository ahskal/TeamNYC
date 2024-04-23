#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class APlayerCharacter;

UCLASS()
class TEAMNYC_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY()
	APlayerCharacter* PlayerCharacter;

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

};
