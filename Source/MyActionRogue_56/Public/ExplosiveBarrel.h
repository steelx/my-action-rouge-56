// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosiveBarrel.generated.h"

class URadialForceComponent;

UCLASS()
class MYACTIONROGUE_56_API AExplosiveBarrel : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AExplosiveBarrel();
	
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// exposed methods

protected:
	UPROPERTY(EditAnywhere, Category="Explosive Barrel")
	float ExplosionRadius;
	
	UPROPERTY(EditAnywhere, Category="Explosive Barrel")
	float ExplosionDamage;
	
	UPROPERTY(VisibleAnywhere, Category="Explosive Barrel")
	TObjectPtr<UStaticMeshComponent> MeshComp;
	
	UPROPERTY(VisibleAnywhere, Category="Explosive Barrel")
	TObjectPtr<URadialForceComponent> RadialForceComp;

	UFUNCTION()
	void OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void DisablePhysics();
};
