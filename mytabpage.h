#ifndef MYTABPAGE_H
#define MYTABPAGE_H

#include <QWidget>
#include <QTextEdit>
#include <QList>
namespace Ui {
class MyTabPage;
}

class MyTabPage : public QWidget
{
    Q_OBJECT

public:
    explicit MyTabPage(QWidget *parent = nullptr);
    ~MyTabPage();
    QTextEdit* getTextEdit();


private:
    Ui::MyTabPage *ui;
};

#endif // MYTABPAGE_H
