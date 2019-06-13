#include "playstate.h"


// Vaš kod.

#include <SFML/Audio.hpp>
#include <time.h>
#include "game.h"

#include <unistd.h>


PlayState::PlayState(Game *pGame) : GameState{pGame}
{
    if (!mMusic.openFromFile("TetrisKorobeiniki.ogg"))
      return;
  mMusic.setVolume(70.f);
}

void PlayState::start()
{
    mBoard.emptyGridContent();
    mBoard.setNoGameOver();
    mScore.setNull();
    mMusic.play();
    mBoard.setSpeed(mpGame->mGameSpeed);
}

void PlayState::handleEvents(sf::Event event)
{
    switch(event.type)
      {
      case sf::Event::KeyPressed:
          if(event.key.code == sf::Keyboard::Left)
              mLeft = 1;
          if(event.key.code == sf::Keyboard::Right)
              mRight = 1;
          if(event.key.code == sf::Keyboard::Down)
              mDown = 1;
          if(event.key.code == sf::Keyboard::Up)
              mRotate = 1;
          if(event.key.code == sf::Keyboard::Space)
              mDrop = 1;
            break;
      case sf::Event::KeyReleased:
          if(event.key.code == sf::Keyboard::Left)
              mLeft = 0;
          if(event.key.code == sf::Keyboard::Right)
              mRight = 0;
          if(event.key.code == sf::Keyboard::Up)
              mRotate = 0;
          if(event.key.code == sf::Keyboard::Down)
              mDown = 0;
          if(event.key.code == sf::Keyboard::Space)
              mDrop = 0;
          break;
      }
}

int PlayState::update(const sf::Time &dt)
{
    if(mBoard.isGameOver()) { mpGame->setState(State::Speed); mpGame->mGameScore=mScore.getScore(); return -1; }
    int no = mBoard.update(dt, mLeft, mRight, mDrop, mDown, mRotate);
    mScore.update(no);
}

void PlayState::render()
{
    sf::RenderWindow * win = mpGame->getWindow();
    win->draw(mBoard);
    win->draw(mScore);
}
