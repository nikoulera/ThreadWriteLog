#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    m_welcomDlg = new WelcomDlg(this);
    m_writeLog = WriteLog::getInstance();
    connect(this,&Dialog::signalSendLogMsg,m_writeLog,&WriteLog::slot_receMsg);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::checkedLoginInInfo()
{
    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    outPutLogMsg("开始验证登录信息！",str);

    QString strAccount = ui->lineEditAccount->text().trimmed();
    QString strPassword = ui->lineEditPassword->text();

    QString strMsg = "用户名：" + strAccount + "密码：" + strPassword;
    QString strInfo = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    outPutLogMsg(strMsg,strInfo);

    if(strAccount.compare("123") == 0 && strPassword.compare("123") == 0)//大小写敏感的
    {
        QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
        outPutLogMsg("登录信息正确！",str);

        accept();//隐藏模式对话框
        m_welcomDlg->show();
    }
    else
    {
        QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
        outPutLogMsg("登录信息输入错误！",str);

        QMessageBox::warning(this,tr("警告"),tr("用户名或密码错误，请重新输入！"),QMessageBox::Yes);
        on_cancelButton_clicked();
        ui->lineEditAccount->setFocus();
    }
}

void Dialog::outPutLogMsg(QString strInfo,QString strIndex)
{
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd: hh:mm:ss");
    strIndex.prepend(strTime);
    strIndex.append(strInfo);
    emit signalSendLogMsg(strIndex);
}

//void Dialog::closeEvent(QCloseEvent *event)
//{
//    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
//    outPutLogMsg("执行关闭事件",str);
//    Q_UNUSED(event);
//    m_writeLog->closeFileThread();
//}


void Dialog::on_enterButton_clicked()
{
    checkedLoginInInfo();
}

void Dialog::on_cancelButton_clicked()
{
    ui->lineEditAccount->clear();//清空之后，恢复原来的提示文字
    ui->lineEditPassword->clear();

    QString strMsg = QString::number(0);
    strMsg = strMsg.prepend("数据被清空为：");
    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    outPutLogMsg(strMsg,str);
}
