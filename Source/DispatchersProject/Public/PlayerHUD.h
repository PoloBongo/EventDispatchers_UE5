#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class DISPATCHERSPROJECT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void ModifyCoins(float _coins);
	void ShowCoinsWidget();

	UFUNCTION()
	void AddXP(ACharacter* Enemy = nullptr);
	void ShowXPWidget();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float Coins = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Références", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> CoinsWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Variables", meta=(AllowPrivateAccess=true))
	float XP = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Références", meta=(AllowPrivateAccess=true))
	TSubclassOf<UUserWidget> XPWidgetClass;
};
