// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CustomDetailsSettings.generated.h"

/*
*
*/
UCLASS(BlueprintType, config = EditorPerProjectUserSettings)
class UCustomDetailsSettings : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, category = "Transform")
	FRotator Rotation;

	UPROPERTY(EditAnywhere, category = "Static Mesh")
	UStaticMesh* StaticMesh;

	UPROPERTY(EditAnywhere, category = "Materials")
	UMaterial* Element0;
};
