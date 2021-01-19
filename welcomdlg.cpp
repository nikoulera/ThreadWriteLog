#include "welcomdlg.h"
#include "ui_welcomdlg.h"
#include <QDateTime>

WelcomDlg::WelcomDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomDlg)
{
    ui->setupUi(this);
    m_writeLog = WriteLog::getInstance();
    connect(this,&WelcomDlg::signalSendLogMsg,m_writeLog,&WriteLog::slot_receMsg);
    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    outPutLogMsg("执行欢迎界面的构造函数!",str);
}

WelcomDlg::~WelcomDlg()
{
    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    outPutLogMsg("执行欢迎界面的析构函数!",str);
    delete ui;
}

void WelcomDlg::outPutLogMsg(QString strInfo,QString strIndex)
{
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd: hh:mm:ss");
    strIndex.prepend(strTime);
    strIndex.append(strInfo);
    emit signalSendLogMsg(strIndex);
}
