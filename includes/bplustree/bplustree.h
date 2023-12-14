#ifndef BPLUS_TREE_H 
#define BPLUS_TREE_H 
#include <iomanip>
#include <iostream>

#include "../../includes/bplustree/btree_array_funcs.h"

template <class T>
class BPlusTree
{
public:
    class Iterator{
    public:
        friend class BPlusTree;
        Iterator(BPlusTree<T>* _it=nullptr, int _key_ptr = 0): it(_it), key_ptr(_key_ptr){}


        //return first data item in b plus tree
        T operator *(){
            return it->data[key_ptr]; 
        }

        Iterator operator++(int un_used){//hmm?
            key_ptr++; 
            Iterator returnIter(it, key_ptr); 
            if(it && key_ptr >= it->data_count){ //next bPlusTree 
                key_ptr = 0;
                it = it->next;
                returnIter = Iterator(it, key_ptr);
            }
            return returnIter; 
        }

        Iterator operator++(){
            key_ptr++; 
            Iterator returnIter(it, key_ptr); 

            if(it && key_ptr == it->data_count){ //next bPlusTree 
                key_ptr = 0;
                //cout<<"it: "<<*it<<endl; 
                it = it->next; 
                returnIter = Iterator(it, key_ptr); 
            }
            return returnIter; 
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){ //what is keyptr
            return (lhs.it == rhs.it && lhs.key_ptr == rhs.key_ptr); 
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return(!(lhs == rhs)); 
        }

        void print_Iterator(){
            if (it){
                cout<<"iterator: ";
                print_array(it->data, it->data_count, key_ptr);
            }
            else{
                cout<<"iterator: NULL, key_ptr: "<<key_ptr<<endl;
            }
        }

        bool is_null(){
            return !it;
        }

        void info(){
            cout<<endl<<"Iterator info:"<<endl;
            cout<<"key_ptr: "<<key_ptr<<endl;
            cout<<"it: "<<*it<<endl;
        }

    private:
        BPlusTree<T>* it; 
        int key_ptr;
    };

    BPlusTree(bool dups = false);
    BPlusTree(T *a, int size, bool dups = false);

    //big three:
    BPlusTree(const BPlusTree<T>& other);
    ~BPlusTree();
    BPlusTree<T>& operator =(const BPlusTree<T>& RHS);

    void copy_tree(const BPlusTree<T>& other);  //copy other into this object
    void copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node);

    void insert(const T& entry);   //insert entry into the tree
    void remove(const T& entry);   //remove entry from the tree
    void clear_tree();             //clear this object (delete all nodes etc.)

    bool contains(const T& entry) const; //true if entry can be found
    T& get(const T& entry);              //return a reference to entry
    const T& get(const T& entry)const;   //return a reference to entry
    T& get_existing(const T& entry);     //return a reference to entry


    Iterator find(const T& key);         //return an iterator to this key.
                                         //     NULL if not there.
    Iterator lower_bound(const T& key);  //return first that goes NOT BEFORE
                                         // key entry or next if does not
                                         // exist: >= entry
    Iterator upper_bound(const T& key);  //return first that goes AFTER key
                                         //exist or not, the next entry  >entry

    int size() const;                    //count the number of elements

    bool empty() const;                  //true if the tree is empty

    void print_tree(int level = 0,
                    ostream &outs=cout) const;
    friend ostream& operator<<(ostream& outs, const BPlusTree<T>& print_me){
        print_me.print_tree(0, outs);
        return outs;
    }

    bool is_valid();
    string in_order();
    string pre_order(); 
    string post_order(); 

    Iterator begin(); 
    Iterator end();

    ostream& list_keys(Iterator from = NULL, Iterator to = NULL){
        if (from == NULL) from = begin();
        if (to == NULL) to = end();
        for (Iterator it = from; it != to; it++)
            cout<<*it<<" ";
        return cout;

    }

    
private:
    static const int MINIMUM = 1;
    static const int MAXIMUM = 2 * MINIMUM;
    
    bool dups_ok;                        //true if duplicate keys are allowed
    int data_count;                      //number of data elements
    T data[MAXIMUM + 1];                 //holds the keys
    int child_count;                     //number of children
    BPlusTree* subset[MAXIMUM + 2];      //subtrees
    BPlusTree* next;
    


    bool is_leaf() const{
        return (child_count==0); //next == nullptr 
    }             //true if this is a leaf node

    T* find_ptr(const T& entry);         //return a pointer to this key.
                                         // NULL if not there. 

    //insert element functions
    void loose_insert(const T& entry);   //allows MAXIMUM+1 data elements in
                                         //   the root
    void fix_excess(int i);              //fix excess in child i

    //remove element functions:
    void loose_remove(const T& entry);  //allows MINIMUM-1 data elements
                                        //  in the root
                                        

    BPlusTree<T>* fix_shortage(int i);  //fix shortage in child i
    // and return the smallest key in this subtree
    BPlusTree<T>* get_smallest_node();
    void get_smallest(T& entry);      //entry := leftmost leaf
    void get_biggest(T& entry);       //entry := rightmost leaf
    void remove_biggest(T& entry);    //remove the biggest child of tree->entry
    void transfer_left(int i);        //transfer one element LEFT from child i
    void transfer_right(int i);       //transfer one element RIGHT from child i
    BPlusTree<T> *merge_with_next_subset(int i); //merge subset i with  i+1

};

//More iterator funcs 

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::begin(){
    BPlusTree<T>::Iterator returnIter(this, 0); 
    if(is_leaf()){
        return returnIter; 
    }
    else{
        returnIter = subset[0]->begin(); //go to left most child
    }
    return returnIter; 
}


template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::end(){
   BPlusTree<T>::Iterator nullIter(nullptr, 0); 
   return nullIter; 
}

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::find(const T& key){
BPlusTree<T>::Iterator nullIter; 
   for(BPlusTree<T>::Iterator beg = begin(); beg != end(); beg++){
    if(*beg == key){
        BPlusTree<T>::Iterator foundIter (beg.it, beg.key_ptr); 
        return foundIter; 
    }
   }
   return nullIter; 
}     
//return an iterator to this key. NULL if not there.

//20 21 22 22
template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::lower_bound(const T& key){ //assuming we are trying to find the previous ???
    BPlusTree<T>::Iterator found; 

    for(BPlusTree<T>::Iterator iter = begin(); iter != end(); iter++){
        if(*iter > key || *iter == key){ 
            found = iter;
            return found; 
        }
    }
    return end();
    //return found; 
}
//return first that goes NOT BEFORE
// key entry or next if does not
// exist: >= entry

template <typename T>
typename BPlusTree<T>::Iterator BPlusTree<T>::upper_bound(const T& key){//assuming that this key is in there? prob not
     BPlusTree<T>::Iterator found; 

    for(BPlusTree<T>::Iterator iter = begin(); iter != end(); iter++){ //what if we are the greatest?? --> end 
        if(*iter > key){//the first time we find something greater
            found = iter; 
            return found; 
        }
    }
    return end(); 
}  //return first that goes AFTER key
                                        //exist or not, the next entry  >entry

template <typename T>
BPlusTree<T>::BPlusTree(bool dups){
    next = nullptr;
    data_count = 0; 
    child_count = 0; 
    dups_ok = dups; 
    //cout<<"DUPS ALLOWED:?"<<boolalpha<<dups_ok<<endl; 
    //cout<<"dups allowed?: "<<boolalpha<<dups<<endl; 
}

template <typename T>
BPlusTree<T>::BPlusTree(T *a, int size, bool dups){ //making a btree
    next = nullptr; 
    dups_ok = dups; 
    //cout<<"DUPS ALLOWED:?"<<boolalpha<<dups_ok<<endl; 
    data_count = 0; 
    child_count = 0; 
    for(int i = 0; i < size; i++){
        insert(a[i]); 
    }
}

//big three:

template <typename T>
BPlusTree<T>::BPlusTree(const BPlusTree<T>& other){//copy ctor
    child_count = 0; 
    data_count = 0; 
    copy_tree(other); 
    dups_ok = other.dups_ok; 
}

template <typename T>
BPlusTree<T>::~BPlusTree(){
    clear_tree(); 
}


template <typename T>
BPlusTree<T>& BPlusTree<T>::operator =(const BPlusTree<T>& RHS){
    if(this == &RHS){
        return *this; 
    }

    clear_tree(); 
    copy_tree(RHS); 
    dups_ok = RHS.dups_ok; 
    return *this; 
}

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other){
    BPlusTree<T>* last = nullptr; 
    copy_tree(other, last);
}//copy other into this object

template <typename T>
void BPlusTree<T>::copy_tree(const BPlusTree<T>& other, BPlusTree<T>*& last_node){ //hmm oh our last node?? that we update
    copy_array(data, other.data, data_count, other.data_count); //copying other data 
    child_count = other.child_count;
    for(int i = 0; i < other.child_count; i++){//if other is a leaf then there is nothing else to copy
        BPlusTree<T>* copyChild = new BPlusTree<T>; 
        subset[i] = copyChild;
        subset[i]->copy_tree(*other.subset[i], last_node); 
    }
   
   if(other.is_leaf()){
    if(last_node){
         last_node->next = this; 
    }
       
    last_node = this; 
   }
   /*
    copy_array(data, other.data, data_count, other.data_count); //copying other data 
    child_count = other.child_count;
    for(int i = 0; i < other.child_count; i++){//if other is a leaf then there is nothing else to copy
        BPlusTree<T>* copyChild = new BPlusTree<T>(dups_ok); 
        subset[i] = copyChild;
        if(last_node && last_node->is_leaf()){
            last_node->next = subset[i]; 
        } 
        if(other.subset[i]->is_leaf())
            last_node = subset[i]; 
        subset[i]->copy_tree(*other.subset[i], last_node); 
    }*/
}


//insert element functions
template <typename T>
void BPlusTree<T>::loose_insert(const T& entry){
    int insertIndex = first_ge(data, data_count, entry);
    if(is_leaf()){ //if we finally reached leaf, insert //still want to insert in leaf, even in BPlusTree
        ordered_insert(data, data_count, entry); //should update next in fix_excess 
        return;  
    }

    subset[insertIndex]->loose_insert(entry);
    BPlusTree<T>* fatChild = subset[insertIndex]; //possibly fat child //it has to be the subset at the insertedIndex whos fat 
    if(fatChild->data_count > MAXIMUM){//we are in excess 
        fix_excess(insertIndex); 
    }
}  //allows MAXIMUM+1 data elements in the root

template <typename T>
void BPlusTree<T>::fix_excess(int fatIndex){
    BPlusTree<T>* fat = subset[fatIndex]; 
    T attach;
    BPlusTree<T>* right = new BPlusTree<T>(dups_ok); 
    //attach to parent
    delete_item(fat->data, MAXIMUM/2, fat->data_count, attach); //deleting from fat  

    split(fat->data, fat->data_count, right->data, right->data_count);
    split(fat->subset, fat->child_count, right->subset, right->child_count); 

    ordered_insert(data, data_count, attach);  //attaching to parent 

    insert_item(subset, fatIndex + 1, child_count, right); //and then insert our new child into data
   
    if(fat->is_leaf()){
        ordered_insert(right->data, right->data_count, attach); 
        right->next = fat->next; 
        fat->next = right;
    }
}             //fix excess in child i 


template <typename T>
void BPlusTree<T>::insert(const T& entry){ 
    T* found = find_ptr(entry);  
    //cout<<"duops?: "<<boolalpha<<dups_ok<<endl;
    if(found && dups_ok){//update 
        *found = *found + entry; //for multimap it should add to vec
        return; 
    }
   
    loose_insert(entry);

    if(data_count > MAXIMUM){//if the root is in excess, //fixing root excess 
        T attach; 
        BPlusTree<T>* copy = new BPlusTree<T>(dups_ok); 

        copy_array(copy->data, data, copy->data_count, data_count); //copying data into copy 
        copy_array(copy->subset, subset, copy->child_count, child_count); //copying children into copy 

        //now set ourself to 
        data_count = 0; 
        child_count = 1; 
        subset[0] = copy; 
        fix_excess(0); //0 being fat index
    }
}//insert entry into the tree



template <typename T>
BPlusTree<T>* BPlusTree<T>::get_smallest_node(){
    BPlusTree<T>* returnThis(dups_ok); 
     if(is_leaf()){
        return this; 
    }

    returnThis = subset[0]->get_smallest_node();  
    return returnThis; 
}

template <typename T>
void BPlusTree<T>::get_smallest(T& entry){
    //keep going left 
    if(is_leaf()){
        entry = data[0];
        return; 
    }

    subset[0]->get_smallest(entry);  
}      
//entry := leftmost leaf

template <typename T>
void BPlusTree<T>::get_biggest(T& entry){
    if(is_leaf()){
        entry = data[data_count - 1]; 
        return; 
    }
    subset[child_count - 1]->get_biggest(entry); 
}       //entry := rightmost leaf

template <typename T>
void BPlusTree<T>::remove_biggest(T& entry){ //hm?
     if(!is_leaf()){
        subset[child_count - 1]->remove_biggest(entry); //go right again
        if(!is_leaf() && subset[child_count -1]->data_count < MINIMUM){
            fix_shortage(child_count - 1);
        }
    }
    else{//now we are leaf 
        delete_item(data, data_count - 1, data_count, entry); //delete right most and put it into entry 
    }
}   //remove the biggest child of tree->entry

template <typename T>
void BPlusTree<T>::transfer_left(int index){ //assuming this is rotate left //stealing from right 
    //assuming for the rotates nothing changes about the next ptr 
    T deleted;
    BPlusTree<T>* deletedChild(dups_ok); 
    BPlusTree<T>* shortChild = subset[index];  //rotate to 
    BPlusTree<T>* right = subset[index + 1]; //borrowing from right

    if(!shortChild->is_leaf()){ 
        delete_item(data, index, data_count, deleted); //deleting from parent 
        ordered_insert(shortChild->data, shortChild->data_count, deleted);
        delete_item(right->data, 0,right->data_count, deleted); 
        ordered_insert(data, data_count, deleted); 

        if(!right->is_leaf()){
         delete_item(right->subset, 0, right->child_count, deletedChild); 
         insert_item(shortChild->subset, shortChild->data_count, shortChild->child_count, deletedChild); //getting from right so should be larger 
        }
    }
    else{
        delete_item(right->data, 0, right->data_count, deleted); 
        ordered_insert(shortChild->data, shortChild->data_count, deleted); 
        data[index] = right->data[0]; 
    }
} //transfer one element LEFT from child i

template <typename T>
void BPlusTree<T>::transfer_right(int index){//assuming this is rotate right //stealing from left
    //when we are at leaves, do 
    T deleted; 
    BPlusTree<T>* deletedChild(dups_ok); 
    BPlusTree<T>* shortChild = subset[index]; 
    BPlusTree<T>* left = subset[index - 1];

    if(!shortChild->is_leaf()){
        delete_item(data, index - 1, data_count, deleted); //might just do a swap here hmm //was 0 before, what if short index is 0 will never be
        ordered_insert(shortChild->data, shortChild->data_count, deleted); 
        delete_item(left->data, left->data_count - 1, left->data_count, deleted); 
        ordered_insert(data, data_count, deleted); 

        //steal child
        if(!left->is_leaf()){
            delete_item(left->subset, left->child_count - 1, left->child_count, deletedChild); //stealing right most child
            insert_item(shortChild->subset, 0, shortChild->child_count, deletedChild); 
        }
    }
    else{
        delete_item(left->data, left->data_count - 1, left->data_count, deleted); 
        data[index - 1] = deleted; 
        ordered_insert(shortChild->data, shortChild->data_count, deleted); 
    }
} //transfer one element RIGHT from child i

template <typename T>
BPlusTree<T>* BPlusTree<T>::merge_with_next_subset(int index){
    //doesn't seem like I need to update the next ptr

    BPlusTree<T>* deleted(dups_ok); 
    BPlusTree<T>* merging = subset[index]; 
    BPlusTree<T>* right = subset[index + 1];

    merge(merging->data, merging->data_count, right->data, right->data_count); 
    merge(merging->subset, merging->child_count, right->subset, right->child_count);
    delete_item(subset, index+1, child_count, deleted);

    if(merging->is_leaf())
        merging->next = deleted; 
    deleted->data_count = 0; 
    deleted->child_count = 0; 
    delete deleted;
    deleted = nullptr;
    
    return merging; //returning the short child?
    //needs to return something?
}//merge subset i with  i+1


template <typename T>
BPlusTree<T>* BPlusTree<T>::fix_shortage(int shortIndex){ //we return what we just removed, 
    T deleted; 
    BPlusTree<T>* left = nullptr; 
    BPlusTree<T>* right = nullptr; 
    BPlusTree<T>* shortChild = subset[shortIndex]; //data_count should be 0 in this case
    BPlusTree<T>* returned = nullptr; 
    if(shortIndex != child_count - 1)
        right = subset[shortIndex + 1]; 
    if(shortIndex != 0)
        left = subset[shortIndex - 1];
    bool STEAL_RIGHT = (right && right->data_count > MINIMUM), STEAL_LEFT = left && left->data_count > MINIMUM, BEGIN_CASE = (shortIndex == 0); 

    if(STEAL_RIGHT){//can steal from right
        transfer_left(shortIndex); 
        returned = shortChild;    
    }
    else if(STEAL_LEFT){//can steal from left
        transfer_right(shortIndex); 
        returned = shortChild; 
    }
    else if(BEGIN_CASE){//begin case
        T small;
        delete_item(data, shortIndex, data_count, deleted); //delete begin
        if(!shortChild->is_leaf())
            ordered_insert(shortChild->data, shortChild->data_count, deleted); 
        returned = merge_with_next_subset(shortIndex); 
    }
    else{
        delete_item(data, shortIndex - 1, data_count, deleted); //delete last //first less than equal
       if(!shortChild->is_leaf()) //if we are not leaf, then isnert to short child, else don't 
            ordered_insert(shortChild->data, shortChild->data_count, deleted);
        returned = merge_with_next_subset(shortIndex - 1);
    }
   return returned; 
}  //fix shortage in child i
// and return the smallest key in this subtree


//remove element functions:
template <typename T>
void BPlusTree<T>::loose_remove(const T& entry){
    int goToIndex = first_ge(data, data_count, entry); 
    BPlusTree<T>* returned; 

    if(goToIndex < data_count && data[goToIndex] == entry){//found 
        T temp;  
        //deleting breadcrumbs first
        if(!is_leaf()){ //of we are not leaf, we need to go to breadcrumbs and remove
            T small;  
            BPlusTree<T>* right = subset[goToIndex + 1]; 
            right->loose_remove(entry); 
           
            if(!is_leaf() && subset[goToIndex + 1]->data_count < MINIMUM){//cause we can land in a deleted place? 
                returned = fix_shortage(goToIndex + 1);
            }

            bool replaced = false; 

            if(goToIndex < data_count && data[goToIndex] != entry && !replaced){//find entry. which should be in children
               // cout<<"search in origin\n"; 
                for(int i = 0; i < data_count; i++){//search ourselves
                    if(data[i] == entry){
                       // cout<<"found in origin\n";
                        T small; 
                        right = subset[i + 1]; 
                        right->get_smallest(small); 
                       // cout<<"replacing: "<<data[i]<<" with "<<small<<endl;
                        data[i] = small;
                        replaced = true; 
                        break; 
                    }
                }
                
            }
            
            
            for(int i = 0; i < child_count && !replaced; i++){
                    for(int n = 0; n < subset[i]->data_count; n++){
                        if(subset[i]->data[n] == entry){
                        T small; 
                        right = subset[i]->subset[n + 1];  
                        right->get_smallest(small); 
                        subset[i]->data[n] = small; 
                        break; 
                    }
                }
                }
        
            if(!replaced && data[goToIndex] == entry && goToIndex < data_count ){
                T small; 
                right = subset[goToIndex + 1]; 
                right->get_smallest(small); 
                data[goToIndex] = small; 
            }
        }
        else{
            //cout<<"deleting: "<<data[goToIndex]<<endl; 
            delete_item(data, goToIndex, data_count, temp); 
        }

    }
    else if(is_leaf()){ //leaf and not found
        return;
    }
    else{
        subset[goToIndex]->loose_remove(entry);
    }

    if(!is_leaf() && subset[goToIndex]->data_count < MINIMUM){
        fix_shortage(goToIndex); //goToIndex should be short index
    }   

}//allows MINIMUM-1 data elements
                                    //  in the root

template <typename T>
void BPlusTree<T>::remove(const T& entry){
    if(empty()){
        return; //nothing to remove
    }

    loose_remove(entry); 
    BPlusTree<T>* child = subset[0];  
    if(data_count == 0 && !is_leaf()){//if we ourself is short  
        cout<<"root short\n";
        child_count = 0;
        copy_array(data, child->data, data_count, child->data_count);
        copy_array(subset, child->subset, child_count, child->child_count); 

        child->data_count = 0; 
        child->child_count = 0; 
        delete child; 
        child = nullptr; 
    }
}//remove entry from the tree

template <typename T>
void BPlusTree<T>::clear_tree(){ //don't think we need to do anything to next 
    for(int i = 0; i < child_count; i++){ //meaning there is some child to clear
        if(!is_leaf())
            subset[i]->clear_tree();  //we go to child and clear it 
        delete subset[i]; 
        subset[i] = nullptr; //now setting it to null when we get out cause it was deleted. just for sanity 
    }
    data_count = 0; 
    child_count = 0;
}    
//clear this object (delete all nodes etc.)

template <typename T>
bool BPlusTree<T>::contains(const T& entry) const{
    int index = first_ge(data, data_count, entry); 
    bool foundPtr = false; 
    //cout<<"index: "<< index <<" path: "<<data[index]<<endl; 
    if(index < data_count && data[index] == entry){ //go right --> else entry must be kess so we go left = 
        ///cout<<"found: "<<entry<<endl; 
        return true; 
    }
    else if(is_leaf()){
        return false; //no children and not found 
    }
    else{
       foundPtr = subset[index]->contains(entry); //go left or right depending on what index
    }
    return foundPtr;   
} 

//true if entry can be found

template <typename T>
T& BPlusTree<T>::get(const T& entry){ //must test
    T* found = find_ptr(entry);

    if(found){//if found
        return *found;    
    }
    else{//not found, insert 
        //cout<<"not found\n";
        insert(entry); //insert entry 
        found = find_ptr(entry); 
    }
    return *found; 
}//return a reference to entry

template <typename T>
const T& BPlusTree<T>::get(const T& entry) const{ //what if not found??
    int index = first_ge(data, data_count, entry); 
    T* found; 

    if(index < data_count && data[index] == entry && is_leaf()){ //go right --> else entry must be kess so we go left =
        return *(data + index); //no we don't want this 
    }
    else if(index < data_count && data[index] == entry){
       found = &subset[index + 1]->get(entry); 
    }
    else if(is_leaf()){
        return T(); //no children and not found 
    }
    else{
       found = &subset[index]->get(entry); //go left or right depending on what index
    }
    return *found; 
}//return a reference to entry

template <typename T>
T& BPlusTree<T>::get_existing(const T& entry){ //assuming is in here
    T* found = find_ptr(entry); 
    assert(found); 
    return *found; 
}//return a reference to entry


template <typename T>
int BPlusTree<T>::size() const{//do we include the duplicates? //curr btree code includes dups 10 in node, 10 in leafs
    int size = data_count; //count ourself
    for(int i = 0; i < child_count; i++){
        if(subset[i])
            size += subset[i]->size(); 
    }
    return size;
}        

//count the number of elements

template <typename T>
bool BPlusTree<T>::empty() const{
    return (data_count == 0 && child_count == 0); 
}
//true if the tree is empty


template <typename T>
void BPlusTree<T>::print_tree(int level, ostream &outs) const{
    for(int i = data_count; i >= 0; i--){//because start from rightmost 
        if(i!= -1 && !is_leaf())
            subset[i]->print_tree(level + 1, outs); //child will always be one more than data count  
        if(i!= 0){
            outs<<setw(6 * level)<<"["<<data[i - 1]<<"]"<<"dc: "<<data_count<<"cc: "<<child_count; //<<" a: "<<this; 
            //outs<<"next?: "<<boolalpha<<(next == nullptr);
            //if(next)
                //outs<<"next: "<<next->data[0];  
            outs<<endl; 
        }
    }
}

template <typename T>
bool BPlusTree<T>::is_valid(){
    return true; 
}

template <typename T>
string BPlusTree<T>::in_order(){
    string inOrder = ""; 
    for(int i = 0; i <= data_count; i++){
        if(!is_leaf())
            inOrder += subset[i]->in_order();
        if(i < data_count) 
            inOrder+= to_string(data[i]) + "|"; 
    }
    return inOrder; 
}



template <typename T>
string BPlusTree<T>::post_order(){//print children, then print root
    string postOrder = ""; 
    for(int i = 0; i < data_count; i++){ 
        if(!is_leaf()){
            if(i == 0){
                postOrder += subset[0]->post_order(); 
                postOrder += subset[1]->post_order(); 
            }
            else{
                 for(int n = i + 1; n < child_count; n++){ 
                    postOrder += subset[n]->post_order(); // go get the children
                }
            }
        } 
        postOrder += to_string(data[i]) + "|"; //add all children
    }
    return postOrder; 
}



template <typename T>
string BPlusTree<T>::pre_order(){
    string preOrder = ""; 
    for(int i = 0; i <= data_count; i++){
        if(i < data_count){
            preOrder += to_string(data[i]) + "|";  
        }
        if(!is_leaf())
            preOrder += subset[i]->pre_order();     
    }
    return preOrder;
}


//PRIVATE FUNCTIONS 
template <typename T>
T* BPlusTree<T>::find_ptr(const T& entry){ //find should be fin
    int index = first_ge(data, data_count, entry);
    T* foundPtr = nullptr; 

         
    if(index < data_count && data[index] == entry && is_leaf()){ //go right --> else entry must be kess so we go left =
        foundPtr = (data + index); //no we don't want this 
        return foundPtr; 
    }
    else if(index < data_count && data[index] == entry){
       foundPtr = subset[index + 1]->find_ptr(entry); 
    }
    else if(is_leaf()){
        return nullptr; //no children and not found 
    }
    else{
       foundPtr = subset[index]->find_ptr(entry); //go left or right depending on what index
    }
    return foundPtr; 
}
//return a pointer to this key. // NULL if not there.


//update next
#endif
