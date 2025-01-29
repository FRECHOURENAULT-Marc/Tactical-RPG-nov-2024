#include "Character.h"
#include "Spectre.h"
#include "Golem.h"
#include "Faucheur.h"
#include "Grid.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

//AMELIORER ECRAN FIN (les 2) ET METTRE COULEURS ?

// https://miro.com/app/board/uXjVLKapMjU=/?share_link_id=295133431418 // MIRO
// https://docs.google.com/presentation/d/1MYPokjs6bPR_BENMlzY2HSbLMGbfrBbq6KR5mGMQlek/edit?usp=sharing // DIAPO

void GiveInfos()    //Infos pour comprendre le jeu
{
    cout << "#---------INFORMATIONS IMPORTANTES---------#" << endl;
    cout << "|*    Bienvenue dans ce jeu incroyable    *|" << endl;
    cout << "|*   Tu vas rencontrer des monstres ici   *|" << endl;
    cout << "|*   Chacun avec des attributs propres:   *|" << endl;
    cout << "|*            [* S: Spectre *]            *|" << endl;
    cout << "|*   ATK faible et fuit en combat         *|" << endl;
    cout << "|*   Loot : Regen totale HP et HPMax +1   *|" << endl;
    cout << "|*             [* G: Golem *]             *|" << endl;
    cout << "|*   ATK/HP RAS, peut bloquer tes coups   *|" << endl;
    cout << "|*   Loot : Augmente ATK +1               *|" << endl;
    cout << "|*           [* F : Faucheur *]           *|" << endl;
    cout << "|*   ATK elevee et peut se regen total    *|" << endl;
    cout << "|*   Loot : Victoire une fois tous KO     *|" << endl;
    cout << "|*            [* @ : Joueur *]            *|" << endl;
    cout << "|*   Tu n'as pas de stats speciales...    *|" << endl;
    cout << "|*                   --                   *|" << endl;
    cout << "|*   En esperant te voir triompher...     *|" << endl;
    cout << "#------------------------------------------#" << endl;
    cout << "\033[2mEntrer pour skip...\033[22m" << endl;
    char tmp = _getch();
}

void DisplayGame(Grid* pGrid, Character* player)    //Affiche le dongeon et les stats du joueur
{
    pGrid->ShowGrid();
    player->ShowStats();
}

void Fight(Character* player, Character* ennemi, Grid* pGrid)   //Combat entre joueur et 1 monstre (capacités comprises)
{
    cout << "Debut du combat" << endl;
    while (true)
    {
        DisplayGame(pGrid, player);
        ennemi->ShowStats();
        ennemi->TakeDamage(player->ReturnATK());
        if (ennemi->IsDead() == true)
        {
            player->KillReward(pGrid, pGrid->GetType(ennemi->ReturnCharacterLine(), ennemi->ReturnCharacterColumn()));
            ennemi->IsDeadAndResetCase(pGrid);
            break;
        }
        player->TakeDamage(ennemi->ReturnATK());
        if (player->IsDeadAndResetCase(pGrid) == true)
            break;
        cout << "Entrer pour continuer." << endl;
        char tmp = _getch();
        system("cls");
        if (pGrid->GetType(ennemi->ReturnCharacterLine(), ennemi->ReturnCharacterColumn()) == 2 && ennemi->IsDead() == false && ennemi->GoAway(pGrid, player) == true)  //Fuite du spectre
        {
            DisplayGame(pGrid, player);
            cout << "Le Spectre a fuit !" << endl;
            break;
        }
    }
    cout << "Fin du combat ! Entrer pour continuer." << endl;
    char tmp = _getch();
}
void main() //GameManager "temporaire" ...
{
    srand(time(NULL));  //Init seed random
    Grid grid;  //Init Dongeon
    Character p1 (6, 2, 8, 2);      //HP ATK LINE COL SPE //HP = 5
    p1.SetCharacterPos(&grid);

    Golem* pg[3];   //Init Golem
    pg[0] = new Golem(5, 2, 5, 5, 3);
    pg[0]->SetCharacterPos(&grid);
    pg[1] = new Golem(5, 2, 2, 0, 3);
    pg[1]->SetCharacterPos(&grid);
    pg[2] = new Golem(5, 2, 10, 5, 3);
    pg[2]->SetCharacterPos(&grid);

    Spectre* ps[2];     //Init Spectre
    ps[0] = new Spectre(5, 2, 6, 3);
    ps[0]->SetCharacterPos(&grid);
    ps[1] = new Spectre(5, 2, 8, 0);
    ps[1]->SetCharacterPos(&grid);

    Faucheur* pf[2];    //Init Faucheur
    pf[0] = new Faucheur(5, 2, 3, 10, 3);
    pf[0]->SetCharacterPos(&grid);
    pf[1] = new Faucheur(5, 2, 0, 8, 3);
    pf[1]->SetCharacterPos(&grid);

    GiveInfos();

    DisplayGame(&grid, &p1);

    bool defeat = true;
    while (true)
    {
        p1.Movement(&grid);
        DisplayGame(&grid, &p1);

        int state = 1;
        while(state != 0)
        {
            state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn()); //Renvoie le type du monstre (ou pas si rien) pour lancer le combat approprié 
            if (state == 1)
            {
                if (pg[0]->IsDead() == false && grid.IsPlayerAround(pg[0]->ReturnCharacterLine(), pg[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[0], &grid);
                else if (pg[1]->IsDead() == false && grid.IsPlayerAround(pg[1]->ReturnCharacterLine(), pg[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[1], &grid);
                else if (pg[2]->IsDead() == false && grid.IsPlayerAround(pg[2]->ReturnCharacterLine(), pg[2]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[2], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            else if (state == 2)
            {
                if (ps[0]->IsDead() == false && grid.IsPlayerAround(ps[0]->ReturnCharacterLine(), ps[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, ps[0], &grid);
                else if (ps[1]->IsDead() == false && grid.IsPlayerAround(ps[1]->ReturnCharacterLine(), ps[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, ps[1], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            else if (state == 3)
            {
                if (pf[0]->IsDead() == false && grid.IsPlayerAround(pf[0]->ReturnCharacterLine(), pf[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pf[0], &grid);
                else if (pf[1]->IsDead() == false && grid.IsPlayerAround(pf[1]->ReturnCharacterLine(), pf[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pf[1], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            if (p1.IsDead() == true)    //Vérif si player meurt pour interrompre
            {
                state = 0;
                break;
            }
            DisplayGame(&grid, &p1);
        }

        if (grid.IsVictory() == true)
        {
            defeat = false;
            break;
        }
        if (p1.IsDead() == true)
        {
            break;
        }

        for (int i = 0; i < 2; i++)     //Spectre fuient
        {
            if (ps[i]->IsDead() == false)
                ps[i]->GoAway(&grid, &p1);
        }
        for (int i = 0; i < 2; i++)
        {
            if (pf[i]->IsDead() == false)
                pf[i]->GoToYou(&grid, &p1);
        }
        DisplayGame(&grid, &p1);    //Faucheurs viennent

        state = 1;
        while (state != 0)  //Actualisation à cause des mouvements monstres
        {
            state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            if (state == 1)
            {
                if (pg[0]->IsDead() == false && grid.IsPlayerAround(pg[0]->ReturnCharacterLine(), pg[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[0], &grid);
                else if (pg[1]->IsDead() == false && grid.IsPlayerAround(pg[1]->ReturnCharacterLine(), pg[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[1], &grid);
                else if (pg[2]->IsDead() == false && grid.IsPlayerAround(pg[2]->ReturnCharacterLine(), pg[2]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pg[2], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            else if (state == 2)
            {
                if (ps[0]->IsDead() == false && grid.IsPlayerAround(ps[0]->ReturnCharacterLine(), ps[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, ps[0], &grid);
                else if (ps[1]->IsDead() == false && grid.IsPlayerAround(ps[1]->ReturnCharacterLine(), ps[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, ps[1], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            else if (state == 3)
            {
                if (pf[0]->IsDead() == false && grid.IsPlayerAround(pf[0]->ReturnCharacterLine(), pf[0]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pf[0], &grid);
                else if (pf[1]->IsDead() == false && grid.IsPlayerAround(pf[1]->ReturnCharacterLine(), pf[1]->ReturnCharacterColumn()) == -1)
                    Fight(&p1, pf[1], &grid);
                state = grid.IsMonsterAround(p1.ReturnCharacterLine(), p1.ReturnCharacterColumn());
            }
            if (p1.IsDead() == true)
            {
                state = 0;
                break;
            }
            DisplayGame(&grid, &p1);
        }
        if (grid.IsVictory() == true)
        {
            defeat = false;
            break;
        }
        if (p1.IsDead() == true)
        {
            break;
        }
    }
    if (defeat == true) //Relance si défaite
    {
        main();
    }
}

