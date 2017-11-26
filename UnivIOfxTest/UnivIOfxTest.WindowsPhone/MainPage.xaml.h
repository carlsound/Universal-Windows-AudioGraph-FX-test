//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "WASAPICapture.h"
//#include "Constants.h"
#include <wrl.h>

#include "pch.h"
#include "MainPage.g.h"

#define OSC_START_X  100
#define OSC_START_Y  100
#define OSC_X_LENGTH 700
#define OSC_TOTAL_HEIGHT 200

namespace UnivIOfxTest
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		//
	private:
		//WASAPICapture *wc;
		ComPtr<WASAPICapture> m_spCapture;

		//
		// TODO: add XAudio2 MasteringVoice ivar
		//
		// TODO: add XAudio2 SourceVoice ivar [collection (?)]
		//
		//SDKSample::WASAPIAudio::WASAPIRenderer wr;
	};
}
