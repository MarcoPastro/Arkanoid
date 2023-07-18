// All the SDL includes we need
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

#include <cstdio> //Some utilities for the log
#include <memory> // Needed for the smart pointers
#include <iostream>
#include <random>

#include "MGDMovableTexture.h"
#include "MGDTexture.h"
#include "MGDTimer.h"
#include "TextureManagement.h"
#include "Player.h"
#include "CollisionManager.h"
#include "Ball.h"
#include "EnemiesBlock.h"

#include "MGDMain.hpp" // Used just to hide some extra code

/*
        @brief
        get a random number in a range
        @param min the min number of the range
        @param max the max number of the range
        @return the random value in the range
*/
int getRandomNumber(int min, int max) {
    return min + (rand() % (max-min));
}
/*
        @brief
        get a random number in a range
        @param numBlocks number of blocks
        @param windowWidth the width where blocks can spawn
        @param windowHeight the height where blocks can spawn
        @param spaceForThePlayer the space to subtract for the player
        @param textureGiver the texture manager for each block
        @param textureGiver the collisionManager manager for each block
        @return the array of blocks with a random location in a window
*/
EnemiesBlock** CreateRandomBlocks(int numBlocks, int windowWidth, int windowHeight, int spaceForThePlayer, TextureManagement* textureGiver, CollisionManager* collisionManager) {
    EnemiesBlock** enemiesArray = new EnemiesBlock*[numBlocks];
    int realWindowHeight = windowHeight-spaceForThePlayer;

    int numCols = 1;
    int numRows = numBlocks;

    for (int i = 2; i <= sqrt(numBlocks); ++i) {
        if (numBlocks % i == 0) {
            numCols = i;
            numRows = numBlocks / i;
            break;
        }
    }

    for (int i = 0; i < numBlocks; ++i) {
        int life = getRandomNumber(1, 4);//possible Blocks
        std::string textureName;
        switch (life) {
        case 1:
            textureName = "Block1";
            break;
        case 2:
            textureName = "Block2";
            break;
        case 3:
            textureName = "Block3";
            break;
        }
        enemiesArray[i] = new EnemiesBlock(textureGiver, textureName, collisionManager,life);
    }

    int rectangleSizeX = windowWidth / numRows;
    int rectangleSizeY = realWindowHeight / numCols;

    int i = 0;
    for (int col = 0; col < numCols; ++col) {
        for (int row = 0; row < numRows; ++row) {
            if (i < numBlocks) {
                int x = row * rectangleSizeX;
                int y = col * rectangleSizeY;
                enemiesArray[i]->setPosX(getRandomNumber(x, x + rectangleSizeX - enemiesArray[i]->getTextureWidth()));
                enemiesArray[i]->setPosY(getRandomNumber(y, y + rectangleSizeY - enemiesArray[i]->getTextureHeight()));
                ++i;
            }
        }
    }
    return enemiesArray;
}
int main() {
    // SDL Event handler
    SDL_Event sdlEvent;
        
    // Game loop flag
    bool isQuittingGame = false;
    bool isMenu = true;
    bool restart = false;
    bool gameOver = false;
    // Keeps track of time between steps
    MGDTimer stepTimer;

    // I will add a rotation to the smile
    double smileAngle = 0.0;

    // I will alternate the images in the spreadsheet, so I have to mantain a counter of which image I am using
    constexpr unsigned int spritesNum = 6;
    constexpr unsigned int spritesheetRowSize = 4;
    unsigned int spritesheetCurrentColumn = 0;
    unsigned int spritesheetCurrentRow = 0;
    unsigned int spriteCurrentIndex = 0;
    unsigned int nextSpriteCountdown = 0; // in milliseconds
    constexpr int maxCount = 30000;       // this value is used to restore to 0 the milliseconds count (useful for the movement on the x axis)

    srand(time(NULL));

    int numberOfBlocksPerLevels = 3;
    const int MAX_BLOCKS = 30;
    const int MIN_BLOCKS = 1;

    // TEXTURES LOADING, with different type of allocation:
    SDL_Color textColor{ 0x5c, 0x80, 0x01 }; // a kind of green

    while (isMenu) {
        SDL_SetRenderDrawColor(globalRenderer, 0xca, 0xcc, 0x90, 0xFF); // a kind of yellow
        SDL_RenderClear(globalRenderer);
        // TEXTURES LOADING, with different type of allocation:
        MGDTexture* startTexture = new MGDTexture();

        std::string stringNumberOfBlocks = "Press a/d to start, w/s N blocks = " + std::to_string(numberOfBlocksPerLevels);

        startTexture->loadFromRenderedText(stringNumberOfBlocks, textColor);


        while (SDL_PollEvent(&sdlEvent) != 0) {
            switch (sdlEvent.key.keysym.sym) {
            case SDLK_UP:
            case 'w':
                if(MAX_BLOCKS > numberOfBlocksPerLevels) ++numberOfBlocksPerLevels;
                break;
            case SDLK_DOWN:
            case 's':
                if (MIN_BLOCKS < numberOfBlocksPerLevels) --numberOfBlocksPerLevels;
                break;
            case SDLK_LEFT:
            case 'a':
            case SDLK_RIGHT:
            case 'd':
                isMenu = false;
                break;
            case SDLK_ESCAPE:
                isQuittingGame = true;
                isMenu = false;
            }
        }
        startTexture->render((SCREEN_WIDTH / 2) - (startTexture->getWidth() / 2), 0);
        SDL_RenderPresent(globalRenderer);
        delete startTexture;
    }

    MGDTexture* finishTexture = new MGDTexture();

    finishTexture->loadFromRenderedText("Game Over! Press a or d to restart!", textColor);

    const int playerStartingPositionX = 320;
    const int playerStartingPositionY = 450;

    const int velocityPlayer = 300;
    const int velocityBall = 200;
    const int numTextures = 6;
    std::string* allthepaths = new std::string[numTextures]{
        "Assets/Player1.png",
        "Assets/Block1.png",
        "Assets/Block2.png",
        "Assets/Block3.png",
        "Assets/dot.bmp",
        "Assets/arkanoidBackground.png"
    };
    std::string* allTheDefaultNames = new std::string[numTextures]{
        "Player",
        "Block1",
        "Block2",
        "Block3",
        "Ball",
        "Background"
    };

    CollisionManager* collisionManager = new CollisionManager();

    TextureManagement* textureManagement = new TextureManagement(allthepaths, allTheDefaultNames, numTextures);

    
    EnemiesBlock** enemiesBlocks = CreateRandomBlocks(numberOfBlocksPerLevels, SCREEN_WIDTH, SCREEN_HEIGHT, 100, textureManagement, collisionManager);

    Player* player = new Player(textureManagement, "Player", collisionManager, velocityPlayer, playerStartingPositionX, playerStartingPositionY);
    player->setVelX(0.0);
    player->setVelY(0.0);
    Ball* ball = new Ball(textureManagement, "Ball", collisionManager, velocityBall, playerStartingPositionX, playerStartingPositionY-player->getTextureHeight()*2);
    ball->setVelY(-(ball->getVelocity()));

    MGDTexture* backgroundTexture = textureManagement->getTheTexture("Background");

    collisionManager->AddBlock(player);
    collisionManager->AddBall(ball);
    for (int i = 0; i < numberOfBlocksPerLevels; ++i) {
        collisionManager->AddBlock(enemiesBlocks[i]);
    }
    


    

    // GAME LOOP
    // While application is running
    while (!isQuittingGame) {



        // Handle events on queue
        while (SDL_PollEvent(&sdlEvent) != 0) {
            // User requests quit
            if (sdlEvent.type == SDL_QUIT) {
                isQuittingGame = true;
            }

            // Handle input for the texture
            player->handleEvent(sdlEvent);
        }

        // Get the delta time in milliseconds
        Uint32 deltaTime = stepTimer.getTicks();
        // Calculate the delta time in seconds
        double deltaTimeF = deltaTime * 0.001;
        // Move for time step
        player->move(deltaTimeF);
        ball->move(deltaTimeF);

        // Restart step timer
        stepTimer.start();

        // Clear screen
        SDL_SetRenderDrawColor(globalRenderer, 0xca, 0xcc, 0x90, 0xFF); // a kind of yellow
        SDL_RenderClear(globalRenderer);

        // TEXTURE RENDERING:
        backgroundTexture->render(0, 0);
        // Rendering the player:
        player->render();
        ball->render();
        for (int i = 0; i < numberOfBlocksPerLevels; ++i) {
            enemiesBlocks[i]->render();
        }
        {
            bool finish = true;
            for (int i = 0; i < numberOfBlocksPerLevels && finish; ++i) {
                if (enemiesBlocks[i]->getActive()) {
                    finish = false;
                }
            }
            if (finish || ball->getActive()==false) {
                gameOver = true;
            }
        }
        while (gameOver) {
            SDL_SetRenderDrawColor(globalRenderer, 0xca, 0xcc, 0x90, 0xFF); // a kind of yellow
            SDL_RenderClear(globalRenderer);
            while (SDL_PollEvent(&sdlEvent) != 0) {
                // User requests quit
                switch (sdlEvent.key.keysym.sym) {
                case SDLK_LEFT:
                case 'a':
                case SDLK_RIGHT:
                case 'd':
                    for (int i = 0; i < numberOfBlocksPerLevels; ++i) {
                        enemiesBlocks[i]->setActive(true);
                        enemiesBlocks[i]->ResetLife();
                    }
                    ball->setActive(true);
                    ball->setPosX(playerStartingPositionX);
                    ball->setPosY(playerStartingPositionY - player->getTextureHeight() * 2);
                    ball->setVelY(-(ball->getVelocity()));
                    gameOver = false;
                    break;
                case SDLK_ESCAPE:
                    isQuittingGame = true;
                    gameOver = false;
                }
            }
            finishTexture->render((SCREEN_WIDTH / 2) - (finishTexture->getWidth() / 2), 0);
            SDL_RenderPresent(globalRenderer);
        }

        // Update screen
        SDL_RenderPresent(globalRenderer);
        
    }

    // Free resources

    delete[] allthepaths;
    delete[] allTheDefaultNames;
    delete finishTexture;

    delete player;
    player = nullptr;
    delete ball;
    ball = nullptr;
    for (int i = 0; i < numberOfBlocksPerLevels; ++i) {
        delete enemiesBlocks[i];
        enemiesBlocks[i] = nullptr;
    }
    delete[] enemiesBlocks;
    enemiesBlocks = nullptr;

    delete collisionManager;
    delete textureManagement;
    return 0;
}
