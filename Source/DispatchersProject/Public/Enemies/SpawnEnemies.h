#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "SpawnEnemies.generated.h"

class APlayerHUD;
class ATargetPoint;
DECLARE_DYNAMIC_DELEGATE(FOnSpawnEnemies);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyDead, ACharacter*, Enemy);

UCLASS()
class DISPATCHERSPROJECT_API ASpawnEnemies : public AActor
{
	GENERATED_BODY()
	
public:
	ASpawnEnemies();

	// Spawn Enemy dynamic delegate c++
	UPROPERTY()
	FOnSpawnEnemies OnSpawnEnemies;
	
	UFUNCTION(BlueprintCallable)
	void CallSpawnEnemies();

	UFUNCTION()
	void ExecuteSpawnEnemies();

	UFUNCTION(Server, Reliable)
	void ServerExecuteSpawnEnemies();

	// Enemy die dynamic multicast delegate hybrid
	UPROPERTY(BlueprintAssignable)
	FOnEnemyDead OnEnemyDead;

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_OnEnemyDead(ACharacter* EnemyDie);
	
	UFUNCTION(BlueprintCallable)
	void CallDieEnemy(ACharacter* EnemyDie);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	TArray<ATargetPoint*> ListTargetPoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	TSubclassOf<ACharacter> EnemyClass;

	APlayerHUD* PlayerHUD;
	void GetPlayerHud();
};
