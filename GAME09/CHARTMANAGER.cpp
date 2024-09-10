#include "CHARTMANAGER.h"
#include "GAME09.h"
#include "CONTAINER.h"
//#include "TAPNOTE.h"
//#include "LONGNOTE.h"
//#include "LONGBELT.h"
#include "../../libOne/inc/window.h"
#include "../../libOne/inc/graphic.h"
#include "../../libOne/inc/input.h"
#include <fstream>
#include <algorithm>
#include "../../libOne/inc/stb_image_reader.h"
#include <filesystem>
#include <iostream>
//#include "myFunc.h"

//#define new new( _CLIENT_BLOCK, __FILE__, __LINE__)

namespace GAME09 {
	CHARTMANAGER::CHARTMANAGER(GAME* game) :
		GAME_OBJECT(game) {
		
	}
	CHARTMANAGER::~CHARTMANAGER() {

	}

	void CHARTMANAGER::create() {
		ChartMNG = game()->container()->data().chartMNG;
	}

	void CHARTMANAGER::init() {

	}

	/*
	//double CHARTMANAGER::loadChart(const char* fileName, std::vector<NOTE*>& notes,
	//	std::vector<RHYTHM_GAME_CONTROLLER::CHANGEDATA>& changeDatas, RHYTHM_GAME_CONTROLLER::SONGINFO& songInfo) {

	//	//�����I�t�Z�b�g�𔽉f
	//	songInfo.offset += AudioOffset / 1000.0f;
	//	songInfo.offset += VisualOffset / 1000.0f;
	//	songInfo.offsetB = -songInfo.offset / (60.0f / songInfo.bpm);
	//	songInfo.offset -= VisualOffset / 1000.0f;

	//	safe_clear(notes);
	//	//notes.clear();
	//	changeDatas.clear();
	//	NOTE::NOTE_DATA data;
	//	RHYTHM_GAME_CONTROLLER::CHANGEDATA changeData;
	//	std::vector<NOTE::NOTE_DATA*> longData;
	//	std::vector< std::vector<NOTE::NOTE_DATA*>* > longBeltData;
	//	for (int i = 0; i < Cont->numLane(); i++) {
	//		longData.emplace_back(nullptr);
	//		longBeltData.emplace_back(new std::vector<NOTE::NOTE_DATA*>);
	//	}

	//	std::ifstream file;
	//	file.open(fileName, std::ios::in);
	//	std::string buffer;
	//	std::vector<std::string> bar;
	//	bool notesTag = false;

	//	double offset = songInfo.offset;
	//	double offsetB = songInfo.offsetB;
	//	double bpm = songInfo.bpm;
	//	VECTOR2 measure = songInfo.measure;
	//	int curBar = 0;
	//	float speed = 0;
	//	double tempTime = 0;       //bpm�Ȃǂ��ς�����Ƃ��ɂ��̎��_�̎��Ԃ��L�^���Ă���
	//	double curTime = 0;        //���݂̎���
	//	double tempVisualBeat = 0; //bpm�Ȃǂ��ς�����Ƃ��ɂ��̎��_�̌����ڏ�̔������L�^���Ă���
	//	double visualBeat = 0;     //���݂̌����ڏ�̔���
	//	double endTime = 0;        //�Ō�̃m�[�c�̎���

	//	while (std::getline(file, buffer)) {
	//		if (!notesTag) {
	//			std::string t = "#NOTES";
	//			if (buffer.size() >= t.size() &&
	//				buffer.find(t) != std::string::npos) {
	//				notesTag = true;
	//				for (int i = 0; i < 4; i++) {   //�]�v�ȏ��4�s�����΂�
	//					std::getline(file, buffer);
	//				}
	//			}
	//		}
	//		else {
	//			if (buffer.find(ChartMNG.commandStr[BPMCHANGE]) != std::string::npos) { //BPM�R�}���h
	//				tempTime += (60.0 / bpm / (measure.y / 4) * measure.x) * curBar;
	//				tempVisualBeat += (measure.x * 4 / measure.y) * curBar;
	//				curBar = 0;

	//				int conS = buffer.find(':') + 1;
	//				int conE = buffer.find_last_of(';');
	//				std::string content = buffer.substr(conS, conE - conS);
	//				bpm = std::stof(content);

	//				changeData.time = tempTime - offset;
	//				changeData.visualBeat = tempVisualBeat + offsetB;
	//				changeData.bpm = bpm;
	//				changeData.measure = measure;
	//				changeDatas.emplace_back(changeData);
	//			}
	//			else if (buffer.find(ChartMNG.commandStr[MEASURECHANGE]) != std::string::npos) { //MEASURE�R�}���h
	//				tempTime += (60.0 / bpm / (measure.y / 4) * measure.x) * curBar;
	//				tempVisualBeat += (measure.x * 4 / measure.y) * curBar;
	//				curBar = 0;

	//				int conS = buffer.find(':') + 1;
	//				int conE = buffer.find_last_of(';');
	//				std::string content = buffer.substr(conS, conE - conS);
	//				int n = std::stoi(content.substr(0, content.find('/')));
	//				int d = std::stoi(content.substr(content.find('/') + 1));
	//				measure = VECTOR2(n, d);

	//				changeData.time = tempTime - offset;
	//				changeData.visualBeat = tempVisualBeat + offsetB;
	//				changeData.bpm = bpm;
	//				changeData.measure = measure;
	//				changeDatas.emplace_back(changeData);
	//			}
	//			else {
	//				//�ꏬ�ߕ��̏�����x�ɓǂ�
	//				bar.clear();
	//				bar.emplace_back(buffer);
	//				bool end = false;
	//				while (!end) {
	//					std::getline(file, buffer);
	//					if (buffer.find(',') != std::string::npos ||
	//						buffer.find(';') != std::string::npos) {
	//						end = true;
	//					}
	//					else {
	//						bar.emplace_back(buffer);
	//					}
	//				}
	//				int divisionNum = bar.size();
	//				int j = 0;
	//				for (auto it = bar.begin(); it != bar.end(); ++it) {
	//					visualBeat = tempVisualBeat + (measure.x * 4 / measure.y) * (curBar + (float)j / divisionNum) + offsetB;
	//					curTime = tempTime + (60.0 / bpm / (measure.y / 4) * measure.x) * (curBar + (float)j / divisionNum) - offset;
	//					speed = Cont->speed() * (Cont->rawSpeed() / songInfo.bpm);

	//					for (int i = 0; i < Cont->numLane(); i++) {
	//						if ((*it)[i] == '1' || (*it)[i] == 'F') {
	//							notes.emplace_back(new TAPNOTE(game(), Cont, Cont->soundMNG()));
	//							notes.back()->create();
	//							data.lane = i;
	//							data.speed = speed;
	//							data.time = curTime;
	//							data.visualBeat = visualBeat;
	//							notes.back()->setData(data);
	//							notes.back()->init();
	//							endTime = curTime;
	//						}
	//						else if (std::toupper((*it)[i]) == 'A' || std::toupper((*it)[i]) == 'X') {
	//							if (longData[i] == nullptr) {
	//								longData[i] = new NOTE::NOTE_DATA;
	//								longData[i]->lane = i;
	//								longData[i]->speed = speed;
	//								longData[i]->time = curTime;
	//								longData[i]->visualBeat = visualBeat;

	//								longBeltData[i]->emplace_back(new NOTE::NOTE_DATA);
	//								longBeltData[i]->back()->lane = i;
	//								longBeltData[i]->back()->speed = speed;
	//								longBeltData[i]->back()->time = curTime;
	//								longBeltData[i]->back()->visualBeat = visualBeat;
	//							}
	//						}
	//						else if (std::toupper((*it)[i]) == 'C' || std::toupper((*it)[i]) == 'Z') {
	//							if (longData[i] != nullptr) {
	//								longData[i]->timeE = curTime;
	//								longData[i]->visualBeatE = visualBeat;
	//								longBeltData[i]->back()->timeE = curTime;
	//								longBeltData[i]->back()->visualBeatE = visualBeat;
	//								endTime = curTime;

	//								notes.emplace_back(new LONGNOTE(game(), Cont, Cont->soundMNG()));
	//								notes.back()->create();
	//								notes.back()->setData(*longData[i]);
	//								notes.back()->init();
	//								((LONGNOTE*)notes.back())->setBelts(*longBeltData[i]);

	//								delete longData[i];
	//								longData[i] = nullptr;
	//								safe_clear(*longBeltData[i]);
	//							}
	//						}
	//					}
	//					j++;
	//				}
	//				curBar++;
	//			}
	//		}
	//	}
	//	file.close();
	//	longData.clear();
	//	safe_clear(longBeltData);

	//	//�����I�t�Z�b�g�̒l�����񑫂����̂�h�����߂ɂ����Ō��炷
	//	songInfo.offset -= AudioOffset / 1000.0f;

	//	return curTime;
	//}
	*/

	void CHARTMANAGER::loadCharts() {
		std::vector<SONGINFO>& Songs = game()->songs();
		Songs.clear();
		//charts�t�H���_�̃C�e���[�^�[
		std::filesystem::directory_iterator songsDirectory = std::filesystem::directory_iterator(ChartMNG.chartPath);
		//�͈�for��charts�t�H���_�̒��̂��ׂẴt�H���_���m�F
		for (auto d : songsDirectory) {
			std::string chartPath = d.path().string();
			//�y�ȃt�H���_�̃C�e���[�^�[
			std::filesystem::directory_iterator chartDirectory = std::filesystem::directory_iterator(chartPath);
			bool isLoadChart = false;
			bool isLoadScore = false;
			Score = 0;
			Achievement = -1;
			//�n�C�X�R�A��ۑ�����t�@�C���̃p�X
			std::string scorePath = chartPath + "\\high_score.txt";
			//�͈�for�Ŋy�ȃt�H���_�̒��̂��ׂẴt�@�C�����m�F
			for (auto chart : chartDirectory) {
				//�e�L�X�g�t�@�C��������������
				if (chart.path().extension().string() == ".txt") {
					//�n�C�X�R�A��ۑ�����t�@�C���ł���΃n�C�X�R�A��ǂݍ���
					if (chart.path().string() == scorePath) {
						loadHiscore(scorePath);
						isLoadScore = true;
					}
					//���ʂ��ǂݍ��܂�ĂȂ���Γǂݍ���
					else if (!isLoadChart) {
						Songs.emplace_back();
						Songs.back().fileName = chart.path().string();
						Songs.back().scorePath = scorePath;
						loadChartInfo(chart.path().string().c_str(), Songs.back());
						//�y�ȃt�@�C����ǂݍ���ŃC���f�b�N�X���i�[
						std::string musicFile = chartPath + "\\" + Songs.back().music;
						//Songs.back().musicIdx = game()->soundMNG()->loadMusic(musicFile.c_str(), Songs.back().volume);
						//�w�i�摜�t�@�C����ǂݍ���ŃC���f�b�N�X���i�[
						loadChartImage(chartPath, Songs.back().backGround, Songs.back().backImageIdx, Songs.back().backImageSize);
						//�W���P�G�t�@�C����ǂݍ���ŃC���f�b�N�X���i�[
						loadChartImage(chartPath, Songs.back().banner, Songs.back().jacketImageIdx, Songs.back().jacketImageSize);
						isLoadChart = true;
					}
				}
				//���ʂƃn�C�X�R�A���Ƃ��ɓǂݍ��܂ꂽ�甲����
				if (isLoadChart && isLoadScore) {
					break;
				}
			}
			Songs.back().highScore = Score;
			Songs.back().achievement = Achievement;
		}
	}

	void CHARTMANAGER::loadChartInfo(std::string fileName, struct SONGINFO& songInfo) {
		std::ifstream file;
		file.open(fileName, std::ios::in);
		std::string buffer;
		bool notes = false;

		while (std::getline(file, buffer) && !notes) {
			for (int i = 0; i < NUM_INFOS; i++) {
				std::string t = ChartMNG.infoStartStr[i];
				if (buffer.size() >= t.size() &&
					buffer.find(t) != std::string::npos) {
					int conS = buffer.find(':') + 1;
					int conE = buffer.find_last_of(';');
					std::string content = buffer.substr(conS, conE - conS);
					switch (i) {
					case TITLE:
						songInfo.title = content;
						break;
					case ARTIST:
						songInfo.artist = content;
						break;
					case CREDIT:
						songInfo.credit = content;
						break;
					case MUSIC:
						songInfo.music = content;
						break;
					case BANNER:
						songInfo.banner = content;
						break;
					case BACKGROUND:
						songInfo.backGround = content;
						break;
					case OFFSET:
						songInfo.offset = std::stof(content);
						break;
					case BASEBPM:
						songInfo.bpm = std::stof(content);
						break;
					case MEASURE: {
						int n = std::stoi(content.substr(0, content.find('/')));
						int d = std::stoi(content.substr(content.find('/') + 1));
						songInfo.measure = VECTOR2(n, d);
					}
								break;
					case VOLUME:
						songInfo.volume = std::stof(content);
						break;
					case NOTES:
						notes = true;
						break;
					default:
						break;
					}
				}
			}
		}

		//songInfo.offsetB = -songInfo.offset / (60.0f / songInfo.bpm);
	}

	void CHARTMANAGER::loadHiscore(std::string fileName) {
		std::ifstream file;
		file.open(fileName, std::ios::in);
		std::string buffer;

		while (std::getline(file, buffer)) {
			for (int i = 0; i < NUM_SCORE_DATAS; i++) {
				std::string t = ChartMNG.scoreDataStr[i];
				if (buffer.size() >= t.size() &&
					buffer.find(t) != std::string::npos) {
					int conS = buffer.find(':') + 1;
					int conE = buffer.find_last_of(';');
					std::string content = buffer.substr(conS, conE - conS);
					switch (i) {
					case SCORE:
						Score = std::stoi(content);
						break;
					case ACHIEVEMENT:
						Achievement = std::stoi(content);
						break;
					default:
						break;
					}
				}
			}
		}
	}

	void CHARTMANAGER::loadChartImage(std::string chartPath, std::string fileName, int& idx, VECTOR2& size) {
		if (fileName == "") {
			idx = -1;
		}
		else {
			std::string imageFile = chartPath + "\\" + fileName;
			idx = loadImage(imageFile.c_str());
			int w, h, p;
			unsigned char* pixels = 0;
			pixels = stbi_load(imageFile.c_str(), &w, &h, &p, 4); //�g�����Ⴄ���ǂ���ō����ƕ����擾
			size = VECTOR2(w, h);
			stbi_image_free(pixels);
		}
	}
}