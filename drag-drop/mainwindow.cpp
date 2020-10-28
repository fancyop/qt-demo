#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDragEnterEvent>
#include <QMimeData>
#include <QFile>
#include <QUrl>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //setCentralWidget(ui->textEdit);
    ui->textEdit->setAcceptDrops(false);
    ui->lineEdit->setAcceptDrops(false);
    setAcceptDrops(true);
    setWindowTitle(tr("drag-drop"));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))
        e->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    QList<QUrl> urls = e->mimeData()->urls();
    if(urls.isEmpty())
        return ;

    QString fileName = urls.first().toLocalFile();

    foreach (QUrl u, urls) {
        qDebug()<<u.toString();
    }
    qDebug()<< urls.size();

    if(fileName.isEmpty())
        return;

    if(readFile(fileName))
        setWindowTitle(tr("%1 - %2").arg(fileName).arg("Drag File"));
}

bool MainWindow::readFile(const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly | QFile::Text))
          return false;

    QByteArray data;
    data = file.readAll();
    ui->textEdit->setText(QString::fromUtf8(data));
    ui->lineEdit->setText(fileName);
    return true;
}
