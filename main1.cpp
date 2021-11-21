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
#include "avl.cpp"
using namespace std;


int main(int argc, const char**argv) {

    Avltree<int> tree;
    Node<int>* node_1(1,1);
    tree.insert(node_1);

}
