#include <iostream>
#include <cstdlib>
using namespace std;

enum enChoices { paper = 1, scissor, stone };
enum enWinner { Player=0, Computer, Draw };

struct stGameInfo {
    int winTimes, loseTimes, DrawTimes, NumberOfRounds;
    enWinner GameWinner;
    string GameWinnerName;
};
struct stRoundInfo {
    int RoundNumber;
    enWinner RoundWinner;
    string RoundWinnerName;
    enChoices ComputerChoice,PLayerChoice;

};
string WinnerName(enWinner WinnerName) {
    string Winner[3] = { "Player","Computer","No winner" };
    return Winner[WinnerName];
}

int ReadNumber(string message) {
    int number;
    do {
        cout << message;
        cin >> number;
    } while (number <= 0);
    return number;
}

int RandomNumber(int from, int to) {

    return rand() % (to - from + 1) + from;
}
string Choice(enChoices TheChoice) {
    switch (TheChoice) {
    case scissor:
        return "Scissor";
    case paper:
        return "Paper";
    default:
        return "Stone";

    }
}
void PrintScreenWinColor(stRoundInfo RoundInfo) {
    switch (RoundInfo.RoundWinner) {
    case enWinner::Draw:
        system("color 6f");
        break;
    case enWinner::Player:
        system("color 2f");
        break;
    default:
        cout << "\a";
        system("color 4f");
    }
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.PLayerChoice == RoundInfo.ComputerChoice)
        return enWinner::Draw;
    else if (RoundInfo.PLayerChoice > RoundInfo.ComputerChoice)
        return enWinner::Player;
    else
        return enWinner::Computer;

}
enWinner WhoWonTheGame(int winTimes,int loseTimes) {
    if (winTimes == loseTimes)
        return enWinner::Draw;
    else if (winTimes > loseTimes)
        return enWinner::Player;
    else
        return enWinner::Computer;

}
string Tab(int NumberOfTabs) {
    string Tabs = "";
    for (int i = 0; i < NumberOfTabs; i++)
        Tabs += '\t';
    return Tabs;
}
void PrintGameOver() {
    
    cout << "\n"<<Tab(2)<<"----------------------------------------------------" << endl;
    cout << Tab(2);
    cout << "--------------------- Game Over --------------------" << endl;
    cout << Tab(2);
    cout << "----------------------------------------------------" << endl;
}
enChoices ReadPLayerChoice() {
   int PlayerChoice= ReadNumber("Enter your choice [1]paper, [2]scissor, [3]stone: ");
   return (enChoices)PlayerChoice;
}
enChoices GetComputerChoice() {
    int ComputerChoice = RandomNumber(1, 3);
    return (enChoices)ComputerChoice;

}
void PrintGameInformation(stGameInfo GameInfo) {
    cout << "\n"<<Tab(4)<<"Game Rounds : " << GameInfo.NumberOfRounds << endl;
    cout << Tab(4);
    cout << "Player Won Times: " << GameInfo.winTimes << endl;
    cout << Tab(4);
    cout << "Computer Won Times: " << GameInfo.loseTimes << endl;
    cout << Tab(4);
    cout << "Draw Times: " << GameInfo.DrawTimes << endl;
    cout << Tab(4);
    cout << "Final Winner is " << GameInfo.GameWinnerName<<endl;  
    cout << "\n"<<Tab(2)<<"----------------------------------------------------" << endl;
}
void ResetScreen() {
    system("cls");
    system("color 0f");
}
stGameInfo FillGameInfo(int winTimes, int loseTimes, int DrawTimes, int NumberOfRounds, enWinner GameWinner)
{
    stGameInfo GameInfo;
    GameInfo.DrawTimes = DrawTimes;
    GameInfo.GameWinnerName = WinnerName(GameWinner);
    GameInfo.loseTimes = loseTimes;
    GameInfo.winTimes = winTimes;
    GameInfo.NumberOfRounds = NumberOfRounds;
    return GameInfo;

}
int ReadRoundNumbers() {
    int RoundNumbers = ReadNumber("How many rounds you want to play ? ");
    return RoundNumbers;
}
stGameInfo PlayGame() {
    int NumberOfRounds = ReadRoundNumbers();
    stRoundInfo RoundInfo;
    int winTimes=0, loseTimes=0, DrawTimes=0;
    for (int i = 1; i <= NumberOfRounds; i++) {
        cout << "\n================Round[" << i << "]===============\n" << endl;
        RoundInfo.PLayerChoice = ReadPLayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.RoundWinnerName = WinnerName(RoundInfo.RoundWinner);
        cout << "Player Choice is " << Choice(RoundInfo.PLayerChoice) << endl;
        cout << "Computer Choice is " << Choice(RoundInfo.ComputerChoice) << endl;
        cout << "The winner is " << RoundInfo.RoundWinnerName << endl;
        PrintScreenWinColor(RoundInfo);
        cout << "\n=======================================" << endl<<endl;

        if (RoundInfo.RoundWinner == enWinner::Player)
            winTimes++;
        else if (RoundInfo.RoundWinner == enWinner::Computer)
            loseTimes++;
        else
            DrawTimes++;

    }
    return FillGameInfo(winTimes, loseTimes, DrawTimes, NumberOfRounds, WhoWonTheGame(winTimes, loseTimes));

}
void StartGame() {
    bool answer = 1;
    while (answer){
        ResetScreen();
        stGameInfo GameInfo = PlayGame();
        PrintGameOver();
        PrintGameInformation(GameInfo);

        Tab(2);
    cout << "\nDo you want to play the game again [0]No, [1]Yes ? ";
    cin >> answer;
} 


}
    

int main()
{
    srand((unsigned)time(NULL));
    StartGame();
    
 

    
    return 0;
}

