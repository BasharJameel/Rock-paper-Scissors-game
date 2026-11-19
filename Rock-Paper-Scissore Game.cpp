#include<iostream>
#include<cstdlib>
#include<ctime>
#include<windows.h>

enum enGameChoice {stone=1,paper=2,scissor=3};
enum enWiner {Player=1,Computer=2,draw=3};

using namespace std;

struct stRoundInfo 
{
	short RoundNumber = 0;
	enGameChoice playerChoice;
	enGameChoice ComputerChoice;
	enWiner Winner;
	string WinnerName;
};

struct stGameInfo
{
	short GameRound=0;
	short PlayerWinTimes=0;
	short ComputWinTimes=0;
	short DrawTimes=0;
	enWiner Winner;
	string WinnerName="";
};


string Tap (int Num)
{
	string t="";

	for (short i =0;i<Num;i++)
	{
		t+="\t";
	}

	return t;
}

int HowManyRounds()
{
	int Num;
	do{
		cout<<"how Many Round? enter form 1-10 "<<endl;
		cin>>Num;
		
	}while(Num<0);
	return Num; 
}

int RandNumber(int From, int To)
{
	int randNum= rand()%(To - From + 1 )+ From;
	return randNum;
}
//
//
//string WinnerName(stRoundInfo RoundInform)
//{
//	string arrGameChoice[3]={"stone","Paper","Scisser"};
//	return arrGameChoice[1+(int)Choice];
//
//}

string GameChoice (enGameChoice Choice)
{
	string arrGameChoice[3]={"stone","Paper","Scisser"};
	return arrGameChoice[(int)Choice-1];
	
}


string WinnerName(enWiner Winner)
{
	string arrWinnerName[3]={"player1","Computer","No Winner"};
	return arrWinnerName[(int)Winner-1];

}


enWiner HowAreTheWinerOfTheRound(stRoundInfo RoundInform )
{
	    
    if (RoundInform.ComputerChoice==RoundInform.playerChoice)
   {
	return enWiner::draw;
   }

   switch(RoundInform.ComputerChoice)
   {
	case enGameChoice::paper:
	if(RoundInform.playerChoice==enGameChoice::stone)
	{
		return enWiner::Computer;
	}
	break;
	case enGameChoice::scissor:
	if(RoundInform.playerChoice==enGameChoice::paper)
	{
		return enWiner::Computer;
	}
	break;
	case enGameChoice::stone:
	if(RoundInform.playerChoice==enGameChoice::scissor)
	{
		return enWiner::Computer;
	}
	break;
   }

   return enWiner::Player;
}

void PrintRuseltOfTheRound (stRoundInfo RoundInfo)
{
	
	cout<<"____________Round["<<RoundInfo.RoundNumber<<"]_____________\n\n";
	cout<<"\nPlayer1 Choice : "<<GameChoice(RoundInfo.playerChoice)<<endl;
	cout<<"Computer Choice : "<<GameChoice (RoundInfo.ComputerChoice)<<endl;
	cout<<"Round Winnerr  : "<<RoundInfo.WinnerName<<endl;
	cout<<"\n_________________________________\n\n";



	//I staped here
}

void ColorScreen (stRoundInfo RoundInfo)
{
	switch (RoundInfo.Winner)
	{
	case enWiner::Player:
	system("color 2");
	return ;

	case enWiner::Computer:
	system("color 4");
	cout<<"\a";
	return ;

	case enWiner::draw:
	system("color 6");
	return;

	}

}

void ShowGameOverScreen()
{
    cout<<Tap(3)<<"_____________________________________________________________\n\n";

	cout<<Tap(3)<<"                   +++ G a m e  O v e r +++                    \n";
	cout<<Tap(3)<<"_____________________________________________________________\n\n";

}

void PrintResulte (stGameInfo GameResult)
{
	
	
	cout<<Tap(3)<<"________________________[Game Results]_______________________\n\n";

	cout<<Tap(3)<<"Game Rounds : "        <<GameResult.GameRound<<  " Point .\n";
	cout<<Tap(3)<<"Player     won times: "<<GameResult.PlayerWinTimes<<" Point .\n";
	cout<<Tap(3)<<"Computer   won times: "<<GameResult.ComputWinTimes<<   " Point .\n";
	cout<<Tap(3)<<"Draw times          : "<<GameResult.DrawTimes<<   " Point .\n";
	cout<<Tap(3)<<"Final Winner        :" <<GameResult.WinnerName<<endl;
	cout<<Tap(3)<<"_____________________________________________________________\n\n";
}

void ResetScreen ()
{
		system("color 0F");
		system("cls");
}

enGameChoice ReadPlayerChoice ()
{
	int Choice;
	 cout<<"\nEnteryour choice : [1]:stone, [2]:Paper, [3]:Scissors ?"<<endl;
	 cin>>Choice;
	 return (enGameChoice)Choice;

}

enGameChoice GetComputerChoice ()
{
	return (enGameChoice)RandNumber(1,3);
}

enWiner WhoWonTheGame(stGameInfo GameInfo)
{
	if(GameInfo.ComputWinTimes<GameInfo.PlayerWinTimes)
	{
		return enWiner::Player;
	}
	else if (GameInfo.ComputWinTimes>GameInfo.PlayerWinTimes)
	{
		return enWiner::Computer;
	}
	else
	{
		return enWiner::draw;
	}
}

stGameInfo FillGameResults (short NumberOfRounds,short playerWinTimes,short ComputerWinTimes,int DrawTimes)
{
	stGameInfo GameResult;

	GameResult.GameRound=NumberOfRounds;
	GameResult.PlayerWinTimes=playerWinTimes;
	GameResult.ComputWinTimes=ComputerWinTimes;
	
	GameResult.DrawTimes=DrawTimes;
	GameResult.Winner=WhoWonTheGame(GameResult);
	GameResult.WinnerName=WinnerName(GameResult.Winner);
	
	return GameResult;


}

stGameInfo PlayGame (int NumberOfRound)
{
	stRoundInfo RoundInfo;
	int ComputerPoint=0,PlayerPoint=0,Draw=0;
	
	for (int GameRound = 1; GameRound <= NumberOfRound; GameRound++)
	{
		
		cout<<"\nRound ["<<GameRound<<"] begins :\n";
	    RoundInfo.RoundNumber=GameRound;
	    RoundInfo.playerChoice=ReadPlayerChoice();
		RoundInfo.ComputerChoice=GetComputerChoice();
		RoundInfo.Winner=HowAreTheWinerOfTheRound(RoundInfo);
		RoundInfo.WinnerName=WinnerName(RoundInfo.Winner);

		if(RoundInfo.Winner==enWiner::Computer)
		{
			ComputerPoint++;
				    cout<<"\nPlayerPoint++"<<ComputerPoint<<endl;
		}
		else if(RoundInfo.Winner==enWiner::Player)
		{
		    PlayerPoint++;
	
		}
		else 
		{
			Draw++;
		}

		PrintRuseltOfTheRound(RoundInfo);
		ColorScreen(RoundInfo);
	}
	return FillGameResults(NumberOfRound,PlayerPoint,ComputerPoint,Draw);	
}

void StartGame ()
{

	char GameRetrive ='Y';
	do{
		ResetScreen();

		stGameInfo GameResult =PlayGame(HowManyRounds());
		
		ShowGameOverScreen();
		PrintResulte(GameResult);
		cout<<"\n\nDo you want to Play again ? Y/N ";
		cin>>GameRetrive;

	}while(GameRetrive=='y'||GameRetrive=='Y');
	
}

int main ()
{
	int arrayLength1 , arrayLength2 , array1[100],array2[100];
 	srand((unsigned)time(NULL));

	StartGame();
	stGameInfo s;
	

}

