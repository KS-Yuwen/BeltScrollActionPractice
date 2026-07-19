// Copyright Epic Games, Inc. All Rights Reserved.

#include "Gameplay/BeltScrollActionStageBounds.h"

#include "Components/BoxComponent.h"
#include "Components/SceneComponent.h"

ABeltScrollActionStageBounds::ABeltScrollActionStageBounds()
{
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	LeftWall = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftWall"));
	RightWall = CreateDefaultSubobject<UBoxComponent>(TEXT("RightWall"));
	FrontWall = CreateDefaultSubobject<UBoxComponent>(TEXT("FrontWall"));
	BackWall = CreateDefaultSubobject<UBoxComponent>(TEXT("BackWall"));

	for (UBoxComponent* Wall : { LeftWall, RightWall, FrontWall, BackWall })
	{
		Wall->SetupAttachment(SceneRoot);
		Wall->SetCollisionProfileName(TEXT("BlockAll"));
		Wall->SetGenerateOverlapEvents(false);
		Wall->SetHiddenInGame(true);
	}

	UpdateWallTransforms();
}

void ABeltScrollActionStageBounds::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	UpdateWallTransforms();
}

void ABeltScrollActionStageBounds::UpdateWallTransforms()
{
	const float HalfWidth = Width * 0.5f;
	const float HalfDepth = Depth * 0.5f;
	const float HalfHeight = WallHeight * 0.5f;
	const float HalfThickness = WallThickness * 0.5f;

	LeftWall->SetRelativeLocation(FVector(-HalfWidth - HalfThickness, 0.0f, HalfHeight));
	LeftWall->SetBoxExtent(FVector(HalfThickness, HalfDepth + WallThickness, HalfHeight));

	RightWall->SetRelativeLocation(FVector(HalfWidth + HalfThickness, 0.0f, HalfHeight));
	RightWall->SetBoxExtent(FVector(HalfThickness, HalfDepth + WallThickness, HalfHeight));

	FrontWall->SetRelativeLocation(FVector(0.0f, -HalfDepth - HalfThickness, HalfHeight));
	FrontWall->SetBoxExtent(FVector(HalfWidth + WallThickness, HalfThickness, HalfHeight));

	BackWall->SetRelativeLocation(FVector(0.0f, HalfDepth + HalfThickness, HalfHeight));
	BackWall->SetBoxExtent(FVector(HalfWidth + WallThickness, HalfThickness, HalfHeight));
}
