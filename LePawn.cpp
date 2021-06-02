// Fill out your copyright notice in the Description page of Project Settings.

#include "whythisnowork.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/InputComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Math/Vector.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "LePawn.h"

// Sets default values
ALePawn::ALePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Comp"));
	UCameraComponent * CameraPawn = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Pawn"));
	VisibleActor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Moosh"));
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	CharMove = CreateDefaultSubobject<UCharacterMovementComponent>(TEXT("Character Movement"));
	//VisibleActor->SetStaticMesh(Cube)
	CameraPawn->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	CameraPawn->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));
	
	arm->AttachTo(RootComponent);
	CameraPawn->AttachTo(VisibleActor);
	VisibleActor->AttachTo(RootComponent);

	arm->TargetArmLength = 300.0f;
	arm->SetRelativeRotation(FRotator(-15.0f, 0.0f, 0.0f));

	arm->bEnableCameraLag = true;
	arm->CameraLagSpeed = 2;
	arm-> CameraLagMaxDistance = 1.5f;

	arm->bEnableCameraRotationLag = true;
	arm->CameraRotationLagSpeed = 4;
	arm->CameraLagMaxTimeStep = 1;

	CameraPawn->AttachTo(arm, USpringArmComponent::SocketName);

	FRotator NewRotation = GetActorRotation();

	VisibleScale = VisibleActor->GetComponentScale().X;

	ObjRot = GetActorRotation();
	relativeRot = armRot - ObjRot;
	//FRotator NewRotationY = FRotator(1.0f, 0.0f, 0.0f);
	//FQuat QuertRotation = FQuat(NewRotationY);
}

// Called when the game starts or when spawned
void ALePawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALePawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	ForwardVector = VisibleActor->GetForwardVector();
	ForwardVelocity = GetActorForwardVector() + 0, 1, 0;
	BackVelocity = GetActorForwardVector() - 0, 1, 0;

	if(!CurrentVelocity.IsZero())
	{
		NewRotation = GetActorRotation();
		NewLocation = GetActorLocation() + (ForwardVelocity * DeltaTime);	
		//FVector NewLocation = GetActorLocation() + (ForwardVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}

	ActorLocation = GetActorLocation();

	/*NewRotation.Pitch += 1.0f;
	VisibleActor->AddLocalRotation(NewRotation, false, 0, ETeleportType::None);
	NewRotation = GetActorRotation();
	*/

	if(Growing == true){
		VisibleScale += DeltaTime;
	}
	else{
		VisibleScale -= DeltaTime;
	}

	ImpulseValue = 50000000000000000000000.0f;

	VisibleScale = FMath::Clamp(VisibleScale, 0.5f, 2.0f);
	VisibleActor->SetWorldScale3D(FVector(VisibleScale));

	ImpulseLocation = VisibleActor->GetComponentLocation() - 10.0f, 0.0f, 0.0f;
}

// Called to bind functionality to input
void ALePawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	InputComponent->BindAxis("MoveX", this, &ALePawn::MoveX);
	InputComponent->BindAxis("MoveY", this, &ALePawn::MoveY);
	InputComponent->BindAxis("MoveZ", this, &ALePawn::MoveZ);	
	InputComponent->BindAxis("MouseX", this, &ALePawn::MouseX);	
	InputComponent->BindAxis("MouseY", this, &ALePawn::MouseY);	
	InputComponent->BindAction("Heal", IE_Pressed, this, &ALePawn::Heal);
	InputComponent->BindAction("Fire", IE_Pressed, this, &ALePawn::NoHeal);
}

void ALePawn::MoveX(float AxisValue)
{
	//CurrentVelocity = FMath::Clamp(AxisValue, -1, 1);
	VelocityGoBrr = FVector(AxisValue, 0, 0);
	SetActorLocation(GetActorLocation() + (ForwardVelocity * AxisValue) * MovementSpeed);
	VelocityGoBrr = ForwardVelocity;
}
void ALePawn::MoveY(float AxisValue)
{
	//CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MovementSpeed;
	AddActorWorldRotation(FRotator(0, AxisValue, 0));
	//VisibleActor->AddLocalRotation(FRotator(0, AxisValue, 0));
}
void ALePawn::MoveZ(float AxisValue)
{
	CurrentVelocity.Z = FMath::Clamp(AxisValue, -1.0f, 1.0f) * MovementSpeed;
}
void ALePawn::Heal()
{
	//Growing = true;
	//VisibleActor->AddImpulse(ForwardVector * ImpulseValue * VisibleActor->GetMass());
}
void ALePawn::NoHeal(){
	//Growing = false;
}
void ALePawn::MouseX(float value){
	float temp = relativeRot.Pitch + value;
	/*if(temp <  25 && temp > -65){
			arm->AddLocalRotation(FRotator(0, value, 0));
			VisibleActor->AddLocalRotation(FRotator(0, value, 0));
	}*/
}
void ALePawn::MouseY(float value){
/*	float temp = relativeRot.Yaw + value;
	if(temp <  3 && temp > -5){
			arm->AddLocalRotation(FRotator(value, 0, 0));
			//VisibleActor->AddLocalRotation(FRotator(value, 0, 0));
	}
	*/
}