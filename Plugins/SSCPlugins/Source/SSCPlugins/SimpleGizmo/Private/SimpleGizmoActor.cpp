
#include "SimpleGizmoActor.h"

#include "ProceduralMeshComponent.h"

#include "RHIStaticStates.h"
#include "DynamicMeshBuilder.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/Engine.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/Canvas.h"
#include "Runtime/Engine/Classes/GameFramework/HUD.h"
#include "DrawDebugHelpers.h"


static const float AXIS_LENGTH = 35.0f;
static const float AXIS_SIZERATIO = 1.5f;


static 	void DrawDashedLine(UWorld* World, const FVector& Start, const FVector& End, const FColor& Color, float DashSize)
{
	FVector LineDir = End - Start;
	float LineLeft = (End - Start).Size();
	if (LineLeft)
	{
		LineDir /= LineLeft;
	}

	//const int32 nLines = FMath::CeilToInt(LineLeft / (DashSize * 2));
	//PDI->AddReserveLines(DepthPriority, nLines, DepthBias != 0);

	const FVector Dash = (DashSize * LineDir);

	FVector DrawStart = Start;
	while (LineLeft > DashSize)
	{
		const FVector DrawEnd = DrawStart + Dash;

		// PDI->DrawLine(DrawStart, DrawEnd, Color, DepthPriority, 0.0f, DepthBias);
		DrawDebugLine(World, DrawStart, DrawEnd, Color, false, -1.0f, 0, 1.1);

		LineLeft -= 2 * DashSize;
		DrawStart = DrawEnd + Dash;
	}
	if (LineLeft > 0.0f)
	{
		const FVector DrawEnd = End;

		// PDI->DrawLine(DrawStart, DrawEnd, Color, DepthPriority, 0.0f, DepthBias);
		DrawDebugLine(World, DrawStart, DrawEnd, Color, false, -1.0f, 0, 1.1);
	}

}

//static void BuildCylinderVerts1(const FVector& Base, const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, float Radius, float HalfHeight, int32 Sides, TArray<FDynamicMeshVertex>& OutVerts, TArray<int32>& OutIndices)
//{
//	const float	AngleDelta = 2.0f * PI / Sides;
//	FVector	LastVertex = Base + XAxis * Radius;
//
//	FVector2D TC = FVector2D(0.0f, 0.0f);
//	float TCStep = 1.0f / Sides;
//
//	FVector TopOffset = HalfHeight * ZAxis;
//
//	int32 BaseVertIndex = OutVerts.Num();
//
//	//Compute vertices for base circle.
//	for (int32 SideIndex = 0; SideIndex < Sides; SideIndex++)
//	{
//		const FVector Vertex = Base + (XAxis * FMath::Cos(AngleDelta * (SideIndex + 1)) + YAxis * FMath::Sin(AngleDelta * (SideIndex + 1))) * Radius;
//		FVector Normal = Vertex - Base;
//		Normal.Normalize();
//
//		FDynamicMeshVertex MeshVertex;
//
//		MeshVertex.Position = Vertex - TopOffset;
//		MeshVertex.TextureCoordinate = TC;
//
//		MeshVertex.SetTangents(
//			-ZAxis,
//			(-ZAxis) ^ Normal,
//			Normal
//		);
//
//		OutVerts.Add(MeshVertex); //Add bottom vertex
//
//		LastVertex = Vertex;
//		TC.X += TCStep;
//	}
//
//	LastVertex = Base + XAxis * Radius;
//	TC = FVector2D(0.0f, 1.0f);
//
//	//Compute vertices for the top circle
//	for (int32 SideIndex = 0; SideIndex < Sides; SideIndex++)
//	{
//		const FVector Vertex = Base + (XAxis * FMath::Cos(AngleDelta * (SideIndex + 1)) + YAxis * FMath::Sin(AngleDelta * (SideIndex + 1))) * Radius;
//		FVector Normal = Vertex - Base;
//		Normal.Normalize();
//
//		FDynamicMeshVertex MeshVertex;
//
//		MeshVertex.Position = Vertex + TopOffset;
//		MeshVertex.TextureCoordinate = TC;
//
//		MeshVertex.SetTangents(
//			-ZAxis,
//			(-ZAxis) ^ Normal,
//			Normal
//		);
//
//		OutVerts.Add(MeshVertex); //Add top vertex
//
//		LastVertex = Vertex;
//		TC.X += TCStep;
//	}
//
//	//Add top/bottom triangles, in the style of a fan.
//	//Note if we wanted nice rendering of the caps then we need to duplicate the vertices and modify
//	//texture/tangent coordinates.
//	for (int32 SideIndex = 1; SideIndex < Sides; SideIndex++)
//	{
//		int32 V0 = BaseVertIndex;
//		int32 V1 = BaseVertIndex + SideIndex;
//		int32 V2 = BaseVertIndex + ((SideIndex + 1) % Sides);
//
//		//bottom
//		OutIndices.Add(V0);
//		OutIndices.Add(V1);
//		OutIndices.Add(V2);
//
//		// top
//		OutIndices.Add(Sides + V2);
//		OutIndices.Add(Sides + V1);
//		OutIndices.Add(Sides + V0);
//	}
//
//	//Add sides.
//
//	for (int32 SideIndex = 0; SideIndex < Sides; SideIndex++)
//	{
//		int32 V0 = BaseVertIndex + SideIndex;
//		int32 V1 = BaseVertIndex + ((SideIndex + 1) % Sides);
//		int32 V2 = V0 + Sides;
//		int32 V3 = V1 + Sides;
//
//		OutIndices.Add(V0);
//		OutIndices.Add(V2);
//		OutIndices.Add(V1);
//
//		OutIndices.Add(V2);
//		OutIndices.Add(V3);
//		OutIndices.Add(V1);
//	}
//
//}
//
//static FVector CalcConeVert(float Angle1, float Angle2, float AzimuthAngle)
//{
//	float ang1 = FMath::Clamp<float>(Angle1, 0.01f, (float)PI - 0.01f);
//	float ang2 = FMath::Clamp<float>(Angle2, 0.01f, (float)PI - 0.01f);
//
//	float sinX_2 = FMath::Sin(0.5f * ang1);
//	float sinY_2 = FMath::Sin(0.5f * ang2);
//
//	float sinSqX_2 = sinX_2 * sinX_2;
//	float sinSqY_2 = sinY_2 * sinY_2;
//
//	float tanX_2 = FMath::Tan(0.5f * ang1);
//	float tanY_2 = FMath::Tan(0.5f * ang2);
//
//
//	float phi = FMath::Atan2(FMath::Sin(AzimuthAngle)*sinY_2, FMath::Cos(AzimuthAngle)*sinX_2);
//	float sinPhi = FMath::Sin(phi);
//	float cosPhi = FMath::Cos(phi);
//	float sinSqPhi = sinPhi * sinPhi;
//	float cosSqPhi = cosPhi * cosPhi;
//
//	float rSq, r, Sqr, alpha, beta;
//
//	rSq = sinSqX_2 * sinSqY_2 / (sinSqX_2*sinSqPhi + sinSqY_2 * cosSqPhi);
//	r = FMath::Sqrt(rSq);
//	Sqr = FMath::Sqrt(1 - rSq);
//	alpha = r * cosPhi;
//	beta = r * sinPhi;
//
//	FVector ConeVert;
//
//	ConeVert.X = (1 - 2 * rSq);
//	ConeVert.Y = 2 * Sqr*alpha;
//	ConeVert.Z = 2 * Sqr*beta;
//
//	return ConeVert;
//}
//
//void BuildConeVerts1(float Angle1, float Angle2, float Scale, float XOffset, int32 NumSides, TArray<FDynamicMeshVertex>& OutVerts, TArray<int32>& OutIndices)
//{
//	TArray<FVector> ConeVerts;
//	ConeVerts.AddUninitialized(NumSides);
//
//	for (int32 i = 0; i < NumSides; i++)
//	{
//		float Fraction = (float)i / (float)(NumSides);
//		float Azi = 2.f*PI*Fraction;
//		ConeVerts[i] = (CalcConeVert(Angle1, Angle2, Azi) * Scale) + FVector(XOffset, 0, 0);
//	}
//
//	for (int32 i = 0; i < NumSides; i++)
//	{
//		// Normal of the current face 
//		FVector TriTangentZ = ConeVerts[(i + 1) % NumSides] ^ ConeVerts[i]; // aka triangle normal
//		FVector TriTangentY = ConeVerts[i];
//		FVector TriTangentX = TriTangentZ ^ TriTangentY;
//
//
//		FDynamicMeshVertex V0, V1, V2;
//
//		V0.Position = FVector(0) + FVector(XOffset, 0, 0);
//		V0.TextureCoordinate.X = 0.0f;
//		V0.TextureCoordinate.Y = (float)i / NumSides;
//		V0.SetTangents(TriTangentX, TriTangentY, FVector(-1, 0, 0));
//		int32 I0 = OutVerts.Add(V0);
//
//		V1.Position = ConeVerts[i];
//		V1.TextureCoordinate.X = 1.0f;
//		V1.TextureCoordinate.Y = (float)i / NumSides;
//		FVector TriTangentZPrev = ConeVerts[i] ^ ConeVerts[i == 0 ? NumSides - 1 : i - 1]; // Normal of the previous face connected to this face
//		V1.SetTangents(TriTangentX, TriTangentY, (TriTangentZPrev + TriTangentZ).GetSafeNormal());
//		int32 I1 = OutVerts.Add(V1);
//
//		V2.Position = ConeVerts[(i + 1) % NumSides];
//		V2.TextureCoordinate.X = 1.0f;
//		V2.TextureCoordinate.Y = (float)((i + 1) % NumSides) / NumSides;
//		FVector TriTangentZNext = ConeVerts[(i + 2) % NumSides] ^ ConeVerts[(i + 1) % NumSides]; // Normal of the next face connected to this face
//		V2.SetTangents(TriTangentX, TriTangentY, (TriTangentZNext + TriTangentZ).GetSafeNormal());
//		int32 I2 = OutVerts.Add(V2);
//
//		// Flip winding for negative scale
//		if (Scale >= 0.f)
//		{
//			OutIndices.Add(I0);
//			OutIndices.Add(I1);
//			OutIndices.Add(I2);
//		}
//		else
//		{
//			OutIndices.Add(I0);
//			OutIndices.Add(I2);
//			OutIndices.Add(I1);
//		}
//	}
//}
//
//static void DrawCylinder(FCustomCanvas* Canvas, const FMatrix& CylToWorld, const FVector& Base, const FVector& XAxis, const FVector& YAxis, const FVector& ZAxis, float Radius, float HalfHeight, int32 Sides, FLinearColor InColor)
//{
//	TArray<FDynamicMeshVertex> Vertices;
//	TArray<int32> Indices;
//
//	BuildCylinderVerts1(Base, XAxis, YAxis, ZAxis, Radius, HalfHeight, Sides, Vertices, Indices);
//
//	FCustomCanvasBatchRenderItem* BatchRenderItem = new FCustomCanvasBatchRenderItem(nullptr, nullptr, SE_BLEND_MAX, FCanvas::ET_Triangle, CylToWorld, FDepthFieldGlowInfo());
//	Canvas->AddRenderItem(BatchRenderItem);
//	FBatchedElements* TriangleBatcher = BatchRenderItem->GetBatchedElements();
//
//	for (int32 i = 0; i < Vertices.Num(); ++i)
//	{
//		TriangleBatcher->AddVertex(Vertices[i].Position, Vertices[i].TextureCoordinate, InColor, FHitProxyId());
//	}
//
//	for (int32 i = 0; i < Indices.Num() - 3; i += 3)
//	{
//		TriangleBatcher->AddTriangle(Indices[i + 0], Indices[i + 1], Indices[i + 2], GWhiteTexture, SE_BLEND_Opaque);
//	}
//}
//
//void DrawCone(FCustomCanvas* Canvas, const FMatrix& ConeToWorld, float Angle1, float Angle2, int32 NumSides, const FLinearColor& InColor)
//{
//	TArray<FDynamicMeshVertex> Vertices;
//	TArray<int32> Indices;
//
//	BuildConeVerts1(Angle1, Angle2, 1.0f, 0.0f, NumSides, Vertices, Indices);
//
//	FCustomCanvasBatchRenderItem* BatchRenderItem = new FCustomCanvasBatchRenderItem(nullptr, nullptr, SE_BLEND_MAX, FCanvas::ET_Triangle, ConeToWorld, FDepthFieldGlowInfo());
//	Canvas->AddRenderItem(BatchRenderItem);
//	FBatchedElements* TriangleBatcher = BatchRenderItem->GetBatchedElements();
//
//	for (int32 i = 0; i < Vertices.Num(); ++i)
//	{
//		TriangleBatcher->AddVertex(Vertices[i].Position, Vertices[i].TextureCoordinate, InColor, FHitProxyId());
//	}
//
//	for (int32 i = 0; i < Indices.Num() - 3; i += 3)
//	{
//		TriangleBatcher->AddTriangle(Indices[i + 0], Indices[i + 1], Indices[i + 2], GWhiteTexture, SE_BLEND_Opaque);
//	}
//}

ASimpleGizmoActor::ASimpleGizmoActor()
{
	ComponentRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(ComponentRoot);
	ComponentRoot->SetMobility(EComponentMobility::Movable);

	XAxisMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("XAxisMeshComponent"));
	YAxisMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("YAxisMeshComponent"));
	ZAxisMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZAxisMeshComponent"));

	XAxisProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("XAxisProceduralMeshComponent"));
	YAxisProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("YAxisProceduralMeshComponent"));
	ZAxisProceduralMeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("ZAxisProceduralMeshComponent"));

	XAxisProceduralMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);
	YAxisProceduralMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);
	ZAxisProceduralMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);

	XAxisMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);
	YAxisMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);
	ZAxisMeshComponent->AttachToComponent(ComponentRoot, FAttachmentTransformRules::KeepRelativeTransform);

	XAxisMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));
	YAxisMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));
	ZAxisMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));

	XAxisProceduralMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));
	YAxisProceduralMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));
	ZAxisProceduralMeshComponent->SetCollisionProfileName(TEXT("Gizmo"));

	XAxisMeshComponent->bRenderInMainPass = true;
	YAxisMeshComponent->bRenderInMainPass = true;
	ZAxisMeshComponent->bRenderInMainPass = true;

	XAxisMeshComponent->CastShadow = false;
	YAxisMeshComponent->CastShadow = false;
	ZAxisMeshComponent->CastShadow = false;

	//XAxisMeshComponent->bRenderCustomDepth = true;
	XAxisMeshComponent->CustomDepthStencilValue = 1;

	//YAxisMeshComponent->bRenderCustomDepth = true;
	YAxisMeshComponent->CustomDepthStencilValue = 2;

	//ZAxisMeshComponent->bRenderCustomDepth = true;
	ZAxisMeshComponent->CustomDepthStencilValue = 3;

	ConstructorHelpers::FObjectFinder<UStaticMesh> XMeshFinder(TEXT("StaticMesh'/SSCPlugins/BP/SimpleGizmo/GizmoMeshes/SM_TranslationArrow.SM_TranslationArrow'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> YMeshFinder(TEXT("StaticMesh'/SSCPlugins/BP/SimpleGizmo/GizmoMeshes/SM_TranslationArrow.SM_TranslationArrow'"));
	ConstructorHelpers::FObjectFinder<UStaticMesh> ZMeshFinder(TEXT("StaticMesh'/SSCPlugins/BP/SimpleGizmo/GizmoMeshes/SM_TranslationArrow.SM_TranslationArrow'"));

	if (XMeshFinder.Succeeded())
	{
		XAxisMeshComponent->SetStaticMesh(XMeshFinder.Object);
	}
	if (YMeshFinder.Succeeded())
	{
		YAxisMeshComponent->SetStaticMesh(YMeshFinder.Object);
	}
	if (ZMeshFinder.Succeeded())
	{
		ZAxisMeshComponent->SetStaticMesh(ZMeshFinder.Object);
	}

	CurrentAxis = ESimpleGizmoAxis::ESGA_None;
	HighlightAxis = ESimpleGizmoAxis::ESGA_None;
	CurrentLockedAxis = ESimpleGizmoAxis::ESGA_None;

	ArrowOriginalColors.Add(FColor(63, 173, 155));
	ArrowOriginalColors.Add(FColor(124, 168, 43));
	ArrowOriginalColors.Add(FColor(161, 57, 98));
	ArrowHiglightColor = FLinearColor::Yellow;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	bDragStarted = false;

	UniformScale = 1.0f;
}

void ASimpleGizmoActor::BeginPlay()
{
	Super::BeginPlay();

	AxisComponents.Add(XAxisMeshComponent);
	AxisComponents.Add(YAxisMeshComponent);
	AxisComponents.Add(ZAxisMeshComponent);
}

void ASimpleGizmoActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsHidden())
		return;

	if (BindedActor.IsValid() && GetWorld() && DoWorking)
	{
		FVector Origin, BoxExtent;
		//BindedActor->GetActorBounds(true, Origin, BoxExtent);
		Origin = BindedActor->GetActorLocation();
		if (Origin != SavedBindedActorBoundsOrign)
			SetAxisPoistions(Origin);

		

		UniformScale = 1.0f;
		ULocalPlayer* const LP = CurrentController->GetLocalPlayer();
		if (LP && LP->ViewportClient)
		{
			// get the projection data
			FSceneViewProjectionData ProjectionData;
			FIntPoint ViewportSize = LP->ViewportClient->Viewport->GetSizeXY();
			if (LP->GetProjectionData(LP->ViewportClient->Viewport, eSSP_FULL, /*out*/ ProjectionData))
			{
				FMatrix const ProjectionMatrix = ProjectionData.ProjectionMatrix;
				FMatrix const InViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();
				FVector4 ProjectedOrg = InViewProjectionMatrix.TransformFVector4(FVector4(Origin, 1.0f));
				UniformScale = ProjectedOrg.W * (4.0f / ViewportSize.X / ProjectionMatrix.M[0][0]);
			}
		}

		//const float VideoWidth = 1280;

		//FDisplayMetrics DisplayMetrics;
		//FDisplayMetrics::GetDisplayMetrics(DisplayMetrics);

		//UniformScale *= DisplayMetrics.PrimaryDisplayWidth / VideoWidth;
		UniformScale *= 1.6*AXIS_SIZERATIO;

		FVector Scale(UniformScale, UniformScale, UniformScale);
		for (int32 i = 0; i < AxisComponents.Num(); ++i)
		{
			AxisComponents[i]->SetRelativeScale3D(Scale);
		}

		SavedBindedActorBoundsOrign = Origin;

		RenderDistanceLine();
	}
}


void ASimpleGizmoActor::SetController(APlayerController* NewController)
{
	CurrentController = NewController;
	DoWorking = true;
}

void ASimpleGizmoActor::SetAxisPoistions(const FVector& InOrigin)
{
	SetActorLocation(InOrigin);
}

ESimpleGizmoAxis ASimpleGizmoActor::SetCurrentAxisByComponent( UPrimitiveComponent* TouchedComponent)
{
	ESimpleGizmoAxis Axis = GetAxisByComponent(TouchedComponent);
	SetCurrentAxis(Axis);

	return Axis;
}

ESimpleGizmoAxis ASimpleGizmoActor::GetAxisByComponent(UPrimitiveComponent* TouchedComponent)
{
	ESimpleGizmoAxis Axis = ESimpleGizmoAxis::ESGA_None;

	if (TouchedComponent == XAxisMeshComponent)
	{
		Axis = ESimpleGizmoAxis::ESGA_X;
	}
	else if (TouchedComponent == YAxisMeshComponent)
	{
		Axis = ESimpleGizmoAxis::ESGA_Y;
	}
	else if (TouchedComponent == ZAxisMeshComponent)
	{
		Axis = ESimpleGizmoAxis::ESGA_Z;
	}
	else
	{
		Axis = ESimpleGizmoAxis::ESGA_None;
	}

	return Axis;
}

void ASimpleGizmoActor::SetCurrentAxis(ESimpleGizmoAxis Axis)
{
	if (Axis != CurrentAxis)
	{
		//SetHighlightAxis(Axis, CurrentAxis);
		CurrentAxis = Axis;
	}
}

void ASimpleGizmoActor::SetHighlightAxis(ESimpleGizmoAxis Axis)
{
	for (int32 i = 0; i < AxisComponents.Num(); ++i)
	{
		AxisComponents[i]->SetCustomDepthStencilValue(i + 1);
	}
	if (Axis <= ESimpleGizmoAxis::ESGA_Z)
	{
		AxisComponents[(int32)Axis]->SetCustomDepthStencilValue(4);
	}

	HighlightAxis = Axis;
}

void ASimpleGizmoActor::BindActor(class AActor* Actor)
{
	BindedActor = Actor;
}

void ASimpleGizmoActor::ResetStates()
{
	SetCurrentAxis(ESimpleGizmoAxis::ESGA_None);
	SetHighlightAxis(ESimpleGizmoAxis::ESGA_None);
	bDragStarted = false;
	BindedActor = nullptr;
}


//FORCEINLINE static FLinearColor GetActuallyAxisColor(ESimpleGizmoAxis InAxis, ESimpleGizmoAxis HighlightAxis, const FLinearColor& OriginalColor, const FLinearColor& HighlightColor)
//{
//	if (InAxis == HighlightAxis)
//		return HighlightColor;
//
//	return OriginalColor;
//}
//
//void ASimpleGizmoActor::PostRenderFor(class APlayerController* PC, class UCanvas* Canvas, FVector CameraPosition, FVector CameraDir)
//{
//	if (bHidden)
//		return;
//
//	UFont* TextFont = GEngine->GetSmallFont();
//	TCHAR* AxisTexts[] = { TEXT("X"), TEXT("Y"), TEXT("Z") };
//	FVector AxisOffsets[] = { FVector(36, 0, 0), FVector(0, 36, 0), FVector(0, 0, 36) };
//
//	for (int32 i = 0; i < 3; ++i)
//	{
//		FVector TextWorldPosition = AxisComponents[i]->GetComponentLocation() + AxisOffsets[i] * UniformScale;
//		FVector2D TextScreenPosition;
//		if (UGameplayStatics::ProjectWorldToScreen(PC, TextWorldPosition, TextScreenPosition))
//		{
//			Canvas->SetLinearDrawColor(ArrowOriginalColors[i]);
//			FFontRenderInfo FontRenderInfo;
//			FontRenderInfo.bEnableShadow = true;
//			Canvas->DrawText(TextFont, AxisTexts[i], TextScreenPosition.X, TextScreenPosition.Y, 1.0f, 1.0f, FontRenderInfo);
//		}
//	}
//
//	ULocalPlayer* LP = VRController->GetLocalPlayer();
//	if (LP && LP->ViewportClient)
//	{
//		// get the projection data
//		FSceneViewProjectionData ProjectionData;
//		FIntPoint ViewportSize = LP->ViewportClient->Viewport->GetSizeXY();
//		if (LP->GetProjectionData(LP->ViewportClient->Viewport, eSSP_FULL, /*out*/ ProjectionData))
//		{
//			FMatrix const ProjectionMatrix = ProjectionData.ProjectionMatrix;
//			FMatrix InViewProjectionMatrix = ProjectionData.ComputeViewProjectionMatrix();
//			FVector4 ProjectedOrg = InViewProjectionMatrix.TransformFVector4(FVector4(SavedBindedActorBoundsOrign, 1.0f));
//			float TempUniformScale = ProjectedOrg.W * (4.0f / ViewportSize.X / ProjectionMatrix.M[0][0])*AXIS_SIZERATIO;
//
//			UGameViewportClient* GameViewportClient = LP->ViewportClient;
//			FViewport* Viewport = GameViewportClient->Viewport;
//			UWorld* ViewportWorld = GameViewportClient->GetWorld();
//			FCustomCanvas CustomCanvas(Viewport, NULL, ViewportWorld, ViewportWorld ? ViewportWorld->FeatureLevel : GMaxRHIFeatureLevel);
//			CustomCanvas.SetRenderTargetRect(FIntRect(0, 0, ViewportSize.X, ViewportSize.Y));
//
//			CustomCanvas.SetBaseTransform(InViewProjectionMatrix);
//
//			//const float VideoWidth = 1280;
//
//			//FDisplayMetrics DisplayMetrics;
//			//FDisplayMetrics::GetDisplayMetrics(DisplayMetrics);
//
//			//TempUniformScale *= DisplayMetrics.PrimaryDisplayWidth / VideoWidth;
//
//			FVector2D ScreenPos;
//			FTranslationMatrix ActorTranslateMatrix(SavedBindedActorBoundsOrign);
//
//			for (int32 i = 0; i <= static_cast<int32>(ESimpleGizmoAxis::ESGA_Z); ++i)
//			{
//				Render_Axis(&CustomCanvas, static_cast<ESimpleGizmoAxis>(i), ActorTranslateMatrix, InViewProjectionMatrix, GetActuallyAxisColor(static_cast<ESimpleGizmoAxis>(i), HighlightAxis, ArrowOriginalColors[i], ArrowHiglightColor), ScreenPos, FVector(TempUniformScale, TempUniformScale, TempUniformScale), false);
//			}
//
//			CustomCanvas.Flush_GameThread();
//		}
//	}
//}
//
void ASimpleGizmoActor::RenderDistanceLine()
{
	if (!BindedActor.IsValid())
		return;
	const static FVector AxisDirs[] =
	{
		FVector(1.0f, 0, 0),
		FVector(0, 1.0f, 0),
		FVector(0, 0, 1.0f),
		FVector(-1.0f, 0, 0),
		FVector(0, -1.0f, 0),
		FVector(0, 0, -1.0f),
	};
	const float StringPosAvoidMultiplier = 20;
	FVector Origin, Extent;
	BindedActor->GetActorBounds(false, Origin, Extent);

	if (DistanceLineOrigin != Origin)
	{
		DistanceLineOrigin = Origin;
		DistanceLineData.Empty();
		DistanceLineDistData.Empty();
		FCollisionQueryParams Param;
		Param.bTraceComplex = true;
		Param.AddIgnoredActor(BindedActor.Get());
		Param.AddIgnoredActor((AActor*)UGameplayStatics::GetPlayerCharacter(this, 0));

		TArray<AActor*> AttachedActors;
		BindedActor.Get()->GetAttachedActors(AttachedActors);
		Param.AddIgnoredActors(AttachedActors);

		float HitResultTraceDistance = 100000.f;
		FHitResult Hit;
		FVector BeginPos, EndPos, StringPos;

		int ArrayLen = sizeof(AxisDirs) / sizeof(FVector);
		for (int i = 0; i < ArrayLen; i++)
		{
			BeginPos = Origin + AxisDirs[i] * Extent;
			EndPos = Origin + AxisDirs[i] * HitResultTraceDistance;
			if (!GetWorld()->LineTraceSingleByChannel(Hit, BeginPos, EndPos, ECC_EngineTraceChannel6, Param))
				continue;

			StringPos = Origin + AxisDirs[i] * (Extent + StringPosAvoidMultiplier) * 2;

			DistanceLineData.Add(BeginPos);
			DistanceLineData.Add(Hit.Location);
			DistanceLineData.Add(StringPos);
			DistanceLineDistData.Add(FVector::Dist(BeginPos, Hit.Location));
		}
	}

	int ArrayLen = DistanceLineData.Num();
	for (int i = 0, j = 0; i < ArrayLen;)
	{
		DrawDashedLine(GetWorld(), DistanceLineData[i], DistanceLineData[i + 1], FColor::White, 6);

		/*if (VRController.IsValid())
			if (VRController->MyHUD)
				VRController->MyHUD->AddDebugText(
					*FString::Printf(TEXT("%.f CM"), DistanceLineDistData[j++]),
					GetWorld()->GetWorldSettings(),
					0.f,
					DistanceLineData[i + 2],
					DistanceLineData[i + 2],
					FColor::Green,
					true,
					true,
					false,
					nullptr,
					1.3f,
					true);*/
		//DrawDebugString(GetWorld(), DistanceLineData[i+2], *FString::Printf(TEXT("%.f CM"), DistanceLineDistData[j++]), nullptr, FColor::Green, 0.f, true);

		i += 3;
	}
}


//void ASimpleGizmoActor::StartDrag(const FVector2D& InMousePosition)
//{
//	if (bDragStarted)
//		return;
//
//	bDragStarted = true;
//	PrevMousePosition = InMousePosition;
//	MousePosition = InMousePosition;
//	StartDragMousePosition = InMousePosition;
//
//	StartDragActorPosition = BindedActor->GetActorLocation();
//
//	FVector BoxExtent;
//	SavedBindedActorBoundsOrign = BindedActor->GetActorLocation();
//
//	PrepareStartDragMovement();
//
//	////��ק��Ҫ��������ʾ����Ϊ��Щ�ط�����UMG���������ʱ���������inputmodeΪOnlyUI,����������ǿ����ʾ��������inputmode����Щ��  
//	//if (UVRGameInstance* t_gmins = Cast<UVRGameInstance>(GetWorld()->GetGameInstance()))
//	//{
//	//	FInputModeGameAndUI InputModeGameUI;
//	//	InputModeGameUI.SetHideCursorDuringCapture(false);
//	//	t_gmins->GetFirstLocalPlayerController()->SetInputMode(InputModeGameUI);
//	//}
//}

//void ASimpleGizmoActor::PrepareStartDragMovement()
//{
//	FVector FaceNormal;
//	FaceNormal = -UGameplayStatics::GetPlayerCameraManager(CurrentController.Get(), 0)->GetCameraRotation().Vector().GetUnsafeNormal();
//
//	FVector AxisDirs[] =
//	{
//		FVector(1.0f, 0, 0),
//		FVector(0, 1.0f, 0),
//		FVector(0, 0, 1.0f)
//	};
//
//	int32 AxisIndex = 0;
//	float MaxCosineValue = 0.0f;
//	int32 MaxIndex = 0;
//
//	TArray<FVector> CandidatePlaneNormal;
//
//	for (int32 i = 0; i < 3; ++i)
//	{
//		if (i != (int32)CurrentAxis)
//		{
//			CandidatePlaneNormal.Push(AxisDirs[i]);
//		}
//	}
//
//	for (AxisIndex = 0; AxisIndex < CandidatePlaneNormal.Num(); ++AxisIndex)
//	{
//		float CosineValue = FaceNormal | CandidatePlaneNormal[AxisIndex];
//		CosineValue = FMath::Abs(CosineValue);
//		if (CosineValue > MaxCosineValue)
//		{
//			MaxCosineValue = CosineValue;
//			MaxIndex = AxisIndex;
//		}
//	}
//
//	MovementPlane = FPlane(StartDragActorPosition, CandidatePlaneNormal[MaxIndex]);
//	MovementDirVector = AxisDirs[static_cast<int32>(CurrentAxis)];
//
//	float HitResultTraceDistance = 100000.f;
//
//	FVector WorldOrigin;
//	FVector WorldDirection;
//	if (UGameplayStatics::DeprojectScreenToWorld(CurrentController.Get(), StartDragMousePosition, WorldOrigin, WorldDirection))
//	{
//		DragStartPlanePosition = FMath::LinePlaneIntersection(WorldOrigin - WorldDirection * HitResultTraceDistance, WorldOrigin + WorldDirection * HitResultTraceDistance, MovementPlane);
//	}
//}
//
//void ASimpleGizmoActor::StopDrag(const FVector2D& InMousePosition)
//{
//	if (!bDragStarted)
//		return;
//
//	bDragStarted = false;
//	MousePosition = InMousePosition;
//
//	if (BindedActor.IsValid())
//	{
//		FVector NewActorPosition = BindedActor->GetActorLocation();
//		if (NewActorPosition != StartDragActorPosition)
//		{
//			//VRController->ItemOperateManager->VRItemsSystem->RecordMoveItem(Cast<AVRNewItem>(BindedActor.Get()), StartDragActorPosition);
//		}
//	}
//}
//
//void ASimpleGizmoActor::OnMousePosition(const FVector2D& InMousePosition)
//{
//	if (!bDragStarted)
//	{
//		FHitResult HitResult;
//
//
//		if (CurrentController->GetHitResultAtScreenPosition(InMousePosition, ECC_TraceGizmo_Channel, true, HitResult))
//		{
//			CurrentLockedAxis = GetAxisByComponent(HitResult.GetComponent());
//			SetHighlightAxis(CurrentLockedAxis);
//		}
//		else
//		{
//			if (!CurrentController->IsInputKeyDown(EKeys::LeftShift) && !CurrentController->IsInputKeyDown(EKeys::RightShift))
//			{
//				SetHighlightAxis(ESimpleGizmoAxis::ESGA_None);
//				CurrentLockedAxis = ESimpleGizmoAxis::ESGA_None;
//			}
//
//		}
//		return;
//	}
//
//	PrevMousePosition = MousePosition;
//	MousePosition = InMousePosition;
//
//	FVector2D DeltaMousePosition = MousePosition - PrevMousePosition;
//
//	if (DeltaMousePosition.Size() > 0.1)
//	{
//		{
//			float HitResultTraceDistance = 100000.f;
//
//			FVector HitPlanePosition;
//
//			FVector WorldOrigin;
//			FVector WorldDirection;
//			if (UGameplayStatics::DeprojectScreenToWorld(CurrentController.Get(), MousePosition, WorldOrigin, WorldDirection))
//			{
//				HitPlanePosition = FMath::LinePlaneIntersection(WorldOrigin - WorldDirection * HitResultTraceDistance, WorldOrigin + WorldDirection * HitResultTraceDistance, MovementPlane);
//
//				FVector PlaneDeltaPosition;
//				PlaneDeltaPosition = (HitPlanePosition - DragStartPlanePosition);
//				FVector ActuallyMoveDelta = MovementDirVector * (PlaneDeltaPosition | MovementDirVector);
//
//				if (BindedActor.IsValid())
//				{
//					if (VRController->IsInputKeyDown(EKeys::LeftShift) || VRController->IsInputKeyDown(EKeys::RightShift))
//					{
//						ActuallyMoveDelta = ActuallyMoveDelta / 10;
//					}
//					BindedActor->SetActorLocation(StartDragActorPosition + ActuallyMoveDelta);
//					//UNetModule::Get()->GetNetActorManager()->SendActorMove(BindedActor.Get());
//
//				}
//
//
//			}
//		}
//	}
//}
//
//void ASimpleGizmoActor::SetGizmoVisible(bool bVisible)
//{
//	SetActorHiddenInGame(!bVisible);
//	SetActorEnableCollision(bVisible);
//}
//
//void ASimpleGizmoActor::Render_Axis(class FCustomCanvas* Canvas, ESimpleGizmoAxis InAxis, FMatrix& InMatrix, FMatrix& InViewProjection, const FLinearColor& InColor, FVector2D& OutAxisDir, const FVector& InScale, bool bCubeHead)
//{
//	FSimpleGizmoRenderAxisParameters AxisParameters;
//
//	FMatrix AxisRotation = FMatrix::Identity;
//	if (InAxis == ESimpleGizmoAxis::ESGA_Y)
//	{
//		AxisRotation = FRotationMatrix::MakeFromXZ(FVector(0, 1, 0), FVector(0, 0, 1));
//	}
//	else if (InAxis == ESimpleGizmoAxis::ESGA_Z)
//	{
//		AxisRotation = FRotationMatrix::MakeFromXY(FVector(0, 0, 1), FVector(0, 1, 0));
//	}
//
//	FMatrix ArrowToWorld = AxisRotation * InMatrix;
//
//	// The scale that is passed in potentially leaves one component with a scale of 1, if that happens
//	// we need to extract the inform scale and use it to construct the scale that transforms the primitives
//	float TempUniformScale = InScale.GetMax() > 1.0f ? InScale.GetMax() : InScale.GetMin() < 1.0f ? InScale.GetMin() : 1.0f;
//	// After the primitives have been scaled and transformed, we apply this inverse scale that flattens the dimension
//	// that was scaled up to prevent it from intersecting with the near plane.  In perspective this won't have any effect,
//	// but in the ortho viewports it will prevent scaling in the direction of the camera and thus intersecting the near plane.
//	FVector FlattenScale = FVector(InScale.Component(0) == 1.0f ? 1.0f / TempUniformScale : 1.0f, InScale.Component(1) == 1.0f ? 1.0f / TempUniformScale : 1.0f, InScale.Component(2) == 1.0f ? 1.0f / TempUniformScale : 1.0f);
//
//	FScaleMatrix Scale(TempUniformScale);
//	ArrowToWorld = Scale * ArrowToWorld;
//
//	FMatrix CylinderWorldMatrix;
//	FMatrix ArrowWorldMatrix;
//
//	const float AxisLength = AXIS_LENGTH;
//	const float HalfHeight = AxisLength / 2.0f;
//	const float CylinderRadius = 1.2f;
//	const FVector Offset(0, 0, HalfHeight);
//
//	AxisParameters.AxisLength = AxisLength;
//	AxisParameters.HalfHeight = AxisLength / 2.0f;
//	AxisParameters.CylinderRadius = CylinderRadius;
//	AxisParameters.Offset = Offset;
//
//	switch (InAxis)
//	{
//	case ESimpleGizmoAxis::ESGA_X:
//	{
//		CylinderWorldMatrix = (Scale * FRotationMatrix(FRotator(-90, 0.f, 0)) * InMatrix) * FScaleMatrix(FlattenScale);
//
//		DrawCylinder(Canvas, CylinderWorldMatrix * InViewProjection, Offset, FVector(1, 0, 0), FVector(0, 1, 0), FVector(0, 0, 1), CylinderRadius, HalfHeight, 16, InColor);
//		break;
//	}
//	case ESimpleGizmoAxis::ESGA_Y:
//	{
//		CylinderWorldMatrix = (Scale * FRotationMatrix(FRotator(0, 0, 90)) * InMatrix)* FScaleMatrix(FlattenScale);
//
//		DrawCylinder(Canvas, CylinderWorldMatrix * InViewProjection, Offset, FVector(1, 0, 0), FVector(0, 1, 0), FVector(0, 0, 1), CylinderRadius, HalfHeight, 16, InColor);
//		break;
//	}
//	case ESimpleGizmoAxis::ESGA_Z:
//	{
//		CylinderWorldMatrix = (Scale * InMatrix) * FScaleMatrix(FlattenScale);
//
//		DrawCylinder(Canvas, CylinderWorldMatrix * InViewProjection, Offset, FVector(1, 0, 0), FVector(0, 1, 0), FVector(0, 0, 1), CylinderRadius, HalfHeight, 16, InColor);
//		break;
//	}
//	}
//
//	if (bCubeHead)
//	{
//		const float CubeHeadOffset = 3.0f;
//		FVector RootPos(AxisLength + CubeHeadOffset, 0, 0);
//
//		//Render_Cube(PDI, (FTranslationMatrix(RootPos) * ArrowToWorld) * FScaleMatrix(FlattenScale), InMaterial, FVector(4.0f));
//	}
//	else
//	{
//		const float ConeHeadOffset = 12.0f;
//		FVector RootPos(AxisLength + ConeHeadOffset, 0, 0);
//
//		float Angle = FMath::DegreesToRadians(PI * 5);
//
//
//		AxisParameters.ConeHeadOffset = ConeHeadOffset;
//		AxisParameters.ConeRootPos = RootPos;
//		AxisParameters.Angle = Angle;
//
//		DrawCone(Canvas, (FScaleMatrix(-13) * FTranslationMatrix(RootPos) * ArrowToWorld) * FScaleMatrix(FlattenScale) * InViewProjection, Angle, Angle, 32, InColor);
//	}
//
//	FVector2D AxisEnd;
//	//if (!View->ScreenToPixel(View->WorldToScreen(ArrowToWorld.TransformPosition(FVector(64, 0, 0))), AxisEnd))
//	{
//		AxisEnd.X = AxisEnd.Y = 0;
//	}
//
//	FVector2D Origin(0, 0);
//
//	OutAxisDir = (AxisEnd - Origin).GetSafeNormal();
//
//	//Build_AxisCollision(InAxis, AxisParameters, CylinderWorldMatrix, ArrowWorldMatrix, bCubeHead);
//}
//
//void ASimpleGizmoActor::Build_AxisCollision(ESimpleGizmoAxis InAxis, const FSimpleGizmoRenderAxisParameters& AxisParameters, FMatrix& InCylinderMatrix, FMatrix& InArrowMatrix, bool bCubeHead)
//{
//	if (InAxis >= ESimpleGizmoAxis::ESGA_None)
//		return;
//
//	const float AxisLength = AxisParameters.AxisLength;
//
//	const float HalfHeight = AxisParameters.HalfHeight;
//	const float CylinderRadius = AxisParameters.CylinderRadius;
//	const FVector Offset = AxisParameters.Offset;
//
//	const float ConeHeadOffset = AxisParameters.ConeHeadOffset;
//	FVector RootPos = AxisParameters.ConeRootPos;
//
//	float Angle = AxisParameters.Angle;
//
//	TArray<FDynamicMeshVertex> Vertices;
//	TArray<int32> Indices;
//
//	BuildCylinderVerts1(Offset, FVector::ForwardVector, FVector::RightVector, FVector::UpVector, CylinderRadius, HalfHeight, 16, Vertices, Indices);
//
//	for (int32 i = 0; i < Vertices.Num(); ++i)
//	{
//		Vertices[i].Position = InCylinderMatrix.TransformPosition(Vertices[i].Position);
//	}
//
//	int32 StartVert = Vertices.Num();
//	BuildConeVerts1(Angle, Angle, 1, 0, 32, Vertices, Indices);
//
//	//FRotationMatrix RotateCone(FRotator(90, 0, 0));
//
//	for (int32 i = StartVert; i < Vertices.Num(); ++i)
//	{
//		Vertices[i].Position = InArrowMatrix.TransformPosition(Vertices[i].Position);
//	}
//
//	TArray<FVector> MeshVertices;
//	for (int32 i = 0; i < Vertices.Num(); ++i)
//	{
//		MeshVertices.Add(Vertices[i].Position);
//	}
//
//	UProceduralMeshComponent* AxisProceduralMeshComponent = Cast<UProceduralMeshComponent>(AxisComponents[static_cast<int32>(InAxis)]);
//	if (AxisProceduralMeshComponent)
//	{
//		AxisProceduralMeshComponent->CreateMeshSection(0, MeshVertices, Indices, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), true);
//	}
//}
//
//void ASimpleGizmoActor::MeasureObjectDistance()
//{
//	if (!BindedActor.IsValid())
//		return;
//	if (BiItemGroupMove)
//		return;
//	const static FVector AxisDirs[] =
//	{
//		FVector(1.0f, 0, 0),
//		FVector(0, 1.0f, 0),
//		FVector(0, 0, 1.0f),
//		FVector(-1.0f, 0, 0),
//		FVector(0, -1.0f, 0),
//		FVector(0, 0, -1.0f),
//	};
//
//	FVector Origin, Extent;
//	BindedActor->GetActorBounds(false, Origin, Extent);
//
//	DistanceLineAlldata.Empty();
//	FCollisionQueryParams Param;
//	Param.bTraceAsyncScene = true;
//	Param.bTraceComplex = true;
//	Param.AddIgnoredActor(BindedActor.Get());
//	Param.AddIgnoredActor((AActor*)UGameplayStatics::GetPlayerCharacter(this, 0));
//
//	TArray<AActor*> AttachedActors;
//	BindedActor.Get()->GetAttachedActors(AttachedActors);
//	Param.AddIgnoredActors(AttachedActors);
//
//	float HitResultTraceDistance = 100000.f;
//	FHitResult Hit;
//	FVector BeginPos, EndPos;
//
//	int ArrayLen = sizeof(AxisDirs) / sizeof(FVector);
//	for (int i = 0; i < ArrayLen; i++)
//	{
//		BeginPos = Origin + AxisDirs[i] * Extent;
//		EndPos = Origin + AxisDirs[i] * HitResultTraceDistance;
//		if (!GetWorld()->LineTraceSingleByChannel(Hit, BeginPos, EndPos, ECC_EngineTraceChannel6, Param))
//		{
//			DistanceLineAlldata.Add(0);
//			continue;
//		}
//		DistanceLineAlldata.Add(FVector::Dist(BeginPos, Hit.Location));
//
//		if (FVector::Dist(BeginPos, Hit.Location) > 0 && FVector::Dist(BeginPos, Hit.Location) <= 15)
//		{
//			AVRProductItem* NearItem = nullptr;
//			NearItem = Cast<AVRProductItem>(Hit.GetActor());
//			if (NearItem)
//				MeasureObjectAActor.Add(i, NearItem);
//		}
//	}
//
//}