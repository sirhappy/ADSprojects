#include <cstdlib>
#include "SkipList.h"
#include <ctime>
//=============================================================================
//== NodeSkipList =============================================================
//=============================================================================

template <class Value, class Key, int numLevels>
void NodeSkipList<Value,Key,numLevels>::clear(void)
{
	for (int i = 0; i < numLevels; ++i)
	{
		m_nextjump[i] = 0;
	}
	m_levelHighest = -1;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(void)
{
	clear();
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key)
{
	clear();

	m_key = key;
}

template <class Value, class Key, int numLevels>
NodeSkipList<Value, Key, numLevels>::NodeSkipList(Key key, Value value)
{
	clear();

	m_key = key;
	m_value = value;
}
//=============================================================================
//== End of: NodeSkipList =====================================================
//=============================================================================

//=============================================================================
//== SkipList =================================================================
//=============================================================================
template <class Value, class Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(double probability)
{
	m_probability = probability;
	for (int i = 0; i < numLevels; ++i)
	{
		// Lets use m_pPreHead as a final sentinel element
		m_pPreHead->m_nextjump[i] = m_pPreHead;
	}

	m_pPreHead->m_levelHighest = numLevels-1;
}

template <typename Value, typename Key, int numLevels>
SkipList<Value, Key, numLevels>::SkipList(const SkipList& other) 
{
    m_probability = other.m_probability;

    for (int i = 0; i < numLevels; ++i)
    {
        m_pPreHead->m_nextjump[i] = m_pPreHead;
    }

    m_pPreHead->m_levelHighest = numLevels - 1;

    //Next code inserts elements which key and value are the same as
    //key and value of corresponding element of "other".
    //This means that structure of upper lists 
    //will be different in this and other SkipLists.
    TypeNode* curr = other.m_pPreHead;

    while (curr->m_next != other.m_pPreHead)
    {
        insert(curr->m_next->m_value, curr->m_next->m_key);
        curr = curr->m_next;
    }
}

template<typename Value, typename Key, int numLevels>
SkipList<Value,Key,numLevels>& SkipList<Value,Key,numLevels>::operator=(const SkipList& other)
{
    SkipList temp(other);
    swap(*this, temp);
    return *this;
}

//TODO:check if it's required to delete some inherited things
template <typename Value, typename Key, int numLevels>
SkipList<Value, Key, numLevels>::~SkipList() 
{
    TypeNode* temp = m_pPreHead;
    TypeNode* curr = m_pPreHead->m_next;
   
    //Move through the lowest level until meet m_pPreHead
    //and delete nodes.
    while (curr != m_pPreHead)
    {        
        temp = curr->m_next;
        delete curr;
        curr = temp;
    }

    delete curr;
}


template<typename Value, typename Key, int numLevels>
void SkipList<Value, Key, numLevels>::insert(Value value, Key key)
{	
	TypeNode* curr = m_pPreHead;
	TypeNode* ins = new TypeNode(key, value);

    //Search for position for "ins" using upper levels
    //and save pointers to previous element for "ins" on each level
    //in "ins->m_nextjump" in order to access it later
	for (int i = numLevels - 1; i >= 0; --i)
	{
		while (curr->m_nextjump[i] != m_pPreHead && curr->m_nextjump[i]->m_key <= key)
			curr = curr->m_nextjump[i];

		ins->m_nextjump[i] = curr;  //store previous elements
	}

    //Search for position for "ins" on lowest level
	while (curr->m_next != m_pPreHead && curr->m_next->m_key <= key)
		curr = curr->m_next;
	
    //Insert "ins" to lowest level
	ins->m_next = curr->m_next;
	curr->m_next = ins;
	
    //Insert "ins" on upper levels depending on probability
	for (int i = 0; i < numLevels; ++i)
	{
		double probability = (double)rand() / RAND_MAX; //in [0;1]
		
        //If probability is greater than probability of insert
        //save the index of the most upper level where 
        //"ins" occurs and finish insert on upper levels
		if (probability > m_probability)
		{		
			ins->m_levelHighest = i - 1;			
			break;
		}

        //Insert "ins" on upper level with index "i"
		TypeNode* temp = ins->m_nextjump[i];  
		ins->m_nextjump[i] = temp->m_nextjump[i];
		temp->m_nextjump[i] = ins;
	}
    
    //Fill the rest pointers to next elements with "m_pPreHead"
	for (int i = ins->m_levelHighest + 1; i < numLevels; ++i)
		ins->m_nextjump[i] = m_pPreHead;  
}

template<typename Value, typename Key, int numLevels>
void SkipList<Value, Key, numLevels>::remove(TypeNode * node)
{
	if (node == m_pPreHead)
		return;

	TypeNode* curr = m_pPreHead;
	TypeNode* prevNodes[numLevels]; //stores nodes previous to "node" on each level (excluding lowest)

    //Search for position of "node" using upper levels
    //and save nodes previous to "node"
	for (int i = numLevels - 1; i >= 0; --i)
	{
		while (curr->m_nextjump[i] != m_pPreHead && curr->m_nextjump[i]->m_key < node->m_key)
			curr = curr->m_nextjump[i];

		prevNodes[i] = curr;  //store previous nodes
	}

    //Search for "node" on lowest level
    while (curr->m_next != m_pPreHead && curr->m_next != node)
        curr = curr->m_next;

    //If node wasn't found report about it
	if (curr->m_next != node)
		throw std::invalid_argument("Wrong pointer to node for delete");

    //Connect previous node for "node" on each level
    //to next node for "node" on corresponding level 
	for (int i = 0; i <= node->m_levelHighest; ++i)
		prevNodes[i]->m_nextjump[i] = node->m_nextjump[i];

    //Connect previous and next nodes for "node" on lowest level
    curr->m_next = node->m_next;

	delete node;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value,Key,numLevels>* SkipList<Value, Key, numLevels>::findLastLessThan(Key key) const
{
	TypeNode* curr = m_pPreHead;	

    //Search for position of last node with key less than given key
	for (int i = numLevels - 1; i >= 0;  --i) 
	{
		while (curr->m_nextjump[i] != m_pPreHead && curr->m_nextjump[i]->m_key < key)
			curr = curr->m_nextjump[i];
	}

    //Search for last node which key is less than given key
	while (curr->m_next != m_pPreHead && curr->m_next->m_key < key)
		curr = curr->m_next;

	return curr;
}

template<class Value, class Key, int numLevels>
NodeSkipList<Value,Key,numLevels>* SkipList<Value, Key, numLevels>::findFirst(Key key) const
{    
    //Find last node which key is less than given key and get next node
	TypeNode* result = findLastLessThan(key)->m_next;

    //Check if found node key equals to given key (it could be greater)
	if (result->m_key == key)
		return result;

	return nullptr;
}

template<typename Value, typename Key, int numLevels>
void SkipList<Value,Key,numLevels>::swap(SkipList& first, SkipList& second)
{
    TypeNode* firstTempPreHead = first->m_pPrehead;             //stores m_pPreHead of "first" SkipList
    TypeNode* secondPreHeadNext = second->m_pPreHead->m_next;   //stores element after m_pPreHead in "second" SkipList    
    TypeNode* secondPreHeadPrevNodes[numLevels];                //stores pointers to last node on each level (exclucing lowest) of "second" SkipList 
    TypeNode* secondPreHeadNextJump[numLevels];                 //stores pointers to first node on each level (excluding lowest) of "second" SkipLists
    TypeNode* curr = second->m_pPreHead;                        //used for walking through SkipLists
    
    //Save pointers to first elements on each level(excluding lowest) of "second" SkipList
    for (int i = numLevels - 1; i >= 0; --i)    
        secondPreHeadNextJump[i] = second->m_pPreHead->m_nextjump[i];    

    //Save pointers to last elements on each level(excluding lowest) of "second" SkipList
    for (int i = numLevels - 1; i >= 0; --i)
    {
        while (curr->m_next != second->m_pPreHead)
            curr = curr->m_nextjump[i];

        secondPreHeadPrevNodes[i] = curr;
    }

    while (curr->m_next != second->m_pPreHead)
        curr = curr->m_next;

    TypeNode* SecondPreHeadPrev = curr; //stores pointer to last element on lowest level of "second"

    //Connect m_pPreHead of "second" to first nodes on each level of "first".
    for (int i = numLevels - 1; i >= 0; --i)
        second->m_pPreHead->m_nextjump[i] = first->m_pPreHead->m_nextjump[i];

    second->m_pPreHead->m_next = first->m_pPreHead->m_next; //connect the first element on lowest level of "first" to m_pPreHead of "second"


    curr = first->m_pPreHead;   //now use curr for walking through "first"

    //Connect the last element on each level of "first" SkipList to m_pPreHead of "second"
    for (int i = numLevels - 1; i >= 0; --i)
    {
        while (curr->m_next != first->m_pPreHead)
            curr = curr->m_nextjump[i];

        curr->m_nextjump[i] = second->m_pPreHead;
    }

    while (curr->m_next != first->m_pPreHead)
        curr = curr->m_next;

    curr->m_next = second->m_pPreHead; //connect last element on lowest level of "first" to m_pPreHead of "second"

    //Finish connection of "second" m_pPreHead to "first" by making it m_pPreHead of "first"
    first->m_pPreHead = second->m_pPreHead;


    //Connect "first" saved m_pPreHead to beginning of "second" SkipList
    for (int i = numLevels - 1; i >= 0; --i)
        firstTempPreHead->m_nextjump[i] = secondPreHeadNextJump[i];

    firstTempPreHead->m_next = secondPreHeadNext;   //connect first element on lowest level of "second" to "first" saved m_pPreHead

    //Connect end of "second" SkipList to "first" saved m_pPreHead
    for (int i = numLevels - 1; i >= 0; --i)
        secondPreHeadPrevNodes[i]->m_nextjump[i] = firstTempPreHead;
    
    secondPreHeadPrev->m_next = firstTempPreHead;   //connect last element on lowest level of "second" to "first" saved m_pPreHead

    //Finish connection by making "first" saved m_pPreHead actual "second" m_pPreHead
    second->m_pPreHead = firstTempPreHead;
}


// Put your code here

//=============================================================================
//== End of: SkipList =========================================================
//=============================================================================
