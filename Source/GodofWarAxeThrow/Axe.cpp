// Fill out your copyright notice in the Description page of Project Settings.


#include "Axe.h"

#include <Actor.h>


#include "DrawDebugHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GodofWarAxeThrow/GodofWarAxeThrowCharacter.h"
#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

// Sets default values
AAxe::AAxe()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AxeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AxeMesh"));
	AxeMesh->SetSimulatePhysics(false);
	AxeMesh->SetEnableGravity(false);
	AxeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
	RootComponent = AxeMesh;

	RotatingMovementComp = CreateDefaultSubobject<URotatingMovementComponent>(TEXT("RotatingMovementComp"));

	AxeSpeed = 5000.0f;
	TraceDistance = 25.0f;

	bIsAxeThrown = false;
	bIsAxeReturning = false;

	Time = 0;
}

// Called when the game starts or when spawned
void AAxe::BeginPlay()
{
	Super::BeginPlay();

	AxeThrowCharacter = Cast<AGodofWarAxeThrowCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	PlayerCamera = AxeThrowCharacter->FindComponentByClass<UCameraComponent>();

	AxeMesh->OnComponentHit.AddDynamic(this, &AAxe::OnCompHit);
}

FVector AAxe::GetBQCPoint(float T, FVector P0, FVector P1, FVector P2)
{
	float U = 1 - T;
	float TT = T * T;
	float UU = U * U;
	FVector P = (UU * P0) + (2 * U * T * P1) + (TT * P2);
	return P;
}

// Called every frame
void AAxe::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AxeReturn();

	if(GetDistanceTo(AxeThrowCharacter) > 1000.0f)
	{
		AxeMesh->SetEnableGravity(true);
	}
}

void AAxe::DetachAxe()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	float PlayerRotateX = AxeThrowCharacter->GetActorRotation().Roll;
	float PlayerRotateY = AxeThrowCharacter->GetActorRotation().Pitch;
	float PlayerRotateZ = AxeThrowCharacter->GetActorRotation().Yaw;

	SetActorRotation(FRotator(-45.0f, PlayerRotateZ, -90.0f));
}

void AAxe::AxeThrow()
{
	if(bIsAxeThrown == false)
	{
		DetachAxe();
		//SetActorLocation(FVector(GetActorLocation().X, PlayerCamera->GetComponentLocation().Y, PlayerCamera->GetComponentLocation().Z));
		bIsAxeThrown = true;
	}
	bIsAxeThrown = false;
	bIsAxeReturning = false;
	
	ForwardVector = PlayerCamera->GetForwardVector();

	AxeMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	AxeMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	AxeMesh->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	AxeMesh->SetSimulatePhysics(true);
	AxeMesh->AddForce(ForwardVector * AxeSpeed * AxeMesh->GetMass() * 30.0f);

	RotatingMovementComp->RotationRate.Yaw = 2000.0f * -1.0f;
}

void AAxe::AxeReturn()
{
	if(AxeThrowCharacter->bCanReturn)
	{
		if(bIsAxeReturning == false)
		{
			SetActorRotation(FRotator(0.0f, AxeThrowCharacter->GetActorRotation().Yaw, -90.0f));
			bIsAxeReturning = true;
		}
		AxeMesh->SetSimulatePhysics(false);
		AxeMesh->SetEnableGravity(false);
		AxeMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		FVector SocketLocation = AxeThrowCharacter->GetMesh()->GetSocketLocation("SocketAxe");
		FVector CurrentLocation = GetActorLocation();
		FVector CurvePoint;
		if(GetDistanceTo(AxeThrowCharacter) > 100.0f)
		{
			SetActorLocation(FMath::LerpStable(CurrentLocation, SocketLocation, 0.05f));
			RotatingMovementComp->RotationRate.Yaw = 2000.0f;
		}
		else
		{
			ResetAxe();
		}
	}
}

void AAxe::ResetAxe()
{
	RotatingMovementComp->RotationRate.Yaw = 0.0f;
	FRotator SocketRotation = AxeThrowCharacter->GetMesh()->GetSocketRotation("SocketAxe");
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FMath::Lerp(CurrentRotation, SocketRotation, 0.01f));
	AttachToComponent(AxeThrowCharacter->GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, "SocketAxe");
	bIsAxeReturning = false;
	AxeThrowCharacter->bCanReturn = false;
}

void AAxe::OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
	{
		AxeMesh->SetSimulatePhysics(false);
		AxeMesh->SetEnableGravity(false);
		SetActorRotation(FRotator(-45.0f, AxeThrowCharacter->GetActorRotation().Yaw, -90.0f));
		RotatingMovementComp->RotationRate.Yaw = 0.0f;
		AxeThrowCharacter->bCanAim = false;
		
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
	}
}

