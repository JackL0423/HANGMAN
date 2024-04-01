#include <stdio.h>
#include <stdlib.h>

#include "./headers/generic_vector.h"
#include "./headers/generic.h"
#include "./headers/avl_tree.h"


struct node {
    Node* left;
    Node* right;
    MY_STRING key;
    GENERIC_VECTOR data;
};

//  Fix init funciton.
TREE avl_tree_init_default(void) {
    Node* pRoot = (Node*)malloc(sizeof(Node));
    if (pRoot == NULL) {
        return NULL;
    }
    pRoot->left = NULL;
    pRoot->right = NULL;

    return (TREE)pRoot;
}

void avl_tree_destroy(TREE* phTree) {
    Node* pRoot = (Node*)*phTree;
    if (pRoot != NULL) {
        avl_tree_node_destroy(pRoot->left);
        avl_tree_node_destroy(pRoot->right);

        free(pRoot);
    }
    phTree = NULL;
}


void avl_tree_node_destroy(Node* root) {
    if (root != NULL) {
        my_string_destroy(root->key);
        generic_vector_destroy(root->data);
        avl_tree_node_destroy(root->left);
        avl_tree_node_destroy(root->right);

        free(root);
    }
}
//  Fix the push function and correct to use the right values.
Status avl_tree_push(TREE hTree, MY_STRING key, MY_STRING item) {
    Node* pRoot = (Node*)hTree;
    int flag;

    if (pRoot == NULL) {
        pRoot = (Node*)malloc(sizeof(Node));
        if (pRoot == NULL) {
            return FAILURE;
        }
        pRoot->left = NULL;
        pRoot->right = NULL;
        pRoot->key = my_string_init_c_string(my_string_c_str(key));

        pRoot->data = generic_vector_init_default((ITEM)my_string_assignment, my_string_destroy);
        generic_vector_push_back(pRoot->data, item);
    }

    //  Need to come up with recursive solution.
    //  Need to also add way for tree to reorginize itself if magnitute >2
    //  Reference heap lecture for how to reorganize tree based on string_compare

   flag = my_string_compare(pRoot->key, key);
    if (flag == 1) {
        avl_tree_push(&(pRoot->right), key, item);
    }
    else if (flag == 0) {
        generic_vector_push_back(pRoot->data, item);
    }
    else if (flag == -1) {
        avl_tree_push(&(pRoot->left), key, item);
    }
    else {
        return FAILURE;
    }
    return SUCCESS;
}

GENERIC_VECTOR avl_tree_get_largest_family(TREE hTree, int print_val) {
    Node* pRoot = (Node*)hTree;
    GENERIC_VECTOR return_vector = NULL;
    GENERIC_VECTOR temp;
    int indx;

    temp = find_max_family(pRoot, print_val);
    return_vector = generic_vector_init_default((ITEM)my_string_assignment, my_string_destroy);

    for (indx=0; indx<generic_vector_get_size(temp); indx++) {
        generic_vector_push_back(return_vector, generic_vector_at(temp, indx));
    }
    return return_vector;
}

GENERIC_VECTOR find_max_family(TREE hTree, int print_val) {
    Node* pRoot = (Node*)hTree;
    GENERIC_VECTOR* temp = NULL;
    //  S L R
    if (pRoot != NULL) {
        if (pRoot->left != NULL) {
            temp = find_max_family(pRoot->left, print_val);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }
        }
        if (pRoot->right != NULL) {
            temp = find_max_family(pRoot->right, print_val);
            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }

            if (temp == NULL || generic_vector_get_size(temp) < generic_vector_get_size(pRoot->data)) {
                temp = pRoot->data;
            }
        }

        if (print_val) {
            my_string_insertion(pRoot->key, stdout);
            printf(" %d\n", generic_vector_get_size(pRoot->data));
        }

        return temp;
    }

    return NULL;
}


//  Make function for balancing factor. 
int avl_find_tree_magnitude(TREE hTree) {
    Node* pRoot = (Node*)hTree;
    if (pRoot != NULL) {
        return 1 + ((avl_find_tree_magnitude(pRoot->left) > avl_find_tree_magnitude(pRoot->right)) ? avl_find_tree_magnitude(pRoot->left):avl_find_tree_magnitude(pRoot->right));
    }

    return 0;
}