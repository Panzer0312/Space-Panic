//the core function to run this game3

#include "GameView.h"
#include "GameModel.h"
#include "GameController.h"


/**
 * Function thats starting the whole game, sets up GameModel, GameView and instantiates the GameController with references to them
 * 
 * \param argc
 * \param argv
 * \return 
 */
int main(int argc, char* argv[])
{
    GameModel gm;
    GameView gv;
    GameController gc(&gm, &gv);
    gc.init();
}
