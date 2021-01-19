#ifndef WELCOMDLG_H
#define WELCOMDLG_H

#include <QDialog>
#include "writelog.h"

namespace Ui {
class WelcomDlg;
}

class WelcomDlg : public QDialog
{
    Q_OBJECT

public:
    explicit WelcomDlg(QWidget *parent = nullptr);
    ~WelcomDlg();

    void outPutLogMsg(QString strInfo,QString strIndex);

signals:
    void signalSendLogMsg(QString strMsg);
private:
    Ui::WelcomDlg *ui;

    WriteLog *m_writeLog;
};

#endif // WELCOMDLG_H
