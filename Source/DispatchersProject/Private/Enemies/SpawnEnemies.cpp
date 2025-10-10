#include "Enemies/SpawnEnemies.h"

#include "PlayerHUD.h"
#include "Engine/TargetPoint.h"
#include "Kismet/GameplayStatics.h"

ASpawnEnemies::ASpawnEnemies()
{
}

void ASpawnEnemies::BeginPlay()
{
	GetPlayerHud();
	OnSpawnEnemies.BindDynamic(this, &ASpawnEnemies::ExecuteSpawnEnemies);
	if (PlayerHUD) OnEnemyDead.AddDynamic(PlayerHUD, &APlayerHUD::AddXP);
	Super::BeginPlay();
}

void ASpawnEnemies::GetPlayerHud()
{
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	}
}

void ASpawnEnemies::ExecuteSpawnEnemies()
{
	if (GetLocalRole() < ROLE_Authority)
	{
		ServerExecuteSpawnEnemies();
		return;
	}

	ServerExecuteSpawnEnemies();
}

void ASpawnEnemies::ServerExecuteSpawnEnemies_Implementation()
{
	if (ListTargetPoint.Num() <= 0) return;
	
	for (ATargetPoint* spawnPoint : ListTargetPoint)
	{
		GetWorld()->SpawnActor<ACharacter>(EnemyClass, spawnPoint->GetActorTransform());
	}
}

void ASpawnEnemies::CallSpawnEnemies()
{
	bool success = OnSpawnEnemies.ExecuteIfBound();
	if (!success)
	{
		if (!GEngine) return;
		GEngine->AddOnScreenDebugMessage
		(
		-1,
		3.f,
		FColor::Red,
		FString::Printf(TEXT("Le delegate n'a pas marché")
		));
	}
}

void ASpawnEnemies::CallDieEnemy(ACharacter* EnemyDie)
{
	Multicast_OnEnemyDead(EnemyDie);
}

void ASpawnEnemies::Multicast_OnEnemyDead_Implementation(ACharacter* EnemyDie)
{
	OnEnemyDead.Broadcast(EnemyDie);
}
