#include "Tetris.h"
#include <iostream>
#include <cassert>
#include <vector>
#include "SFML/Audio.hpp"
#include <fstream>
#include <sstream>

#include "../BrickPong/UtilityFunc.h"

enum TexturesID
{
	Blocks, UI, Buttons, TexturesCount
};
enum SoundsID
{
	Click, ClearRow, TetrisClear, GameOver, SoundsCount
};

enum FontsID
{
	Calibri, Retro, FontCount
};

void loadTextures(std::vector<sf::Texture>* textures)
{

	sf::Texture fTetrisTexture;
	assert(fTetrisTexture.loadFromFile("Textures/Tetris_Unit_block.png"));
	sf::Texture fUITexture;
	assert(fUITexture.loadFromFile("Textures/UI.png"));
	sf::Texture fButtonsTexture;
	assert(fButtonsTexture.loadFromFile("Textures/Buttons.png"));

	textures->push_back(fTetrisTexture);
	textures->push_back(fUITexture);
	textures->push_back(fButtonsTexture);
}

void loadSounds(std::vector<sf::SoundBuffer>* fSounds)
{
	sf::SoundBuffer fClickSound;
	assert(fClickSound.loadFromFile("Sounds/buttonPressed.ogg"));
	sf::SoundBuffer fClearRow;
	assert(fClearRow.loadFromFile("Sounds/clear.wav"));
	sf::SoundBuffer fTetrisClear;
	assert(fTetrisClear.loadFromFile("Sounds/tetrisClear.ogg"));
	sf::SoundBuffer fGameOver;
	assert(fGameOver.loadFromFile("Sounds/gameOver.wav"));

	fSounds->push_back(fClickSound);
	fSounds->push_back(fClearRow);
	fSounds->push_back(fTetrisClear);
	fSounds->push_back(fGameOver);
}

void loadFonts(std::vector<sf::Font>* fFonts)
{
	sf::Font calibri;
	assert(calibri.loadFromFile("Fonts/Calibri.ttf"));
	sf::Font retro;
	assert(retro.loadFromFile("Fonts/Retrofuturism.otf"));

	fFonts->push_back(calibri);
	fFonts->push_back(retro);
}

enum class GameStates
{
	Menu, GameOn, GameOver
};

std::pair<unsigned long int, int> loadHighScore()
{
	std::pair<unsigned long int, int> retScore;
	std::ifstream file("HighScore.txt");
	assert(file.is_open());

	file >> retScore.first >> retScore.second;

	file.close();

	return retScore;
}

void saveHighScore(std::pair<unsigned long int, int> highScore)
{
	std::ofstream file("HighScore.txt");
	assert(file.is_open());

	file << highScore.first << " " << highScore.second;

	file.close();
}

int main()
{
	sf::RenderWindow window{ sf::VideoMode(WIDTH, HEIGHT), "TETRIS", sf::Style::Close };
	sf::Time frameRate = sf::seconds(1.f / 10.f);
	sf::Time frameRateMovement = sf::seconds(1.f / 3.f);

	int fLevel = 1;
	unsigned int levelChanging = 10;
	unsigned long int fScore = 0;
	int TotalLines = 0;
	int linesToLevelUpCount = levelChanging;

	std::vector<sf::Font> fFonts;
	loadFonts(&fFonts);
	std::vector<sf::Texture> fTextures;
	loadTextures(&fTextures);
	std::vector<sf::SoundBuffer> fSounds;
	loadSounds(&fSounds);

	sf::Text fLevelText(std::to_string(fLevel), fFonts[Retro]);
	fLevelText.setFillColor(sf::Color::Green);
	Utility::CenterOrigin(fLevelText);
	fLevelText.setPosition(79.f, 194.f);

	sf::Text fScoreText(std::to_string(fScore), fFonts[Retro]);
	Utility::CenterOrigin(fScoreText);
	fScoreText.setFillColor(sf::Color::Red);
	fScoreText.setPosition(282.f, 523.f);

	std::pair<unsigned long int, int> highScore = loadHighScore();
	sf::Text fHighScoreSText(std::to_string(highScore.first), fFonts[Retro]);
	Utility::CenterOrigin(fHighScoreSText);
	fHighScoreSText.setPosition(78.f, 558.f);

	sf::Text fHighScoreLText(std::to_string(highScore.second), fFonts[Retro]);
	Utility::CenterOrigin(fHighScoreLText);
	fHighScoreLText.setPosition(78.f, 472.f);

	sf::Text fTotalLinesCount(std::to_string(TotalLines), fFonts[Retro]);
	Utility::CenterOrigin(fTotalLinesCount);
	fTotalLinesCount.setPosition(78.f, 270.f);

	sf::Text fRemainingLines(std::to_string(linesToLevelUpCount), fFonts[Retro]);
	Utility::CenterOrigin(fRemainingLines);
	fRemainingLines.setPosition(78.f, 374.f);

	sf::Sprite fUIBackground(fTextures[UI]);

	/*buttons*/
	sf::Sprite retryButton(fTextures[Buttons], sf::IntRect(173, 0, 173, 70));
	Utility::CenterOrigin(retryButton);
	retryButton.setPosition(WIDTH / 2.f, HEIGHT / 2.f - retryButton.getGlobalBounds().height - 10.f);

	sf::Sprite quitButton(fTextures[Buttons], sf::IntRect(2 * 173, 0, 173, 70));
	Utility::CenterOrigin(quitButton);
	quitButton.setPosition(WIDTH / 2.f, HEIGHT / 2.f);

	sf::Sound fPressButtonSound(fSounds[Click]);
	fPressButtonSound.setVolume(50.f);
	/***********/

	/*sounds*/
	sf::Sound fLineClear(fSounds[ClearRow]);
	fLineClear.setVolume(25.f);

	sf::Sound fTetrisClear(fSounds[TetrisClear]);
	fTetrisClear.setVolume(20.f);

	sf::Sound fGameOverSound(fSounds[GameOver]);
	fGameOverSound.setVolume(40.f);

	sf::Music fMusic;
	fMusic.openFromFile("Sounds/OriginalMusic.ogg");
	fMusic.setVolume(2.f);
	fMusic.setLoop(true);
	fMusic.play();
	/*******/
	
	std::vector<Block*> GAllTheBlocks(GgameBorders.width * GgameBorders.height, nullptr);

	sf::Vector2i activeDefaultPos(3, 0);
	sf::Vector2i passiveDefaultPos(-6, 2);

	Tetris::Type tetType = static_cast<Tetris::Type>(Utility::randomInt(static_cast<int>(Tetris::Type::Count)));
	Tetris* tetrisActive = new Tetris{ fTextures[Blocks], activeDefaultPos.x, activeDefaultPos.y, tetType, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)) };

	Tetris* tetrisPassive = new Tetris{ fTextures[Blocks], passiveDefaultPos.x, passiveDefaultPos.y, tetType, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)) };

	sf::Clock clock;
	sf::Time deltaTime = sf::Time::Zero;
	sf::Time Accu = sf::Time::Zero;
	sf::Time AccuMovement = sf::Time::Zero;

	bool fEndOfErasingAnimation = true;
	int fAnimationIndex_left = GgameBorders.width / 2;
	int fAnimationIndex_right = GgameBorders.width / 2;

	int LineCount = 0;

	int tetrisNotHeroCount = 0;

	std::vector<unsigned int> rowsToDelete;
	auto DeletingRows = [&GAllTheBlocks, &fEndOfErasingAnimation, &fAnimationIndex_left,
		&fAnimationIndex_right, &rowsToDelete, &fTetrisClear, &fLineClear, &fScore,
		&fScoreText, &fLevel, &fLevelText, &LineCount, &levelChanging, &linesToLevelUpCount, &TotalLines, &fTotalLinesCount, &fRemainingLines]()
	{
		/*First we find the rows to erase*/
		if (fEndOfErasingAnimation) {
			for (int j = 0; j < GgameBorders.height; ++j)
			{
				bool isUpForDelete = true;
				for (int i = 0; i < GgameBorders.width; ++i)
				{
					int coords = i + j * GgameBorders.width;
					if (!GAllTheBlocks[coords])
					{
						isUpForDelete = false;
					}
				}
				if (isUpForDelete && j > 0)
				{
					rowsToDelete.push_back(j);
				}
			}
		}

		if (rowsToDelete.size() > 0 && fEndOfErasingAnimation) {
			fEndOfErasingAnimation = false;
			if (rowsToDelete.size() == 4)
			{
				//epic sound effect
				fTetrisClear.play();
				fScore += 100;
				fScoreText.setString(std::to_string(fScore));
				LineCount += 4;
				TotalLines += 4;
				linesToLevelUpCount = (linesToLevelUpCount - 4) % levelChanging;
				if (linesToLevelUpCount == 0)
					linesToLevelUpCount = levelChanging;
				fRemainingLines.setString(std::to_string(linesToLevelUpCount));
				fTotalLinesCount.setString(std::to_string(TotalLines));
			}
			else
			{
				//less epic but still epic sound effect
				fLineClear.play();
				fScore += 10 * rowsToDelete.size();
				fScoreText.setString(std::to_string(fScore));
				LineCount += rowsToDelete.size();
				TotalLines += rowsToDelete.size();
				linesToLevelUpCount = (linesToLevelUpCount - rowsToDelete.size()) % levelChanging;
				if (linesToLevelUpCount == 0)
					linesToLevelUpCount = levelChanging;
				fRemainingLines.setString(std::to_string(linesToLevelUpCount));
				fTotalLinesCount.setString(std::to_string(TotalLines));
			}

		}
		/*Then we erase them*/
		//TODO: Animate the process of erasing the rows
		if (fAnimationIndex_left <= -1 && fAnimationIndex_right >= GgameBorders.width)
		{
			fEndOfErasingAnimation = true;
			fAnimationIndex_left = GgameBorders.width / 2;
			fAnimationIndex_right = GgameBorders.width / 2;
		}
		else {
			for (int k = 0; k < rowsToDelete.size(); ++k)
			{
				if (fAnimationIndex_left > -1 && GAllTheBlocks[fAnimationIndex_left + rowsToDelete[k] * GgameBorders.width]) {
					delete GAllTheBlocks[fAnimationIndex_left + rowsToDelete[k] * GgameBorders.width];
					GAllTheBlocks[fAnimationIndex_left + rowsToDelete[k] * GgameBorders.width] = nullptr;
				}
				if (fAnimationIndex_right < GgameBorders.width && GAllTheBlocks[fAnimationIndex_right + rowsToDelete[k] * GgameBorders.width]) {
					delete GAllTheBlocks[fAnimationIndex_right + rowsToDelete[k] * GgameBorders.width];
					GAllTheBlocks[fAnimationIndex_right + rowsToDelete[k] * GgameBorders.width] = nullptr;
				}

			}
		}

		if (fEndOfErasingAnimation) {
			/*And then we adjust the position of the remaining rows*/
			int movingAmount = 1;
			for (int j = GgameBorders.height - 1; j >= movingAmount; --j)
			{
				bool isUpForMoving = false;
				auto iter = std::find(rowsToDelete.begin(), rowsToDelete.end(), j);
				if (iter != rowsToDelete.end())	//this row has been deleted
				{
					movingAmount = 1;
					while (std::find(rowsToDelete.begin(), rowsToDelete.end(), j - movingAmount) != rowsToDelete.end()) //the one above has also been deleted
						movingAmount++;
					isUpForMoving = true;
				}
				for (int i = 0; i < GgameBorders.width; ++i)
				{
					int coords = i + j * GgameBorders.width;

					//the current row was not destroy but the next row was so we need to move the current row down 1 row
					if (isUpForMoving)
					{
						/*move down the row*/
						Block* b = GAllTheBlocks[i + (j - movingAmount) * GgameBorders.width];
						if (b)
						{
							GAllTheBlocks[i + (j - movingAmount) * GgameBorders.width] = nullptr;
							GAllTheBlocks[coords] = b;
							b->setBlockGlobalPos(b->getBlockGlobalPos().x, b->getBlockGlobalPos().y + movingAmount);
						}
					}
				}
				if (isUpForMoving)	//now it's the former row that has been "destroyed" (actually, it has just been moved down)
				{
					*iter = j - movingAmount;
				}
			}
			rowsToDelete.clear();
		}
	};

	bool focus = true;

	GameStates fCurrentGameState = GameStates::GameOn;

	while (window.isOpen())
	{
		deltaTime = clock.restart();
		Accu += deltaTime;
		AccuMovement += deltaTime;
		sf::Event e;

		while (window.pollEvent(e))
		{
			switch (e.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (fCurrentGameState == GameStates::GameOn) {
					if ((e.key.code == sf::Keyboard::Space || e.key.code == sf::Keyboard::Enter) && tetrisActive->getState() != Tetris::State::Static)
					{
						tetrisActive->rotateBlock(GAllTheBlocks);
					}
					switch (e.key.code)
					{
					case sf::Keyboard::Left:
					case sf::Keyboard::Q:
						if (hasReachBorders(*tetrisActive) != Borders::Left)
							tetrisActive->moveBlock(-1, 0, GAllTheBlocks);
						break;
					case sf::Keyboard::Right:
					case sf::Keyboard::D:
						if (hasReachBorders(*tetrisActive) != Borders::Right)
							tetrisActive->moveBlock(1, 0, GAllTheBlocks);
						break;
					case sf::Keyboard::Down:
					case sf::Keyboard::S:
						while (tetrisActive->getState() != Tetris::State::Static)
							tetrisActive->moveBlock(0, 1, GAllTheBlocks);
						break;
					default:
						break;
					}
				}
				if (e.key.code == sf::Keyboard::Escape)
					window.close();
				break;
			case sf::Event::GainedFocus:
				focus = true;
				break;
			case sf::Event::LostFocus:
				focus = false;
				break;
			case sf::Event::MouseButtonPressed:
				if (fCurrentGameState == GameStates::GameOver)
				{
					if (retryButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						//retry
						fMusic.play();
						TotalLines = 0;
						fScore = 0;
						fLevel = 1;
						LineCount = 0;
						levelChanging = 10;
						linesToLevelUpCount = levelChanging;
						frameRateMovement = sf::seconds(1.f / 3.f);
						fScoreText.setString(std::to_string(fScore));
						fLevelText.setString(std::to_string(fLevel));
						fRemainingLines.setString(std::to_string(linesToLevelUpCount));
						fTotalLinesCount.setString(std::to_string(TotalLines));
						fPressButtonSound.play();
						for (Block* b : GAllTheBlocks) {
							if(b)
								delete b;
						}
						GAllTheBlocks.clear();
						GAllTheBlocks = std::vector<Block*>(GgameBorders.width * GgameBorders.height, nullptr);
						if (tetrisActive)
							delete tetrisActive;
						if (tetrisPassive)
							delete tetrisPassive;
						tetrisActive = new Tetris{ fTextures[Blocks], activeDefaultPos.x, activeDefaultPos.y, static_cast<Tetris::Type>(Utility::randomInt(static_cast<int>(Tetris::Type::Count)))
							, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)) };
						tetrisActive->setBlockPos(activeDefaultPos);
						tetrisPassive = new Tetris(fTextures[Blocks], passiveDefaultPos.x, passiveDefaultPos.y, static_cast<Tetris::Type>(Utility::randomInt(static_cast<int>(Tetris::Type::Count)))
							, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)));

						fCurrentGameState = GameStates::GameOn;
					}
					else if (quitButton.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition(window))))
					{
						//quit
						window.close();
					}
				}
				break;
			default:
				break;
			}
		}

		//update stuff
		while (Accu >= frameRate)
		{
			Accu -= frameRate;

			if (fLevel >= 3)
				levelChanging = 7;
			if (fLevel >= 5)
				levelChanging = 5;
			if (fLevel >= 10)
				levelChanging = 4;
			if (focus) {
				switch (fCurrentGameState)
				{
				case GameStates::GameOn:
					if (LineCount >= levelChanging)	//level up
					{
						LineCount -= levelChanging;
						fLevelText.setString(std::to_string(++fLevel));
						frameRateMovement = sf::seconds(1.f / (3.f + std::log(float(fLevel))));
					}

					if (AccuMovement >= frameRateMovement) {
						tetrisActive->moveBlock(0, 1, GAllTheBlocks);
						AccuMovement = sf::Time::Zero;
					}
					if (tetrisActive->getState() == Tetris::State::Static)
					{
						if (tetrisActive->getBlockPos().y == 0)
						{
							//game over
							fCurrentGameState = GameStates::GameOver;
							fGameOverSound.play();
							fMusic.stop();

							if (fScore > highScore.first)
							{
								saveHighScore(std::make_pair(fScore, highScore.second));
								highScore.first = fScore;
								fHighScoreSText.setString("HighScore : " + std::to_string(fScore));
							}
							if (fLevel > highScore.second)
							{
								saveHighScore(std::make_pair(highScore.first, fLevel));
								highScore.second = fLevel;
								fHighScoreLText.setString("HighLevel : " + std::to_string(fLevel));
							}
							
						}
						else {
							DeletingRows();

							if (fEndOfErasingAnimation) {
								delete tetrisActive;
								tetrisActive = tetrisPassive;
								tetrisActive->setBlockPos(activeDefaultPos);
									if (tetrisNotHeroCount >= 14) {
										tetrisPassive = new Tetris(fTextures[Blocks], passiveDefaultPos.x, passiveDefaultPos.y, Tetris::Type::Hero
											, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)));
									}
									else
									{
										tetrisPassive = new Tetris(fTextures[Blocks], passiveDefaultPos.x, passiveDefaultPos.y, static_cast<Tetris::Type>(Utility::randomInt(static_cast<int>(Tetris::Type::Count)))
											, static_cast<Block::Color>(Utility::randomInt(Block::ColorCount)));
									}
								if (tetrisActive->fType != Tetris::Type::Hero)
									tetrisNotHeroCount++;
								else
								{
									tetrisNotHeroCount = 0;
								}
							}
							else
							{
								fAnimationIndex_left--;
								fAnimationIndex_right++;
							}
						}
					}
					break;
				case GameStates::GameOver:

					break;
				default:
					break;
				}
				
			}
		}

		//////////
		window.clear(sf::Color::Black);
		switch (fCurrentGameState)
		{
		case GameStates::GameOn:
			window.draw(fUIBackground);
			if(fEndOfErasingAnimation && tetrisActive)
				window.draw(*tetrisActive);
			if(tetrisPassive)
				window.draw(*tetrisPassive);

			for (Block* b : GAllTheBlocks) {
				if (b)
					window.draw(*b);
			}
			break;
		case GameStates::GameOver:
		{
			window.draw(fUIBackground);
			if(tetrisActive)
				window.draw(*tetrisActive);
			if(tetrisPassive)
				window.draw(*tetrisPassive);

			for (Block* b : GAllTheBlocks) {
				if (b)
					window.draw(*b);
			}

			sf::RectangleShape backFog{ window.getView().getSize() };
			backFog.setFillColor(sf::Color::Color(0, 0, 0, 125));

			window.draw(backFog);
			window.draw(retryButton);
			window.draw(quitButton);
		}
			break;
		default:
			break;
		}
		
		window.draw(fLevelText);
		window.draw(fScoreText);
		window.draw(fHighScoreSText);
		window.draw(fHighScoreLText);
		window.draw(fTotalLinesCount);
		window.draw(fRemainingLines);
		window.display();
	}


	for (Block* b : GAllTheBlocks)
		if (b)
			delete b;
	if (tetrisActive)
		delete tetrisActive;
	if (tetrisPassive)
		delete tetrisPassive;

	return 0;
}