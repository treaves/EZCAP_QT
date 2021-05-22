#include "ui/ezCap.hpp"
#include <QApplication>
#include <QTextCodec>
#include <QPushButton>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <qhyccd.h>
#include <QStyleFactory>
#include <QScreen>
#include <QDebug>

#include <qhyccd.h>

QString logFileFullName;

char _mali_clz_lut[256] = {
    8, 7, 6, 6, 5, 5, 5, 5, 4, 4, 4, 4, 4, 4, 4, 4,
    3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};
//回调函数实现debug信息到文件
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
  Q_UNUSED(context)
    QByteArray localMsg = msg.toLocal8Bit();
    QString logText = "";
    switch (type)
    {
    case QtDebugMsg:
        //logText = QString("\tDebug\t %1 (%2:%3, %4)").arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
        logText = QString("\tDebug\t %1").arg(localMsg.constData());
        break;
    case QtInfoMsg:
        logText = QString("\tInfo\t %1").arg(localMsg.constData());
        break;
    case QtWarningMsg:
        logText = QString("\tWarning\t %1").arg(localMsg.constData());
        break;
    case QtCriticalMsg:
        logText = QString("\tCritical\t %1").arg(localMsg.constData());
        break;
    case QtFatalMsg:
        logText = QString("\tFatal\t %1").arg(localMsg.constData());
        abort();
    }

    QDateTime dt = QDateTime::currentDateTime();//获取系统现在的时间
    QString current_date = dt.toString("yyyy/MM/dd hh:mm:ss");

    QFile outFile(logFileFullName);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
    {
        QTextStream logTextStream(&outFile);
        logTextStream << current_date << logText << Qt::endl;

        outFile.flush();
        outFile.close();
    }
    else
    {
        qDebug() << "Failed to open log file.";
    }
}

static void installMsgHandler()
{
    //create a logfilename with current datatime
    QDateTime dt = QDateTime::currentDateTime();//get the current system datatime
    QString current_date = dt.toString("yyyy-MM-dd.hh-mm-ss");

    QString logPath = QCoreApplication::applicationDirPath() + "/log";
    logPath = QDir::toNativeSeparators(logPath);

    QDir logdir;
    if(!logdir.exists(logPath))
        logdir.mkdir(logPath); //if log folder not exists, make it

    QString logfileName = current_date + ".log";
    logFileFullName = logPath + "/" + logfileName;
    logFileFullName = QDir::toNativeSeparators(logFileFullName);

#ifdef QT_NO_DEBUG_OUTPUT
    qInstallMessageHandler(myMessageOutput);
#else
    qInstallMessageHandler(0);  //To restore the message handler, will output to console
#endif

}

int main(int argc, char *argv[])
{
#if(QT_VERSION >= QT_VERSION_CHECK(4,0,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication a(argc, argv);

    const double DEFAULT_DPI = 96.0;
//    HDC screen = GetDC(NULL);
//    FLOAT dpiX = static_cast<FLOAT>(GetDeviceCaps(screen, LOGPIXELSX));
//    ReleaseDC(0, screen);
//    float fontSize = dpiX / DEFAULT_DPI;
//    QFont font = a.font();
//    font.setPointSize(font.pointSize()*fontSize);
//    a.setFont(font);

      QList<QScreen*> screens = QApplication::screens();
      if (screens.size() > 0) {
          QScreen* screen = screens[0];
          double dpiX = screen->logicalDotsPerInch();
          //rate = dpiX / 96.0;
          double fontSize = dpiX / DEFAULT_DPI;
          if (fontSize < 1.1) {
              fontSize = 1.0;
          } else if (fontSize < 1.4) {
              fontSize = 1.25;
          } else if (fontSize < 1.6) {
              fontSize = 1.5;
          } else if (fontSize < 1.8) {
              fontSize = 1.75;
          } else {
              fontSize = 2.0;
          }
          QFont font = a.font();
          font.setPointSize(static_cast<int>(font.pointSize() * fontSize));
          a.setFont(font);
      }

    installMsgHandler();

    unsigned int ret=0;
    QDir *temp = new QDir;
    bool exist = temp->exists("./Bias");
    if(!exist)
    {
        bool ok = temp->mkdir("./Bias");
        if(ok)
        {
            qDebug() << "mkdir Bias failed" << Qt::endl;
        }
    }
    exist = temp->exists("./Black");
    if(!exist)
    {
        bool ok = temp->mkdir("./Black");
        if(ok)
        {
            qDebug() << "mkdir Black failed" << Qt::endl;
        }
    }
    ret = InitQHYCCDResource();
    if(ret != QHYCCD_SUCCESS)
    {
        qCritical("InitQHYCCDResource: failed");
    }
    else
    {
        qDebug() << "EZCAP   InitQHYCCDSDK success";
    }
//20200426 lyl 修正样式
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    //set application stylesheet
    QString qss;
    QFile qssFile(":/qss/style.qss");
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen())
    {
        qss = QLatin1String(qssFile.readAll());
        a.setStyleSheet(qss);
        qssFile.close();
    }
//    double rate = 0;
//    QList<QScreen*> screens = QApplication::screens();
//    if (screens.size() > 0) {
//        QScreen* screen = screens[0];
//        double dpi = screen->logicalDotsPerInch();
//        rate = dpi / 96.0;
//        if (rate < 1.1) {
//            rate = 1.0;
//        } else if (rate < 1.4) {
//            rate = 1.25;
//        } else if (rate < 1.6) {
//            rate = 1.5;
//        } else if (rate < 1.8) {
//            rate = 1.75;
//        } else {
//            rate = 2.0;
//        }
//    }
//    qputenv("QT_SCALE_FACTOR", QString::number(rate).toLatin1());
    EZCAP w;
    w.resize(1024,768);//*rate *rate
    w.show();
    return a.exec();
}
