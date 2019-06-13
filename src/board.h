#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "tetrimino.h"
#include <random>

/** Klasa Board
 *
 *  Klasa implementira svu logiku Tetris igre.
 */
class Board : public sf::Drawable, public sf::Transformable, public sf::NonCopyable {
public:
    Board();
    // Aktualizacija
    int update(/* potrebne varijable */const sf::Time &dt, int left, int right, int drop, int down, int rotate);
    // Pozicioniraj novi tetrimino na ploči.
    void spawnPiece();
    // Vraća true ako je igra gotova, inače false
    bool isGameOver() const;
    // Broj obrisanih linija od zadnje aktualizacije scene.
    int getNoLinesCompleted() const;
    void clearNoLinesCompleted();
    void emptyGridContent();
    void setNoGameOver();
    void setSpeed(float x);
private:
    static const int EMPTY = -1;
    static const int mCols = 10;       // Broj stupaca u mreži
    static const int mRows = 2* mCols; // Broj redaka u mreži

    sf::VertexArray mGrid;             // Linije koje čine mrežu.
    int mGridContent[mRows][mCols];    // Logički prikaz mreže

    // Dimenzije mreže
    float mLeftMargin = 50.f;
    float mTopMargin = 50.0f;
    float mWidth=200.f;
    float mHeight=2*mWidth;
    // Početak mreže = gornji lijevi kut
    float mOriginX, mOriginY;
    // Dimenzije ćelija
    float mDx = 20, mDy = 20;
    // Vremenski interval između propadanja tetrimina.
    float mDt = 0.3f; // sekunde
    sf::Time next = sf::Time::Zero;
    sf::Time next1 = sf::Time::Zero;
    // Signalizacija da je igra završena
    bool mGameOver = false;
    // Broj linija obrisanih od jednom (0,1,2,3 ili 4)
    int mNoLinesCompleted = 0;
    int mNovi = 0;

    // Generiranje slučajnog elementa.
    std::random_device r;
    std::default_random_engine mRNE;            // mRNE.seed(r());
    std::uniform_int_distribution<> mUniformDist = std::uniform_int_distribution<>(0, 6);;

    // Komad koji pada
    Tetrimino mPiece;
    // Iscrtavanje
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const override;

    // Provjerava da li se komad može smjestiti na ploču. .......vidi se koji komad iz mPiece
    bool checkSpace();
    // Smjesti komad na ploču. Pretpostavlja se da je checkSpace(piece) vratio true.
    void placePiece();
    // Ukloni komad sa ploče.
    void removePiece();
    // Pomakni komad ako je moguće. Vrati true ako je pomak izvršen, inače false.
    bool movePiece(int x, int y);
    // Rotiraj komad. Vrati true ako je rotacija izvršena, inače false.
    bool rotatePiece();
    // Da li je linija y prazna ili nije ?
    bool isLineFull(int y) const;
    // Obriši kompletne linije i vrati broj obrisanih linija -->povratna vrijednost ide u mNoLinesCompleted;
    int clearLines();
    // Eventualno vaše dodatne metode dolaze ovdje.
    // Privatne metode koje ne trebate možete slobodno ukloniti.
    void crtaj();

};

#endif // BOARD_H
