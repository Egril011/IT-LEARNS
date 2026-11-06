// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InteractionComponent.generated.h"

UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent,  DisplayName="InteractionComponent"))

class IT_LEARNS_API UInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInteractionComponent();
	
	UFUNCTION(BlueprintCallable)
	void Interact();
	
protected:
	virtual void BeginPlay() override;
	
private:
	UPROPERTY(EditAnywhere, Category="LineTrace", meta=(AllowPrivateAccess = true))
	float LineTraceDistancePower = 1000.0f;
	
	TObjectPtr<ACharacter> OwningCharacter = nullptr;
	
	//Perform a LineTrace
	bool PerformInteractionTrace(FHitResult& OutHit) const;
	
	//Check if the object is interactable
	bool IsItemInteractable(AActor*&) const;
};
