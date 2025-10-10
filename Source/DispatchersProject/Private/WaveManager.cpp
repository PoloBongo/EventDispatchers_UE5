#include "WaveManager.h"

#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AWaveManager::AWaveManager(): PlayerHUD(nullptr)
{
}

void AWaveManager::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		PlayerHUD = Cast<APlayerHUD>(PC->GetHUD());
	}

	// AddUObject pour les add au callback
	OnPlayerIsReady.AddUObject(this, &AWaveManager::StartGame);
	OnPlayerIsReady.AddUObject(this, &AWaveManager::ShowWidget);
	if (PlayerHUD)
	{
		OnPlayerIsReady.AddUObject(PlayerHUD, &APlayerHUD::ShowCoinsWidget);
		OnPlayerIsReady.AddUObject(PlayerHUD, &APlayerHUD::ShowXPWidget);
	}
}

void AWaveManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AWaveManager, CurrentWave);
}

void AWaveManager::StartGame()
{
	CurrentWave = 0;
	if (GEngine) GEngine->AddOnScreenDebugMessage
	(
	-1,
	3.f,
	FColor::Green,
	FString::Printf(TEXT("Wave :%i"), CurrentWave
	));
}

void AWaveManager::ShowWidget()
{
	UUserWidget* WaveWidget = CreateWidget<UUserWidget>(GetWorld(), WaveWidgetClass);
	if (WaveWidget)
	{
		WaveWidget->AddToViewport();
	}
}

void AWaveManager::PlayerIsReady()
{
	OnPlayerIsReady.Broadcast();
}

void AWaveManager::NextWave()
{
	CurrentWave++;
	if (GEngine) GEngine->AddOnScreenDebugMessage
	(
	-1,
	3.f,
	FColor::Green,
	FString::Printf(TEXT("Wave :%i"), CurrentWave
	));
}