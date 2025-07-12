// Fill out your copyright notice in the Description page of Project Settings.


#include "MagicProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
AMagicProjectile::AMagicProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SetRootComponent(SphereComp);

	// Collision preset
	SphereComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComp->SetCollisionObjectType(ECC_WorldDynamic);
	SphereComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Overlap);
	SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	EffectComp = CreateDefaultSubobject<UParticleSystemComponent>("EffectComp");
	EffectComp->SetupAttachment(SphereComp);

	MoveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	MoveComp->SetUpdatedComponent(SphereComp);
	MoveComp->InitialSpeed = 1000.0f;
	MoveComp->MaxSpeed = 1500;
	MoveComp->bRotationFollowsVelocity = true;
	MoveComp->bInitialVelocityInLocalSpace = true;
	MoveComp->ProjectileGravityScale = 0.0f;
}

// Called when the game starts or when spawned
void AMagicProjectile::BeginPlay()
{
	Super::BeginPlay();

	/**
	 1. The World Geometry (Walls, Floors) Response set to ECC_WorldStatic = ECR_Block
	   * Identity: Their Object Type is WorldStatic.
	   * Behavior: They are set to BLOCK everything, including your WorldDynamic projectile.
	   * Efficiency: Generate Overlap Events is OFF. This is the key to good performance. The world doesn't need to do extra work; it just needs to be a solid barrier.

	 2. The Characters (`Pawn`) and Physics Objects (`PhysicsBody`) ECC_Pawn & ECC_PhysicsBody = ECR_Overlap
	   * Identity: Their Object Types are Pawn and PhysicsBody.
	   * Behavior: They are configured to OVERLAP with your WorldDynamic projectile.
	   * The "Magic" Checkbox: Generate Overlap Events is ON for these specific objects. This is perfectly fine and efficient because, as you noted, there are only a few of them.
	 */
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &AMagicProjectile::OnActorOverlap);
	SphereComp->OnComponentHit.AddDynamic(this, &AMagicProjectile::OnHit);
}

void AMagicProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/** Scenario A: Projectile Hits a Wall
1. The WorldDynamic projectile flies towards a WorldStatic wall.
2. The engine checks their relationship: Block vs. Block.
3. A collision occurs. The projectile stops.
4. The engine fires the `OnComponentHit` event.
5. Your OnHit() function runs, and you can spawn an impact effect, destroy the projectile, etc.
*/
void AMagicProjectile::OnActorOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Warning, TEXT("Overlapped with %s"), *OtherActor->GetName());
		// draw debug sphere
		DrawDebugSphere(GetWorld(), GetActorLocation(), 20.0f, 32, FColor::Red, false, 2.0f);
		Destroy();
	}
}

/** Scenario B: Projectile Hits a Character (Pawn)
1. The WorldDynamic projectile flies towards a Pawn.
2. The engine checks their relationship: Overlap vs. Overlap.
3. The projectile is allowed to pass through the character.
4. Because Generate Overlap Events is enabled on the Pawn, the engine fires the `OnComponentBeginOverlap` event.
5. Your OnActorOverlap() function runs. Here you can apply damage, add a status effect, etc., without stopping the projectile (allowing it to potentially hit multiple enemies).
*/
void AMagicProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor && OtherActor != GetInstigator())
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit with %s"), *OtherActor->GetName());
		// draw debug sphere
		DrawDebugSphere(GetWorld(), GetActorLocation(), 20.0f, 32, FColor::Red, false, 2.0f);
		Destroy();
	}
}

