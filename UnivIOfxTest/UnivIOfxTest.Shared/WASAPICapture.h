//*********************************************************
//
// Copyright (c) Microsoft. All rights reserved.
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
//*********************************************************

//
// WASAPICapture.h
//

#pragma once

#include "pch.h"
//
#include <Windows.h>
#include <wrl\implements.h>
#include <mfapi.h>
#include <AudioClient.h>
#include <mmdeviceapi.h>
#include "MainPage.xaml.h"
#include "DeviceState.h"
#include "PlotData.h"

using namespace Microsoft::WRL;
using namespace Windows::Media::Devices;
using namespace Windows::Storage::Streams;

#define AUDIO_FILE_NAME "WASAPIAudioCapture.wav"
#define FLUSH_INTERVAL_SEC 3


//


namespace UnivIOfxTest
    {
        // Primary WASAPI Capture Class
        class WASAPICapture : public RuntimeClass< RuntimeClassFlags< ClassicCom >, FtmBase, IActivateAudioInterfaceCompletionHandler > 
        {
        public:
            WASAPICapture();

            HRESULT InitializeAudioDeviceAsync();
            HRESULT StartCaptureAsync();
            HRESULT StopCaptureAsync();
            HRESULT FinishCaptureAsync();

            DeviceStateChangedEvent^ GetDeviceStateEvent() { return m_DeviceStateChanged; };

            METHODASYNCCALLBACK( WASAPICapture, StartCapture, OnStartCapture );
            METHODASYNCCALLBACK( WASAPICapture, StopCapture, OnStopCapture );
            METHODASYNCCALLBACK( WASAPICapture, SampleReady, OnSampleReady );
            METHODASYNCCALLBACK( WASAPICapture, FinishCapture, OnFinishCapture );
            METHODASYNCCALLBACK( WASAPICapture, SendScopeData, OnSendScopeData );

            // IActivateAudioInterfaceCompletionHandler
            STDMETHOD(ActivateCompleted)( IActivateAudioInterfaceAsyncOperation *operation );

        private:
            ~WASAPICapture();

            HRESULT OnStartCapture( IMFAsyncResult* pResult );
            HRESULT OnStopCapture( IMFAsyncResult* pResult );
            HRESULT OnFinishCapture( IMFAsyncResult* pResult );
            HRESULT OnSampleReady( IMFAsyncResult* pResult );
            HRESULT OnSendScopeData( IMFAsyncResult* pResult );

            HRESULT CreateWAVFile();
            HRESULT FixWAVHeader();
            HRESULT OnAudioSampleRequested( Platform::Boolean IsSilence = false );
            HRESULT InitializeScopeData();
            HRESULT ProcessScopeData( BYTE* pData, DWORD cbBytes );
        
        private:
            Platform::String^   m_DeviceIdString;
            UINT32              m_BufferFrames;
            HANDLE              m_SampleReadyEvent;
            MFWORKITEM_KEY      m_SampleReadyKey;
            CRITICAL_SECTION    m_CritSec;
            DWORD               m_dwQueueID;

            DWORD               m_cbHeaderSize;
            DWORD               m_cbDataSize;
            DWORD               m_cbFlushCounter;
            BOOL                m_fWriting;

            IRandomAccessStream^     m_ContentStream;
            IOutputStream^           m_OutputStream;
            DataWriter^              m_WAVDataWriter;
            WAVEFORMATEX            *m_MixFormat;
            IAudioClient            *m_AudioClient;
            IAudioCaptureClient     *m_AudioCaptureClient;
            IMFAsyncResult          *m_SampleReadyAsyncResult;

            DeviceStateChangedEvent^       m_DeviceStateChanged;

            Platform::Array<int, 1>^    m_PlotData;
            UINT32                      m_cPlotDataMax;
            UINT32                      m_cPlotDataFilled;
        };
    }