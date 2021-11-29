/***************************************************************************/
/*                                                                         */
/* 234218 Data DSs 1, Winter 2021-2022                                     */
/* Homework : Wet 1                                                        */
/*                                                                         */
/***************************************************************************/

/***************************************************************************/
/*                                                                         */
/* File Name : main1.cpp                                                   */
/*                                                                         */
/* Holds the "int main()" function and the parser of the shell's           */
/* command line.                                                           */
/***************************************************************************/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library1.h"
#include <iostream>
#include "avl.h"
#include "squidsystem.h"

using namespace std;


int main(int argc, const char **argv) {
    Avltree<int, int> tree;

    std::shared_ptr<Node<int, int>> node_12 = make_shared<Node<int, int>>(12, 12);
    std::shared_ptr<Node<int, int>> node_8 = make_shared<Node<int, int>>(8, 8);
    std::shared_ptr<Node<int, int>> node_15 = make_shared<Node<int, int>>(15, 15);
    std::shared_ptr<Node<int, int>> node_6 = make_shared<Node<int, int>>(6, 6);
    std::shared_ptr<Node<int, int>> node_10 = make_shared<Node<int, int>>(10, 10);
    std::shared_ptr<Node<int, int>> node_14 = make_shared<Node<int, int>>(14, 14);
    std::shared_ptr<Node<int, int>> node_24 = make_shared<Node<int, int>>(24, 24);
    std::shared_ptr<Node<int, int>> node_4 = make_shared<Node<int, int>>(4, 4);
    std::shared_ptr<Node<int, int>> node_11 = make_shared<Node<int, int>>(11, 11);
    std::shared_ptr<Node<int, int>> node_13 = make_shared<Node<int, int>>(13, 13);
    std::shared_ptr<Node<int, int>> node_20 = make_shared<Node<int, int>>(20, 20);
    std::shared_ptr<Node<int, int>> node_29 = make_shared<Node<int, int>>(29, 29);
    std::shared_ptr<Node<int, int>> node_17 = make_shared<Node<int, int>>(17, 17);
    std::shared_ptr<Node<int, int>> node_9 = make_shared<Node<int, int>>(9, 9);
    std::shared_ptr<Node<int, int>> node_7 = make_shared<Node<int, int>>(7, 7);
    std::shared_ptr<Node<int, int>> node_3 = make_shared<Node<int, int>>(3, 3);
    std::shared_ptr<Node<int, int>> node_1 = make_shared<Node<int, int>>(1, 1);
    std::shared_ptr<Node<int, int>> node_2 = make_shared<Node<int, int>>(2, 2);
    std::shared_ptr<Node<int, int>> node_5 = make_shared<Node<int, int>>(5, 5);

/*
    Node<int, int> node_8(8,8);
    Node<int, int> node_15(15,15);
    Node<int, int> node_6(6,6);
    Node<int, int> node_10(10,10);
    Node<int, int> node_14(14,14);
    Node<int, int> node_24(24, 24);
    Node<int, int> node_4(4,4);
    Node<int, int> node_11(11,11);
    Node<int, int> node_13(13,13);
    Node<int, int> node_20(20,20);
    Node<int, int> node_29(29,29);
    Node<int, int> node_19(19,19);
    Node<int, int> node_18(18,18);
*/
//testing rr roll
/*
    tree.insert(node_12);
    tree.insert(node_8);
    tree.insert(node_15);
    tree.insert(node_6);
    tree.insert(node_10);
    tree.insert(node_14);
    tree.insert(node_24);
    tree.insert(node_4);
    tree.insert(node_11);
    tree.insert(node_13);
    tree.insert(node_20);
    tree.insert(node_29);
    tree.insert(node_30);
    tree.insert(node_31);
    //testing left roll
    */
/*
    tree.insert(node_12);
    tree.insert(node_8);
    tree.insert(node_15);
    tree.insert(node_6);
    tree.insert(node_10);
    tree.insert(node_14);
    tree.insert(node_24);
    tree.insert(node_4);
    tree.insert(node_11);
    tree.insert(node_13);
    tree.insert(node_20);
    tree.insert(node_29);
    tree.insert(node_19);
    tree.insert(node_18);
    //testing left right roll
    */
/*
    tree.insert(node_15);
    tree.insert(node_10);
    tree.insert(node_20);
    tree.insert(node_19);
    tree.insert(node_24);
    tree.insert(node_6);
    tree.insert(node_13);
    tree.insert(node_12);
    tree.insert(node_14);
    tree.insert(node_4);
    tree.insert(node_8);
    tree.insert(node_11);
*/
//testing rl
    tree.insert(node_5);
    tree.insert(node_2);
    tree.insert(node_8);
    tree.insert(node_1);
    tree.insert(node_4);
    tree.insert(node_10);
    tree.insert(node_6);
    tree.insert(node_3);
    tree.insert(node_7);
    tree.insert(node_9);
    tree.insert(node_12);
    tree.insert(node_11);
/*
    int arr[12];
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i = 0; i < 12; i++) {
        cout << arr[i] << endl;
    }
    tree.remove(node_1);
    tree.inorder(tree.getRoot(), arr, 0);
    cout << "second loop" << endl;
    for (int i = 0; i < 11; i++) {
        cout << arr[i] << endl;
    }
    */
    //constructor
    cout << "!!!!" << endl;
    SquidSystem sys = SquidSystem();
    //adds a group
    cout << sys.AddGroup(1) << endl;
    //adds a group
    cout << sys.AddGroup(2) << endl;
    //tries to add the same group again
    cout << sys.AddGroup(1) << endl;
    //tries to add a group with an invalid id
    cout << sys.AddGroup(0) << endl;
    //adds a new player
    cout << sys.AddPlayer(1234, 1, 0) << endl;
    //tries to add the same player to two diffenrent groups
    cout << sys.AddPlayer(1234, 2, 3) << endl;

    sys.AddPlayer(123,1,2);



    sys.ReplaceGroup(1,2);

//    cout<<sys.RemovePlayer(1234)<<endl;

//    sys.ReplaceGroup(1,2);
    cout<<sys.IncreaseLevel(1234, 2);
    cout<<sys.IncreaseLevel(123, 5);
    cout<<sys.IncreaseLevel(12345, 5);
    cout<<sys.IncreaseLevel(1234, 10);

    cout<<"test";
}
