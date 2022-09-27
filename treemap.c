#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  TreeMap * newTree = (TreeMap *) malloc(sizeof(TreeMap));
  if (newTree == NULL) exit(1);
  newTree->current = NULL;
  newTree->root = NULL;
  newTree->lower_than = lower_than;
  return newTree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
 TreeNode *newNode = createTreeNode(key, value);
  TreeNode *aux;
  searchTreeMap(tree, key);
  aux = tree->current;
  newNode->parent = aux;
  if (tree->lower_than(aux->pair->key, key) == 1) {
    aux->right = newNode;
  }else if (tree->lower_than(key, aux->pair->key) == 1) {
    aux->left = newNode;
  }
  tree->current = newNode;
}

TreeNode * minimum(TreeNode * x){
  if (x == NULL) return NULL;

    while (x->left != NULL) {
        x = x->left;
    }

    return x;

  return NULL;
}


void removeNode(TreeMap * tree, TreeNode* node) {
  TreeNode *parentNode = node->parent;  
  if (node->left == NULL && node->right == NULL) {
    if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
      parentNode->right = NULL; 
    }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
      parentNode->left = NULL; 
    }
    }else if ((node->left != NULL && node->right == NULL) || (node->left == NULL && node->right != NULL)) {
    if (node->left == NULL) {
      if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
        parentNode->right = node->right; 
      }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
        parentNode->left = node->right; 
      }
    node->right->parent = parentNode; 
    }
    if(node->right == NULL) {
      if (tree->lower_than(parentNode->pair->key, node->pair->key) == 1) {
        parentNode->right = node->left; 
      }else if (tree->lower_than(node->pair->key, parentNode->pair->key) == 1) {
        parentNode->left = node->left;
      }
    node->left->parent = parentNode;
    }
    free(node);
  } 
  else {
    TreeNode *min = minimum(node->right);
    node->pair->key = min->pair->key;
    node->pair->value = min->pair->value;
    removeNode(tree, min);
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
  if (tree == NULL || tree->root == NULL) return;

  if (searchTreeMap(tree, key) == NULL) return;
  TreeNode* node = tree->current;
  removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
  if (tree == NULL) return NULL;
  TreeNode *aux = tree->root;

  while (aux != NULL) {
    tree->current = aux;
    if (tree->lower_than(aux->pair->key, key) == 1) {
      aux = aux->right;
    }else if (tree->lower_than(key, aux->pair->key) == 1) {
      aux = aux->left;
    }else break;
  }
  if (is_equal(tree, tree->current->pair->key, key)) return tree->current->pair;
  return NULL;

}


Pair * upperBound(TreeMap * tree, void* key) {
  TreeNode * node;
  tree -> current = tree -> root;
  node = NULL;
  while (tree -> current != NULL){
    if (tree -> lower_than(key,tree -> current -> pair -> key) == 1 ){
      node = tree -> current;
      if(tree -> current -> left == NULL){
        break;
      }tree -> current = tree -> current -> left;
    }else if (is_equal(tree, key,tree -> current -> pair -> key) == 1){
      node = tree -> current;
      break;
    }else
    if(tree -> current -> right == NULL){
        break;
      }tree -> current = tree -> current -> right;
    }
  }
  return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
