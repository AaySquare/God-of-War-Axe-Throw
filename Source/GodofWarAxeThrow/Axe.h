// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/Actor.h"


#include "Axe.generated.h"

class UStaticMeshComponent;
class UCameraComponent;
class URotatingMovementComponent;

UCLASS()
class GODOFWARAXETHROW_API AAxe : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAxe();

	UPROPERTY(EditAnywhere, Category="Components")
	UStaticMeshComponent* AxeMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Movement")
	URotatingMovementComponent* RotatingMovementComp;

	UCameraComponent* PlayerCamera;
	FVector ForwardVector;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	class AGodofWarAxeThrowCharacter* AxeThrowCharacter;

	void DetachAxe();

	UFUNCTION(BlueprintCallable, Category="Axe")
	void AxeThrow();

	UFUNCTION(BlueprintCallable, Category="Axe")
	void AxeReturn();

	void ResetAxe();

	bool bIsAxeThrown;
	bool bIsAxeReturning;

	UPROPERTY(EditDefaultsOnly, Category="Movement")
	float AxeSpeed;

	UPROPERTY(EditDefaultsOnly, Category="Collision")
	float TraceDistance;

	FVector GetBQCPoint(float T, FVector P0, FVector P1, FVector P2);

	float Time;

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
