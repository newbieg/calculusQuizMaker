#include "quizprompt.h"


using namespace std;

quizPrompt::quizPrompt()
{

}

quizPrompt::quizPrompt(QString section, QString question, QString answer)
{
    this->ans = answer;
    this->Qtn = question;
    this->topic = section;
}

void quizPrompt::addHint(QString hint)
{
    this->hints.push_back(hint);
}

string quizPrompt::toString() const
{
    string temp = this->topic.toStdString() + "\n%%\n" + this->Qtn.toStdString() + "\n%%\n" + this->ans.toStdString() + "\n%%\n";
    for(size_t i = 0; i < hints.size(); i ++)
    {
        temp += this->hints[i].toStdString();
        temp += "\n%%\n";
    }
    return temp;
}

ostream& operator << (ostream& stream, const quizPrompt& prompt)
{
    stream << prompt.toString();
    return stream;
}

istream& operator >> (istream& stream, quizPrompt& prompt)
{
    string temp;
    string section;
    string question;
    string answer;
    string hint;
    // get the topic
    while(stream.good() && temp != "%%" && temp != "%%%%%%%%%%")
    {
        section += temp;
        getline(stream, temp);
    }
    if(temp == "%%")
    {
        temp = "";
        while(stream.good() && temp != "%%" && temp != "%%%%%%%%%%")
        {
            question += temp;
            getline(stream, temp);
        }
    }
    if(temp == "%%")
    {
        temp = "";
        while(stream.good() && temp != "%%" && temp != "%%%%%%%%%%")
        {
            answer += temp;
            getline(stream, temp);
        }
    }
    QString first = QString::fromStdString(section);
    QString second = QString::fromStdString(question);
    QString third = QString::fromStdString(answer);
    quizPrompt tempPrompt(first, second, third);
    if(temp == "%%" && temp != "%% %%%%%%%%%%")
    {
        temp = "";
        while(stream.good() && temp != "%%%%%%%%%%")
        {
            hint += temp;
            getline(stream, temp);
            if(temp == "%%")
            {
                first = QString::fromStdString(hint);
                tempPrompt.addHint(first);
                temp = "";
            }
        }
    }
    prompt = tempPrompt;
    return stream;
}


QString quizPrompt::getAnswer()
{
    return ans;
}

QString quizPrompt::getTopic()
{
    return topic;
}


QString quizPrompt::getQuestion()
{
    return Qtn;
}

void quizPrompt::setAnswer(QString answer)
{
    this->ans = answer;
}

void quizPrompt::setQuestion(QString question)
{
    this->Qtn = question;
}

void quizPrompt::setTopic(QString section)
{
    this->topic = section;
}


bool quizPrompt::isEmpty()
{
    return (this->topic == this->Qtn && this->ans == this->topic);
}


