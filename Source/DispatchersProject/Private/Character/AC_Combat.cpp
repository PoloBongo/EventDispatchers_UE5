#include "Character/AC_Combat.h"

#include "GameFramework/Character.h"

UAC_Combat::UAC_Combat(): MaxIndexAck(0)
{
}

void UAC_Combat::BeginPlay()
{
	Super::BeginPlay();
	
	OnAttackKatana.BindUObject(this, &UAC_Combat::DeclenchAttack);
}

void UAC_Combat::ExecuteKatana()
{
	bool success = OnAttackKatana.ExecuteIfBound();
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

void UAC_Combat::DeclenchAttack()
{
	// pour le client
	if (GetOwnerRole() < ROLE_Authority)
	{
		ServerDeclenchAttack();
		return;
	}

	// pour le server
	MulticastDeclenchAttack();
}

void UAC_Combat::ServerDeclenchAttack_Implementation()
{
	MulticastDeclenchAttack();
}

void UAC_Combat::MulticastDeclenchAttack_Implementation()
{
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character pas trouvé"));
		return;
	}

	USkeletalMeshComponent* Mesh = OwnerCharacter->GetMesh();
	if (!Mesh) return;

	UAnimInstance* AnimInstance = Mesh->GetAnimInstance();
	if (!AnimInstance) return;
	
	if (Attacks[IndexAck])
	{
		AnimInstance->Montage_Play(Attacks[IndexAck]);
	}

	IndexAck++;
	if (IndexAck >= MaxIndexAck) IndexAck = 0;
}