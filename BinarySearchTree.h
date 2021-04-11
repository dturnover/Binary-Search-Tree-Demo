#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "dsexceptions.h"
#include <algorithm>
#include <vector>

using namespace std;       

// BinarySearchTree class
//
// CONSTRUCTION: zero parameter
//
// ******************PUBLIC OPERATIONS*********************
// void insert( x )       --> Insert x
// void remove( x )       --> Remove x
// bool contains( x )     --> Return true if x is present
// Comparable findMin( )  --> Return smallest item
// Comparable findMax( )  --> Return largest item
// boolean isEmpty( )     --> Return true if empty; else false
// void makeEmpty( )      --> Remove all items
// void printTree( )      --> Print tree in sorted order
// ******************ERRORS********************************
// Throws UnderflowException as warranted

bool inVector (int element, vector <int> v);

template <typename Comparable>
class BinarySearchTree
{
  public:
    BinarySearchTree( ) : root{ nullptr }
    {
    }

    /**
     * Copy constructor
     */
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );
    }

    /**
     * Move constructor
     */
    BinarySearchTree( BinarySearchTree && rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }
    
    /**
     * Destructor for the tree
     */
    ~BinarySearchTree( )
    {
        makeEmpty( );
    }

    /**
     * Copy assignment
     */
    BinarySearchTree & operator=( const BinarySearchTree & rhs )
    {
        BinarySearchTree copy = rhs;
        std::swap( *this, copy );
        return *this;
    }
        
    /**
     * Move assignment
     */
    BinarySearchTree & operator=( BinarySearchTree && rhs )
    {
        std::swap( root, rhs.root );       
        return *this;
    }
    
    
    /**
     * Find the smallest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMin( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMin( root )->element;
    }

    /**
     * Find the largest item in the tree.
     * Throw UnderflowException if empty.
     */
    const Comparable & findMax( ) const
    {
        if( isEmpty( ) )
            throw UnderflowException{ };
        return findMax( root )->element;
    }

    /**
     * Returns true if x is found in the tree.
     */
    bool contains( const Comparable & x ) const
    {
        return contains( x, root );
    }

    /**
     * Test if the tree is logically empty.
     * Return true if empty, false otherwise.
     */
    bool isEmpty( ) const
    {
        return root == nullptr;
    }

    /**
     * Print the tree contents in sorted order.
     */
    void printTree( ostream & out = cout ) const
    {
        if( isEmpty( ) )
            out << "Empty tree" << endl;
        else
            printTree( root, out );
    }

    /**
     * Make the tree logically empty.
     */
    void makeEmpty( )
    {
        makeEmpty( root );
    }

    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( const Comparable & x, int line )
    {
      insert( x, line, root );
    }
     
    /**
     * Insert x into the tree; duplicates are ignored.
     */
    void insert( Comparable && x, int line )
    {
      insert( std::move( x ), line, root );
    }
    
    /**
     * Remove x from the tree. Nothing is done if x is not found.
     */
    void remove( const Comparable & x )
    {
        remove( x, root );
    }

    int getHeight ()
    {
        getHeight( root );
    }

    int getSize ()
    {
      getSize ( root );
    }

    void search ( const Comparable & x, ostream & out = cout )
    {
      if( isEmpty( ) )
	out << "Empty tree" << endl;
      else 
	search ( x, cout, root );
    }
    
  private:
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;
        vector <int> lineNumberList;

    BinaryNode( const Comparable & theElement, BinaryNode *lt, BinaryNode *rt, int line )
    : element{ theElement }, left{ lt }, right{ rt }, lineNumberList{line} { }
        
    BinaryNode( Comparable && theElement, BinaryNode *lt, BinaryNode *rt, int line )
    : element{ std::move( theElement ) }, left{ lt }, right{ rt }, lineNumberList{line} { }
    };

    BinaryNode *root;

    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( const Comparable & x, int line, BinaryNode * & t )
    {
        if( t == nullptr )
	  t = new BinaryNode{ x, nullptr, nullptr, line };
	else if( x < t->element )
	  insert( x, line, t->left );
        else if( t->element < x )
	  insert( x, line, t->right );
        else
	  if (inVector(line, t->lineNumberList) == false)
	    t->lineNumberList.push_back(line);	  
    }
    
    /**
     * Internal method to insert into a subtree.
     * x is the item to insert.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void insert( Comparable && x, int line, BinaryNode * & t )
    {
        if( t == nullptr )
	  t = new BinaryNode{ std::move( x ), nullptr, nullptr, line };
        else if( x < t->element )
	  insert( std::move( x ), line, t->left );
        else if( t->element < x )
	  insert( std::move( x ), line, t->right );
        else
	  if (inVector(line, t->lineNumberList) == false)
	    t->lineNumberList.push_back(line);
    }

    /**
     * Internal method to remove from a subtree.
     * x is the item to remove.
     * t is the node that roots the subtree.
     * Set the new root of the subtree.
     */
    void remove( const Comparable & x, BinaryNode * & t )
    {
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }
    }

    /**
     * Internal method to find the smallest item in a subtree t.
     * Return node containing the smallest item.
     */
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
            return nullptr;
        if( t->left == nullptr )
            return t;
        return findMin( t->left );
    }

    /**
     * Internal method to find the largest item in a subtree t.
     * Return node containing the largest item.
     */
    BinaryNode * findMax( BinaryNode *t ) const
    {
        if( t != nullptr )
            while( t->right != nullptr )
                t = t->right;
        return t;
    }


    /**
     * Internal method to test if an item is in a subtree.
     * x is item to search for.
     * t is the node that roots the subtree.
     */
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        if( t == nullptr )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else
            return true;    // Match
    }
/****** NONRECURSIVE VERSION*************************
    bool contains( const Comparable & x, BinaryNode *t ) const
    {
        while( t != nullptr )
            if( x < t->element )
                t = t->left;
            else if( t->element < x )
                t = t->right;
            else
                return true;    // Match

        return false;   // No match
    }
*****************************************************/

    /**
     * Internal method to make subtree empty.
     */
    void makeEmpty( BinaryNode * & t )
    {
        if( t != nullptr )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    /**
     * Internal method to print a subtree rooted at t in sorted order.
     */
    void printTree( BinaryNode *t, ostream & out ) const
    {
      if( t != nullptr )
        {
	  printTree( t->left, out );
	  out << t->element;
	  for (int i = 0; i < 20 - t->element.length(); i++)
	    out << " ";
	  
	  if (t->lineNumberList.size() == 1)
	    out << t->lineNumberList[0];
	  else
	    {
	      out << t->lineNumberList[0];
	      for (int j = 1; j < t->lineNumberList.size(); j++)
		out << ", " << t->lineNumberList[j];
	    }
	  out << endl;
	  printTree( t->right, out );
	}
    }

    
    /**
     * Internal method to clone subtree.
     */
    BinaryNode * clone( BinaryNode *t ) const
    {
      if( t == nullptr )
	  return nullptr;
        else
	  return new BinaryNode{ t->element, clone( t->left ), clone( t->right ) };
    }
    
    int getHeight( BinaryNode * & t )
    {
      if (t == nullptr)
	return -1;
      return 1 + max(getHeight(t->left), getHeight(t->right));
      /*
      else if (getHeight(t->left) > getHeight(t->right))
	return 1 + getHeight(t->left);
      else
	return 1 + getHeight(t->right);*/
    }
    
    int getSize( BinaryNode * & t )
    {
      if (t == nullptr)
	return -1;
      else
	return (2 + getSize(t->left) + getSize(t->right));
    }
    
    void search ( const Comparable & x, ostream & out, BinaryNode * t )
    {
      if (t != nullptr)
	{
	  search (x, out, t->left);
	  if (x == t->element)
	    {
	      if (t->lineNumberList.size() == 1)
		cout << t->lineNumberList[0];
	      else
		{		
		  cout << t->lineNumberList[0];	 
		  for (int i = 1; i < t->lineNumberList.size(); i++)     
		    cout << ", " << t->lineNumberList[i];
        	}
	    }
	  search (x, out, t->right);
	}
    }
};
    
bool inVector (int element, vector <int> v)
{
  for (int i = 0; i < v.size(); i++)
    {
      if (element == v[i])
	return true;
    }
  return false;
}
#endif
