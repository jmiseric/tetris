#include "score.h"
#include <cstdlib>
#include <iostream>

// Vaša implementacija (mala izmjena prema prvoj verziji)

Score::Score()
{
    if(!mFont.loadFromFile("Gasalt-Regular.ttf")){
        std::cerr << "Ne mogu učitati font: Gasalt-Regular.ttf !" << std::endl;
        std::exit(1);
    }
   // Vaš kod dolazi ovdje
    mScoreText.setFont(mFont);
    mScoreText.setString("Score: 0");
    mScoreText.setCharacterSize(25);
    mScoreText.setPosition(350,100);

}

void Score::addNoLinesCompleted(int n)
{
  // Vaš kod.
    mScore += n*10;
    mTotalLinesCompleted += n;
}
void Score::update(int no)
{
  // Vaš kod.
    //if(no == -1) setGameOver();
    addNoLinesCompleted(no);
    std::string score = std::to_string(mScore);
    score = "Score: " + score;
    mScoreText.setString(score);
}

void Score::setNull()
{
    mScore = 0;
}

void Score::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  // Vaš kod.
    target.draw(mScoreText, states);
}
