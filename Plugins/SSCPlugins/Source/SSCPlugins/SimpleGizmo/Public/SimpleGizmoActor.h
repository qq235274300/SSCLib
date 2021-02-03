// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GizmoTypes.h"
#include "GameFramework/PlayerController.h"
#include "SimpleGizmoActor.generated.h"


#define ECC_TraceGizmo_Channel ECC_GameTraceChannel2

class UProceduralMeshComponent;
class UMeshComponent;
class AController;
class UPrimitiveComponent;
class USceneComponent;
class UStaticMeshComponent;

struct FSimpleGizmoRenderAxisParameters
{
	float AxisLength;
	float HalfHeight;
	float CylinderRadius;
	FVector Offset;

	float ConeHeadOffset;
	FVector ConeRootPos;

	float Angle;
};



UCLASS(BlueprintType, Blueprintable)
class SSCPLUGINS_API ASimpleGizmoActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASimpleGizmoActor();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

public:
	/**************SetGet BullShit*****************************/
	UFUNCTION(BlueprintCallable, Category = "SimpleGizmo")
	void SetController(APlayerController* NewController);
	void SetAxisPoistions(const FVector& Origin);
	ESimpleGizmoAxis SetCurrentAxisByComponent( UPrimitiveComponent* TouchedComponent);
	ESimpleGizmoAxis GetAxisByComponent( UPrimitiveComponent* TouchedComponent);
	UFUNCTION(BlueprintCallable, Category = "SimpleGizmo")
		void SetCurrentAxis(ESimpleGizmoAxis Axis);
	ESimpleGizmoAxis GetCurrentAxis() const { return CurrentAxis; }
	void SetHighlightAxis(ESimpleGizmoAxis Axis);
	UFUNCTION(BlueprintCallable, Category = "SimpleGizmo")
	void BindActor(AActor* Actor);
	AActor* GetBindedActor() const { return BindedActor.Get(); }
	void ResetStates();


	/***************************************************************/

	/*void StartDrag(const FVector2D& InMousePosition);

	void PrepareStartDragMovement();

	void StopDrag(const FVector2D& InMousePosition);

	bool IsDragStarted() const { return bDragStarted; }

	void OnMousePosition(const FVector2D& InMousePosition);

	void SetGizmoVisible(bool bVisible);

	bool GetGizmoVisible() const { return !bHidden; }

	ESimpleGizmoAxis GetCurrentLockedDir() { return CurrentLockedAxis; }
*/
//protected:
//	void Render_Axis(class FCustomCanvas* Canvas, ESimpleGizmoAxis InAxis, FMatrix& InMatrix, FMatrix& InViewProjection, const FLinearColor& InColor, FVector2D& OutAxisDir, const FVector& InScale, bool bCubeHead);
//
//	void Build_AxisCollision(ESimpleGizmoAxis InAxis, const FSimpleGizmoRenderAxisParameters& AxisParameters, FMatrix& InCylinderMatrix, FMatrix& InArrowMatrix, bool bCubeHead);
//
	void RenderDistanceLine();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		USceneComponent* ComponentRoot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UStaticMeshComponent* XAxisMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UStaticMeshComponent* YAxisMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UStaticMeshComponent* ZAxisMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UProceduralMeshComponent* XAxisProceduralMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UProceduralMeshComponent* YAxisProceduralMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		UProceduralMeshComponent* ZAxisProceduralMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Transient)
		TArray<UMeshComponent*> AxisComponents;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TArray<FLinearColor> ArrowOriginalColors;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FLinearColor ArrowHiglightColor;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
		TWeakObjectPtr<APlayerController> CurrentController;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Transient)
		TWeakObjectPtr<AActor> BindedActor;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ESimpleGizmoAxis CurrentAxis;

	ESimpleGizmoAxis HighlightAxis;

	//����shift�������ķ�����
	ESimpleGizmoAxis CurrentLockedAxis;

	UPROPERTY()
		bool bDragStarted;

	UPROPERTY()
		float UniformScale;

	UPROPERTY()
		FVector2D PrevMousePosition;

	UPROPERTY()
		FVector2D MousePosition;

	UPROPERTY()
		FVector2D StartDragMousePosition;

	UPROPERTY()
		FVector StartDragActorPosition;

	UPROPERTY()
		FVector SavedBindedActorBoundsOrign;

	UPROPERTY()
		FPlane MovementPlane;

	UPROPERTY()
		FVector MovementDirVector;

	FVector DragStartPlanePosition;

protected:
	FVector DistanceLineOrigin;

	UPROPERTY()
		TArray<FVector> DistanceLineData;

	UPROPERTY()
		TArray<float> DistanceLineDistData;
public:
	UPROPERTY()
		TArray<float> DistanceLineAlldata;


	bool DoWorking =false;
	//void MeasureObjectDistance();

	/*UPROPERTY()
		TMap<int, class AVRProductItem*> MeasureObjectAActor;
	bool  BiItemGroupMove = false;*/

};
