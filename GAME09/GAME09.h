#pragma once
#include "../MAIN/GAME_BASE.h"
#include "SONGINFO.h"
#include "CHANGEDATA.h"
#include "NOTE.h"
#include <vector>
//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
extern bool EscapeKeyValid;
namespace GAME09
{
	class GAME :
		public GAME_BASE
	{
	public:
		GAME(class MAIN* main) :GAME_BASE(main) {};
		~GAME() {};
		int create();
		void proc();
		void destroy();
		//�R���e�i
	private:
		class CONTAINER* Container;
	public:
		class CONTAINER* container() {
			return Container;
		}
	public:
		enum SCENE_ID {
			TITLE_ID,
			SELECT_ID,
			OPTION_ID,
			STAGE_ID,
			GAME_CLEAR_ID,
			LOADSONGS_ID,
			LOADCHART_ID,
			NUM_SCENES
		};
	private:
		class SCENE* Scenes[NUM_SCENES];
		SCENE_ID CurSceneId;
		class FADE* Fade;
		class CHARTMANAGER* ChartMNG;
		class BANNER* Banner;
		class JACKET* Jacket;
		class BACKGROUND* BackGround;
		class RHYTHM_GAME_CONTROLLER* RGCont;
		class LANE* Lane;
		class SOUNDMANAGER* SoundMNG;
		class KEYCONFIG* KeyConfig;
		class JUDGEMANAGER* JudgeMNG;
		class OPTIONBUTTON* OptionButton;
		class BACKBUTTON* BackButton;
		class LOADOPTION* LoadOption;
		class COLOR_PICKER* ColorPicker;
		class DETAIL_VIEW* Detail;
		class COMBO* Combo;
		class SCORE* Score;
		class ACHIEVEMENT* Achievement;
		class AUTOBUTTON* AutoButton;
		class SONGTITLE* SongTitle;
		class STARTBUTTON* StartButton;
		class DIFFICULTYSELECT* DifficultySelect;
		class WARNING_MESSAGE* WarningMessage;
		class RETRYBUTTON* RetryButton;

		std::vector<SONGINFO> Songs;
		std::vector<NOTE*> Notes;
		std::vector<CHANGEDATA> ChangeDatas;
	public:
		void changeScene(SCENE_ID sceneId);
		void exit();
		class SCENE* scene(SCENE_ID sceneId) { return Scenes[sceneId]; }
		class FADE* fade() { return Fade; }
		class CHARTMANAGER* chartMNG() { return ChartMNG; }
		class BANNER* banner() { return Banner; }
		class JACKET* jacket() { return Jacket; }
		class BACKGROUND* backGround() { return BackGround; }
		class RHYTHM_GAME_CONTROLLER* rgCont() { return RGCont; }
		class LANE* lane() { return Lane; }
		class SOUNDMANAGER* soundMNG() { return SoundMNG; }
		class KEYCONFIG* keyConfig() { return KeyConfig; }
		class JUDGEMANAGER* judgeMNG() { return JudgeMNG; }
		class OPTIONBUTTON* optionButton() { return OptionButton; }
		class BACKBUTTON* backButton() { return BackButton; }
		class LOADOPTION* loadOption() { return LoadOption; }
		class COLOR_PICKER* colorPicker() { return ColorPicker; }
		class DETAIL_VIEW* detail() { return Detail; }
		class COMBO* combo() { return Combo; }
		class SCORE* score() { return Score; }
		class ACHIEVEMENT* achievement() { return Achievement; }
		class AUTOBUTTON* autoButton() { return AutoButton; }
		class SONGTITLE* songTitle() { return SongTitle; }
		class STARTBUTTON* startButton() { return StartButton; }
		class DIFFICULTYSELECT* difficultySelect() { return DifficultySelect; }
		class WARNING_MESSAGE* warningMessage() { return WarningMessage; }
		class RETRYBUTTON* retryButton() { return RetryButton; }

		std::vector<SONGINFO>& songs() { return Songs; }
		std::vector<NOTE*>& notes() { return Notes; }
		std::vector<CHANGEDATA>& changeDatas() { return ChangeDatas; }
    };
}
