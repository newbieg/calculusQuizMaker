#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "quizprompt.h"

#include <vector>

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void populateSymbols();
    void resetView();
    void updateQuestion();
    ~MainWindow();

private:

    QVBoxLayout * v1;
    QHBoxLayout * h1;
    QHBoxLayout * symbols;
    QHBoxLayout * saveLayout;
    QHBoxLayout * navLayout;


    QPushButton * btnPi;
    QPushButton * btnLn;
    QPushButton * btnTheta;
    QPushButton * btnSqrt;
    QPushButton * btnSigma;
    QPushButton * btnCubert;
    QPushButton * btnIntegral;
    QPushButton * btndoubleIntegral;

    QTextEdit * topic;
    QTextEdit * Question;
    QTextEdit * answer;

    QLineEdit *lineFileName;
    QPushButton *btnSaveQuiz;
    QPushButton *btnLoadQuiz;
    QPushButton *btnNavRight;
    QPushButton *btnNavLeft;


    QPushButton browseQuestionImages;

    std::vector <quizPrompt> questions;

public slots:
//    void addQuestion();
    void handleSymbolClick();
    void handleNavClick();
    void saveQuizToFile();
    void loadQuizFromFile();

};

#endif // MAINWINDOW_H
