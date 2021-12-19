#include <bits/stdc++.h>

class Hospital {
public:
  int id;
  int casos;
  int new_index;
};

void swapy(Hospital *arr, int x, int y) {
  int temp1 = arr[x].id;
  arr[x].id = arr[y].id;
  arr[y].id = temp1;

  int temp2 = arr[x].casos;
  arr[x].casos = arr[y].casos;
  arr[y].casos = temp2;

  arr[arr[x].id].new_index = x;
  arr[arr[y].id].new_index = y;
}

Hospital *bubble_up(Hospital *arr, int i) {

  int p = floor((i - 1) / 2);
  while (i > 0 && arr[i].casos >= arr[p].casos) {
    swapy(arr, i, p);
    i = floor((i - 1) / 2);
    p = floor((i - 1) / 2);
  }

  return arr;
}

Hospital *bubble_down(Hospital *arr, int p, int size) {

  int l = 2 * p + 1, r = 2 * p + 2, m = p;

  if (l < size && arr[l].casos >= arr[m].casos)
    m = l;
  if (r < size && arr[r].casos >= arr[m].casos)
    m = r;

  if (m != p) {
    swapy(arr, m, p);
    return bubble_down(arr, m, size);
  }

  return arr;
}

void build_heap(Hospital *arr, int n) {
  int p = (n / 2) - 1;

  for (int i = p; i >= 0; i--) {
    bubble_down(arr, i, n);
  }
}

// int binarySearch_r(Hospital *arr, int l, int r, int x){

//     if(r >= l){
//         int mid = l - (l-r)/2;

//         if( arr[mid].id == x )
//             return mid;

//         else if( arr[mid].id < x )
//             return binarySearch_r( arr, mid+1, r, x);

//         else
//             return binarySearch_r( arr, l, mid-1, x );

//     }

//     return -1;

// }

int heap_search(Hospital *arr, int size, int i, int p) {
  int l = 2 * p + 1, r = 2 * p + 2;
  if (arr[p].id == i)
    return p;

  if (l < size && i >= arr[l].id)
    return heap_search(arr, size, i, l);

  if (r < size && i >= arr[r].id)
    return heap_search(arr, size, i, r);

  return -1;
}

Hospital *insert_hosp(int *size, int *N, Hospital *arr, int i, int c) {

  int new_size = *size + 1;
  if (new_size == *N - 1) {
    *N *= 2;
    Hospital *new_arr = new Hospital[*N];
    for (int i = 0; i < *size; i++) {
      new_arr[i] = arr[i];
    }

    new_arr[*size].casos = c;
    new_arr[*size].id = i;
    new_arr[i].new_index = *size;

    *size = new_size;
    // delete[] arr;
    return new_arr;
  }

  arr[*size].casos = c;
  arr[*size].id = i;
  arr[i].new_index = *size;

  bubble_up(arr, *size);
  *size = new_size;

  return arr;
}

int main() {

  int N, N_heap;
  std::string action;
  std::cin >> N;
  N_heap = 2 * N;
  Hospital *hosp = new Hospital[2 * N];

  for (int i = 0; i < N; i++) {
    std::cin >> hosp[i].casos;
    hosp[i].id = i;
    hosp[i].new_index = i;
  }

  //  ! teste

  //! teste

  build_heap(hosp, N);

  while (action != "END") {

    if (action == "NEW") {

      int i, c;
      std::cin >> i >> c;
      hosp = insert_hosp(&N, &N_heap, hosp, i, c);
      // build_heap(hosp, N);
      if (N > 0)
        std::cout << hosp[0].id << " " << hosp[0].casos << std::endl;
      else
        std::cout << "-1 -1" << std::endl;

    } else if (action == "DEL") {

      int i;
      std::cin >> i;

      int index = hosp[i].new_index;
      // std::cout << "Deletando o hospital" << hosp[index].id << std::endl;
      hosp = delete_hosp(&N, hosp, index, i);

      build_heap(hosp, N);
      if (N > 0)
        std::cout << hosp[0].id << " " << hosp[0].casos << std::endl;
      else
        std::cout << "-1 -1" << std::endl;

    } else if (action == "IN") {

      int i, c;
      std::cin >> i >> c;

      int index = hosp[i].new_index;

      hosp[index].casos += c;
      std::cout << hosp[index].casos << std::endl;
    } else if (action == "OUT") {
      int i, c;
      std::cin >> i >> c;

      int index = hosp[i].new_index;

      hosp[index].casos -= c;
      std::cout << hosp[index].casos << std::endl;
    } else if (action == "PAY") {
      int R;
      std::cin >> R;

    } else if (action == "PR") {
      for (int i = 0; i < 20; i++) {
        std::cout << "[" << i << "]"
                  << " Id: " << hosp[i].id << " casos:" << hosp[i].casos
                  << std::endl;
        std::cout << "->OR[" << i << "]"
                  << " Id: " << hosp[hosp[i].new_index].id
                  << " casos:" << hosp[hosp[i].new_index].casos << std::endl;
      }
    }
    std::cin >> action;
  }

  return 0;
}
