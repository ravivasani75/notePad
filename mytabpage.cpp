#include "mytabpage.h"
#include "ui_mytabpage.h"
#include <QTextCursor>
#include <QTextEdit>

MyTabPage::MyTabPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyTabPage)
{
    ui->setupUi(this);
}

MyTabPage::~MyTabPage()
{
    delete ui;
}

QTextEdit* MyTabPage::getTextEdit()
{
    return ui->textEdit;
}
