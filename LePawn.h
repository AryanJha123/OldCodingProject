// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "LePawn.generated.h"

UCLASS()
class WHYTHISNOWORK_API ALePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ALePawn();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* VisibleActor;

	UPROPERTY(EditAnywhere)
	UCharacterMovementComponent* CharMove;

	void MoveX(float AxisValue);
	void MoveY(float AxisValue);
	void MoveZ(float AxisValue);

	int Health = 100;
	int HealingPotions = 3;
	
	FRotator armRot;
	FRotator ObjRot;
	FRotator relativeRot;

	FVector CurrentVelocity;
	FVector ForwardVelocity;
	FVector BackVelocity;
	FVector ActorLocation;
	FVector VelocityGoBrr;
	FVector NewLocation;
	FVector ImpulseLocation;
	FVector ForwardVector;

	bool goingForward;
	
	void Heal();
	void NoHeal();

	float clampvalue = 0.0f;
	float MovementSpeed = 5.0f;
	float HealthUp = 10.0f;
	float ImpulseValue;

	FRotator NewRotation;
	float VisibleScale;
	bool Growing;
	//FQuat QuatRotation = FQuat(0.0f, 0.0f, 0.0f);

	void MouseX(float value);
	void MouseY(float value);

	UPROPERTY(EditAnywhere)
	USpringArmComponent * arm;
};

