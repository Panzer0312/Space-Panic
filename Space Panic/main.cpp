//the core function to run this game3

#include "GameView.h"
#include "GameModel.h"
#include "GameController.h"

int main(int argc, char* argv[])
{

    GameModel gm;
    GameView gv;
    GameController gc(&gm, &gv);
    gc.init();
     
}
