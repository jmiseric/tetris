#include <iostream>
#include "board.h"


Board::Board()
{
    for(int x=0; x<mRows; ++x)
        for(int y=0; y<mCols; ++y)
        {
            mGridContent[x][y] = EMPTY;
        }


    sf::Color grid_color(60,60,60);
    mGrid = sf::VertexArray(sf::Lines,(mRows+1+mCols+1)*2);
    for(int i=0;i<=mRows;++i)
    {
        mGrid[i*2] = sf::Vertex(sf::Vector2f(mLeftMargin+ 0,mTopMargin + i*mDy));
        mGrid[i*2+1] = sf::Vertex(sf::Vector2f(mLeftMargin + mCols*mDx,mTopMargin + i*mDy));

        mGrid[i*2].color = grid_color;
        mGrid[i*2+1].color = grid_color;
    }
    for(int i=0;i<=mCols;++i)
    {
        mGrid[(mRows+1)*2 + i*2] = sf::Vertex(sf::Vector2f(mLeftMargin + i*mDx, mTopMargin + 0));
        mGrid[(mRows+1)*2 + i*2+1] = sf::Vertex(sf::Vector2f(mLeftMargin + i*mDx,mTopMargin + mRows*mDy));

        mGrid[(mRows+1)*2 + i*2].color = grid_color;
        mGrid[(mRows+1)*2 + i*2+1].color = grid_color;
    }
}

int Board::update(const sf::Time &dt, int left, int right, int drop, int down, int rotate)
{
    mNoLinesCompleted = 0;

    if(isGameOver()) return -1;
    next += dt;
    next1 += dt;
    sf::Time t = sf::seconds(mDt);
    sf::Time t1 = sf::seconds(0.2f);
    while(next1 > t1) {
        next1 -= t1;
        if(mNovi == 0) { spawnPiece(); mNovi = 1; }
        if(left) movePiece(0,-1);
        if(right) movePiece(0,1);
        if(drop) {
            while(1)
            {
                bool p = movePiece(1,0);
                if (p == false) { mNovi = 0; clearNoLinesCompleted(); break; }
            }
        }
        if(down) if( !movePiece(1,0) ) { mNovi = 0; clearNoLinesCompleted(); }
        if(rotate) rotatePiece();
    }

    while(next > t) {
        next -= t;
        bool d = movePiece(1,0);
        if (d == false) { mNovi = 0; clearNoLinesCompleted(); }
    }

    return  getNoLinesCompleted();
}

void Board::spawnPiece()
{
    mRNE.seed(r());
    mPiece.mType = (Tetrimino::Types)mUniformDist(mRNE);
    mPiece.mRotacija = 0;
    mPiece.mXposition = -1;
    mPiece.mYposition = 3;
    if(checkSpace() == true) placePiece();
    else mGameOver = true;
}

bool Board::isGameOver() const
{
    return mGameOver;
}

int Board::getNoLinesCompleted() const
{
    return mNoLinesCompleted;
}

void Board::clearNoLinesCompleted()
{
    mNoLinesCompleted = clearLines();
    return;
}

void Board::emptyGridContent()
{
    for(int i = 0; i < 20; ++i)
        for(int j = 0; j < 10; ++j)
            mGridContent[i][j] = EMPTY;
}

void Board::setNoGameOver()
{
    mNovi = 0;
    mGameOver = false;
}

void Board::setSpeed(float x)
{
    mDt = 1.f/x;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    for(int y=0; y<mRows; ++y)
        for(int x=0; x<mCols; ++x)
        {
            if(mGridContent[y][x] != EMPTY)
            {
                sf::RectangleShape rectangle(sf::Vector2f(mDx,mDy));
                rectangle.setFillColor(Tetrimino::mColors[mGridContent[y][x]]);
                rectangle.setPosition(mLeftMargin + x*mDx,mTopMargin + y*mDy);
                target.draw(rectangle,states);
            }
        }
    target.draw(mGrid, states);
}

bool Board::checkSpace()
{
    int br = (int)mPiece.mType;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if(mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 && mGridContent[mPiece.mXposition+i][mPiece.mYposition+j] != EMPTY) return false;
        }
    return true;
}

void Board::placePiece()
{
    int br = (int)mPiece.mType;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if( mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 ) mGridContent[i-1][3+j] = br;
        }
}

void Board::removePiece()
{
    int br = (int)mPiece.mType;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if(mGridContent[mPiece.mXposition+i][mPiece.mYposition+j] == br && mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 )
                mGridContent[mPiece.mXposition+i][mPiece.mYposition+j] = EMPTY;
        }
}

bool Board::movePiece(int x, int y)
{
    removePiece();
    int br = (int)mPiece.mType;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if( (mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 && mGridContent[mPiece.mXposition+x+i][mPiece.mYposition+y+j] != EMPTY) ||
                    (mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 && (mPiece.mXposition+x+i < 0 || mPiece.mYposition+y+j < 0 || mPiece.mXposition+x+i > 19 || mPiece.mYposition+y+j > 9) ) )
            {
                crtaj();
                return false;
            }
        }
    mPiece.mXposition += x;
    mPiece.mYposition += y;
    crtaj();
    return true;
}

bool Board::rotatePiece()
{
    removePiece();
    int br = (int)mPiece.mType;
    mPiece.mRotacija = (mPiece.mRotacija+1)%4;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if((mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 && mGridContent[mPiece.mXposition+i][mPiece.mYposition+j] != EMPTY) ||
                    (mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 && (mPiece.mXposition+i < 0 || mPiece.mYposition+j < 0 || mPiece.mXposition+i > 19 || mPiece.mYposition+j > 9)))
            {
                mPiece.mRotacija = (mPiece.mRotacija-1)%4;
                crtaj();
                return false;
            }
        }
    crtaj();
    return true;
}

bool Board::isLineFull(int y) const
{
    for(int i = 0; i < mCols; ++i)
        if(mGridContent[y][i] == EMPTY) return false;
    return true;
}

int Board::clearLines()
{
    int brojac = 0;
    for(int i = mRows-1; i>=0; i--)
        if(isLineFull(i)){
            for(int j = i; j >0; j--)
            {
                for(int k = 0; k < mCols; ++k) mGridContent[j][k] = mGridContent[j-1][k];
            }
            //for(int k = 0; k< mCols; ++k) mGridContent[0][k] = EMPTY;
            i++;
            brojac++;
        }
    return brojac;
}

void Board::crtaj()
{
    int br = (int)mPiece.mType;
    for(int i = 0; i < 4; ++i)
        for(int j = 0; j < 4; ++j)
        {
            if( mPiece.mDijelovi[br][mPiece.mRotacija][i][j] != 0 ) mGridContent[mPiece.mXposition+i][mPiece.mYposition+j] = br;
        }
}
