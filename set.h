#pragma once
#include <iostream>

class set {
    struct node {
        node* left;
        node* right;
        int value;
        int size;
        node(int v) {
            value = v;
            left = NULL;
            right = NULL;
        }
    };
    node* first;
    int size;

    void insert_branch(node* q) {
        if(!q)
            return;
        
        --size;
        insert(q->value);
        insert_branch(q->left);
        insert_branch(q->right);
        delete q;
        return;
    }

public:
    set() {
        first = NULL;
        size = 0;
    }

    bool empty() {
        if(first)
            return 0;
        return 1;
    }

    void insert(int a) {
        node* q = new node(a);
        ++size;
        if(empty()) {
            first = q;
            return;
        }

        node* g = first;
        while(1) {
            if(q->value<g->value) {
                if(!g->left) {
                    g->left = q;
                    return;
                }
                g = g->left;
            }
            else {
                if(!g->right) {
                    g->right = q;
                    return;
                }
                g = g->right;
            }
        }
    }

    bool exist(int a) {
        if(empty())
            return 0;
        node* q = first;

        while(1) {
            if(!q)
                return 0;
            if(q->value == a)
                return 1;
            
            if(q->value < a) {
                q = q->right;
            }
            else {
                q = q->left;
            }
        }
    }

    void remove(int a) {
        if(empty())
            return;

        node* q = first;

        if(first->value == a) {
            --size;
            first = first->left;
            insert_branch(first->right);
            delete q;
            return;
        }

        while(1) {
            if(!q)
                return;

            if(q->left && q->left->value == a) {
                --size;
                node* g = q->left;
                q->left = g->left;
                insert_branch(g->right);
                delete g;
                return;
            }

            if(q->right && q->right->value == a) {
                --size;
                node* g = q->right;
                q->right = g->left;
                insert_branch(g->right);
                delete g;
                return;
            }

            if(q->value < a) {
                q = q->right;
            }
            else {
                q = q->left;
            }
        }
    }

    int member_count() {
        return size;
    }
};