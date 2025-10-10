// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WaveManager.generated.h"

class APlayerHUD;

DECLARE_MULTICAST_DELEGATE(FOnPlayerIsReady);

UCLASS()
class DISPATCHERSPROJECT_API AWaveManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaveManager();

	FOnPlayerIsReady OnPlayerIsReady;

	UFUNCTION(BlueprintCallable)
	void PlayerIsReady();

	UFUNCTION(BlueprintCallable)
	void NextWave();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	int CurrentWave = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float WaveReward = 100.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Références", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> WaveWidgetClass;

	APlayerHUD* PlayerHUD;

	void StartGame();
	void ShowWidget();
};
