#include<iostream>
using namespace std;

enum enQustionsLevel{EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4};
enum enOperationType{Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5};

string GetOpTypeSymbol(enOperationType OpType)
{

	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "*";
	case enOperationType::Div:
		return "/";
	default:
		return "+";
	}


}

string GetQustionLevelText(enQustionsLevel QustionLevel)
{

	string arrQustionLevel[4] = { "Easy","Med","Hard","Mix" };
	return arrQustionLevel[QustionLevel - 1];

}

int RandomNumber(int From, int To)
{
	
	int randNum = rand() % (To - From + 1) + From;
	return randNum;

}

void SetScreenColor(bool Right)
{

	if (Right)
		system("color 2F");
	else
	{
		system("color 4F");
		cout << "\a";
	}

}

short ReadHowManyQuestions()
{
	short NumberOfQuestions;

	do
	{

		cout << "How Many Questions do you want to answer ? ";
		cin >> NumberOfQuestions;


	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);


	return NumberOfQuestions;
}

enQustionsLevel ReadQustionLevel()
{
	short QustionLevel = 0;

	do
	{

		cout << "Enter Questions Level [1] Easy, [2] Med, [3]Hard, [4] Mix ? ";
			cin >> QustionLevel;


	} while (QustionLevel < 1 || QustionLevel>4);


	return (enQustionsLevel)QustionLevel;
}

enOperationType ReadOpType()
{
	short OpType;


	do
	{

	 cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul,[4] Div, [5] Mix ? ";
	 cin >> OpType;

	} while (OpType < 1 || OpType >5);


	return (enOperationType)OpType;
}

struct stQustion
{

	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType;
	enQustionsLevel QustionLevel;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = 0;

};

struct stQuizz
{

	stQustion QustionList[100];
	short NumberOfQustions;
	enQustionsLevel QustionLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;

};

int SimpleCalculator(int Number1, int Number2, enOperationType OpType)
{

	switch (OpType)
	{

	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;

	}


}

enOperationType GetRandomOperation()
{

	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;

}

stQustion GenerateQuestion(enQustionsLevel QuestionLevel,
	enOperationType OpType)
{

	stQustion Question;

	if (QuestionLevel == enQustionsLevel::Mix)
	{
		QuestionLevel = (enQustionsLevel)RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOp)
	{
		OpType = GetRandomOperation();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQustionsLevel::EasyLevel:

	 Question.Number1 = RandomNumber(1, 10);
	 Question.Number2 = RandomNumber(1, 10);
     Question.CorrectAnswer =SimpleCalculator(Question.Number1, Question.Number2,Question.OperationType);

		Question.QustionLevel = QuestionLevel;
		return Question;

	case enQustionsLevel::MedLevel:

	 Question.Number1 = RandomNumber(10, 50);
	 Question.Number2 = RandomNumber(10, 50);
	 Question.CorrectAnswer =SimpleCalculator(Question.Number1, Question.Number2,Question.OperationType);

		Question.QustionLevel = QuestionLevel;
		return Question;
		
	case enQustionsLevel::HardLevel:

	 Question.Number1 = RandomNumber(50, 100);
	 Question.Number2 = RandomNumber(50, 100);
	 Question.CorrectAnswer =SimpleCalculator(Question.Number1, Question.Number2,Question.OperationType);

	 Question.QustionLevel = QuestionLevel;
		return Question;

	}

	return Question;
}

void GenerateQuizzQuestions(stQuizz& Quizz)
{

	for (short Question = 0; Question < Quizz.NumberOfQustions;Question++)
	{

		Quizz.QustionList[Question] =GenerateQuestion(Quizz.QustionLevel, Quizz.OpType);

	}

}

int ReadQuestionAnswer()
{

	int Answer = 0;
	cin >> Answer;

	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{

	cout << "\n";

	cout << "Question [" << QuestionNumber + 1 << "/" <<
		Quizz.NumberOfQustions << "] \n\n";
	cout << Quizz.QustionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QustionList[QuestionNumber].Number2 << " ";
	cout <<GetOpTypeSymbol(Quizz.QustionList[QuestionNumber].OperationType);

	cout << "\n_________" << endl;

}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{

	if (Quizz.QustionList[QuestionNumber].PlayerAnswer !=
		Quizz.QustionList[QuestionNumber].CorrectAnswer)
	{

		Quizz.QustionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Worng Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QustionList[QuestionNumber].CorrectAnswer;
		cout << "\n";

	}
	else
	{
		Quizz.QustionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "Right Answer :-) \n";

	}
	cout << endl;

	SetScreenColor(Quizz.QustionList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{

	for (short QuestionNumber = 0; QuestionNumber <Quizz.NumberOfQustions; QuestionNumber++)
	{

		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QustionList[QuestionNumber].PlayerAnswer =
			ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);

	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{

	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";

}

void PrintQuizzResults(stQuizz Quizz)
{

	cout << "\n";

	cout << "______________________________\n\n";
	cout << " Final Resutls is " <<GetFinalResultsText(Quizz.isPass);
	cout << "\n______________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQustions <<endl;
	cout << "Questions Level : " <<GetQustionLevelText(Quizz.QustionLevel) << endl;
	cout << "OpType : " <<GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " <<Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " <<Quizz.NumberOfWrongAnswers << endl;

	cout << "______________________________\n";

}

void PlayMathGame()
{

	stQuizz Quizz;

	Quizz.NumberOfQustions = ReadHowManyQuestions();
	Quizz.QustionLevel = ReadQustionLevel();
	Quizz.OpType = ReadOpType();
	GenerateQuizzQuestions(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQuizzResults(Quizz);

}

void ResetScreen()
{

	system("cls");
	system("color 0F");

}

void StartGame()
{

	char PlayAgain = 'Y';

	do
	{

		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again? Y/N? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');


}

int main()
{

	srand((unsigned)time(NULL));

	StartGame();

	return 0;

}















