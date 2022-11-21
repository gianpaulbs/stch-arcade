#pragma once

using namespace System::Media;
using namespace WMPLib;
ref class Soundtrack {
	private: 
		WMPLib::WindowsMediaPlayer^ wmpTitle;
		WMPLib::WindowsMediaPlayer^ wmpButtons;
		WMPLib::WindowsMediaPlayer^ wmpEnter;
		WMPLib::WindowsMediaPlayer^ wmpBack;
		WMPLib::WindowsMediaPlayer^ wmpCountdown;
		WMPLib::WindowsMediaPlayer^ wmpRun;
		WMPLib::WindowsMediaPlayer^ wmpAddWater;
		WMPLib::WindowsMediaPlayer^ wmpAddMedicaments;
		WMPLib::WindowsMediaPlayer^ wmpHealing;
		WMPLib::WindowsMediaPlayer^ wmpPunch;
		WMPLib::WindowsMediaPlayer^ wmpWinning;
		WMPLib::WindowsMediaPlayer^ wmpLosing;

	public:
		~Soundtrack() {
			delete wmpTitle;
			delete wmpButtons;
			delete wmpEnter;
			delete wmpBack;
			delete wmpCountdown;
			delete wmpRun;
			delete wmpAddWater;
			delete wmpAddMedicaments;
			delete wmpHealing;
			delete wmpPunch;
			delete wmpWinning;
			delete wmpLosing;
		}

		Soundtrack() {
			wmpTitle = gcnew WindowsMediaPlayerClass();
			wmpButtons = gcnew WindowsMediaPlayerClass();
			wmpEnter = gcnew WindowsMediaPlayerClass();
			wmpBack = gcnew WindowsMediaPlayerClass();
			wmpCountdown = gcnew WindowsMediaPlayerClass();
			wmpRun = gcnew WindowsMediaPlayerClass();
			wmpAddWater = gcnew WindowsMediaPlayerClass();
			wmpAddMedicaments = gcnew WindowsMediaPlayerClass();
			wmpHealing = gcnew WindowsMediaPlayerClass();
			wmpPunch = gcnew WindowsMediaPlayerClass();
			wmpWinning = gcnew WindowsMediaPlayerClass();
			wmpLosing = gcnew WindowsMediaPlayerClass();
		}

		void Play_TitleScreen() {
			wmpTitle->URL = "resources/music/titlescreen.wav";
			wmpTitle->controls->play();
		}

		void Stop_TitleScreen() {
			wmpTitle->controls->stop();
		}

		void Play_ChooseButton() {
			wmpButtons->URL = "resources/music/beep.wav";
			wmpButtons->controls->play();
		}

		void Play_Enter() {
			wmpEnter->URL = "resources/music/bomb.wav";
			wmpEnter->controls->play();
		}

		void Play_Back() {
			wmpBack->URL = "resources/music/back.wav";
			wmpBack->controls->play();
		}

		void Play_Countdown() {
			wmpCountdown->URL = "resources/music/countdown.wav";
			wmpCountdown->controls->play();
		}

		void Play_Run() {
			wmpRun->URL = "resources/music/run.mp3";
			wmpRun->controls->play();
		}

		void Stop_Run() {
			wmpRun->controls->stop();
		}

		void Play_AddWater() {
			wmpAddWater->URL = "resources/music/water.wav";
			wmpAddWater->controls->play();
		}

		void Play_AddMedicaments() {
			wmpAddMedicaments->URL = "resources/music/medicaments.wav";
			wmpAddMedicaments->controls->play();
		}

		void Play_Healing() {
			wmpHealing->URL = "resources/music/healing.wav";
			wmpHealing->controls->play();
		}

		void Play_Punch() {
			wmpPunch->URL = "resources/music/punch.wav";
			wmpPunch->controls->play();
		}

		void Play_Winning() {
			wmpWinning->URL = "resources/music/winning.mp3";
			wmpWinning->controls->play();
		}

		void Stop_Winning() {
			wmpWinning->controls->stop();
		}

		void Play_Losing() {
			wmpLosing->URL = "resources/music/losing.mp3";
			wmpLosing->controls->play();
		}

		void Stop_Losing() {
			wmpLosing->controls->stop();
		}
};