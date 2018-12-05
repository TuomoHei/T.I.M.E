#pragma once

//#include "CoreMinimal.h"
//#include "UObject/NoExportTypes.h"
#include "ScoreManager.generated.h"

/**
 * 
 */

//Functionality has been moved to SceneScoreActor!

UCLASS()
class CPPTEST_API UScoreManager : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:
	UScoreManager();
	~UScoreManager() {}

private:
	void Tick(float DeltaTime) override;
	TStatId GetStatId() const override;

};
