#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytabpage.h"
#include <QFileDialog>
#include <QTextStream>
#include <QFile>
#include<QCoreApplication>
#include <QTextCharFormat>
#include <QFont>
#include <QTextCursor>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->clear();
    editList.append(new MyTabPage);
    ui->tabWidget->addTab(editList.at(0), "untitled");
    ui->stackedWidget->setCurrentIndex(1);
    fileList.append(new QFile());
}

MainWindow::~MainWindow()
{
    ui->tabWidget->clear();
    for(auto node: fileList)
        delete node;
    for(auto node: editList)
        delete node;
    delete ui;
}


void MainWindow::on_actionNew_File_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    editList.append(new MyTabPage());
    ui->tabWidget->addTab(editList.at(editList.size()-1), "untitled");
    ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
    fileList.append(new QFile());

    ui->actionSave->setEnabled(true);
    ui->actionSave_As->setEnabled(true);
    ui->actionCut->setEnabled(true);
    ui->actionCopy->setEnabled(true);
    ui->actionPaste->setEnabled(true);
    ui->actionSelect_All->setEnabled(true);
    ui->actionUndo->setEnabled(true);
    ui->actionRedo->setEnabled(true);
    ui->actionBold->setEnabled(true);
    ui->actionSubscript->setEnabled(true);
    ui->actionSuperscript->setEnabled(true);
}

void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    delete fileList.at(index);
    editList.removeAt(index);
    fileList.removeAt(index);
    ui->tabWidget->removeTab(index);
    if(!ui->tabWidget->count())
    {
        ui->stackedWidget->setCurrentIndex(0);
        ui->actionSave->setEnabled(false);
        ui->actionSave_As->setEnabled(false);
        ui->actionCut->setEnabled(false);
        ui->actionCopy->setEnabled(false);
        ui->actionPaste->setEnabled(false);
        ui->actionSelect_All->setEnabled(false);
        ui->actionUndo->setEnabled(false);
        ui->actionRedo->setEnabled(false);
        ui->actionBold->setEnabled(false);
        ui->actionSubscript->setEnabled(false);
        ui->actionSuperscript->setEnabled(false);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), "./");
    if(!file.isEmpty())
    {
        ui->actionSave->setEnabled(true);
        ui->actionSave_As->setEnabled(true);
        ui->actionCut->setEnabled(true);
        ui->actionCopy->setEnabled(true);
        ui->actionPaste->setEnabled(true);
        ui->actionSelect_All->setEnabled(true);
        ui->actionUndo->setEnabled(true);
        ui->actionRedo->setEnabled(true);
        ui->actionBold->setEnabled(true);
        ui->actionSubscript->setEnabled(true);
        ui->actionSuperscript->setEnabled(true);

        fileList.append(new QFile(file));
        ui->stackedWidget->setCurrentIndex(1);
        editList.append(new MyTabPage());
        ui->tabWidget->addTab(editList.at(editList.size()-1), "untitled");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);

        int index = ui->tabWidget->currentIndex();
        if(fileList.at(index)->open(QFile::ReadOnly | QFile::Text))
        {
            QTextStream in(fileList.at(index));
            QString text = in.readAll();
            fileList.at(index)->close();
            QFileInfo fileInfo(fileList.at(index)->fileName());

            int index = ui->tabWidget->currentIndex();
            ui->tabWidget->setTabText(index, QString(fileInfo.fileName()));
            editList.at(index)->getTextEdit()->setText(text);
        }
    }
}

void MainWindow::on_actionSave_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    if(fileList.at(index)->fileName().isEmpty())
    {
        on_actionSave_As_triggered();
        QFileInfo fileInfo(fileList.at(index)->fileName());
        if(!fileInfo.fileName().isEmpty())
            ui->tabWidget->setTabText(index, fileInfo.fileName());
    }
    if(fileList.at(index)->open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(fileList.at(index));
        out << editList.at(index)->getTextEdit()->toHtml();

        fileList.at(index)->flush();
        fileList.at(index)->close();
    }
}

void MainWindow::on_actionSave_As_triggered()
{

    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    QString file = QFileDialog::getSaveFileName(this, "Save file");

    fileList.at(index)->setFileName(file);
    if(fileList.at(index)->open(QFile::WriteOnly | QFile::Text))
    {
        QTextStream out(fileList.at(index));
        out << editList.at(index)->getTextEdit()->toHtml();

        fileList.at(index)->flush();
        fileList.at(index)->close();
    }
}

void MainWindow::on_actionUndo_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->redo();
}

void MainWindow::on_actionCut_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->paste();
}

void MainWindow::on_actionSelect_All_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    editList.at(index)->getTextEdit()->selectAll();
}

void MainWindow::on_actionQuit_triggered()
{
    QCoreApplication::quit();
}

void MainWindow::on_actionBold_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    QTextCursor cursor = editList.at(index)->getTextEdit()->textCursor();
    bool isBold = cursor.charFormat().font().bold();
    QTextCharFormat fmt;
    fmt.setFontWeight(isBold ? QFont::Normal : QFont::Bold);
    cursor.mergeCharFormat(fmt);
    editList.at(index)->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionSubscript_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    QTextCursor cursor = editList.at(index)->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    fmt.setVerticalAlignment((cursor.charFormat().verticalAlignment() == QTextCharFormat::AlignSubScript)? QTextCharFormat::AlignNormal : QTextCharFormat::AlignSubScript);
    cursor.mergeCharFormat(fmt);
    editList.at(index)->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionSuperscript_triggered()
{
    int index = ui->tabWidget->currentIndex();
    if (index < 0)
        return;
    QTextCursor cursor = editList.at(index)->getTextEdit()->textCursor();
    QTextCharFormat fmt;
    fmt.setVerticalAlignment((cursor.charFormat().verticalAlignment() == QTextCharFormat::AlignSuperScript)? QTextCharFormat::AlignNormal : QTextCharFormat::AlignSuperScript);
    cursor.mergeCharFormat(fmt);
    editList.at(index)->getTextEdit()->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_aboutMeButton_clicked()
{
    QString title = "About Me";
    QFile file(":/resources/data/aboutMe.html");
    QString description = "" ;
    if(file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream in(&file);
        description = in.readAll();
        file.close();
    }
    QMessageBox::information(this, title, description);
}


