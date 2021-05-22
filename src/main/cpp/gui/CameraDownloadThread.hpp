#pragma once

#include <QThread>

class CameraDownloadThread : public QThread
{
   Q_OBJECT
   Q_DISABLE_COPY_MOVE(CameraDownloadThread)
public:
   explicit CameraDownloadThread(QObject * parent = nullptr);

signals:

public slots:

protected:
   void run() override;
};
