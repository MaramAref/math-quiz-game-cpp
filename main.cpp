#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
using namespace std;

const int Max_Of_Questions=100;

enum enQustionLevel{Easy= 1,Medium= 2,Hard= 3,MixLevel= 4};
enum enOperationType {Add= 1,Subtract= 2,Multiply= 3,Divide= 4,Mix= 5};

int ReadNumberOfQuestions(string Message)
{
	short NumberOfQuestions=1;
	do{
	cout<<Message<<endl;
	cin>>NumberOfQuestions;
	}while(NumberOfQuestions<1 || NumberOfQuestions>Max_Of_Questions);
return NumberOfQuestions;	
}

enQustionLevel ReadQustionLevel(){
	short Choice;
	do{
		cout<<"Enter Qustion Level :\n [1]:Easy \n [2]:Medium \n [3]:Hard\n [4]:Mix\n";
		cin>>Choice;
	}while(Choice<1||Choice>4);
	return (enQustionLevel)Choice;
}

enOperationType ReadOperationType(){
	short operation;
	do{
	cout<<"Enter Operation Type:\n [1]:Add\n [2]Subtract:\n [3]:Multiply\n [4]:Divide\n [5]:Mix\n ";
	cin>>operation;
	}while(operation<1||operation>5);
	return (enOperationType)operation;
}

int RandomNumber(int from,int to)
{
	int RandNum=rand()%(to-from+1)+ from;
	return RandNum;
}

string GetOperationSymbol(enOperationType OpType)
{
	switch(OpType)
	{
	case enOperationType::Add:
	return"+";
	case enOperationType::Subtract:
	return"-";
	case enOperationType::Multiply:
	return"x";
	case enOperationType::Divide:
	return"/";
	default:
	return "Mix";
	}
}

enOperationType GetOperationType()
{
	return (enOperationType)RandomNumber(1,4);
}

void SetScreenColor(bool Right)
{
	if(Right)
	system("color 2F");
	else{
	system("color 4F");
	cout<<"\a";
	}
}

float SimpleCalculator(enOperationType OpType,float Number1,float Number2)
{
	switch (OpType) 
 { 
 case enOperationType::Add: 
  return Number1 + Number2; 
 
 case enOperationType::Subtract: 
  return Number1 - Number2; 
 
 case enOperationType::Multiply: 
  return Number1 * Number2; 
 
 case enOperationType::Divide: 
  return (Number2 !=0)?(Number1/Number2):0; 
 
 default: 
  return Number1+Number2;
 }
}

struct stQuestion
{
      float number1=0;
	float number2=0;
	enOperationType OperationType;
	enQustionLevel QustionsLevel;
	float CorrectAnswer=0;
   	float PlayerAnswer=0;
   	bool AnswerRuslt=false;
};

struct stQuizz
{
	stQuestion QuestionList[Max_Of_Questions];
	int NumberOfQuestions;
	enQustionLevel QustionLevel ;
	enOperationType OpType;
	short NumberOfRigthAnswer=0;
   	short NumberOfWrongAnswer=0;
   	bool IsPass=false;
};

stQuestion GenerateQuestion(enQustionLevel QustionsLevel,enOperationType OperationTypeType)
{
	stQuestion Question;
	if(QustionsLevel== enQustionLevel::MixLevel){
	QustionsLevel=(enQustionLevel)RandomNumber(1,3);
	}
	
	if(OperationTypeType==enOperationType::Mix){
		OperationTypeType=GetOperationType();
	}
	
	Question.OperationType=OperationTypeType;
	switch(QustionsLevel){
		case enQustionLevel::Easy:
		Question.number1=RandomNumber(1,10);
		Question.number2=RandomNumber(1,10);
		break;
		case enQustionLevel::Medium:
		Question.number1=RandomNumber(10,50);
		Question.number2=RandomNumber(10,50);
		break;
		case enQustionLevel::Hard:
		Question.number1=RandomNumber(50,100);
		Question.number2=RandomNumber(50,100);
		break;
	}
	
	Question.CorrectAnswer=SimpleCalculator(Question.OperationType,Question.number1,Question.number2);
	Question.QustionsLevel=QustionsLevel;
	return Question;
	
}

void GenerateQuizzQuestions(stQuizz &Quizz){
	for(short Question =0;Question<Quizz.NumberOfQuestions;Question++){
		Quizz.QuestionList[Question]=GenerateQuestion(Quizz.QustionLevel,Quizz.OpType);
	}
}

void PrintQuestionsList(stQuizz &Quizz,short QustionNumber ){
	cout<<"\nQustion ["<<QustionNumber+1<<"/"<<Quizz.NumberOfQuestions<<"]\n";
	cout<<Quizz.QuestionList[QustionNumber].number1<<endl;
	cout<<Quizz.QuestionList[QustionNumber].number2<<" ";
	cout<<GetOperationSymbol(Quizz.QuestionList[QustionNumber].OperationType);
	cout<<"\n--------------"<<endl;
	
}

float ReadQustionAnswer(){
	 float Answer;
	cin>>Answer;
	return Answer;
}

void CorrectQustionAnswer(stQuizz &Quizz,short QustionNumber){
	if(Quizz.QuestionList[QustionNumber].PlayerAnswer==Quizz.QuestionList[QustionNumber].CorrectAnswer){
	cout<<"Correct Answer !\n";
	Quizz.QuestionList[QustionNumber].AnswerRuslt=true;
	Quizz.NumberOfRigthAnswer++;
	cout<<endl;
  }
  
  else{
  	cout<<"Wrong Answer ! \n"<<"Correct Answer: "<<Quizz.QuestionList[QustionNumber].CorrectAnswer<<endl;
  	Quizz.NumberOfWrongAnswer++;
	Quizz.QuestionList[QustionNumber].AnswerRuslt=false;
  }
  cout<<"\n";
  SetScreenColor(Quizz.QuestionList[QustionNumber].AnswerRuslt);
}

void AskAndCorrectAnswers(stQuizz &Quizz)
{
	for(short QustionNumber=0;QustionNumber<Quizz.NumberOfQuestions;QustionNumber++){
		PrintQuestionsList(Quizz,QustionNumber);
	      Quizz.QuestionList[QustionNumber].PlayerAnswer=ReadQustionAnswer();
	      CorrectQustionAnswer(Quizz,QustionNumber);
	Quizz.IsPass=(Quizz.NumberOfRigthAnswer>=Quizz.NumberOfWrongAnswer);
}
}
string GetFinalResultsText(bool Pass){
	if(Pass)
	return "Pass";
	else
	return "Fail";
}

string LevelName(enQustionLevel QustionLevel){
string arrLevelName[4]={"Easy","Medium","Hard","Mix"};
return arrLevelName[QustionLevel-1];
} 

void PrintQuizzResults(stQuizz Quizz){
	cout<<"\n";
	cout<<"===================================\n\n";
	cout<<"Final Results is: "<<GetFinalResultsText(Quizz.IsPass);
	cout<<"===================================\n\n";
	cout<<"Number Of Questions: "<<Quizz.NumberOfQuestions<<endl;
	cout<<"Question Level: "<<LevelName(Quizz.QustionLevel)<<"\n";
	cout<<"Operation Type: "<<GetOperationSymbol(Quizz.OpType)<<"\n";
	cout<<"Number Of Right Answer: "<<Quizz.NumberOfRigthAnswer<<"\n";
	cout<<"Number Of Wrong Answer: "<<Quizz.NumberOfWrongAnswer<<"\n";
	cout<<"===================================\n";
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions=ReadNumberOfQuestions("How Many Questions Do You Want To Answer\n");
	Quizz.QustionLevel=ReadQustionLevel();
	Quizz.OpType=ReadOperationType();
	GenerateQuizzQuestions(Quizz);
	AskAndCorrectAnswers(Quizz);
	PrintQuizzResults(Quizz);
	
}

void StartGame()
{
	
	char PlayAgain='Y';
	do{
		ResetScreen();
		PlayMathGame();
		cout<<endl<< "Do you want to play again ?(Y/N): ";
		cin>>PlayAgain;
		
	}while(PlayAgain=='Y'||PlayAgain=='y');
}

int main(){
	srand((unsigned)time(NULL));
	StartGame();
	return 0;
	
}
