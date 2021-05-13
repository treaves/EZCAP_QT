#include "dllqhyccd.hpp"
dllqhyccd *libqhyccd;
#ifdef  Q_OS_WIN32
QLibrary dll("qhyccd.dll");
#endif
#ifdef Q_OS_LINUX
QLibrary dll("/usr/local/lib/libqhyccd.so");
#endif
#ifdef Q_OS_MAC
QLibrary dll("/usr/local/lib/libqhyccd.dylib");
#endif

dllqhyccd::dllqhyccd()
{
    qDebug()<<"dllqhyccd() start~~";
    if (dll.load())
    {        qDebug()<<"DLL load is OK!";
#if (defined Q_OS_WIN32) && (!defined Q_OS_WIN64) // Q_OS_WIN32 is defined even Q_OS_WIN64 is defined
        InitQHYCCDResource=reinterpret_cast<QTInitQHYCCDResource>(dll.resolve("_InitQHYCCDResource@0"));
        GetQHYCCDFWVersion=reinterpret_cast<QTGetQHYCCDFWVersion>(dll.resolve("_GetQHYCCDFWVersion@8"));
        GetQHYCCDFPGAVersion=reinterpret_cast<QTGetQHYCCDFPGAVersion>(dll.resolve("_GetQHYCCDFPGAVersion@12"));
        GetQHYCCDSDKVersion=reinterpret_cast<QTGetQHYCCDSDKVersion>(dll.resolve("_GetQHYCCDSDKVersion@16"));
        GetQHYCCDSDKBuildVersion=reinterpret_cast<QTGetQHYCCDSDKBuildVersion>(dll.resolve("_GetQHYCCDSDKBuildVersion@0"));
        IsQHYCCDControlAvailable=reinterpret_cast<QTIsQHYCCDControlAvailable>(dll.resolve("_IsQHYCCDControlAvailable@8"));
        GetQHYCCDChipInfo=reinterpret_cast<QTGetQHYCCDChipInfo>(dll.resolve("_GetQHYCCDChipInfo@32"));
        GetQHYCCDMemLength=reinterpret_cast<QTGetQHYCCDMemLength>(dll.resolve("_GetQHYCCDMemLength@4"));
        GetQHYCCDParam=reinterpret_cast<QTGetQHYCCDParam>(dll.resolve("_GetQHYCCDParam@8"));
        GetQHYCCDParamMinMaxStep=reinterpret_cast<QTGetQHYCCDParamMinMaxStep>(dll.resolve("_GetQHYCCDParamMinMaxStep@20"));
        //if(GetQHYCCDParamMinMaxStep)qDebug()<<"GetQHYCCDParamMinMaxStep   -----";
        GetQHYCCDHumidity=reinterpret_cast<QTGetQHYCCDHumidity>(dll.resolve("_GetQHYCCDHumidity@8"));
        GetQHYCCDPressure=reinterpret_cast<QTGetQHYCCDPressure>(dll.resolve("_GetQHYCCDPressure@8"));
        GetQHYCCDNumberOfReadModes=reinterpret_cast<QTGetQHYCCDNumberOfReadModes>(dll.resolve("_GetQHYCCDNumberOfReadModes@8"));
        GetQHYCCDReadModeName=reinterpret_cast<QTGetQHYCCDReadModeName>(dll.resolve("_GetQHYCCDReadModeName@12"));
        GetQHYCCDReadMode=reinterpret_cast<QTGetQHYCCDReadMode>(dll.resolve("_GetQHYCCDReadMode@8"));
        GetQHYCCDReadingProgress=reinterpret_cast<QTGetQHYCCDReadingProgress>(dll.resolve("_GetQHYCCDReadingProgress@4"));
        GetQHYCCDOverScanArea=reinterpret_cast<QTGetQHYCCDOverScanArea>(dll.resolve("_GetQHYCCDOverScanArea@20"));
        GetQHYCCDEffectiveArea=reinterpret_cast<QTGetQHYCCDEffectiveArea>(dll.resolve("_GetQHYCCDEffectiveArea@20"));
        CancelQHYCCDExposingAndReadout=reinterpret_cast<QTCancelQHYCCDExposingAndReadout>(dll.resolve("_CancelQHYCCDExposingAndReadout@4"));
        CloseQHYCCD=reinterpret_cast<QTCloseQHYCCD>(dll.resolve("_CloseQHYCCD@4"));
        ReleaseQHYCCDResource=reinterpret_cast<QTReleaseQHYCCDResource>(dll.resolve("_ReleaseQHYCCDResource@0"));
        ScanQHYCCD=reinterpret_cast<QTScanQHYCCD>(dll.resolve("_ScanQHYCCD@0"));
        GetQHYCCDId=reinterpret_cast<QTGetQHYCCDId>(dll.resolve("_GetQHYCCDId@8"));
        OpenQHYCCD=reinterpret_cast<QTOpenQHYCCD>(dll.resolve("_OpenQHYCCD@4"));
        SetQHYCCDParam=reinterpret_cast<QTSetQHYCCDParam>(dll.resolve("_SetQHYCCDParam@16"));
        SetQHYCCDReadMode=reinterpret_cast<QTSetQHYCCDReadMode>(dll.resolve("_SetQHYCCDReadMode@8"));
        SetQHYCCDStreamMode=reinterpret_cast<QTSetQHYCCDStreamMode>(dll.resolve("_SetQHYCCDStreamMode@8"));
        SetQHYCCDBinMode=reinterpret_cast<QTSetQHYCCDBinMode>(dll.resolve("_SetQHYCCDBinMode@12"));
        SetQHYCCDResolution=reinterpret_cast<QTSetQHYCCDResolution>(dll.resolve("_SetQHYCCDResolution@20"));
        InitQHYCCD=reinterpret_cast<QTInitQHYCCD>(dll.resolve("_InitQHYCCD@4"));
        QHYCCDI2CTwoWrite=reinterpret_cast<QTQHYCCDI2CTwoWrite>(dll.resolve("_QHYCCDI2CTwoWrite@12"));
        QHYCCDI2CTwoRead=reinterpret_cast<QTQHYCCDI2CTwoRead>(dll.resolve("_QHYCCDI2CTwoRead@8"));
        ExpQHYCCDSingleFrame=reinterpret_cast<QTExpQHYCCDSingleFrame>(dll.resolve("_ExpQHYCCDSingleFrame@4"));
        BeginQHYCCDLive=reinterpret_cast<QTBeginQHYCCDLive>(dll.resolve("_BeginQHYCCDLive@4"));
        GetQHYCCDSingleFrame=reinterpret_cast<QTGetQHYCCDSingleFrame>(dll.resolve("_GetQHYCCDSingleFrame@24"));
        GetQHYCCDLiveFrame=reinterpret_cast<QTGetQHYCCDLiveFrame>(dll.resolve("_GetQHYCCDLiveFrame@24"));
        ControlQHYCCDShutter=reinterpret_cast<QTControlQHYCCDShutter>(dll.resolve("_ControlQHYCCDShutter@8"));
        SetQHYCCDTrigerFunction=reinterpret_cast<QTSetQHYCCDTrigerFunction>(dll.resolve("_SetQHYCCDTrigerFunction@8"));
        SendFourLine2QHYCCDInterCamOled=reinterpret_cast<QTSendFourLine2QHYCCDInterCamOled>(dll.resolve("_SendFourLine2QHYCCDInterCamOled@20"));
        SendOrder2QHYCCDCFW=reinterpret_cast<QTSendOrder2QHYCCDCFW>(dll.resolve("_SendOrder2QHYCCDCFW@12"));
        GetQHYCCDCFWStatus=reinterpret_cast<QTGetQHYCCDCFWStatus>(dll.resolve("_GetQHYCCDCFWStatus@8"));
        OSXInitQHYCCDFirmware=reinterpret_cast<QTOSXInitQHYCCDFirmware>(dll.resolve("_OSXInitQHYCCDFirmware@4"));
        SetQHYCCDFineTone=reinterpret_cast<QTSetQHYCCDFineTone>(dll.resolve("_SetQHYCCDFineTone@20"));
        EnableQHYCCDImageOSD=reinterpret_cast<QTEnableQHYCCDImageOSD>(dll.resolve("_EnableQHYCCDImageOSD@8"));
        TestQHYCCDPIDParas=reinterpret_cast<QTTestQHYCCDPIDParas>(dll.resolve("_TestQHYCCDPIDParas@28"));
        CheckPHD2Status=reinterpret_cast<QTCheckPHD2Status>(dll.resolve("_CheckPHD2Status@4"));
        Connect2PHD2=reinterpret_cast<QTConnect2PHD2>(dll.resolve("_Connect2PHD2@0"));
        DisConnect2PHD2=reinterpret_cast<QTDisConnect2PHD2>(dll.resolve("_DisConnect2PHD2@0"));
        //if(DisConnect2PHD2)qDebug()<<"1---";
        ControlPHD2Dither=reinterpret_cast<QTControlPHD2Dither>(dll.resolve("_ControlPHD2Dither@12"));
        //if(ControlPHD2Dither)qDebug()<<"2---";
        PausePHD2Dither=reinterpret_cast<QTPausePHD2Dither>(dll.resolve("_PausePHD2Dither@0"));
        //if(PausePHD2Dither)qDebug()<<"3---";
        EnableQHYCCDMessage=reinterpret_cast<QTEnableQHYCCDMessage>(dll.resolve("_EnableQHYCCDMessage@4"));

        RegisterPnpEvent=reinterpret_cast<QTRegisterPnpEvent>(dll.resolve("RegisterPnpEvent"));
        RegisterTransferEventError=reinterpret_cast<QTRegisterTransferEventError>(dll.resolve("RegisterTransferEventError"));
        RegisterPnpEventIn=reinterpret_cast<QTRegisterPnpEventIn>(dll.resolve("RegisterPnpEventIn"));
        RegisterPnpEventOut=reinterpret_cast<QTRegisterPnpEventOut>(dll.resolve("RegisterPnpEventOut"));
        RegisterDataEventSingle=reinterpret_cast<QTRegisterDataEventSingle>(dll.resolve("RegisterDataEventSingle"));
        RegisterDataEventLive=reinterpret_cast<QTRegisterDataEventLive>(dll.resolve("RegisterDataEventLive"));
        GetCameraIsSuperSpeedFromID=reinterpret_cast<QTGetCameraIsSuperSpeedFromID>(dll.resolve("_GetCameraIsSuperSpeedFromID@4"));
        GetCameraStatusFromID=reinterpret_cast<QTGetCameraStatusFromID>(dll.resolve("_GetCameraStatusFromID@4"));
        ControlQHYCCDGuide=reinterpret_cast<QTControlQHYCCDGuide>(dll.resolve("_ControlQHYCCDGuide@12"));
#else
    InitQHYCCDResource=reinterpret_cast<QTInitQHYCCDResource>(dll.resolve("InitQHYCCDResource"));
    GetQHYCCDFWVersion=reinterpret_cast<QTGetQHYCCDFWVersion>(dll.resolve("GetQHYCCDFWVersion"));
    GetQHYCCDFPGAVersion=reinterpret_cast<QTGetQHYCCDFPGAVersion>(dll.resolve("GetQHYCCDFPGAVersion"));
    GetQHYCCDSDKVersion=reinterpret_cast<QTGetQHYCCDSDKVersion>(dll.resolve("GetQHYCCDSDKVersion"));
    GetQHYCCDSDKBuildVersion=reinterpret_cast<QTGetQHYCCDSDKBuildVersion>(dll.resolve("GetQHYCCDSDKBuildVersion"));
    IsQHYCCDControlAvailable=reinterpret_cast<QTIsQHYCCDControlAvailable>(dll.resolve("IsQHYCCDControlAvailable"));
    GetQHYCCDChipInfo=reinterpret_cast<QTGetQHYCCDChipInfo>(dll.resolve("GetQHYCCDChipInfo"));
    GetQHYCCDMemLength=reinterpret_cast<QTGetQHYCCDMemLength>(dll.resolve("GetQHYCCDMemLength"));
    GetQHYCCDParam=reinterpret_cast<QTGetQHYCCDParam>(dll.resolve("GetQHYCCDParam"));
    GetQHYCCDParamMinMaxStep=reinterpret_cast<QTGetQHYCCDParamMinMaxStep>(dll.resolve("GetQHYCCDParamMinMaxStep"));
    GetQHYCCDHumidity=reinterpret_cast<QTGetQHYCCDHumidity>(dll.resolve("GetQHYCCDHumidity"));
    GetQHYCCDPressure=reinterpret_cast<QTGetQHYCCDPressure>(dll.resolve("GetQHYCCDPressure"));
    GetQHYCCDNumberOfReadModes=reinterpret_cast<QTGetQHYCCDNumberOfReadModes>(dll.resolve("GetQHYCCDNumberOfReadModes"));
    GetQHYCCDReadModeName=reinterpret_cast<QTGetQHYCCDReadModeName>(dll.resolve("GetQHYCCDReadModeName"));
    GetQHYCCDReadMode=reinterpret_cast<QTGetQHYCCDReadMode>(dll.resolve("GetQHYCCDReadMode"));
    GetQHYCCDReadingProgress=reinterpret_cast<QTGetQHYCCDReadingProgress>(dll.resolve("GetQHYCCDReadingProgress"));
    GetQHYCCDOverScanArea=reinterpret_cast<QTGetQHYCCDOverScanArea>(dll.resolve("GetQHYCCDOverScanArea"));
    GetQHYCCDEffectiveArea=reinterpret_cast<QTGetQHYCCDEffectiveArea>(dll.resolve("GetQHYCCDEffectiveArea"));
    CancelQHYCCDExposingAndReadout=reinterpret_cast<QTCancelQHYCCDExposingAndReadout>(dll.resolve("CancelQHYCCDExposingAndReadout"));
    CloseQHYCCD=reinterpret_cast<QTCloseQHYCCD>(dll.resolve("CloseQHYCCD"));
    ReleaseQHYCCDResource=reinterpret_cast<QTReleaseQHYCCDResource>(dll.resolve("ReleaseQHYCCDResource"));
    ScanQHYCCD=reinterpret_cast<QTScanQHYCCD>(dll.resolve("ScanQHYCCD"));
    GetQHYCCDId=reinterpret_cast<QTGetQHYCCDId>(dll.resolve("GetQHYCCDId"));
    OpenQHYCCD=reinterpret_cast<QTOpenQHYCCD>(dll.resolve("OpenQHYCCD"));
    SetQHYCCDParam=reinterpret_cast<QTSetQHYCCDParam>(dll.resolve("SetQHYCCDParam"));
    SetQHYCCDReadMode=reinterpret_cast<QTSetQHYCCDReadMode>(dll.resolve("SetQHYCCDReadMode"));
    SetQHYCCDStreamMode=reinterpret_cast<QTSetQHYCCDStreamMode>(dll.resolve("SetQHYCCDStreamMode"));
    SetQHYCCDBinMode=reinterpret_cast<QTSetQHYCCDBinMode>(dll.resolve("SetQHYCCDBinMode"));
    SetQHYCCDResolution=reinterpret_cast<QTSetQHYCCDResolution>(dll.resolve("SetQHYCCDResolution"));
    InitQHYCCD=reinterpret_cast<QTInitQHYCCD>(dll.resolve("InitQHYCCD"));
    QHYCCDI2CTwoWrite=reinterpret_cast<QTQHYCCDI2CTwoWrite>(dll.resolve("QHYCCDI2CTwoWrite"));
    QHYCCDI2CTwoRead=reinterpret_cast<QTQHYCCDI2CTwoRead>(dll.resolve("QHYCCDI2CTwoRead"));
    ExpQHYCCDSingleFrame=reinterpret_cast<QTExpQHYCCDSingleFrame>(dll.resolve("ExpQHYCCDSingleFrame"));
    BeginQHYCCDLive=reinterpret_cast<QTBeginQHYCCDLive>(dll.resolve("BeginQHYCCDLive"));
    GetQHYCCDSingleFrame=reinterpret_cast<QTGetQHYCCDSingleFrame>(dll.resolve("GetQHYCCDSingleFrame"));
    GetQHYCCDLiveFrame=reinterpret_cast<QTGetQHYCCDLiveFrame>(dll.resolve("GetQHYCCDLiveFrame"));
    ControlQHYCCDShutter=reinterpret_cast<QTControlQHYCCDShutter>(dll.resolve("ControlQHYCCDShutter"));
    SetQHYCCDTrigerFunction=reinterpret_cast<QTSetQHYCCDTrigerFunction>(dll.resolve("SetQHYCCDTrigerFunction"));
    SendFourLine2QHYCCDInterCamOled=reinterpret_cast<QTSendFourLine2QHYCCDInterCamOled>(dll.resolve("SendFourLine2QHYCCDInterCamOled"));
    SendOrder2QHYCCDCFW=reinterpret_cast<QTSendOrder2QHYCCDCFW>(dll.resolve("SendOrder2QHYCCDCFW"));
    GetQHYCCDCFWStatus=reinterpret_cast<QTGetQHYCCDCFWStatus>(dll.resolve("GetQHYCCDCFWStatus"));
    OSXInitQHYCCDFirmware=reinterpret_cast<QTOSXInitQHYCCDFirmware>(dll.resolve("OSXInitQHYCCDFirmware"));
    SetQHYCCDFineTone=reinterpret_cast<QTSetQHYCCDFineTone>(dll.resolve("SetQHYCCDFineTone"));
    EnableQHYCCDImageOSD=reinterpret_cast<QTEnableQHYCCDImageOSD>(dll.resolve("EnableQHYCCDImageOSD"));
    TestQHYCCDPIDParas=reinterpret_cast<QTTestQHYCCDPIDParas>(dll.resolve("TestQHYCCDPIDParas"));
    CheckPHD2Status=reinterpret_cast<QTCheckPHD2Status>(dll.resolve("CheckPHD2Status"));
    Connect2PHD2=reinterpret_cast<QTConnect2PHD2>(dll.resolve("Connect2PHD2"));
    DisConnect2PHD2=reinterpret_cast<QTDisConnect2PHD2>(dll.resolve("DisConnect2PHD2"));
    ControlPHD2Dither=reinterpret_cast<QTControlPHD2Dither>(dll.resolve("ControlPHD2Dither"));
    PausePHD2Dither=reinterpret_cast<QTPausePHD2Dither>(dll.resolve("PausePHD2Dither"));
    EnableQHYCCDMessage=reinterpret_cast<QTEnableQHYCCDMessage>(dll.resolve("EnableQHYCCDMessage"));

    RegisterPnpEvent=reinterpret_cast<QTRegisterPnpEvent>(dll.resolve("RegisterPnpEvent"));
    RegisterTransferEventError=reinterpret_cast<QTRegisterTransferEventError>(dll.resolve("RegisterTransferEventError"));
    RegisterPnpEventIn=reinterpret_cast<QTRegisterPnpEventIn>(dll.resolve("RegisterPnpEventIn"));
    RegisterPnpEventOut=reinterpret_cast<QTRegisterPnpEventOut>(dll.resolve("RegisterPnpEventOut"));
    RegisterDataEventSingle=reinterpret_cast<QTRegisterDataEventSingle>(dll.resolve("RegisterDataEventSingle"));
    RegisterDataEventLive=reinterpret_cast<QTRegisterDataEventLive>(dll.resolve("RegisterDataEventLive"));
    GetCameraIsSuperSpeedFromID=reinterpret_cast<QTGetCameraIsSuperSpeedFromID>(dll.resolve("GetCameraIsSuperSpeedFromID"));
    GetCameraStatusFromID=reinterpret_cast<QTGetCameraStatusFromID>(dll.resolve("GetCameraStatusFromID"));
    ControlQHYCCDGuide=reinterpret_cast<QTControlQHYCCDGuide>(dll.resolve("ControlQHYCCDGuide"));

#endif
    }
    else {
        dll.unload();
        qDebug()<<"DLL load is false!";
    }
    qDebug()<<"dllqhyccd() end~~";
}
dllqhyccd::~dllqhyccd()
{
    dll.unload();
}
