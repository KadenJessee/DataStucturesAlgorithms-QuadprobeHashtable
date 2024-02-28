#include "Hashtable.h"

int Hashtable::hash(int v) const{
   return v % capacity();
}
 
Hashtable::Hashtable()
{
    sz = 0;
    cpcity = 17;
    thresh = .65;
    this->htable = new int[cpcity];
    for(int i = 0; i  < cpcity; i++){
        htable[i] = -2;
    }
}

Hashtable::Hashtable(int capacity)
{
    sz = 0;
    cpcity = capacity;
    thresh = .65;
    this->htable = new int[cpcity];
    for(int i = 0; i  < cpcity; i++){
        htable[i] = -2;
    }
}

Hashtable::Hashtable(int capacity, double threshold)
{
    sz = 0;
    cpcity = capacity;
    thresh = threshold;
    this->htable = new int[cpcity];
    for(int i = 0; i  < cpcity; i++){
        htable[i] = -2;
    }
}

Hashtable::Hashtable(const Hashtable& other)
{
    //set protected variables
    sz = other.sz;
    cpcity = other.cpcity;
    thresh = other.thresh;
    htable = new int[cpcity];
    //loop through and insert
    for(int i = 0; i < cpcity; i++){
        htable[i] = other.htable[i];
    }
}

Hashtable& Hashtable::operator=(const Hashtable& other) {
    //same as copy, just clear and return *this
    clear();
    sz = 0;
    cpcity = other.cpcity;
    thresh = other.thresh;
    htable = new int[cpcity];
    for (int i = 0; i < other.sz; i++) {
        insert(other.htable[i]);
    }
    return *this;
}
//destructor
Hashtable::~Hashtable()
{
    delete[] htable;
}

//returns size
int Hashtable::size() const
{
return sz;
}

//returns cpcity
int Hashtable::capacity() const
{
return cpcity;
}
//returns threshold
double Hashtable::getLoadFactorThreshold() const
{
   return thresh;
}

//if sz == 0, then empty
bool Hashtable::empty() const
{
return sz == 0;
}

void Hashtable::insert(int value)
{
    double check = double(sz+1)/double(cpcity);
    if(check >= thresh){
        //create temp capacity
        int tempCpcity = cpcity;
        //create temp hash table
        int tempHtable[cpcity];
        //populate temp hash table
        for(int i = 0; i < tempCpcity; i++){
            tempHtable[i] = htable[i];
        }
        //get next capacity
        cpcity = nextPrime(tempCpcity * 2);
        //reset size to 0
        sz = 0;
        //clear memory
        delete[] htable;
        //create htable
        htable = new int[cpcity];
        //set values to -2
        for(int i = 0; i < cpcity; i++){
            htable[i] = -2;
        }
        //if it's not -2 or -1, insert
        for(int i = 0; i < tempCpcity; i++){
            if(tempHtable[i] != -2 && tempHtable[i] != -2){
                this->insert(tempHtable[i]);
            }
        }
    }
    //set variables for while loop
    int i = 0;
    int probed = 0;

    //get hash value for initial bucket
    int bucket = hash(value);
    //while probed < capacity
    while(probed < cpcity){
        //insert item in next empty bucket
        if(htable[bucket] == -2 || htable[bucket] == -1){
            htable[bucket] = value;
            sz++;
            return;
        }
        //increment i and bucket
        i += 1;
        bucket = hash(value + i * i);
        //increased probed
        probed = probed + 1;
    }
}


void Hashtable::remove(int value)
{
    //set variables for while loop
    int i = 0;
    int probed = 0;

    //has value to determine inital bucket
    int bucket = hash(value);

    //while not empty and probed < size
    while(htable[bucket] != -1 && probed < size()){
        //if value there and not empty, then remove
        if(htable[bucket] != -1 && htable[bucket] == value){
            htable[bucket] = -1;
            sz--;
            return;
        }
        //increment counters
        i += 1;
        bucket = hash(value + i * i);
        probed = probed + 1;
    }
}

bool Hashtable::contains(int value) const{
    //basically the same as remove, but we don't change the value
    int i = 0;
    int probed = 0;

    int bucket = hash(value);

    while(htable[bucket] != -2 && probed < cpcity){
        if(htable[bucket] > -1 && htable[bucket] == value){
            return true;
        }
        i += 1;
        bucket = hash(value + i * i);
        probed = probed + 1;
    }
    return false;
}

int Hashtable::indexOf(int value) const
{
    //get index and return
    for(int i = 0; i < cpcity; i++){
        if(htable[i] == value){
            return i;
        }
    }
   return -1;
}

void Hashtable::clear()
{
    //not sure about how to go about this
    for(int i = 0; i < cpcity; i++){
        htable[i] = -1;
    }
    sz = 0;
}

bool Hashtable::isPrime(int n){
    //test for 2 and 3
   if(n == 2 || n == 3){
       return true;
   }//if 1 or mod = 0 false
   if(n == 1 || n % 2 == 0){
       return false;
   }
   //start at 3, multiply until less than n
   for(int i = 3; i * i <= n; i += 2){
       //if mod = 0, return false
       if(n % i == 0){
           return false;
       }
   }
   //else true
   return true;
}

int Hashtable::nextPrime(int n){
    //initial case
    if(n <= 1){
        return 2;
    }
    //set found to false
    bool found = false;

    //while it is not found
    while(!found){
        //increment n
        n++;
        //if n is prime
        if(isPrime(n)){
            //out of loop
            found = true;
        }
    }
    //return the value
    return n;
}
