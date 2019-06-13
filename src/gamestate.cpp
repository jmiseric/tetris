#include "gamestate.h"
#include "game.h"
#include <cstdlib>
#include <iostream>


// Vaš kod dolazi ovdje.

WelcomeState::WelcomeState(Game *pGame) : GameState{pGame}
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText1.setString("Tetris clone by J.Miseric");
    mText1.setCharacterSize(35);
    mText1.setPosition(75,200);
    mText2.setString("Press any key to continue");
    mText2.setCharacterSize(25);
    mText2.setPosition(100,300);
}

void WelcomeState::handleEvents(sf::Event event)
{
  //if( sf::Event::KeyPressed ) ;
  if (event.type == sf::Event::KeyPressed) mpGame->setState(State::Playing); //promijeni state

}

int WelcomeState::update(const sf::Time &dt)
{
    return 0;
}

void WelcomeState::render()
{
    sf::RenderWindow * win = mpGame->getWindow();
    win->draw(mText1);
    win->draw(mText2);
}

SpeedState::SpeedState(Game *pGame) : GameState{pGame}
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mText0.setFont(mFont);
    mText1.setFont(mFont);
    mText2.setFont(mFont);
    mText3.setFont(mFont);
    std::string score = "Score = " + std::to_string(mpGame->mGameScore);
    mText0.setString(score);
    mText0.setCharacterSize(25);
    mText0.setPosition(200,200);
    std::string speed = "Current speed = " + std::to_string(mpGame->mGameSpeed);
    mText1.setString(speed);
    mText1.setCharacterSize(25);
    mText1.setPosition(175,225);
    mText2.setString("Use keys Up and Down to change the speed.");
    mText2.setCharacterSize(25);
    mText2.setPosition(30,250);
    mText3.setString("Enter to continue.");
    mText3.setCharacterSize(25);
    mText3.setPosition(185,275);
}

void SpeedState::handleEvents(sf::Event event)
{
    switch(event.type)
      {
      case sf::Event::KeyPressed:
          if(event.key.code == sf::Keyboard::Return)
             { mpGame->setState(State::Playing); break; }
          if(event.key.code == sf::Keyboard::Up)
             { mpGame->mGameSpeed += 0.01;  }
          if(event.key.code == sf::Keyboard::Down)
             { mpGame->mGameSpeed -= 0.01;  }
          /*if(event.key.code == sf::Keyboard::Up)
              mRotate = 1;
          if(event.key.code == sf::Keyboard::Space)
              mDrop = 1;
            break;
      case sf::Event::KeyReleased:
          if(event.key.code == sf::Keyboard::Left)
              mLeft = 0;
          if(event.key.code == sf::Keyboard::Right)
              mRight = 0;*/
          /*if(event.key.code == sf::Keyboard::Up)
             { d = 0; }
          if(event.key.code == sf::Keyboard::Down)
              { d = 0; }
          if(event.key.code == sf::Keyboard::Space)
              mDrop = 0;*/
          break;
      }
}

int SpeedState::update(const sf::Time &dt)
{
    std::string s = std::to_string(mpGame->mGameScore);
    score = "Score = " + s;
    mText0.setString(score);
    next += dt;
    sf::Time t = sf::seconds(0.5);
    while(next > t) {
        next -= t;
        //mpGame->mGameSpeed+=d;

        s = std::to_string(mpGame->mGameSpeed);
        score = "Current speed = " + s;
        mText1.setString(score);
    }
    return 0;
}

void SpeedState::render()
{
    sf::RenderWindow * win = mpGame->getWindow();
    win->draw(mText0);
    win->draw(mText1);
    win->draw(mText2);
    win->draw(mText3);
}
