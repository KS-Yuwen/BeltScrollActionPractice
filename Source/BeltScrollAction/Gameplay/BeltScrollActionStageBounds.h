// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BeltScrollActionStageBounds.generated.h"

class UBoxComponent;
class USceneComponent;

/**
 * Invisible collision walls for a belt-scroll stage.
 * Place one actor in a level and adjust its size in the Details panel.
 */
UCLASS()
class BELTSCROLLACTION_API ABeltScrollActionStageBounds : public AActor
{
	GENERATED_BODY()

public:
	ABeltScrollActionStageBounds();

	virtual void OnConstruction(const FTransform& Transform) override;

protected:
	/** Root used as the center of the playable area. */
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<USceneComponent> SceneRoot;

	/** Left and right walls, which prevent movement along the X axis. */
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> LeftWall;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> RightWall;

	/** Front and back walls, which prevent movement along the Y axis. */
	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> FrontWall;

	UPROPERTY(VisibleAnywhere, Category="Components")
	TObjectPtr<UBoxComponent> BackWall;

	/** Total playable width along the world X axis. */
	UPROPERTY(EditAnywhere, Category="Stage Bounds", meta=(ClampMin="100.0", Units="cm"))
	float Width = 4000.0f;

	/** Total playable depth along the world Y axis. */
	UPROPERTY(EditAnywhere, Category="Stage Bounds", meta=(ClampMin="100.0", Units="cm"))
	float Depth = 1200.0f;

	/** Height of each invisible wall. */
	UPROPERTY(EditAnywhere, Category="Stage Bounds", meta=(ClampMin="100.0", Units="cm"))
	float WallHeight = 600.0f;

	/** Thickness of each invisible wall. */
	UPROPERTY(EditAnywhere, Category="Stage Bounds", meta=(ClampMin="10.0", Units="cm"))
	float WallThickness = 50.0f;

private:
	void UpdateWallTransforms();
};
