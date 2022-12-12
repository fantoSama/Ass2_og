//
// Created by Study on 11/12/2022.
//

#ifndef ASS2_MAP_RB_H
#define ASS2_MAP_RB_H


#include <utility>
#include <iterator>
#include <list>

template<class K, class D>
class map_rb {
public:
    typedef std::pair<const K, D> value_type;
    map_rb() = default;
    ~map_rb()
    {
        delete m_pRoot;
    }

private:
    // Node class
    struct Node {
        Node(const K &key, const D &value) : m_value(key, value) {}

        ~Node() {
            delete m_pLeft;
            delete m_pRight;
        }

        bool is4Node() {
            return ( m_pLeft && m_pLeft->m_isRed ) && ( m_pRight && m_pRight->m_isRed);
        }

        void convert4Node(){
                m_pLeft->m_isRed = false;
                m_pRight->m_isRed = false;
                m_isRed = true;
        }
        value_type m_value;
        Node *m_pLeft = nullptr;
        Node *m_pRight = nullptr;
        bool m_isRed = true;
    };

    struct NodeHanlder {

        explicit NodeHanlder(Node *node) : m_Nodes(node){};

        bool down(bool direction) {
            m_Nodes[GGDAD] = m_Nodes[GDAD];
            m_Nodes[GDAD] = m_Nodes[DAD];
            m_Nodes[DAD] = node();
            m_Nodes[NODE] = direction ? node(NODE)->m_pRight : node(NODE)->m_pLeft;

        }

        void set(Node * nodeToAdd){
            m_Nodes[NODE] = nodeToAdd;
        }

        bool isNull(){
            return m_Nodes[NODE] == nullptr;
        }

        Node* node(unsigned kind){
            return m_Nodes[kind];
        }

        Node *m_Nodes = new Node[4];
        const unsigned NODE = 0;
        const unsigned DAD = 1;
        const unsigned GDAD = 2;
        const unsigned GGDAD = 3;
    };


public:

    class const_iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        std::list<Node *> m_Nodes2Visit;

//         copy constructor
        const_iterator(const const_iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        const_iterator& operator=(const const_iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit const_iterator(Node *start) {
            goDown(start);
        }


        const_iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return *this;
        }

        const_iterator operator++(int) {
            iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return tmp;
        }

        //value_type& operator*(){
        typename const_iterator::value_type &operator*() const {
            return m_Nodes2Visit.back()->m_value;
        }

        typename const_iterator::value_type *operator->() const {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const const_iterator &iter1, const const_iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const const_iterator &iter1, const const_iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pLeft)
                m_Nodes2Visit.push_back(goFrom);
        }

    };

    class iterator : public std::iterator<std::forward_iterator_tag, value_type> {
    public:
        std::list<Node *> m_Nodes2Visit;

//         copy constructor
        iterator(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        iterator& operator=(const iterator &crArg) {
            if (&crArg != this)
                for (auto node: crArg.m_Nodes2Visit)
                    m_Nodes2Visit.push_back(node);
        }

        // constructor
        explicit iterator(Node *start) {
            goDown(start);
        }

        // Operators
        explicit operator const_iterator() {
            return const_iterator(m_Nodes2Visit.front());
        }

        iterator &operator++() {
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp(*this);
            Node *node = m_Nodes2Visit.back();
            m_Nodes2Visit.pop_back();
            goDown(node->m_pRight);
            return tmp;
        }

        //value_type& operator*(){
        typename iterator::value_type &operator*() {
            return m_Nodes2Visit.back()->m_value;
        }

        typename iterator::value_type *operator->() {
            return &m_Nodes2Visit.back()->m_value;
        }

        friend bool operator==(const iterator &iter1, const iterator &iter2) {
            return iter1.m_Nodes2Visit == iter2.m_Nodes2Visit;
        }

        friend bool operator!=(const iterator &iter1, const iterator &iter2) {
            return iter1.m_Nodes2Visit != iter2.m_Nodes2Visit;
        }

    private:
        void goDown(Node *goFrom) {
            for (; goFrom; goFrom = goFrom->m_pLeft)
                m_Nodes2Visit.push_back(goFrom);
        }
    };

    map_rb(const map_rb<K, D> &crArg)  // TODO: deleting copy constructor if not used
    {
        if (crArg.m_pRoot)
            m_pRoot = new Node(*crArg.m_pRoot);
    }

    map_rb &operator=(const map_rb<K, D> &crArg)  // TODO: deleting assign operator if not used
    {
        if (&crArg != this)
        {
            delete m_pRoot;
            m_pRoot = nullptr;
            if (crArg.m_pRoot)
                m_pRoot = new Node(*crArg.m_pRoot);
        }
        return *this;
    }


    iterator find(const K& key)
    {
        Node *pTmp = m_pRoot;
        while (pTmp != nullptr)
        {
            if (key < pTmp->m_value.first)
                pTmp = pTmp->m_pLeft;
            else if (pTmp->m_value.first < key)
                pTmp = pTmp->m_pRight;
            else
                // has been found
                return iterator(pTmp);
        }
        return end();
    }

    const_iterator find(const K& key) const
    {
        Node *pTmp = m_pRoot;
        while (pTmp != nullptr)
        {
            if (key < pTmp->m_value.first)
                pTmp = pTmp->m_pLeft;
            else if (pTmp->m_value.first < key)
                pTmp = pTmp->m_pRight;
            else
                // has been found
                return const_iterator(pTmp);
        }
        return cend();
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        NodeHanlder handler(m_pRoot);
        auto keyToAdd = value.first;
        while (!handler.isNull()){
            if(handler.node()->is4Node())
                handler.node()->convert4Node();
            auto key = handler.node()->m_value.first;
            if(key < keyToAdd)
                handler.down(false);
            else if(keyToAdd < key)
                handler.down(true);
            else
                std::pair<iterator, bool>(end(), false);
        }
        auto newNode = new Node(value);
        handler.set(newNode);
        m_pRoot->m_isRed = false;
        return std::pair<iterator, bool>(newNode, false);
    }

private:
    Node *m_pRoot = nullptr;

public:
    iterator begin() { return iterator(m_pRoot); }
    iterator end() { return iterator(nullptr); }
    const_iterator  cbegin() const { return const_iterator(m_pRoot); }
    const_iterator cend() const { return const_iterator(nullptr); }
};


#endif //ASS2_MAP_RB_H
