#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class QWebEngineView;
class QWebEngineProfile;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString url, QString msg, bool nav,QWebEngineProfile* profile, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void copyText();
    void setJQuery();
    void submit();
private:
    Ui::MainWindow *ui;
    QString m_msg;
    QWebEngineView* m_view;
    QString jQuery;
    bool m_nav = false;
    bool m_submit = false;
    int m_count = 0;
};

#endif // MAINWINDOW_H
