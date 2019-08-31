#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QFile"
#include "QFileInfo"
#include "QFileDialog"
#include "QTreeWidgetItem"
#include "QDebug"
#include "QTextCodec"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(1000,800);
    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,7);                  //设置splitter的比例为1:7 ,0表示右（上），1表示左（下）
    ui->splitter_2->setStretchFactor(0,6);
    ui->splitter_2->setStretchFactor(1,2);
    connect(ui->action_op,&QAction::triggered,this,&MainWindow::Openfile);
    ui->treeWidget->setHeaderHidden(true);
    flist = new QTreeWidgetItem(QStringList()<<"文件");
    ui->treeWidget->addTopLevelItem(flist);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::Openfile(){
    qDebug() << "打开成功";
    QString path= QFileDialog::getOpenFileName(this,"打开文件","C:\\Users\\Administrator\\Documents\\QT\\testcode");
    QFile file(path);
    QFileInfo info(path);
    QTreeWidgetItem *f1= new QTreeWidgetItem(QStringList()<<info.fileName());
    flist->addChild(f1);
    QTextCodec *codec =QTextCodec::codecForName("gbk");
     file.open(QIODevice::ReadOnly);
    QByteArray array =file.readAll();
    ui->textEdit->setText(codec->toUnicode(array));
    int index=flist->indexOfChild(f1);
    qDebug() << "index=" << index;
    file.close();
}
