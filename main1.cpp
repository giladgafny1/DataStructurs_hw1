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
    Avltree<int> tree;
    Node<int> node_12(12,12);
    Node<int> node_8(8,8);
    Node<int> node_15(15,15);
    Node<int> node_6(6,6);
    Node<int> node_10(10,10);
    Node<int> node_14(14,14);
    Node<int> node_24(24, 24);
    Node<int> node_4(4,4);
    Node<int> node_11(11,11);
    Node<int> node_13(13,13);
    Node<int> node_20(20,20);
    Node<int> node_29(29,29);
    Node<int> node_19(19,19);
    Node<int> node_18(18,18);
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
    tree.insert(&node_15);
    tree.insert(&node_10);
    tree.insert(&node_20);
    tree.insert(&node_19);
    tree.insert(&node_24);
    tree.insert(&node_6);
    tree.insert(&node_13);
    tree.insert(&node_12);
    tree.insert(&node_14);
    tree.insert(&node_4);
    tree.insert(&node_8);
    tree.insert(&node_11);
    int arr[12];
    tree.inorder(tree.getRoot(), arr, 0);
    for (int i=0;i<12;i++)
    {
        cout<<arr[i] <<endl;
    }




}
