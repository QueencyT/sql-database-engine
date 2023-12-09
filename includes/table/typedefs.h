#ifndef TYPEDEF_H 
#define TYPEDEF_H 
#include "../../includes/bplustree/map.h"
#include "../../includes/bplustree/multimap.h"
#include "../../includes/queue/MyQueue.h"
#include <vector>
#include <queue> 

using namespace std; 

typedef Map<string,string> map_ss; 
typedef MMap<string,string> mmap_ss; 

typedef Map<string,long> map_sl;
typedef MMap<string,long> mmap_sl; 

typedef vector<string> vectorstr; 
typedef vector<long> vectorlong; 
typedef Queue<string> queuestr; 

#endif 