#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "supportassignment1.h"

myStruct mainstruct;
int deallocatedIndex[21];

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //init_INT_ARRAY(&mainstruct);
    //init_CHARPTR_ARRAY(&mainstruct);

    for(int i = 0; i < 21; i = i + 1)
    {
        deallocatedIndex[i] = 255;
    }


    ui->setupUi(this);
    ui->char_lineEdit_0->setReadOnly(true);
    ui->char_lineEdit_1->setReadOnly(true);
    ui->char_lineEdit_2->setReadOnly(true);
    ui->char_lineEdit_3->setReadOnly(true);
    ui->char_lineEdit_4->setReadOnly(true);
    ui->char_lineEdit_5->setReadOnly(true);
    ui->char_lineEdit_6->setReadOnly(true);
    ui->char_lineEdit_7->setReadOnly(true);
    ui->char_lineEdit_8->setReadOnly(true);
    ui->char_lineEdit_9->setReadOnly(true);
    ui->char_lineEdit_10->setReadOnly(true);
    ui->char_lineEdit_11->setReadOnly(true);
    ui->char_lineEdit_12->setReadOnly(true);
    ui->char_lineEdit_13->setReadOnly(true);
    ui->char_lineEdit_14->setReadOnly(true);
    ui->char_lineEdit_15->setReadOnly(true);
    ui->char_lineEdit_16->setReadOnly(true);
    ui->char_lineEdit_17->setReadOnly(true);
    ui->char_lineEdit_18->setReadOnly(true);
    ui->char_lineEdit_19->setReadOnly(true);

    ui->Title_lineEdit->setReadOnly(true);

    ui->one_lineEdit->setText("Access a Pointer");
    ui->one_lineEdit->setReadOnly(true);

    ui->two_lineEdit->setText("List Deallocated Memory");
    ui->two_lineEdit->setReadOnly(true);

    ui->three_lineEdit->setText("Deallocated All Memory");
    ui->three_lineEdit->setReadOnly(true)
            ;
    ui->four_lineEdit->setText("Exit Program");
    ui->four_lineEdit->setReadOnly(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_one_pushButton_clicked()
{
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::gray);
    palette->setColor(QPalette::Text,Qt::darkGray);
    ui->four_lineEdit->setPalette(*palette);
    ui->pushButton_3->setPalette(*palette);

    ui->one_lineEdit->setText("Print Char's");
    ui->two_lineEdit->setText("Delete Char's");
    ui->three_lineEdit->setText("Return");
    state = 1;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(state == 1)
    {
        state = 0;
        ui->one_lineEdit->setText("Access a Pointer");
        ui->two_lineEdit->setText("List Deallocated Memory");
        ui->three_lineEdit->setText("Deallocated All Memory");
     }
    if(state == 0)
    {
        deallocatedInt = 0;
        for(int i = 0; i < 20; i=i+1)
        {
            if(deallocatedIndex[i] == i || i == 20){}
            else
            {
                deallocatedIndex[i] = i;
                delete mainstruct.charArray[i];
            }
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    if(state == 0)
    {
        QWidget::close();
    }
}
