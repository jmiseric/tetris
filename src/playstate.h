#ifndef PLAY_STATE_H
#define PLAY_STATE_H

#include <SFML/Window/Event.hpp>
#include <SFML/Audio.hpp>


#include "gamestate.h"
#include "board.h"
#include "score.h"

// Ovo je bivša klasa Game. Doraditi.

class PlayState : public GameState
{
public:
    PlayState(Game * pGame = NULL);
    void  start() override;
private:
    Board mBoard;
    Score mScore;
    int mLeft = 0;
    int mRight = 0;
    int mDrop = 0;
    int mDown = 0;
    int mRotate = 0;
    sf::Music mMusic;

    virtual void handleEvents(sf::Event event) override;
    virtual int update(const sf::Time &dt) override;
    virtual void render() override;
};

#endif // PLAY_STATE_H
