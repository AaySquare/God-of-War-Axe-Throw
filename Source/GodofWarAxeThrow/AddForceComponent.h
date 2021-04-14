// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "AddForceComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GODOFWARAXETHROW_API UAddForceComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAddForceComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AxeThrow();

private:
	UPROPERTY()
	class UStaticMeshComponent* MeshComp;

	class AGodofWarAxeThrowCharacter* AxeThrowCharacter;

	UPROPERTY(EditAnywhere, Category="Forces")
	float Force = 1000.0f;
	
};
