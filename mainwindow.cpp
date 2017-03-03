#include "mainwindow.h"

#include <fstream>

#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QLayout>
#include <QWidget>




size_t quizPos = 0;

quizPrompt tempPrompt("", "", "");


QWidget * gWindow;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->questions.push_back(tempPrompt);
    QWidget * window = new QWidget(this);
    gWindow = window;
    this->setCentralWidget(window);

    this->h1 = new QHBoxLayout();
    this->v1 = new QVBoxLayout();
    this->symbols = new QHBoxLayout();
    this->saveLayout = new QHBoxLayout();
    this->navLayout = new QHBoxLayout();

    this->btnPi = new QPushButton(this);
    this->btnLn = new QPushButton(this);
    this->btnSqrt = new QPushButton(this);
    this->btnTheta = new QPushButton(this);
    this->btnCubert = new QPushButton(this);
    this->btnIntegral = new QPushButton(this);
    this->btnSigma = new QPushButton(this);
    this->btndoubleIntegral = new QPushButton(this);
    this->btnSaveQuiz = new QPushButton(this);
    this->btnLoadQuiz = new QPushButton(this);
    this->btnNavLeft = new QPushButton(this);
    this->btnNavRight = new QPushButton(this);

    this->btnSaveQuiz->setText("Save Quiz");
    this->btnLoadQuiz->setText("Load Quiz");
    this->btnNavLeft->setText("<<");
    this->btnNavRight->setText(">>");
    this->btnNavLeft->setObjectName("navLeft");
    this->btnNavRight->setObjectName("navRight");
    this->populateSymbols();


    topic = new QTextEdit(this);
    Question = new QTextEdit(this);
    answer = new QTextEdit(this);
    lineFileName = new QLineEdit(this);

    this->topic->setPlaceholderText("Section/topic description:");
    this->topic->setFixedHeight(50);
    this->answer->setPlaceholderText("Answer:");
    this->Question->setPlaceholderText("Question:");
    this->lineFileName->setPlaceholderText("File Name:");

    connect(btnNavLeft, SIGNAL(clicked(bool)), this, SLOT(handleNavClick()));
    connect(btnNavRight, SIGNAL(clicked(bool)), this, SLOT(handleNavClick()));

    navLayout->addWidget(btnNavLeft);
    navLayout->addWidget(btnNavRight);


    connect(btnSaveQuiz, SIGNAL(clicked(bool)), this, SLOT(saveQuizToFile()));
    connect(btnLoadQuiz, SIGNAL(clicked(bool)), this, SLOT(loadQuizFromFile()));


    saveLayout->addWidget(this->lineFileName);
    saveLayout->addWidget(this->btnSaveQuiz);
    saveLayout->addWidget(this->btnLoadQuiz);

    v1->addLayout(navLayout);
    v1->addWidget(topic);
    v1->addLayout(symbols);
    v1->addWidget(Question);
    v1->addWidget(answer);

    v1->addLayout(saveLayout);

    window->setLayout(v1);
    window->setMinimumSize(450, 400);

    topic->setFocus();



}

void MainWindow::populateSymbols()
{

    this->btnLn->setText("ln(_)");
    this->btnPi->setText("\u03C0");
    this->btnTheta->setText("\u03B8");
    this->btnSqrt->setText("\u221A");
    this->btnCubert->setText("\u221B");
    this->btnIntegral->setText("\u222B");
    this->btnSigma->setText("\u2211");
    this->btndoubleIntegral->setText("\u222C");



    this->btnCubert->setFocusPolicy(Qt::NoFocus);
    this->btnTheta->setFocusPolicy(Qt::NoFocus);
    this->btnPi->setFocusPolicy(Qt::NoFocus);
    this->btnSqrt->setFocusPolicy(Qt::NoFocus);
    this->btnLn->setFocusPolicy(Qt::NoFocus);
    this->btnSigma->setFocusPolicy(Qt::NoFocus);
    this->btnIntegral->setFocusPolicy(Qt::NoFocus);
    this->btndoubleIntegral->setFocusPolicy(Qt::NoFocus);

    this->btnLn->setObjectName("ln");
    this->btnPi->setObjectName("pi");
    this->btnTheta->setObjectName("theta");
    this->btnSqrt->setObjectName("sqrt");
    this->btnCubert->setObjectName("cubert");
    this->btnIntegral->setObjectName("integral");
    this->btndoubleIntegral->setObjectName("doubleIntegral");
    this->btnSigma->setObjectName("sigma");

    symbols->addWidget(this->btnLn);
    symbols->addWidget(this->btnPi);
    symbols->addWidget(this->btnSqrt);
    symbols->addWidget(this->btnCubert);
    symbols->addWidget(this->btnTheta);
    symbols->addWidget(this->btnSigma);
    symbols->addWidget(this->btnIntegral);
    symbols->addWidget(this->btndoubleIntegral);


    connect(btnPi, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
    connect(btnLn, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
    connect(btnTheta, SIGNAL(clicked(bool)), this, SLOT(handleSymbolClick()));
    connect(btnSqrt, SIGNAL(clicked(bool)), this, SLOT(handleSymbolClick()));
    connect(btnCubert, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
    connect(btnIntegral, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
    connect(btndoubleIntegral, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
    connect(btnSigma, SIGNAL(clicked()), this, SLOT(handleSymbolClick()));
}

void MainWindow::handleSymbolClick()
{
    QObject *callerObj = sender();
    QString caller = callerObj->objectName();
    if(!(strcmp(gWindow->focusWidget()->metaObject()->className(),"QTextEdit")))
    {
        QTextCursor cursor = ((QTextEdit*)gWindow->focusWidget())->textCursor();

        if(caller == "theta")
        {
            cursor.insertText("\u03B8");
        }
        else if(caller == "pi")
        {
            cursor.insertText("\u03C0");
        }
        else if(caller == "sqrt")
        {
            cursor.insertText("\u221A()");
        }
        else if(caller == "ln")
        {
            cursor.insertText("ln()");
        }
        else if(caller == "cubert")
        {
            cursor.insertText("\u221B()");
        }
        else if(caller == "integral")
        {
            cursor.insertText("\u222B()dx");
        }
        else if(caller == "doubleIntegral")
        {
            cursor.insertText("\u222C()dxdy");
        }
        else if(caller == "sigma")
        {
            cursor.insertText("\u2211(func, start, finish)");
        }
    }
}


void MainWindow::handleNavClick()
{
    QObject *callerObj = sender();
    QString caller = callerObj->objectName();
    this->updateQuestion();
    if(caller == "navLeft")
    {
        if(quizPos > 0)
        {
            this->updateQuestion();
            quizPos --;
            resetView();
        }
    }
    else if(caller =="navRight")
    {
        if(quizPos < questions.size() - 1)
        {
            quizPos ++;
            resetView();
        }
        else
        {
            questions.push_back(tempPrompt);
            quizPos ++;
            resetView();
        }
    }
}
/*
void MainWindow::addQuestion()
{
    QString qstn = this->Question->toHtml();
    QString ans = this->answer->toHtml();
    QString topic = this->topic->toHtml();

    quizPrompt tempQ(topic, qstn, ans);
    questions.push_back(tempQ);

    this->Question->clear();
    this->answer->clear();

}
*/
void MainWindow::saveQuizToFile()
{
    this->updateQuestion();
    std::string temp;
    temp = lineFileName->text().toStdString();
    std::ofstream fileOut(temp.c_str());

    for(size_t i = 0; i < questions.size(); i ++)
    {
        fileOut << questions[i];
        fileOut << "\n%%%%%%%%%%\n";
    }

    fileOut.close();
}

void MainWindow::loadQuizFromFile()
{
    std::string temp;
    temp = lineFileName->text().toStdString();
    std::ifstream fileIn(temp.c_str());
    quizPrompt input;
    while(fileIn.good())
    {
        fileIn >> input;
        if(!(input.isEmpty()))
        {
            questions.push_back(input);
        }
    }
    fileIn.close();
}


void MainWindow::resetView()
{
    this->topic->setHtml(questions[quizPos].getTopic());
    this->answer->setHtml(questions[quizPos].getAnswer());
    this->Question->setHtml(questions[quizPos].getQuestion());
}

void MainWindow::updateQuestion()
{
    tempPrompt.setTopic((QString) this->topic->toHtml());
    this->questions[quizPos].setTopic((QString) this->topic->toHtml());
    this->questions[quizPos].setAnswer((QString) this->answer->toHtml());
    this->questions[quizPos].setQuestion((QString) this->Question->toHtml());
}

MainWindow::~MainWindow()
{

}
