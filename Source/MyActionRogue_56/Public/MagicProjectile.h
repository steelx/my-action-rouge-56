// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MagicProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class MYACTIONROGUE_56_API AMagicProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMagicProjectile();
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> SphereComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> MoveComp;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UParticleSystemComponent> EffectComp;

	UFUNCTION()
	void OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
