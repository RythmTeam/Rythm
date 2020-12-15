// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Chaos/AABBTree.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "PersonStatics.generated.h"

/**
 * 
 */
UCLASS()
class RYTHM_API UPersonStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	// Calculate angle difference [-180, 180]
	UFUNCTION(BlueprintCallable, Category= "Math")
	static float FindDeltaAngleDegrees(float A1, float A2);

	// Find the angle between two points
	UFUNCTION(BlueprintPure, Category= "Math|Rotator")
	static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle); 
	
};
