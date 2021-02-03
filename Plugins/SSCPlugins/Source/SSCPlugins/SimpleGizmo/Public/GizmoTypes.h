// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GizmoTypes.generated.h"

UENUM(BlueprintType)
enum class  EGizmoState : uint8
{
	None  =0,
	Translate ,
	Rotator,
	Scale,
};

UENUM(BlueprintType)
enum class  EGizmoSpace : uint8
{
	None =0 ,
	Local,
	World,
};

UENUM(BlueprintType)
enum class EGizmoTransformDomain : uint8
{
	None = 0,
	X_Axis,
	Y_Axis,
	Z_Axis,
	
	XY_Plane,
	XZ_Plane,
	YZ_Plane,
	
	XYZ,

};


UENUM(BlueprintType)
enum class ESimpleGizmoAxis : uint8
{
	ESGA_X,
	ESGA_Y,
	ESGA_Z,

	ESGA_None
};


UENUM(BlueprintType)
enum EItemAxisMoveMode
{
	EIMM_None = 0,
	EIMM_X = 1,
	EIMM_Y = 2,
	EIMM_XY = 3,
	EIMM_Z = 4,
	EIMM_XZ = 5,
	EIMM_YZ = 6,
	EIMM_XYZ = 7,
};





UENUM(BlueprintType)
enum class ETransformationType : uint8
{
	TT_NoTransform			UMETA(DisplayName = "None"),
	TT_Translation			UMETA(DisplayName = "Translation"),
	TT_Rotation				UMETA(DisplayName = "Rotation"),
	TT_Scale				UMETA(DisplayName = "Scale")
};

UENUM(BlueprintType)
enum class ESpaceType : uint8
{
	ST_None				UMETA(DisplayName = "None"),
	ST_Local			UMETA(DisplayName = "Local Space"),
	ST_World			UMETA(DisplayName = "World Space"),
};

UENUM(BlueprintType)
enum class ETransformationDomain : uint8
{
	TD_None				UMETA(DisplayName = "None"),

	TD_X_Axis			UMETA(DisplayName = "X Axis"),
	TD_Y_Axis			UMETA(DisplayName = "Y Axis"),
	TD_Z_Axis			UMETA(DisplayName = "Z Axis"),

	TD_XY_Plane			UMETA(DisplayName = "XY Plane"),
	TD_YZ_Plane			UMETA(DisplayName = "YZ Plane"),
	TD_XZ_Plane			UMETA(DisplayName = "XZ Plane"),

	TD_XYZ				UMETA(DisplayName = "XYZ"),

};



UCLASS()
class SSCPLUGINS_API UGizmoTypes : public UObject
{
	GENERATED_BODY()
	
};
