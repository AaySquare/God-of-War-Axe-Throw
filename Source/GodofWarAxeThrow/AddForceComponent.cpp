// Fill out your copyright notice in the Description page of Project Settings.


#include "AddForceComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GodofWarAxeThrow/GodofWarAxeThrowCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UAddForceComponent::UAddForceComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAddForceComponent::BeginPlay()
{
	Super::BeginPlay();
	MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	AxeThrowCharacter = Cast<AGodofWarAxeThrowCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	
}


// Called every frame
void UAddForceComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(AxeThrowCharacter->bCanThrow)
	{
		
	}
	
}

void UAddForceComponent::AxeThrow()
{
	const FVector Forward = AxeThrowCharacter->GetActorForwardVector();

	//MeshComp->SetSimulatePhysics(true);
	//MeshComp->AddForce(Forward * Force * MeshComp->GetMass());
}



