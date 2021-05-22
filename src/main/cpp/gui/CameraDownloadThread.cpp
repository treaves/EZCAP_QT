#include "CameraDownloadThread.hpp"
#include "Config.h"

#include "myStruct.hpp"
#include <QElapsedTimer>
#include <QByteArray>
#include <QDebug>
#include <qhyccd.h>

extern qhyccd_handle * camera;

CameraDownloadThread::CameraDownloadThread(QObject * parent)
   : QThread(parent)
{
}

/* ****************************************************************************************************************** */
// MARK: - QThread over-rides
/* ****************************************************************************************************************** */
void CameraDownloadThread::run()
{
   unsigned int  returnCode = QHYCCD_ERROR;

   QElapsedTimer timer;
   timer.start();

   // get one frame data
   returnCode = GetQHYCCDSingleFrame(camera, &ix.imageX, &ix.imageY, &ix.imgBpp, &ix.imgChannels, ix.ImgData);
   // returnCode = GetQHYCCDSingleFrame(camera,&ix.imageX,&ix.imageY,&ix.imgBpp,&ix.imgChannels,ix.ImgData);
   if (returnCode != QHYCCD_SUCCESS) {
      qCritical() << "GetQHYCCDSingleFrame: failed";
      ix.imageReady = GetSingleFrame_Failed;
   } else {
      qDebug() << "GetQHYCCDSingleFrame: success, Time elapsed:" << timer.elapsed();

      if (ix.imgBpp == BPP_8) {
         qDebug() << "GetQHYCCDSingleFrame the readout image depth is 8bit";
         QByteArray byteArray(static_cast<int>(ix.imageX * ix.imageY * 2), 0);

         for (int i = 0, j = 1; i < static_cast<int>(ix.imageX * ix.imageY); i++) {
            byteArray[j] = static_cast<char>(ix.ImgData[i]);
            j += 2;
         }
         memcpy(ix.ImgData, byteArray.data(), ix.imageX * ix.imageY * 2);
      }

      memset(ix.lastImgData, 0, ix.ccdMaxImgW * ix.ccdMaxImgH * 2);
      memcpy(ix.lastImgData, ix.ImgData, ix.imageX * ix.imageY * 2);
      ix.lastImageX = ix.imageX;
      ix.lastImageY = ix.imageY;

      ix.imageReady = GetSingleFrame_Success;
   }
}
