#ifndef MAP_H 
#define MAP_H 

#include "../../includes/bplustree/pair.h"
#include "../../includes/bplustree/bplustree.h"

template <typename K, typename V>
class Map
{
public:
    typedef BPlusTree<Pair<K, V> > map_base;
    class Iterator{
    public:
        friend class Map;
        Iterator(){
            _it = nullptr;
            //_it = map.begin(); //default the iterator will be begin
            //BPlusTree<Pair<K, V>::Iterator will be returned by begin 
            //we want BPlusTree<Pair<K, V>>::Iterator
           
        }
        Iterator(typename map_base::Iterator it){
            _it = it; 
        }
        Iterator operator ++(int unused){ //hmmm
            _it++; 
            return _it; 
        }
        Iterator operator ++(){
            _it++; 
            return _it; 
        }

        Pair<K, V> operator *(){
            return *_it; //?
        }

        friend bool operator ==(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it == rhs._it); 
        }
        friend bool operator !=(const Iterator& lhs, const Iterator& rhs){
            return (lhs._it != rhs._it); 
        }

    private:
        typename map_base::Iterator _it;

    };

    Map(){
        key_count = 0;
    }
//  Iterators
    Iterator begin(){
        Iterator begIter = map.begin(); 
        return begIter; 
    }

    Iterator end(){
        Iterator nulliter = map.end(); 
        return nulliter; 
    }

//  Capacity
    int size() const{
        return map.size(); 
    }
    bool empty() const{
        return map.empty(); 
    }

//  Element Access
    V& operator[](const K& key){
        Pair<K,V> getThis(key); 
        return map.get(getThis).value; 
    }

    V& at(const K& key){
        //we want BPlusTree<Pair<K, V>>::Iterator
        Pair<K,V> getThis(key); 
        //Pair<K,V> foundPair = 
        return map.get_existing(getThis).value; 
        
    }

    const V& at(const K& key) const{
        Pair<K,V> getThis(key); 
        Pair<K,V> foundPair = map.get_existing(getThis); 
        return foundPair.value;  
    }


//  Modifiers
    void insert(const K& k, const V& v){
        Pair<K,V> insertPair(k,v); 
        map.insert(insertPair); 
        key_count++; 
    }
    void erase(const K& key){
        Pair<K,V> deleteThis(key); 
        map.remove(deleteThis); 
        key_count--; 
    }

    void clear(){
        map.clear_tree(); 
    }

    V get(const K& key){
         //we want BPlusTree<Pair<K, V>>::Iterator
        Pair<K,V> found = map.get(key); 
        return found.value; 
    }

//  Operations:
    Iterator find(const K& key){
        Pair<K,V> findThis(key); 
        return map.find(findThis);
    }
    bool contains(const Pair<K, V>& target) const{
        return map.contains(target); 
    }

    // I have not writtent hese yet, but we will need them:
    int count(const K& key){
        return 0; 
    }
    
    Iterator lower_bound(const K& key){
        Pair<K,V> bound(key);
        Iterator mIter = map.lower_bound(bound); 
        return mIter; 
    }

    Iterator upper_bound(const K& key){
        Pair<K,V> bound(key);
        Iterator mIter = map.upper_bound(bound); 
        return mIter; 
    }


    //    equal_range: //what is this? 

    bool is_valid(){
       // return map.is_valid();
       return true; 
    }

    friend ostream& operator<<(ostream& outs, const Map<K, V>& print_me){
        outs<<print_me.map<<endl;
        return outs;
    }

private:
    int key_count;
    BPlusTree<Pair<K, V> > map;
};

#endif 

