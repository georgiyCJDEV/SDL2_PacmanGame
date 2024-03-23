#include "init.h"
#include "timer.h"
#include "wall.h"
#include "points.h"
#include "file.h"
#include "button.h"
#include "menu.h"
#include "ghost.h"
#include "player.h"
#include <string>
#include <iostream>
#include <thread>

void GameLoop(AppInit& app, bool& ispaused,
	Ghost& Ghost, Wall& walls, Points& points, Player& pac,
	std::string& playerName, int& highScore,
	LTimer& ghostTimer, bool& rmoved, bool& bmoved, bool& ymoved, bool& pmoved,
	bool& quit, bool& isOver)
{

	SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
	SDL_RenderClear(app.getRenderer());
	SDL_RenderPresent(app.getRenderer());

	while (!quit)
	{
		SDL_SetRenderDrawColor(app.getRenderer(), 0, 0, 0, 0);
		SDL_RenderClear(app.getRenderer());

		walls.renderWalls(app);
		points.renderPoints(app);
		pac.showInterf(playerName, highScore, app);

		if (!ispaused)
		{
			if (pac.getPacState()==pac.Alive)
			{
				pac.move(app, walls, points, Ghost, ghostTimer);

				if (Ghost.getGhosts()[Ghost.Red]->getColor() == 0)
				{
					Ghost.getGhosts()[Ghost.Red]->moveTo(pac.getPosX(), pac.getPosY(), walls, rmoved);
				}

				if (Ghost.getGhosts()[Ghost.Blue]->getColor() == 1)
				{
					if (!bmoved)
					{
						Ghost.getGhosts()[Ghost.Blue]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 88, walls, bmoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Blue]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 88, walls, bmoved);
					}
				}

				if (Ghost.getGhosts()[Ghost.Yellow]->getColor() == 2)
				{
					if (!ymoved)
					{
						Ghost.getGhosts()[Ghost.Yellow]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 88, walls, ymoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Yellow]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 88, walls, ymoved);
					}
				}

				if (Ghost.getGhosts()[Ghost.Pink]->getColor() == 3)
				{
					if (!pmoved)
					{
						Ghost.getGhosts()[Ghost.Pink]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 240, walls, pmoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Pink]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 304, walls, pmoved);
					}
				}

				if (Ghost.getGhosts()[Ghost.Red]->getColor() == 5)
				{
					Ghost.getGhosts()[Ghost.Red]->moveTo(pac.getPosX(), pac.getPosY(), walls, rmoved);

					if (ghostTimer.getTicks() >= 7000)
					{
						Ghost.getGhosts()[Ghost.Red]->getColor() = 0;
						Ghost.getGhosts()[Ghost.Red]->setColor(Ghost.Red);
						pac.setKillCount(0);
					}
				}

				if (Ghost.getGhosts()[Ghost.Blue]->getColor() == 5)
				{
					if (!bmoved)
					{
						Ghost.getGhosts()[Ghost.Blue]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 88, walls, bmoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Blue]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 88, walls, bmoved);
					}

					if (ghostTimer.getTicks() >= 7000)
					{
						Ghost.getGhosts()[Ghost.Blue]->getColor() = 1;
						Ghost.getGhosts()[Ghost.Blue]->setColor(Ghost.Blue);
						pac.setKillCount(0);
					}
				}

				if (Ghost.getGhosts()[Ghost.Yellow]->getColor() == 5)
				{
					if (!ymoved)
					{
						Ghost.getGhosts()[Ghost.Yellow]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 88, walls, ymoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Yellow]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 88, walls, ymoved);
					}

					if (ghostTimer.getTicks() >= 7000)
					{
						Ghost.getGhosts()[Ghost.Yellow]->getColor() = 2;
						Ghost.getGhosts()[Ghost.Yellow]->setColor(Ghost.Yellow);
						pac.setKillCount(0);
					}
				}

				if (Ghost.getGhosts()[Ghost.Pink]->getColor() == 5)
				{
					if (!pmoved)
					{
						Ghost.getGhosts()[Ghost.Pink]->moveTo(app.getBounds_x() + 24, app.getBounds_y() + 240, walls, pmoved);
					}
					else
					{
						Ghost.getGhosts()[Ghost.Pink]->moveTo(app.getBounds_x() + 256, app.getBounds_y() + 304, walls, pmoved);
					}

					if (ghostTimer.getTicks() >= 7000)
					{
						Ghost.getGhosts()[Ghost.Pink]->getColor() = 3;
						Ghost.getGhosts()[Ghost.Pink]->setColor(Ghost.Pink);
						pac.setKillCount(0);
					}
				}

				if (Ghost.getGhosts()[Ghost.Red]->getColor() == 4)
				{
					Ghost.getGhosts()[Ghost.Red]->moveTo(app.getBounds_x() + 88, app.getBounds_y() + 144, walls, rmoved);
					if (Ghost.getGhosts()[Ghost.Red]->getPosX() == app.getBounds_x() + 88 && Ghost.getGhosts()[Ghost.Red]->getPosY() == app.getBounds_y() + 144)
					{
						Ghost.getGhosts()[Ghost.Red]->getColor() = 0;
						Ghost.getGhosts()[Ghost.Red]->setColor(Ghost.Red);
					}
				}
				if (Ghost.getGhosts()[Ghost.Blue]->getColor() == 4)
				{
					Ghost.getGhosts()[Ghost.Blue]->moveTo(app.getBounds_x() + 168, app.getBounds_y() + 144, walls, bmoved);
					if (Ghost.getGhosts()[Ghost.Blue]->getPosX() == app.getBounds_x() + 168 && Ghost.getGhosts()[Ghost.Blue]->getPosY() == app.getBounds_y() + 144)
					{
						Ghost.getGhosts()[Ghost.Blue]->getColor() = 1;
						Ghost.getGhosts()[Ghost.Blue]->setColor(Ghost.Blue);
					}
				}
				if (Ghost.getGhosts()[Ghost.Yellow]->getColor() == 4)
				{
					Ghost.getGhosts()[Ghost.Yellow]->moveTo(app.getBounds_x() + 88, app.getBounds_y() + 208, walls, ymoved);
					if (Ghost.getGhosts()[Ghost.Yellow]->getPosX() == app.getBounds_x() + 88 && Ghost.getGhosts()[Ghost.Yellow]->getPosY() == app.getBounds_y() + 208)
					{
						Ghost.getGhosts()[Ghost.Yellow]->getColor() = 2;
						Ghost.getGhosts()[Ghost.Yellow]->setColor(Ghost.Yellow);
					}
				}
				if (Ghost.getGhosts()[Ghost.Pink]->getColor() == 4)
				{
					Ghost.getGhosts()[Ghost.Pink]->moveTo(app.getBounds_x() + 168, app.getBounds_y() + 208, walls, pmoved);
					if (Ghost.getGhosts()[Ghost.Pink]->getPosX() == app.getBounds_x() + 168 && Ghost.getGhosts()[Ghost.Pink]->getPosY() == app.getBounds_y() + 208)
					{
						Ghost.getGhosts()[Ghost.Pink]->getColor() = 3;
						Ghost.getGhosts()[Ghost.Pink]->setColor(Ghost.Pink);
					}
				}
			}

			else if (pac.getPacState() == pac.Dead || pac.getPacState() == pac.NotSpawned)
			{
				Ghost.getGhosts()[Ghost.Red]->setColor(Ghost.Red);
				Ghost.getGhosts()[Ghost.Red]->setVel(0, 0);
				Ghost.getGhosts()[Ghost.Red]->setPos(app.getBounds_x() + 88, app.getBounds_y() + 144);
				Ghost.getGhosts()[Ghost.Red]->setFlags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

				Ghost.getGhosts()[Ghost.Blue]->setColor(Ghost.Blue);
				Ghost.getGhosts()[Ghost.Blue]->setVel(0, 0);
				Ghost.getGhosts()[Ghost.Blue]->setPos(app.getBounds_x() + 168, app.getBounds_y() + 144);
				Ghost.getGhosts()[Ghost.Blue]->setFlags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

				Ghost.getGhosts()[Ghost.Yellow]->setColor(Ghost.Yellow);
				Ghost.getGhosts()[Ghost.Yellow]->setVel(0, 0);
				Ghost.getGhosts()[Ghost.Yellow]->setPos(app.getBounds_x() + 88, app.getBounds_y() + 208);
				Ghost.getGhosts()[Ghost.Yellow]->setFlags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

				Ghost.getGhosts()[Ghost.Pink]->setColor(Ghost.Pink);
				Ghost.getGhosts()[Ghost.Pink]->setVel(0, 0);
				Ghost.getGhosts()[Ghost.Pink]->setPos(app.getBounds_x() + 168, app.getBounds_y() + 208);
				Ghost.getGhosts()[Ghost.Pink]->setFlags(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
			}

			isOver = pac.AnimMov(app);
			if (isOver)
			{
				pac.ShowGameOver(quit, app);
			}
			Ghost.getGhosts()[Ghost.Red]->AnimMov(app);
			Ghost.getGhosts()[Ghost.Blue]->AnimMov(app);
			Ghost.getGhosts()[Ghost.Yellow]->AnimMov(app);
			Ghost.getGhosts()[Ghost.Pink]->AnimMov(app);

		}
		else
		{
			Mix_PauseMusic();
			pac.pausedRender(app);
			pac.render(app);
			Ghost.renderGhosts(app);
		}

		SDL_RenderPresent(app.getRenderer());
	}

}

int main(int argc, char* argv[])
{
	SDL_Event e;

	File file;
	int highScore = 0;
	int len = 0;
	char* char_array = nullptr;
	struct list* player = file.read_file();
	int ncount = file.nodecount(player);

	AppInit app;
	app.Init();

	while (true)
	{
		bool quit = false;

		Menu menu(app);

		if (player != nullptr)
		{
			highScore = player->data.score;
		}

		while (!quit)
		{

			while (SDL_PollEvent(&e) != 0)
			{

				if (e.type == SDL_QUIT)
				{
					app.close();
					return 0;
				}

				switch (menu.getState())
				{
				case menu.Main:
					menu.mainMenu(e, app);
					break;
				case menu.Play:
					menu.plname(e, app, quit);
					break;
				case menu.Leaderboard:
					menu.leaderboard(e, app, player, quit, ncount);
					break;
				case menu.Info:
					menu.inform(e, app, quit);
					break;
				case menu.Exit:
					app.close();
					return 0;

				}

			}

		}
		quit = false;
		bool ispaused = false;
		int gameState = 0;
		bool isOver = false;

		LTimer ghostTimer;

		std::string playerName = menu.getName();
		int scoreCount;

		Wall walls(app);
		Points points(app);
		Ghost ghosts(app);
		Player pac(app);

		bool rmoved = false;
		bool bmoved = false;
		bool ymoved = false;
		bool pmoved = false;

		std::thread th(GameLoop, std::ref(app), std::ref(ispaused),
			std::ref(ghosts), std::ref(walls), std::ref(points), std::ref(pac), std::ref(playerName), std::ref(highScore), std::ref(ghostTimer),
			std::ref(rmoved), std::ref(bmoved), std::ref(ymoved), std::ref(pmoved),
			std::ref(quit), std::ref(isOver));

		while (!quit)
		{

			while (SDL_PollEvent(&e) && !isOver)
			{
				if (pac.getPacState() == pac.Alive)
				{
					pac.handleEvent(e, walls, ispaused);
				}

				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
			}
			if (isOver)
			{
				pac.gameOver(e, quit, gameState);
			}

		}
		scoreCount = pac.getScore();
		len = playerName.length();
		char_array = new char[len + 1];

		strcpy_s(char_array, len + 1, playerName.c_str());
		char_array[len] = '\0';

		player = file.new_node(player, file.input_player(&char_array, scoreCount, len));
		file.sort(player);
		file.clearlastpos(player);
		file.write_file(player);

		th.join();
		if (gameState == 1)
		{
			ghosts.remove_objects();
			points.remove_objects();
			walls.remove_objects();
			continue;
		}
		else
		{
			ghosts.remove_objects();
			points.remove_objects();
			walls.remove_objects();
			break;
		}
	}
	app.close();
	return 0;
}