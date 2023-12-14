#ifndef MMAP_H 
#define MMAP_H 

#include "../../includes/bplustree/bplustree.h"
#include "../../includes/bplustree/mpair.h"
#include <vector>

template <typename K, typename V>
class MMap
{
public:
    typedef BPlusTree<MPair<K, V> > map_base;
    class Iterator{
    public:
        friend class MMap;
        Iterator(){
            //_it = mmap.begin(); 
            _it = nullptr; 
            //dups ok is true for mmap
        }

        Iterator(typename map_base::Iterator it){
            _it = it; 
        }

        Iterator operator ++(int unused){
            //Iterator::BPlusTree<MPair<K, V>> it; 
            _it++;
            //cout<<"it: "<<*_it<<endl; 
            return _it; 
        }

        Iterator operator ++(){
            _it++; 
            return _it; 
        }
        
        MPair<K, V> operator *(){
            return *_it; 
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

    MMap(){
        mmap = BPlusTree<MPair<K,V>>(true); //dups ok 
    }

//  Iterators
    Iterator begin(){
       // cout<<"beg: "<<*mmap.begin()<<endl; 
        return mmap.begin();
    }

    Iterator end(){
        return mmap.end(); 
    }

//  Capacity
    int size() const{
        return mmap.size(); 
    }

    bool empty() const{
        return mmap.empty(); 
    }

//  Element Access
    const vector<V>& operator[](const K& key) const{
        MPair<K,V> getThis(key); 
        return mmap.get(getThis).value_list; 
        //return found.value_list; 
    }

    vector<V>& operator[](const K& key){
        MPair<K,V> getThis(key); 
        return mmap.get(getThis).value_list; 
        //return found.value_list; 
    }

//  Modifiers
    void insert(const K& k, const V& v){
        MPair<K,V> insertPair(k,v); 
        mmap.insert(insertPair); 
    }

    void erase(const K& key){
        
    }

    void clear(){
        mmap.clear_tree(); 
    }

//  Operations:
    bool contains(const K& key) const{
        MPair<K,V> findThis(key);
        return mmap.contains(findThis); 
    }

    vector<V>& get(const K& key){
        //cout<<"get\n"; 
        MPair<K,V> getThis(key);
        return mmap.get(getThis).value_list; 
    }

    Iterator find(const K& key){
        MPair<K,V> findThis(key);
        return mmap.find(findThis); 
    }

    
    int count(const K& key){ //count of what??
        return 0; 
    }
    // I have not writtent hese yet, but we will need them:
    //    int count(const K& key);
    //    lower_bound
    //    upper_bound
    //    equal_range:

    
    Iterator lower_bound(const K& key){
        MPair<K,V> bound(key);
        return mmap.lower_bound(bound); 
    }

    Iterator upper_bound(const K& key){
        MPair<K,V> bound(key);
        return mmap.upper_bound(bound); 
    }


    const V& at(const K& key) const{
        MPair<K,V> findThis(key);
        return mmap.get(findThis).value_list[0]; //idk?? first item of the vector???
        //return found.value_list; 
    } 

    bool is_valid(){
        return true;
    }

    friend ostream& operator<<(ostream& outs, const MMap<K, V>& print_me){
        outs<<print_me.mmap<<endl;
        return outs;
    }

    void print_lookup(){
        for(MMap<string,string>::Iterator beg = begin(); beg != end(); beg++){
            cout<<*beg<<endl; 
        }
    }

private:
    BPlusTree<MPair<K, V> > mmap;
};

#endif  