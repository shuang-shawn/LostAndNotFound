// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Math/UnrealMathUtility.h"
#include "Mover.generated.h"


UENUM(BlueprintType)
enum class MoveState : uint8
{
	Move,
	Stay,
	Return
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOSTANDNOTFOUND_API UMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void Move();
	void Return();
	

	

private:
	UPROPERTY(EditAnywhere)
	MoveState moveState = MoveState::Stay;

	UPROPERTY(EditAnywhere)
	FVector MoveOffset = FVector(0, 0, -600);

	UPROPERTY(EditAnywhere)
	float MoveTime = 4;

	FVector OriginalLocation;






		
};
