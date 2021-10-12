// STUDENT CODE
// San Diego State University
// CS210/CS496: Data Structures
//
// File: BinarySearchTree.h
//
// A concrete implementation of a basic binary search tree. This structure is
// useful only for education and illustration of the BAD things about growth.
//
// Additional Reading:
// https://en.wikipedia.org/wiki/Binary_search_tree


#ifndef PROG2_BINARYSEARCHTREE_H
#define PROG2_BINARYSEARCHTREE_H

#include <memory>
#include <iomanip>

#include "Map.h"

namespace sdsu {
    template<typename KEY, typename VALUE>
    class BinarySearchTree : public Map<KEY,VALUE> {

        int curSize;
        // The BST links together BSTNode objects. The outside world never
        // needs to use these, but this data structure will use them to build
        // the search tree.
        struct BSTNode {

            // The BST structures itself around the KEY's ranking. The key is
            // so important, it must be unique in the BST.
            KEY key;


            // The value will almost certainly not be a void*, but this allows
            // us to store ANYTHING, for we can cast a void* into something else
            // void* is an address to anything . . . not nothingness. Values
            // in a map may be repeated, and values don't appear in a Set.
            VALUE value;

            std::shared_ptr<BSTNode> childL;
            std::shared_ptr<BSTNode> childR;

            BSTNode(KEY item) : key(item), childL(nullptr), childR(nullptr){};

            std::pair<std::shared_ptr<KEY*>&, int> keyset(std::shared_ptr<KEY*> &arr){
                std::pair<std::shared_ptr<KEY*>&,int> toRet(arr);
            };

            // This is something like Java's toString method.
            // This is an IN-ORDER traversal.
            friend std::ostream& operator<<(std::ostream& os,  BSTNode const &node) {
                if( node.childL != nullptr ) os << *node.childL;
                os << std::setw(8) << node.key << " ";
                if( node.childR != nullptr ) os << *node.childR;
                return os;
            }
        };

        std::shared_ptr<BSTNode> root;

        // this function may help when you write other functions. Sometimes you
        // wnat to literally work with the node holding the key, and not
        // just the keys and values themselves. Your design will decide if you
        // need something like this or not.
        std::shared_ptr<BSTNode> getNode(const KEY &key, std::shared_ptr<BSTNode> currentNode) const{
            if (currentNode->key == key)
                return currentNode;
            else if(key < currentNode->key) return getNode(key, currentNode->childL);
            else if(key > currentNode->key) return getNode(key,currentNode->childR);
            else return nullptr;

        }
        //key of child node & node to start search
        std::shared_ptr<BSTNode> getParentNode(const KEY &key, std::shared_ptr<BSTNode> currentNode){

            if(currentNode->childL != nullptr){
                if (currentNode->childL->key == key)
                    return currentNode;
            }
            else if(currentNode->childR != nullptr){
                if (currentNode->childR->key == key)
                    return currentNode;
            }

            if(key < currentNode->key) return getParentNode(key, currentNode->childL);
            else if(key > currentNode->key) return getParentNode(key,currentNode->childR);
            else return nullptr;
        }

        // This is a PRIVATE version of teh insert function that no one on
        // the outside can call. I find it useful for something like
        // the public version to kick things off, and this does the real
        // work.
        bool insert(const KEY &key, std::shared_ptr<BSTNode> &start)  {
            if (start == nullptr){
                start = std::make_shared<BSTNode>(key);
                curSize++;
            }
            else if(key < start->key){
                return insert(key, start->childL);
            }
            else if(key > start->key){
                return insert(key,start->childR);
            }
            return true;
        }

        VALUE *insert(const KEY &key, const VALUE &val, std::shared_ptr<BSTNode> &start)  {
            VALUE *returnVal = nullptr;
            if (start == nullptr){
                start = std::make_shared<BSTNode>(key);
                start->value = val;
                curSize++;
            }
            else if(start->key == key){
                if (start->value == val){

                    returnVal = &start->value;
                    start->value = val;
                    return returnVal;
                }
            }
            else if(key < start->key){
                return insert(key, val, start->childL);
            }
            else if(key > start->key){
                return insert(key, val, start->childR);
            }
            return returnVal;
        }

        VALUE &get(const KEY &key, std::shared_ptr<BSTNode> &start){

            if (start->key == key) return start->value;
            else if(key < start->key) get(key, start->childL);
            else if(key > start->key) get(key,start->childR);

        }
        //need to receive left child of sub tree root
        std::shared_ptr<BSTNode> getPredecessor(std::shared_ptr<BSTNode> currentNode){

            if(currentNode->childR == nullptr)
                return currentNode->childR;
            else
                return (currentNode->childR);
        }

        bool remove(std::shared_ptr<BSTNode> parent, std::shared_ptr<BSTNode> nodeBeingRemoved, bool isLeft){


            //node is a leaf, no children
            if(nodeBeingRemoved->childL == nullptr && nodeBeingRemoved->childR == nullptr){
                if(isLeft)
                    parent->childL= nullptr;
                else
                    parent->childR = nullptr;
            }
            //node has one child
            else if(nodeBeingRemoved->childL == nullptr ^ nodeBeingRemoved->childR == nullptr){
                if(isLeft){
                    if(nodeBeingRemoved->childL == nullptr)
                        parent->childL = nodeBeingRemoved->childR;
                    else
                        parent->childL = nodeBeingRemoved->childL;
                }
                else{
                    if(nodeBeingRemoved->childL == nullptr)
                        parent->childR = nodeBeingRemoved->childR;
                    else
                        parent->childR = nodeBeingRemoved->childL;
                }
            }
            //node has two children
            else{
                std::shared_ptr<BSTNode> predecessor = getPredecessor(nodeBeingRemoved);
                std::shared_ptr<BSTNode> predecessorParent = getParentNode(predecessor->key, nodeBeingRemoved->childL);
                if(isLeft) {
                    nodeBeingRemoved->key = predecessor->key;
                    nodeBeingRemoved->value = predecessor->value;
                    remove(predecessorParent, predecessor,true);
                }
                else{
                    nodeBeingRemoved->key = predecessor->key;
                    nodeBeingRemoved->value = predecessor->value;
                    remove(predecessorParent, predecessor,false);
                }
            }
            return true;
        };

        bool removeRoot() {
            //root is leaf
            if (root->childL == nullptr && root->childR == nullptr) {
                root = nullptr;
                return true;
            }
            //one child
            if (root->childL == nullptr ^ root->childR == nullptr){
                if (root->childL == nullptr) root = root->childR;
                else root = root->childL;
                return true;
             }
            //two children
            return remove(nullptr,root,false);

        }
    public:
        BinarySearchTree():curSize(0) {

        }

        BinarySearchTree(const BinarySearchTree<KEY,VALUE> &other) {
            curSize = other.curSize;
        }

        ~BinarySearchTree() override {

        }

        bool contains(const KEY &key) const override {
            std::shared_ptr<BSTNode> nodeFound =  getNode(key, root);

            if(nodeFound == nullptr)
                return false;
            else
                return true;
        }

        void clear() override {
            root = nullptr;
            curSize = 0;
        }

        virtual VALUE &get(const KEY &key) override {

            VALUE &val = get(key, root);
            return val;
        }

        bool insert(const KEY &key) override {

            return insert(key, root);
        }

        VALUE insert(const KEY &key, const VALUE &val) override {
            VALUE *nullPoint = nullptr;
            VALUE *valReceived = insert(key, val, root);
            if(valReceived == nullptr)
                return *nullPoint;
            else
                return *valReceived;
        }

        std::pair<std::shared_ptr<KEY*>,int> keys() override{
            KEY* raw = new KEY[size()];
            std::shared_ptr<KEY*> arr = std::make_shared<KEY*>(raw);

            // Todo: Extra Credit Students fill up the arr[] with the keys in-order

            std::pair<std::shared_ptr<KEY*>,int> toRet(arr,size());
            return toRet;
        };

        virtual std::pair<std::shared_ptr<VALUE*>,int> values() override {
            VALUE* raw = new VALUE[size()];
            std::shared_ptr<VALUE*> arr = std::make_shared<VALUE*>(raw);

            // Todo: Students fill up the arr[] with the values in-order
            // Todo: with respect to their keys (not each other). Extra Credit

            std::pair<std::shared_ptr<VALUE*>,int> vals(arr,size());
            return vals;
        };

        bool remove(const KEY &key) override {

            //remove root node
            if(root->key == key) {
                curSize--;
                return removeRoot();

            }
            std::shared_ptr<BSTNode> nodeToRemove;
            std::shared_ptr<BSTNode> parentOfNodeToRemove;
            parentOfNodeToRemove = getParentNode(key, root);


            //node to be deleted is the left child of its parent
            if(parentOfNodeToRemove->childL->key == key) {
                nodeToRemove = parentOfNodeToRemove->childL;
                remove(parentOfNodeToRemove,nodeToRemove, true);
            }
            else {
                nodeToRemove = parentOfNodeToRemove->childR;
                remove(parentOfNodeToRemove,nodeToRemove, false);
            }

            //remove(const KEY &key, BSTNode *parent, BSTNode *current);
            curSize--;
            return true;
        }

        int size() const override {
            return curSize;
        }

        VALUE& operator[](std::size_t idx){
            return get(idx);
        }

        friend std::ostream& operator<<(std::ostream& os, sdsu::BinarySearchTree<KEY,VALUE> const &bst) {
            if( bst.root != nullptr ) return os << "[" << (*bst.root) << "]";
            return os;
        }
    };
}
#endif //PROG2_BINARYSEARCHTREE_H
