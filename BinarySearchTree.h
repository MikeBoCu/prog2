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
        BSTNode &getNode(const KEY &key, std::shared_ptr<BSTNode> currentNode){
            if (currentNode->key == key) return currentNode;
            else if(key < currentNode->key) getNode(key, currentNode->childL);
            else if(key > currentNode->key) getNode(key,currentNode->childR);
        }
        std::shared_ptr<BSTNode> getParentNode(const KEY &key, std::shared_ptr<BSTNode> currentNode){

            if (currentNode->childL->key == key || currentNode->childR->key == key) return currentNode;
            else if(key < currentNode->key) getParentNode(key, currentNode->childL);
            else if(key > currentNode->key) getParentNode(key,currentNode->childR);
            else return nullptr;
        }

        // This is a PRIVATE version of teh insert function that no one on
        // the outside can call. I find it useful for something like
        // the public version to kick things off, and this does the real
        // work.
        bool insert(const KEY &key, std::shared_ptr<BSTNode> &start)  {
            if (start == nullptr){
                start = std::make_shared<BSTNode>(key);
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
        BSTNode &getPredecessor(std::shared_ptr<BSTNode> currentNode){

        }
        bool remove(std::shared_ptr<BSTNode> parent, std::shared_ptr<BSTNode> nodeBeingRemoved, bool isLeft){


            //node is a lead, no children
            if(nodeBeingRemoved->childL == nullptr && nodeBeingRemoved->childR == nullptr){
                if(isLeft)
                    parent->childL= nullptr;
                else
                    parent->childR = nullptr;
            }
            //node has one child
            if(nodeBeingRemoved->childL == nullptr ^ nodeBeingRemoved->childR == nullptr){
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

            }

        };
    public:
        BinarySearchTree():curSize(0) {

        }

        BinarySearchTree(const BinarySearchTree<KEY,VALUE> &other) {
            curSize = other.curSize;
        }

        ~BinarySearchTree() override {

        }

        bool contains(const KEY &key) const override {
            return false;
        }

        void clear() override {

        }

        virtual VALUE &get(const KEY &key) override {

            VALUE &val = get(key, root);
            return val;
        }

        bool insert(const KEY &key) override {
            curSize++;
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
            std::shared_ptr<BSTNode> parentOfNodeToRemove;

            parentOfNodeToRemove = getParentNode(key, root);
            std::shared_ptr<BSTNode> nodeToRemove;
            //TODO: remove root node
            //if(parentOfNodeToRemove == nullptr)

            //node to be deleted is the left child of its parent
            if(parentOfNodeToRemove->childL->key == key) {
                nodeToRemove = parentOfNodeToRemove->childL;
                if(nodeToRemove->childL == nullptr && nodeToRemove->childR == nullptr)
                    remove(parentOfNodeToRemove,nodeToRemove, true);
                //if (nodeToRemove->childR == nullptr)

            }
            else nodeToRemove = parentOfNodeToRemove->childR;

            //remove(const KEY &key, BSTNode *parent, BSTNode *current);
            curSize--;
            return false;
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
