#include "downloadPreThread.hpp"
#include "dllqhyccd.hpp"
//#include "qhyccdStatus.h"
#include "myStruct.hpp"

#include <QDebug>
#include <QElapsedTimer>

extern qhyccd_handle *camhandle;

DownloadPreThread::DownloadPreThread(QObject *parent) :
    QThread(parent)
{
}

void DownloadPreThread::run()
{
    unsigned int ret = QHYCCD_ERROR;

    QElapsedTimer t0_prev;
    t0_prev.start();

    //get one frame data
    ret = libqhyccd->GetQHYCCDSingleFrame(camhandle,&ix.imageX,&ix.imageY,&ix.imgBpp,&ix.imgChannels,ix.ImgData);
    //ret = GetQHYCCDSingleFrame(camhandle,&ix.imageX,&ix.imageY,&ix.imgBpp,&ix.imgChannels,ix.ImgData);
    if(ret != QHYCCD_SUCCESS)
    {
        qCritical() << "GetQHYCCDSingleFrame: failed";
        ix.imageReady = GetSingleFrame_Failed;
    }
    else
    {
        qDebug() << "GetQHYCCDSingleFrame: success, Time elapsed:" << t0_prev.elapsed();

        if(ix.imgBpp == 8)
        {
            qDebug("GetQHYCCDSingleFrame the readout image depth is 8bit");
          char *temparray = static_cast<char *>(malloc(ix.imageX * ix.imageY * 2));

            int i = 0,j = 1;
          for(;i < static_cast<int>(ix.imageX * ix.imageY);i++)
            {
              temparray[j] = static_cast<char>(ix.ImgData[i]);
                j += 2;
            }

            memcpy(ix.ImgData,temparray,ix.imageX * ix.imageY * 2);
            delete(temparray);
        }

        memset(ix.lastImgData, 0, ix.ccdMaxImgW * ix.ccdMaxImgH * 2);
        memcpy(ix.lastImgData, ix.ImgData, ix.imageX * ix.imageY * 2);
        ix.lastImageX = ix.imageX;
        ix.lastImageY = ix.imageY;

        ix.imageReady = GetSingleFrame_Success;

    }

}
