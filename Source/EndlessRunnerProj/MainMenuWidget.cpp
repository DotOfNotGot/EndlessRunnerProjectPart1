// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"

#include "SaveGameHighscore.h"
#include "Kismet/GameplayStatics.h"

void UMainMenuWidget::NativeConstruct()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	PlayerController->bShowMouseCursor = true;

	USaveGameHighscore* SaveGameInstance = Cast<USaveGameHighscore>(UGameplayStatics::LoadGameFromSlot("HighScoreSlot", 0));
	
	int AmountOfScores = SaveGameInstance->HighScores.Num();

	if(AmountOfScores > 5)
	{
		AmountOfScores = 5;
	}

	UE_LOG(LogTemp, Warning, TEXT("i + 1 = %d"), SaveGameInstance->HighScores.Num());

	
	TArray<UTextBlock*> ScoreTextBlocks = GetTextBlocksArray();

	for (int i = 0; i < ScoreTextBlocks.Num(); i++)
	{
		ScoreTextBlocks[i]->SetText(FText::FromString(" "));
	}
	
	if(SaveGameInstance->HighScores[0] != 0)
	{
		for (int i = 0; i < AmountOfScores; i++)
		{
			int CurrentScore = i + 1;

			UE_LOG(LogTemp, Warning, TEXT("i + 1 = %d, %d"), CurrentScore, SaveGameInstance->HighScores[i]);
			
			FString NewScoreText;

			NewScoreText.AppendInt(CurrentScore);
			NewScoreText.Append(": ");
			NewScoreText.AppendInt(SaveGameInstance->HighScores[i]);

			ScoreTextBlocks[i]->SetText(FText::FromString(NewScoreText));
		}
	}
	
	Super::NativeConstruct();
}

TArray<UTextBlock*> UMainMenuWidget::GetTextBlocksArray()
{
	
	TArray<UTextBlock*> TextBlocks;

	// TextBlocks.Init(ScoreOne, 5);
	TextBlocks.Add(ScoreOne);
	TextBlocks.Add(ScoreTwo);
	TextBlocks.Add(ScoreThree);
	TextBlocks.Add(ScoreFour);
	TextBlocks.Add(ScoreFive);

	return TextBlocks;
}
