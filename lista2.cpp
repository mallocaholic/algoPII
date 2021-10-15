#include <iostream>
#include <string>

#define SPACE " "
#define endl "\n"
//Returning key 
int key(std::string _name){
    
    int key = 0;
    for(int i = 0; i < _name.length(); i++){
        key += _name[i] * i;
    }

    return key;
}

// Defining song class
class _song{

    public:
    int key, duration, lis_time;
    std::string name;

    _song(){

        name = " ";
        duration = 0;
        key = -1;   
        lis_time = 0;
        
    }

};

class _song_hashtable{ // defining hastable class
    
    private:
    _song *bucket;
    int max_capacity, size;
    float factor;
    
    public:
    _song_hashtable(int capacity){  // defining constructor to hashtable
        
        bucket = new _song[capacity]; // creating buckets
        max_capacity = capacity;
        size = 0;
        factor = 0.0f;
        
    }

    ~_song_hashtable(){
        delete[] bucket;
    }

    _song_hashtable *resize(){

        factor = (float) ++size / (float) max_capacity;

        if(factor >= 50){
            
            max_capacity = 2*max_capacity + 1;
            
            _song_hashtable *new_hash = new _song_hashtable(max_capacity);
            new_hash->size = size;

            for(int i = 0; i < max_capacity; i++) // coppying data
                new_hash->bucket[i] = bucket[i];

            this->~_song_hashtable();

            return new_hash;

        } 
        
        else return this;

    }

    void add(std::string _name, int duration){ // adding song to bucket

        _song new_song;
        new_song.name = _name;
        new_song.duration = duration;
        new_song.key = key(_name) % max_capacity;

        while( bucket[new_song.key].key != -1 ){
            new_song.key++;
            if(new_song.key > max_capacity) new_song.key = new_song.key % max_capacity;
        }

        bucket[new_song.key] = new_song;

        std::cout << bucket[new_song.key].name << SPACE 
                  << new_song.key << endl;

    }

    void play(std::string _name){

        int _key = key(_name) % max_capacity;

        while( bucket[_key].name != _name ){
            _key++;
            if(_key > max_capacity) _key = _key % max_capacity;
        }

        bucket[_key].lis_time += bucket[_key].duration;

        std::cout << bucket[_key].name << SPACE 
                  << bucket[_key].lis_time << endl;

    }

    void time_listened(std::string _name){
        
        int _key = key(_name) % max_capacity;

        while( bucket[_key].name != _name ){
            _key++;
            if(_key > max_capacity) _key = _key % max_capacity;
        }

        std::cout << bucket[_key].name << SPACE 
                  << bucket[_key].lis_time << endl;

    }

};

int main(){

    int initial_capacity, duration;
    std::string action, name;

    std::cin >> initial_capacity;
    std::cin >> action;

    _song_hashtable *hash = new _song_hashtable(initial_capacity); 
    
    while( action != "END" ){
        
        if( action == "ADD" ){

            std::cin >> name >> duration;
            hash->add(name, duration);
            hash->resize();

        }
        else if( action == "PLAY" ){

            std::cin >> name;
            hash->play(name);

        }
        else if( action == "TIME" ){
            
            std::cin >> name;
            hash->time_listened(name);

        }

        std::cin >> action;

    }
    
    delete hash;
    
    return 0;
}