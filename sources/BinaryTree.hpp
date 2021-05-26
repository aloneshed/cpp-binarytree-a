#pragma once
#include <iostream>
#include <list>
#include <map>

#include "iterator_type.hpp"

namespace ariel
{

    template <typename T>
    class BinaryTree
    {
        using iterator = typename std::list<T>::iterator;

        struct Node
        {
            T key;
            Node *left_child, *right_child;
            Node(T k) : key(k), left_child(nullptr), right_child(nullptr) {}
        };

        Node *root;
        std::map<T, Node *> nodes;
        std::list<T> order;
        void fill(iterator_type type, Node *node);
        iterator iterator_root(iterator_type type)
        {
            order.clear();
            fill(type, root);
            return order.begin();
        }

    public:
        BinaryTree &add_root(T r);
        BinaryTree &add_left(T father, T left_child);
        BinaryTree &add_right(T father, T right_child);
        iterator begin_inorder() { return iterator_root(INORDER); }
        iterator end_inorder() { return order.end(); }
        iterator begin_preorder() { return iterator_root(PREORDER); }
        iterator end_preorder() { return order.end(); }
        iterator begin_postorder() { return iterator_root(POSTORDER); }
        iterator end_postorder() { return order.end(); }
        iterator begin() { return iterator_root(INORDER); }
        iterator end() { return order.end(); }
        template <typename F>
        friend std::ostream &operator<<(std::ostream &os, BinaryTree<F> const &bt);
    };

    template <typename T>
    std::ostream &operator<<(std::ostream &os, BinaryTree<T> const &bt)
    {
        return os << "Binary Tree";
    }

    template <typename T>
    void BinaryTree<T>::fill(iterator_type type, Node *node)
    {
        if (!node)
        {
            return;
        }
        if (type == PREORDER)
        {
            order.push_back(node->key);
        }
        fill(type, node->left_child);
        if (type == INORDER)
        {
            order.push_back(node->key);
        }
        fill(type, node->right_child);
        if (type == POSTORDER)
        {
            order.push_back(node->key);
        }
    }

    template<typename T> BinaryTree<T>& BinaryTree<T>::add_root(T r) {
        root = nodes[r] = new Node(r);
        return *this;
    }


    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_right(T father, T right_child)
    {
        if (!nodes.contains(father))
        {
            throw std::invalid_argument{"father is not exist"};
        }
        if (nodes.at(father)->right_child == nullptr)
        {
            nodes.at(father)->right_child = nodes[right_child] = new Node(right_child);
        }
        else
        {
            nodes.at(father)->right_child->key = right_child;
        }
        return *this;
    }

    template <typename T>
    BinaryTree<T> &BinaryTree<T>::add_left(T father, T left_child)
    {
        if (!nodes.contains(father))
        {
            throw std::invalid_argument{"father is not exist"};
        }
        if (nodes.at(father)->left_child == nullptr)
        {
            nodes.at(father)->left_child = nodes[left_child] = new Node(left_child);
        }
        else
        {
            nodes.at(father)->left_child->key = left_child;
        }
        return *this;
    }
}
