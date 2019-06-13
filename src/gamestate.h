#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
class Game;

class GameState
{
public:
    GameState(Game * pGame) : mpGame(pGame){}
    virtual ~GameState() {}
    // Sva moguća stanja igre.
        enum State{
            Welcome,
            Playing,
            Speed,
            SIZE
        };
    // Metode koje moraju osigurati sva stanja igre.
    virtual void handleEvents(sf::Event event) = 0;
    virtual int update(const sf::Time &dt) = 0;
    virtual void render() = 0;
	// Restartanje igre. To će preraditi samo GameState.
    virtual void start() {}

protected:
        Game * const mpGame;
};


class WelcomeState : public GameState{
public:
    WelcomeState(Game * pGame = NULL);
    virtual void handleEvents(sf::Event event) override;
    virtual int update(const sf::Time &dt) override;
    virtual void render() override;
private:
    sf::Text mText1;
    sf::Text mText2;
    sf::Font mFont;
};

class SpeedState : public GameState{
public:
    SpeedState(Game * pGame = NULL);
    virtual void handleEvents(sf::Event event) override;
    virtual int update(const sf::Time &dt) override;
    virtual void render() override;
    float d;
    sf::Time next = sf::Time::Zero;
private:
    std::string score;
    sf::Text mText0;
    sf::Text mText1;
    sf::Text mText2;
    sf::Text mText3;
    sf::Font mFont;

};

#endif // GAMESTATE_H
