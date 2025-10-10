#include "PlayerHUD.h"

#include "Blueprint/UserWidget.h"

void APlayerHUD::ModifyCoins(float _coins)
{
	Coins += _coins;
}

void APlayerHUD::ShowCoinsWidget()
{
	UUserWidget* CoinsWidget = CreateWidget<UUserWidget>(GetWorld(), CoinsWidgetClass);
	if (CoinsWidget)
	{
		CoinsWidget->AddToViewport();
	}
}

void APlayerHUD::AddXP(ACharacter* Enemy)
{
	XP += 10.f;
}

void APlayerHUD::ShowXPWidget()
{
	UUserWidget* XPWidget = CreateWidget<UUserWidget>(GetWorld(), XPWidgetClass);
	if (XPWidget)
	{
		XPWidget->AddToViewport();
	}
}
