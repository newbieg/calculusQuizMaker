#ifndef QUIZPROMPT_H
#define QUIZPROMPT_H

#include <QString>
#include <vector>
#include <string>
#include <fstream>

class quizPrompt
{
public:
    quizPrompt();
    quizPrompt(QString section, QString question, QString answer);
    void addHint(QString);
    std::string toString() const;

    QString getAnswer();
    QString getTopic();
    QString getQuestion();
    void setAnswer(QString answer);
    void setTopic(QString section);
    void setQuestion(QString question);
    bool isEmpty();

private:

    QString topic;
    QString Qtn;
    QString ans;
    std::vector<QString> hints;
};

std::ostream& operator << (std::ostream& stream, const quizPrompt& prompt);
std::istream& operator >> (std::istream& stream, quizPrompt& prompt);

#endif // QUIZPROMPT_H
