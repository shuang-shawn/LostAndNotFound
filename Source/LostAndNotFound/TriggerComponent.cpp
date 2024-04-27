// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTriggerComponent::BeginPlay()
{
    Super::BeginPlay();
    SetMover(MoverActor);

}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if(GetAcceptableActor())
    {
        UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(GetAcceptableActor()->GetRootComponent());
        if (Component != nullptr) 
        {
            Component->SetSimulatePhysics(false);
        }
        GetAcceptableActor()->AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform);
        if (Mover)
        {
            Mover->Move();
        } 
        // else 
        // {
        //     UE_LOG(LogTemp, Warning, TEXT("No Mover detected"));
        // }
        
    } else {
        if (Mover)
        {
            Mover->Return();
        } 

    }
   


}

// UMover* UTriggerComponent::GetMover() const
// {
// 	UMover* NewMover = GetOwner()->FindComponentByClass<UMover>();
// 	if (NewMover == nullptr)
// 	{
// 		UE_LOG(LogTemp, Warning, TEXT("Mover not found"));
// 	}

// 	return NewMover;
// }

void UTriggerComponent::SetMover(AActor* Actor)
{
    Mover = Actor->FindComponentByClass<UMover>();
    if (Mover == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Mover not found"));
	}
}


AActor* UTriggerComponent::GetAcceptableActor() const
{
    TArray<AActor*> OverlappingActors;
    GetOverlappingActors(OverlappingActors);
    for (AActor* Actor : OverlappingActors)
    {
        for (FName Tag : TagsToUnlock)
        {
            if (Actor->ActorHasTag(Tag))
            {
                if (TagsToIgnore.Num() > 0)
                {
                    for (FName IgnoreTag : TagsToIgnore)
                {
                    if (!Actor->ActorHasTag(IgnoreTag))
                    {
                        return Actor;
                    }
                }
                } else {
                    return Actor;
                }
                
                 
            } 
        }
    }
    return nullptr;
}
