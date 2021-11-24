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
using namespace std;


int main(int argc, const char**argv) {
    Avltree<int, int> tree;

    std::shared_ptr<Node<int, int>> node_12= make_shared<Node<int,int>>(12,12);
    std::shared_ptr<Node<int, int>> node_8= make_shared<Node<int,int>>(8,8);
    std::shared_ptr<Node<int, int>> node_15= make_shared<Node<int,int>>(15,15);
    std::shared_ptr<Node<int, int>> node_6= make_shared<Node<int,int>>(6,6);
    std::shared_ptr<Node<int, int>> node_10= make_shared<Node<int,int>>(10,10);
    std::shared_ptr<Node<int, int>> node_14= make_shared<Node<int,int>>(14,14);
    std::shared_ptr<Node<int, int>> node_24= make_shared<Node<int,int>>(24,24);
    std::shared_ptr<Node<int, int>> node_4= make_shared<Node<int,int>>(4,4);
    std::shared_ptr<Node<int, int>> node_11= make_shared<Node<int,int>>(11,11);
    std::shared_ptr<Node<int, int>> node_13= make_shared<Node<int,int>>(13,13);
    std::shared_ptr<Node<int, int>> node_20= make_shared<Node<int,int>>(20,20);
    std::shared_ptr<Node<int, int>> node_29= make_shared<Node<int,int>>(29,29);
    std::shared_ptr<Node<int, int>> node_19= make_shared<Node<int,int>>(19,19);
    std::shared_ptr<Node<int, int>> node_18= make_shared<Node<int,int>>(18,18);

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
    //testing left roll
    /*tree.insert(&node_12);
    tree.insert(&node_8);
    tree.insert(&node_15);
    tree.insert(&node_6);
    tree.insert(&node_10);
    tree.insert(&node_14);
    tree.insert(&node_24);
    tree.insert(&node_4);
    tree.insert(&node_11);
    tree.insert(&node_13);
    tree.insert(&node_20);
    tree.insert(&node_29);
    tree.insert(&node_19);
    tree.insert(&node_18);
*/
    //testing right roll

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
    int arr[12];
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i=0;i<12;i++)
    {
        cout<<arr[i] <<endl;
    }
    tree.removebinary(node_10);
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i=0;i<11;i++)
    {
        cout<<arr[i] <<endl;
    }




}
