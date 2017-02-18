#include <iostream>
#include "LinkedTree.h"

using namespace std;
int main() {
    string edge, type = "solid";
    int userSelection;
    
    cout << "\t********Welcome to the Hexagon Game********" << endl;
    cout << "Which Player do you want to be?\n1) Player 1\n2) Player 2\n--->> ";  // Player 1 makes first move always
    cin >> userSelection;
    while ( userSelection != 1 && userSelection != 2) {
        cout << "Please enter 1 or 2" << endl;
        cin >> userSelection;
    }

    LinkedTree<int> * game = new LinkedTree<int>(userSelection);
    TreeNode<int> * playing = new TreeNode<int>(game->getRoot()->getData(),"MAX");

    cout << "\nAlright, let's play!" << endl;
    cout << "You are player " << userSelection << " computer is player " << ((userSelection == 1) ? "2\n" : "1\n") << endl;
    cout << "Player " << userSelection << " is solid, " << "Player " << ((userSelection == 1) ? "2" : "1") << " is dashed" << endl;

    // Uncomment these lines to make starting state different, program runs faster at this point
    /********************************************
    playing->getData()->addEdge(1, 4, "solid");
    playing->getData()->addEdge(2, 5, "solid");
    playing->getData()->addEdge(3, 6, "solid");
    playing->getData()->addEdge(3, 4, "solid");
    playing->getData()->addEdge(1, 5, "dashed");
    playing->getData()->addEdge(2, 3, "dashed");
    playing->getData()->addEdge(2, 4, "dashed");
    playing->getData()->addEdge(4, 5, "dashed");
    **********************************************/

    if (userSelection == 2) {
        cout << "Computer makes first play!" << endl;
        playing = game->minimax(playing);
        playing->deleteChildren();                
        playing->getData()->printGraph();
    }

     while (true) {
        playing->updateType("MAX");       
        cout << "\nDraw an edge: ";
        cout << "(Enter \"origin,destination\")\n";
        cout << "-->> ";
        cin >> edge;
        
        // Parse string
        int pos = (int)edge.find(',');
        string sub = edge.substr(0, pos);
        string remain = edge.substr(++pos);
        int first = stoi(sub);
        int second = stoi(remain);

        if (first == second) {
            cout << "Please enter again\n" << endl;
            continue;
        }
       
        if (!playing->getData()->findEdge(edge)) {
            playing->getData()->addEdge(first, second, type);
            playing->getData()->printGraph();
            if (game->isTerminal(playing)) {
                cout << "User looses! ;)" << endl;
                break;
            }
        }
        else {
            cout << "Edge is already there, pick a different one" << endl;
            continue;
        }

        cout << "Computer is playing now.....\n" << endl;
        playing = game->minimax(playing);
        playing->deleteChildren();
        playing->getData()->printGraph();
        if (game->isTerminal(playing)) {
            cout << "Computer looses! :(" << endl;
            break;
        }       
    }

     // To avoid Visual Studio cmd window from closing
    cin.get();
    cin.get();
    return 0;

}