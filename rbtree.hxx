#ifndef        __RBTREE_H__
#define        __RBTREE_H__

#include <iostream>
const int RED = 0;
const int BLACK = 1;

struct RBTreeNode
{
    RBTreeNode* left;
    RBTreeNode* right;
    RBTreeNode* parent;
    int nData;
    int color;//RED=0,BLACK=1
};

class RBTree
{

public:
    RBTree();
    ~RBTree();
public:
    bool Insert(const int nData);
    bool Delete(const int nData);
    RBTreeNode* Find(const int nData);
    void Display() 
    {
        PrintTree(root);
    }
private:
    void RotateLeft(RBTreeNode* pNode);
    void RotateRight(RBTreeNode* pNode);
    void InsertFixup(RBTreeNode* pNode);
    void DeleteFixup(RBTreeNode* pNode);

    RBTreeNode* CreateNode(int nData);
    RBTreeNode* DeleteNode(RBTreeNode* pNode);
    RBTreeNode* FindNode(const int nData);
    RBTreeNode* Maximum(RBTreeNode* pNode);
    RBTreeNode* Minimum(RBTreeNode* pNode);
    RBTreeNode* Successor(RBTreeNode* pNode);

    void DeleteTree(RBTreeNode* pNode);
    void PrintTree(RBTreeNode* pNode) const;
private:
    RBTreeNode* root;
    RBTreeNode* nil;
    int    node_count;
};

RBTree::RBTree()
{
    nil = new RBTreeNode();

    nil->left = NULL;
    nil->right = NULL;
    nil->parent = NULL;
    nil->nData = 0;
    nil->color = BLACK;

    root = nil;
}

RBTree::~RBTree()
{
    DeleteTree(root);
    delete nil;
    root = NULL;
    nil = NULL;
}

RBTreeNode* RBTree::CreateNode(int nData)
{
    RBTreeNode* pTempNode = new RBTreeNode();

    pTempNode->left = nil;
    pTempNode->right = nil;
    pTempNode->parent = nil;
    pTempNode->nData = nData;
    pTempNode->color = RED;

    return pTempNode;
}

void RBTree::DeleteTree(RBTreeNode* pNode)
{
    if(pNode == nil)
        return;

    DeleteTree(pNode->left);
    DeleteTree(pNode->right);

    delete pNode;
    pNode = NULL;
}

//左旋转
void RBTree::RotateLeft(RBTreeNode* pNode)
{
    RBTreeNode* pRNode = pNode->right;
    pNode->right = pRNode->left;

    if(pRNode->left != nil)
    {
        pRNode->left->parent = pNode;
        pRNode->parent = pNode->parent;
    }

    if(pNode->parent == nil)
    {
        root = pRNode;
    }
    else if(pNode->parent->left == pNode)
    {
        pNode->parent->left = pRNode;
    }
    else
    {
        pNode->parent->right = pRNode;
    }

    pRNode->left = pNode;
    pNode->parent = pRNode;
}

//右旋转
void RBTree::RotateRight(RBTreeNode* pNode)
{
    RBTreeNode* pLNode = pNode->left;
    pNode->left = pLNode->right;

    if(pLNode->right != nil)
    {
        pLNode->right->parent = pNode;
        pLNode->parent = pNode->parent;
    }

    if(pNode->parent == nil)
    {
        root = pLNode;
    }
    else if(pNode->parent->left == pNode)
    {
        pNode->parent->left = pLNode;
    }
    else
    {
        pNode->parent->right = pLNode;
    }

    pLNode->right = pNode;
    pNode->parent = pLNode;
}

RBTreeNode* RBTree::Maximum(RBTreeNode* pNode)
{
    while(pNode->right != nil)
        pNode = pNode->right;

    return pNode;
}

RBTreeNode* RBTree::Minimum(RBTreeNode* pNode)
{
    while(pNode->left != nil)
        pNode = pNode->left;

    return pNode;
}

RBTreeNode* RBTree::Successor(RBTreeNode* pNode)
{
    if(pNode->right != nil)
        return Minimum(pNode->right);
    
    RBTreeNode* pPNode = pNode->parent;
    while(pPNode != nil && pNode == pPNode->right)
    {
        pNode = pPNode;
        pPNode = pNode->parent;
    }

    return pPNode;
}

bool RBTree::Insert(const int nData)
{
    RBTreeNode* pNewNode = CreateNode(nData);
    RBTreeNode* pPNewNode = nil;
    RBTreeNode* pTemp = root;

    while( pTemp != nil)
    {
        pPNewNode = pTemp;

        if(nData < pTemp->nData)
            pTemp = pTemp->left;
        else
            pTemp = pTemp->right;
    }

    pNewNode->parent = pPNewNode;

    if(pPNewNode == nil)
        root = pNewNode;
    else if(nData < pPNewNode->nData)
        pPNewNode->left = pNewNode;
    else
        pPNewNode->right = pNewNode;

    InsertFixup(pNewNode);

    return true;
}

void RBTree::InsertFixup(RBTreeNode* pNode)
{
    while(pNode->parent->color == RED)
    {
        if(pNode->parent == pNode->parent->parent->left)
        {
            RBTreeNode* pUNode = pNode->parent->parent->right;//pNode的叔父节点
            
            if(pUNode->color == RED)//case 1
            {
                pNode->parent->color = BLACK;
                pUNode->color = BLACK;
                pNode->parent->parent->color = RED;

                pNode = pNode->parent->parent;
            }
            else if(pNode == pNode->parent->right)//case 2
            {
                pNode = pNode->parent;
                RotateLeft(pNode);
            }
            else//case 3
            {
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateRight(pNode->parent->parent);
            }
        }//pNode的父节点是其父节点的左子节点
        else
        {
            RBTreeNode* pUNode = pNode->parent->parent->left;//pNode的叔父节点
            
            if(pUNode->color == RED)//case 1
            {
                pNode->parent->color = BLACK;
                pUNode->color = BLACK;
                pNode->parent->parent->color = RED;

                pNode = pNode->parent->parent;
            }
            else if(pNode == pNode->parent->left)//case 2
            {
                pNode = pNode->parent;
                RotateRight(pNode);
            }
            else//case 3
            {
                pNode->parent->color = BLACK;
                pNode->parent->parent->color = RED;
                RotateLeft(pNode->parent->parent);
            }        
        }//pNode的父节点是其父节点的右子节点
    }//while(pNode->parent->color == RED)

    root->color = BLACK;
}

bool RBTree::Delete(const int nData)
{
    RBTreeNode* pDeleteNode = FindNode(nData);

    if(pDeleteNode == nil)
    {
        std::cout << "no data" << std::endl;
        return false;
    }

    DeleteNode(pDeleteNode);

    return true;
}

RBTreeNode* RBTree::FindNode(const int nData)
{
    RBTreeNode* pTemp = root;

    while(pTemp != nil)
    {
        if(nData < pTemp->nData)
            pTemp = pTemp->left;
        else if(nData > pTemp->nData)
            pTemp = pTemp->right;
        else
            return pTemp;
    }

    return nil;
}

RBTreeNode* RBTree::DeleteNode(RBTreeNode* pNode)
{
    RBTreeNode* pDeleteNode = nil;//删除节点
    RBTreeNode* pCDeleteNode = nil;//删除节点的子节点

    if(pNode->left == nil || pNode->right == nil)
        pDeleteNode = pNode;
    else
        pDeleteNode = Successor(pNode);
    
    if(pDeleteNode->left != nil)
        pCDeleteNode = pDeleteNode->left;
    else
        pCDeleteNode = pDeleteNode->right;

    if(pDeleteNode->parent == nil)
        root = pCDeleteNode;
    else if(pDeleteNode == pDeleteNode->parent->left)
        pDeleteNode->parent->left = pCDeleteNode;
    else
        pDeleteNode->parent->right = pCDeleteNode;

    if(pDeleteNode != pNode)
        pNode->nData = pDeleteNode->nData;

    pCDeleteNode->parent = pDeleteNode->parent;

    if(pDeleteNode->color == BLACK)
        DeleteFixup(pCDeleteNode);

    return pDeleteNode;
}

void RBTree::DeleteFixup(RBTreeNode* pNode)
{
    while(pNode != root && pNode->color == BLACK)
    {
        if(pNode == pNode->parent->left)
        {
            RBTreeNode* pBNode = pNode->parent->right;//pNode的兄弟节点

            if(pBNode->color = RED)//case 1
            {
                pBNode->color = BLACK;
                pNode->parent->color = RED;

                RotateLeft(pNode->parent);
                pBNode = pNode->parent->right;
            }

            if(pBNode->left->color == BLACK && pBNode->right->color == BLACK)//case 2
            {
                pBNode->color = RED;
                pNode = pNode->parent;
            }
            else if(pBNode->right->color == BLACK)//case 3
            {
                pBNode->left->color = BLACK;
                pBNode->color = RED;

                RotateRight(pBNode);
                pBNode = pNode->parent->right;
            }
            else//case 4
            {
                pBNode->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pBNode->right->color = BLACK;

                RotateLeft(pNode->parent);
                pNode = root;
            }
        }
        else
        {
            RBTreeNode* pBNode = pNode->parent->left;//pNode的兄弟节点

            if(pBNode->color = RED)//case 1
            {
                pBNode->color = BLACK;
                pNode->parent->color = RED;

                RotateLeft(pNode->parent);
                pBNode = pNode->parent->left;
            }

            if(pBNode->left->color == BLACK && pBNode->right->color == BLACK)//case 2
            {
                pBNode->color = RED;
                pNode = pNode->parent;
            }
            else if(pBNode->left->color == BLACK)//case 3
            {
                pBNode->right->color = BLACK;
                pBNode->color = RED;

                RotateRight(pBNode);
                pBNode = pNode->parent->left;
            }
            else//case 4
            {
                pBNode->color = pNode->parent->color;
                pNode->parent->color = BLACK;
                pBNode->left->color = BLACK;

                RotateLeft(pNode->parent);
                pNode = root;
            }        
        }//if(pNode == pNode->parent->left)
    }//while(pNode != root && pNode->color == BLACK)

    pNode->color = BLACK;
}

void RBTree::PrintTree(RBTreeNode* pNode) const
{
    if (NULL == root)
        return;

    if (nil == pNode)
    {
        return;
    }

    static int n = 0;
    
    if(pNode == root)
    {
        std::cout << "[" << ++n << "]nData = " << pNode->nData << ",nParentData= 0 ,";

        if(pNode->left)
            std::cout << "nLeftData= " << pNode->left->nData << " ,";
        if(pNode->right)
            std::cout << "nRightData= " << pNode->right->nData << " ,";

        std::cout << "color = " << pNode->color << std::endl;
    }
    else
    {
        std::cout << "[" << ++n << "]nData = " << pNode->nData << ",nParentData= " << pNode->parent->nData << " ,";

        if(pNode->left)
            std::cout << "nLeftData= " << pNode->left->nData << " ,";
        if(pNode->right)
            std::cout << "nRightData= " << pNode->right->nData << " ,";

        std::cout << "color = " << pNode->color << std::endl;
    }
    PrintTree(pNode->left);
    PrintTree(pNode->right);
}

#endif        //__RBTREE_H__

