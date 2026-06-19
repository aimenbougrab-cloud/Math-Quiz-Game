#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>

using namespace std;

enum enQuestionLevel { Easy = 1, Medium = 2, Hard = 3, MixLevel = 4 };
enum enOperationType { Addition = 1, Substraction = 2, Multiplication = 3, Division = 4, MixOp = 5 };

short RandomNumber(short From, short To) {
    int RandomNum = rand() % (To - From + 1) + From;
    return RandomNum;
}

struct stQuestion
{
    short QuestionNumber = 0;
    enOperationType QuestionOperation;
    enQuestionLevel QuestionLevel;
    short Number1 = 0;
    short Number2 = 0;
    short CorrectAnswer = 0;
    short UserAnswer = 0;
    bool AnswerResult = false;
};

struct stQuizz
{
    stQuestion QuestionsList[100];
    short NumberOfQuestions = 0;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    enQuestionLevel QuestionsLevel;
    enOperationType OperationType;
    bool IsPass = false;
};

short ReadHowManyQuestions()
{
    short NumberOfQuestion = 0;
    do
    {
        cout << "\n Enter the Number of Questions , it should be in Range (1 -- 100) !";
        cin >> NumberOfQuestion;
    } while (NumberOfQuestion < 1 || NumberOfQuestion > 100);
    return NumberOfQuestion;
}

enQuestionLevel ReadQuestionLevel()
{
    short QuestionLevel = 4;
    do
    {
        cout << "\n Enter Questions Level : [1]:Easy , [2]:Medium , [3]:Hard , [4]:Mix ?\n";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return (enQuestionLevel)QuestionLevel;
}

enOperationType ReadOperationType()
{
    short OperationType = 5;
    do
    {
        cout << "\n Enter Operation Type :: ' + ' , [2]: ' - ' , [3]: ' x ' , [4]: ' / ' , [5]:Mix\n";
        cin >> OperationType;
    } while (OperationType < 1 || OperationType > 5);
    return (enOperationType)OperationType;
}

short ReadUsersResult()
{
    short Result = 0;
    cin >> Result;
    return Result;
}

void TurnScreenColor(bool CorrectAndPass)
{
    if (CorrectAndPass)
    {
        system("color 2F");
    }
    else
    {
        cout << "\a";
        system("color 4F");
    }
}

string PrintOperationTypeSymbole(enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Addition:
        return " +";
    case enOperationType::Substraction:
        return " -";
    case enOperationType::Multiplication:
        return " x";
    case enOperationType::Division:
        return " /";
    default:
        return " Mix";
    }
}

short Calculator(short Number1, short Number2, enOperationType OperationType)
{
    switch (OperationType)
    {
    case enOperationType::Addition:
        return Number1 + Number2;
    case enOperationType::Substraction:
        return Number1 - Number2;
    case enOperationType::Multiplication:
        return Number1 * Number2;
    case enOperationType::Division:
        return Number1 / Number2;
    }
}

string PrintQuestionsLevelText(enQuestionLevel QuestionLevel)
{
    string ArrayOfLevels[4] = { "Easy" , "Medium", "Hard", "Mix" };
    return ArrayOfLevels[QuestionLevel - 1];
}

stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OperationType)
{
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::MixLevel)
    {
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    }
    if (OperationType == enOperationType::MixOp)
    {
        OperationType = (enOperationType)RandomNumber(1, 4);
    }
    Question.QuestionOperation = OperationType;

    switch (QuestionLevel)
    {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.CorrectAnswer = Calculator(Question.Number1, Question.Number2, Question.QuestionOperation);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::Medium:
        Question.Number1 = RandomNumber(10, 50);
        Question.Number2 = RandomNumber(10, 50);
        Question.CorrectAnswer = Calculator(Question.Number1, Question.Number2, Question.QuestionOperation);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(50, 100);
        Question.Number2 = RandomNumber(50, 100);
        Question.CorrectAnswer = Calculator(Question.Number1, Question.Number2, Question.QuestionOperation);
        Question.QuestionLevel = QuestionLevel;
        return Question;
    }
    return Question;
}

void PrintTheQuestion(stQuestion QuestionInfo, short NumberOfQuestions)
{
    cout << "\n Question [" << QuestionInfo.QuestionNumber + 1 << "/" << NumberOfQuestions << "] :\n\n";
    cout << QuestionInfo.Number1 << endl;
    cout << QuestionInfo.Number2;
    cout << " " << PrintOperationTypeSymbole(QuestionInfo.QuestionOperation) << endl;
    cout << "_______________\n";
    cout << "= ";
}

void PrintFinalResultsScreen(bool IsPass)
{
    if (IsPass)
    {
        cout << " The Final Result is : PASS (-:\n";
    }
    else
    {
        cout << " The Final Result is : FAIL )-:\n";
    }
}

void PrintFinalResults(stQuizz Quizz)
{
    cout << "\n_______________________________________\n\n";
    PrintFinalResultsScreen(Quizz.IsPass);
    cout << "_______________________________________\n\n";
    cout << "\n Number of Questions : " << Quizz.NumberOfQuestions;
    cout << "\n Questions Level : " << PrintQuestionsLevelText(Quizz.QuestionsLevel);
    cout << "\n Operations Type : " << PrintOperationTypeSymbole(Quizz.OperationType);
    cout << "\n Number of right Answers : " << Quizz.NumberOfRightAnswers;
    cout << "\n Number of wrong Answers : " << Quizz.NumberOfWrongAnswers << "\n\n";
    cout << "_______________________________________\n\n";
    TurnScreenColor(Quizz.IsPass);
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{
    for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
    {
        Quizz.QuestionsList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OperationType);
    }
}

void CorrectUserResult(stQuizz& Quizz, short QuestionNumber)
{
    if (Quizz.QuestionsList[QuestionNumber].CorrectAnswer != Quizz.QuestionsList[QuestionNumber].UserAnswer)
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quizz.NumberOfWrongAnswers++;
        cout << "\n Wrong Answer )-:\n";
        cout << "\n The Right Anwer is : ";
        cout << Quizz.QuestionsList[QuestionNumber].CorrectAnswer;
        cout << "\n\n";
    }
    else
    {
        Quizz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quizz.NumberOfRightAnswers++;
        cout << "\n Right Answer )-:\n";
        cout << "\n";
    }
    TurnScreenColor(Quizz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quizz.QuestionsList[QuestionNumber], Quizz.NumberOfQuestions);
        Quizz.QuestionsList[QuestionNumber].UserAnswer = ReadUsersResult();
        CorrectUserResult(Quizz, QuestionNumber);
    }
    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

void ResetGame()
{
    system("cls");
    system("color 0F");
}

void PlayMathGame()
{
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadHowManyQuestions();
    Quizz.QuestionsLevel = ReadQuestionLevel();
    Quizz.OperationType = ReadOperationType();
    GenerateQuizzQuestions(Quizz);
    AskAndCorrectQuestionListAnswers(Quizz);
    PrintFinalResults(Quizz);
}

void StartGame()
{
    char PlayAgain = 'y';
    do {
        ResetGame();
        PlayMathGame();
        cout << "\n Do you want to play again ? YES : print 'y' , NO : print 'n' \n";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}

int main()
{
    //Seeds the random Number Generator in C++ , call only once .
    srand((unsigned)time(NULL));
    StartGame();
    return 0;
}
