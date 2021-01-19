#ifndef WRITELOG_H
#define WRITELOG_H

#include <QObject>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QFile>
#include <QTextStream>

#define LOG_NAME "/log.txt"

class WriteLog : public QObject
{
    Q_OBJECT
private:
    explicit WriteLog(QObject *parent = nullptr);
    void openLogFile();
    void writeLogInfo();
public:
    static WriteLog * getInstance();
    ~WriteLog();

//    void closeFileThread();
signals:

public slots:
    void slot_receMsg(QString str);
    void slot_threadStarted();
//    void slot_threadFinished();
private:
    static QMutex m_mutex;
    static WriteLog *m_instance;
    QThread m_thread;
    QQueue<QString>  m_queue;
    QFile *m_file;
//    QTextStream *m_textStream;//似乎不能chuang创建指针
};

#endif // WRITELOG_H
