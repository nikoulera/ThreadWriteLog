#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "welcomdlg.h"
#include "writelog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    void checkedLoginInInfo();
    void outPutLogMsg(QString strInfo,QString strIndex);

protected:
//    void closeEvent(QCloseEvent *event);
signals:
    void signalSendLogMsg(QString strMsg);

private slots:
    void on_enterButton_clicked();

    void on_cancelButton_clicked();

private:
    Ui::Dialog *ui;

    WelcomDlg *m_welcomDlg;
    WriteLog  *m_writeLog;
};
#endif // DIALOG_H
