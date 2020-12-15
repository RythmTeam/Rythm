// Fill out your copyright notice in the Description page of Project Settings.


#include "Person.h"
#include "PersonStatics.h"

float UPersonStatics::FindDeltaAngleDegrees(float A1, float A2)
{
	float Delta = A1 - A2;

	if (Delta > 180.0f)
	{
		Delta = Delta - 360.0f;
	}
	else if (Delta < -180.0)
	{
		Delta = Delta + 360.0f;
	}
	return Delta;
}

bool UPersonStatics::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	FVector2D Normal = (Target - Start).GetSafeNormal();
	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}
	return false;
}
