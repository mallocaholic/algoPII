#include <iostream>
#include <string>

#define SPACE " "
#define endl "\n"

int key(std::string _name){ // returning key 
    
    int key = 0;
    for(int i = 0; i < _name.length(); i++){
        key += _name[i] * i;
    }

    return key;
    
}

class _song{ // defining song class

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


    void add(_song new_song, bool print_out){ // adding song to bucket

        new_song.key = key(new_song.name) % max_capacity;

        while( bucket[new_song.key].key != -1 ){
            new_song.key++;
            if(new_song.key > max_capacity) new_song.key = new_song.key % max_capacity;
        }

        bucket[new_song.key] = new_song;

        if(print_out == true) std::cout << bucket[new_song.key].name << SPACE 
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

    _song_hashtable *resize(){

        factor = 100 * (float) ++size / (float) max_capacity;

        if(factor >= 50.0f){
            
            _song_hashtable *new_hash = new _song_hashtable(2*max_capacity+1);
            new_hash->size = size;

            for(int i = 0; i < max_capacity; i++) // coppying data
                if(bucket[i].key != -1) new_hash->add(bucket[i], false);
            
            delete this;
            return new_hash;

        } 
        
        else return this;

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
            _song new_song;
            std::cin >> new_song.name >> new_song.duration;
            
            hash->add(new_song, true);
            hash = hash->resize();

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