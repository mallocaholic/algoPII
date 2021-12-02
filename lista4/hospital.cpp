#include <bits/stdc++.h>

class Hospital{
    public:
    int id;
    int casos;
    int new_index;
};

void swapy(Hospital *arr, int x, int y){
    int temp1 = arr[x].id;
    arr[x].id = arr[y].id;
    arr[y].id = temp1;
    
    int temp2 = arr[x].casos;
    arr[x].casos = arr[y].casos; 
    arr[y].casos = temp2;

    arr[arr[x].id].new_index = x;
    arr[arr[y].id].new_index = y;
}


Hospital *bubble_up(Hospital *arr, int i){

    int p = floor((i-1)/2);
    while( i > 0 && (arr[i].casos > arr[p].casos || (arr[i].casos == arr[p].casos && arr[i].id >= arr[p].id)) ){
       swapy(arr, i, p);
       i = floor((i-1)/2);
       p = floor((i-1)/2); 
    } 
       
    return arr;
}


Hospital *bubble_down(Hospital *arr, int p, int size){

    int l = 2*p+1, 
        r = 2*p+2, 
        m = p;

    if(l < size)
        if( arr[l].casos > arr[m].casos || ((arr[l].casos == arr[m].casos && arr[l].id >= arr[m].id)) )
            m = l;
    if(r < size)
        if( arr[r].casos > arr[m].casos || ((arr[r].casos == arr[m].casos && arr[r].id >= arr[m].id)) )
            m = r;

    if(m != p){
        swapy(arr, m, p);
        return bubble_down(arr, m, size);
    }
       
    return arr;
}

void active_heap(Hospital *arr, int p, int size, int *total){
    
    if(p < size) *total += arr[p].casos;
    
    int l = 2*p+1, 
        r = 2*p+2;

    if(l < size)
        active_heap(arr, l, size, total);
    if(r < size)
        active_heap(arr, r, size, total);

}


void build_heap(Hospital *arr, int n)
{
    int p = (n / 2) - 1;
    
    for (int i = p; i >= 0; i--) {
        bubble_down(arr, i, n);
    }
}

int heap_search(Hospital *arr, int size, int i, int p){
    int l = 2*p + 1,
        r = 2*p + 2;
    if( arr[p].id == i )
        return p;

    if( l < size && i >= arr[l].id )
        return heap_search(arr, size, i, l);

    if( r < size && i >= arr[r].id )
        return heap_search(arr, size, i, r); 

    return -1;
}



Hospital *insert_hosp(int *size, int *N, Hospital *arr, int i, int c){

    int new_size = *size + 1;
    if(i >= *N - 1){
        *N *= 2;
        Hospital *new_arr = new Hospital[*N];   
        for(int i = 0; i < *N; i++){
            new_arr[i] = arr[i];
        }
        
        new_arr[*size].casos = c;
        new_arr[*size].id = i;
        new_arr[i].new_index = *size;

        bubble_up(new_arr, *size);
        *size = new_size;
        //delete[] arr;
        return new_arr;
    }

    arr[*size].casos = c;
    arr[*size].id = i;
    arr[i].new_index = *size;

    bubble_up(arr, *size);
    *size = new_size;

    return arr;
}

Hospital *delete_hosp(int *size, Hospital *arr, int id, int i){

    int new_size = *size - 1; 
    
    arr[id].casos = -1;
    arr[id].id = -1;
    swapy(arr, id, new_size);
    //std::cout << "TROCANDO " << id << "COM " << new_size << std::endl;
    *size = new_size;
    int index = arr[id].id;
    bubble_up(arr, arr[index].new_index);
    bubble_down(arr, arr[index].new_index, *size);
    //build_heap(arr, *size);
    return arr;
}

int max(int x, int y){
    
    
    if(x > y) return x;
    
    return y;

}

void pay_heap(Hospital *arr, int size, int *R){
    
    int tam = size - 1;

    while((*R) > 0 && size > 0){
        int diff = arr[0].casos - max(arr[1].casos, arr[2].casos);
        
        if(arr[0].casos == 0) break;

        if( (*R) - diff >= 0 && diff > 0 ){
            arr[0].casos -= diff;
            (*R) -= diff;
            bubble_down(arr, 0, size);
        } else {
            arr[0].casos--;
            (*R)--;
            bubble_down(arr, 0, size);
        }
    }
}

int main(){
    
    int N, N_heap;
    std::string action;
    std::cin >> N;
    N_heap = 2*N;
    Hospital *hosp = new Hospital[2*N];
    
    for(int i = 0; i < N; i++){\
        std::cin >> hosp[i].casos;
        hosp[i].id = i;
        hosp[i].new_index = i; 
    }

    //  ! teste

    //! teste

    build_heap(hosp, N);
    
    while( action != "END" ){

        if( action == "NEW" ){ 

            int i, c;
            std::cin >> i >> c;
            if(i == 17) 
                int a = 17;

            hosp = insert_hosp(&N, &N_heap, hosp, i, c);
            //build_heap(hosp, N);
            if(N > 0)
                std::cout << hosp[0].id << " " << hosp[0].casos << std::endl;
            else 
                std::cout << "-1 -1" << std::endl; 

        } 
        else if( action == "DEL" ){     

            int i;
            std::cin >> i;   

            int index = hosp[i].new_index;
            //std::cout << "Deletando o hospital" << hosp[index].id << std::endl;
            hosp = delete_hosp(&N, hosp, index, i);
            
            //build_heap(hosp, N);
            if(N > 0)
                std::cout << hosp[0].id << " " << hosp[0].casos << std::endl;
            else 
                std::cout << "-1 -1" << std::endl; 

        } 
        else if( action == "IN" ){ 

            int i, c;
            std::cin >> i >> c;
            if(i == 23) 
                int a = 23;
            int index = hosp[i].new_index;

            hosp[index].casos += c;
            std::cout << hosp[index].casos << std::endl;
            bubble_up(hosp, index);
        } 
        else if( action == "OUT" ){ 
            int i, c;
            std::cin >> i >> c;

            if(i == 23) 
                int a = 23;

            int index = hosp[i].new_index;
            
            hosp[index].casos -= c;
            std::cout << hosp[index].casos << std::endl;
            bubble_down(hosp, index, N);
        } 
        else if( action == "PAY" ){
            int R, R_temp;
            std::cin >> R;
            R_temp = R; 

            pay_heap(hosp, N, &R);
            //build_heap(hosp, N);

            std::cout << R_temp - R << std::endl;
        }
        else if( action == "PR" ){ 
            for(int i = 0; i < N; i++){
                //std::cout << "[" << i << "]" << " Id: " << hosp[i].id << " casos:" << hosp[i].casos << std::endl;
                std::cout << "->OR[" << i << "]" << " Id: " << hosp[hosp[i].new_index].id << " casos:" << hosp[hosp[i].new_index].casos << std::endl;
            }
        } 
        std::cin >> action; 
    } 
    int total = 0;
    active_heap(hosp, 0, N, &total);
    std::cout << total << std::endl;
    return 0;  
}