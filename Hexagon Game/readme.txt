Osniel Quintana        U49838358

This C++ program solves the hexagon game. To do this, the program creates the best possible move everytime it is its
turn to play using a minimax algorithm with alpha beta prunning.
The main class is located in Main.cpp. 
To run the program there are two options:
	1- Compile using UNIX enviroment:	
		Type in command line: "g++ -std=c++11 Main.cpp" Note: CIRCE @ USF does not support c++11, use a virtual machine or 
dual boot for this.
	2- Use Visual Studio or some other IDE:
		Import file Main.cpp, CyclicLinkedList.h, TreeNode.h, SLinkedList.h, Node.h, LinkedTree.h, DirGraph.h, Edge.h, Vertex.h, HTable.h
		Build and run program

Note: I used Visual Studio to build my program and tested it in a UNIX Virtual Machine that supports C++11.

My program is based in multiple classes that together run a minimax algorithm which creates a search tree on runtime. The class Node.h defines a node of the SLinkedList class,
and from the CyclicLinkedList.h. The TreeNode class defines the node of the LinkedTree, the Vertex.h and Edge.h define the vertices and edges of the directed graph DirGraph.h respectively.
The HTable was used for fast retrieval and checking of edges in the graph, the CyclicLinkedList is used to generate children and to create the endgames. The program checks the terminal
nodes with a predefined list of endgames.

Game ask the user to select which player to play, user player always draw solid lines, computer player always draw dashed lines. At every play, the current state is showed as the edges
that have been drawn so far and the type they have. Program does not do input validation for player selection input, please be careful here. 

The algorithm right now is taking too long to take the first decisions in the game. If the TA whishes to check the algorithm then by uncommenting lines 25-34 in Main.cpp the game starts 
at a middle state position and from there the algorithm runs flawlessly and always win. I tested the algorithm using 4 and 5 nodes instead of 6 and it also wins even if it runs from start 
position. Alpha beta prunning is also working, this can be demonstrated by uncommenting lines in 165 and 182 LinkedTree.h. This causes the output to show how the children are being 
generated and how the tree gets cut off from time to time.

NOTE: Dr. Korzhova told me that this assigment is supposed to run slow and that it will be graded on the implementation of the algorithm, not in its execution.