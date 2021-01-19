#include "writelog.h"
#include <QMutexLocker>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>


QMutex WriteLog::m_mutex;
WriteLog *WriteLog::m_instance = nullptr;
WriteLog::WriteLog(QObject *parent)
     : QObject(parent)
{
    //创建或打开日志文件
    openLogFile();

    this->moveToThread(&m_thread);
    connect(&m_thread,&QThread::started,this,&WriteLog::slot_threadStarted);
    connect(&m_thread,&QThread::finished,this,&QObject::deleteLater);
    m_thread.start();
}

void WriteLog::openLogFile()
{
    QString logDir = QCoreApplication::applicationDirPath() + "/log/" + QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QDir dir(logDir);
    if(!dir.exists())
    {
        dir.mkpath(logDir);
    }
    logDir += LOG_NAME;
    m_file = new QFile(logDir);
    if(!m_file->open(QFile::WriteOnly | QFile::Text |QFile::Append));
    {
        return ;
    }
//    m_textStream = new QTextStream(m_file);
}

void WriteLog::writeLogInfo()
{
    if(m_queue.isEmpty())
    {
        return ;
    }
    QString strMsg = m_queue.front();
    m_queue.pop_front();
    QTextStream textStream(m_file);
    textStream<<strMsg<<"\r\n";
    m_file->flush();//将缓存区数据刷新到文件中
}

WriteLog *WriteLog::getInstance()
{
    if(m_instance == nullptr)
    {
        QMutexLocker locker(&m_mutex);
        m_instance = new WriteLog;
    }
    return m_instance;
}

WriteLog::~WriteLog()//没有执行析构
{
    //关闭日志文件,退出线程
//    QString preStr1("====================================End:");
//    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
//    QString preStr2("====================================");
//    if(m_file != nullptr)
//    {
//        m_file->close();
//        delete m_file;
//        m_file = nullptr;
//    }

//    m_thread.quit();
//    m_thread.wait();
}

//void WriteLog::closeFileThread()
//{
//    QString preStr1("====================================End:");
//    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
//    QString preStr2("====================================");
//    preStr1 += time + preStr2 + "\r\n";
//    m_queue.push_back(preStr1);
//    writeLogInfo();
////    if(m_file != nullptr)
////    {
////        m_file->close();
////        delete m_file;
////        m_file = nullptr;
////    }

////    m_thread.requestInterruption();
////    m_thread.quit();
////    m_thread.wait();
//}

void WriteLog::slot_receMsg(QString str)
{
    m_queue.push_back(str);
    writeLogInfo();
}

void WriteLog::slot_threadStarted()
{
    QString preStr1("====================================Begin:");
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    QString preStr2("====================================");
    preStr1 += time + preStr2 + "\r\n";

    QString str = QString("%1 :%2(%3): ").arg(__FILE__).arg(__FUNCTION__).arg(__LINE__);
    QString strTime = QDateTime::currentDateTime().toString("yyyy-MM-dd: hh:mm:ss");
    QString info("写日志线程启动");
    strTime += str;
    info.prepend(strTime);
    info.prepend(preStr1);
    m_queue.push_back(info);
    writeLogInfo();
}

//void WriteLog::slot_threadFinished()
//{
////    qDebug()<<"线程完成！";
//    m_queue.push_back("写日志线程结束");
//    writeLogInfo();
//}
