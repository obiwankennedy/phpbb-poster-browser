#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QWebEngineView>
#include <QFile>
#include <QDebug>

#include <QTimer>


MainWindow::MainWindow(QString url, QString msg, bool nav, QWebEngineProfile* profile, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_nav(nav)
{
    m_msg = msg;
    ui->setupUi(this);
    m_view = new QWebEngineView();
    setCentralWidget(m_view);

    QFile file;
    file.setFileName(":/jquery-3.3.1.min.js");
    file.open(QIODevice::ReadOnly);
    jQuery = file.readAll();
    jQuery.append("\nvar qt = { 'jQuery': jQuery.noConflict(true) };");
    file.close();

    QWebEnginePage* page =nullptr;
    if(profile)
        page = new QWebEnginePage(profile,this);
    else
        page = new QWebEnginePage(this);


    m_view->setPage(page);

    //connect(m_view, &QWebEngineView::urlChanged, this, &MainWindow::setJQuery,Qt::QueuedConnection);
    connect(m_view, &QWebEngineView::loadStarted, this, [=](){
        qDebug() << "loading page";
    });
    connect(m_view, &QWebEngineView::urlChanged, this, [=](){
        QTimer::singleShot(2000,this,&MainWindow::setJQuery);
    });
    page->setUrl(QUrl::fromUserInput(url));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setJQuery()
{
    m_view->page()->runJavaScript(jQuery,[=](const QVariant &v){
        if(m_count == 0)
            copyText();
        else
             submit();
    });
}


void MainWindow::copyText()
{
        m_count++;
        //QString code = QStringLiteral("$('#message').html('%1');$('input[name=post]').click();$('#postform').submit();qt.document.getElementsByName(\"post\").submit()").arg(m_msg);//
        QString code = QStringLiteral("$('#message').html('%1');qt.jQuery('input[name=post]').click()").arg(m_msg);
            m_view->page()->runJavaScript(code,[=](const QVariant &v){
                //submit();
        });



}

void MainWindow::submit()
{
    return;
   /* */

    //auto code = QStringLiteral("$('input[name=post]').click()");
    //auto code = QStringLiteral("$('#postform').submit()");
    QString code = QStringLiteral("qt.jQuery('#postform').submit()");
    m_view->page()->runJavaScript(code,[=](const QVariant &v){
        //std::this_thread::sleep_for(std::chrono::seconds(5));
       // QTimer::singleShot(5000, qApp, &QApplication::quit);
    });
}

