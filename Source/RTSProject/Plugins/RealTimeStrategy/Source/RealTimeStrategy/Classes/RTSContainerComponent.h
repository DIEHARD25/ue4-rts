#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "RTSContainerComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSContainerComponentActorEnteredSignature, AActor*, Actor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRTSContainerComponentActorLeftSignature, AActor*, Actor);


/** Can hold one or more actors. */
UCLASS(meta = (BlueprintSpawnableComponent))
class REALTIMESTRATEGY_API URTSContainerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	URTSContainerComponent(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());


	/** Whether the specified actor can enter this container. */
	UFUNCTION(BlueprintPure)
	virtual bool CanLoadActor(AActor* Actor) const;

	/** Adds the specified actor to this container. */
	UFUNCTION(BlueprintCallable)
	virtual void LoadActor(AActor* Actor);

	/** Removes the specified actor from this container. */
	UFUNCTION(BlueprintCallable)
	virtual void UnloadActor(AActor* Actor);


    /** Gets how many actors may enter this container at the same time. Negative number means unlimited capacity, or will be set elsewhere. */
    UFUNCTION(BlueprintPure)
    int32 GetCapacity() const;

    /** Sets how many actors may enter this container at the same time. Negative number means unlimited capacity, or will be set elsewhere. */
    void SetCapacity(int32 InCapacity);

    /** Gets the actors currently held by this container. */
    UFUNCTION(BlueprintPure)
    TArray<AActor*> GetContainedActors() const;


	/** Event when a new actor has entered this container. */
	UPROPERTY(BlueprintAssignable, Category = "RTS")
	FRTSContainerComponentActorEnteredSignature OnActorEntered;

	/** Event when an actor has left this container. */
	UPROPERTY(BlueprintAssignable, Category = "RTS")
	FRTSContainerComponentActorLeftSignature OnActorLeft;

private:
    /** How many actors may enter this container at the same time. Negative number means unlimited capacity, or will be set elsewhere. */
    UPROPERTY(EditDefaultsOnly, Category = "RTS")
    int32 Capacity;

    /** Actors currently held by this container. */
    UPROPERTY()
    TArray<AActor*> ContainedActors;
};
