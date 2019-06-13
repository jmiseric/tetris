#include "game.h"
#include "playstate.h"

#include <iostream>

Game::Game() : mWindow(sf::VideoMode(500,600), "Tetris"), mGameSpeed(3.0f),
               mGameScore(0)
{
    // Inicijalizacija stanja dolazi ovdje
    mAllStates[0] = new WelcomeState(this);
    mAllStates[1] = new PlayState(this);
    mAllStates[2] = new SpeedState(this);
    mpGameState = mAllStates[GameState::State::Welcome];

}

Game::~Game()
{
   // Eventualna dealokacija  
}

void Game::run(){
    sf::Clock clock; //odma krene teći vrijeme
    sf::Time proteklo_vrijeme = sf::Time::Zero;
    sf::Time dt = sf::seconds(1.f/100.f);
    while(mWindow.isOpen()){
        processEvents();
        proteklo_vrijeme = clock.restart();
        while (proteklo_vrijeme > dt)
          {
              proteklo_vrijeme -= dt;
              update(dt);
          //update();
          }
        update(dt);
        render();
    }
}

void Game::setState(GameState::State st)
{
    mpGameState = mAllStates[st];
    mpGameState->start();
}

sf::RenderWindow * Game::getWindow()
{
    return &mWindow;
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            mWindow.close();
        else if(event.type ==sf::Event::Resized){
            // Spriječi deformaciju objekata prilikom promjene veličine prozora
            sf::FloatRect viewRect(0, 0, event.size.width, event.size.height);
            mWindow.setView(sf::View(viewRect));
        }
        else {
            mpGameState->handleEvents(event);
        }
    }
}

void Game::update(const sf::Time &dt)
{

    mpGameState->update(dt);

}

void Game::render()
{
     mWindow.clear();
     mpGameState->render();
     mWindow.display();
}
