#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AC_Combat.generated.h"

DECLARE_DELEGATE(FOnAttackKatana);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DISPATCHERSPROJECT_API UAC_Combat : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAC_Combat();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess=true))
	TArray<UAnimMontage*> Attacks;
	
	FOnAttackKatana OnAttackKatana;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess=true))
	int IndexAck = 0;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Weapons", meta=(AllowPrivateAccess=true))
	int MaxIndexAck;

	void DeclenchAttack(); // fonction appellé localement

	UFUNCTION(Server, Reliable)
	void ServerDeclenchAttack(); // executé sur le server par le client

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDeclenchAttack(); // permet de repliqué sur tout les clients

public:
	UFUNCTION(BlueprintCallable)
	void ExecuteKatana();
};
