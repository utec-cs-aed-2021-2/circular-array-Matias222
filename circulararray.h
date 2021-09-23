#include <iostream>
//#include "tester.h"
using namespace std;

template <class T>
class CircularArray{
private:
    T *array;
    int capacity;
    int l,r,sz;
public:
    CircularArray(int _capacity=0){
        this->array = new T[_capacity];
        capacity = _capacity;
        this->l = 0;
        this->r = -1;
        sz=0;
    }
    ~CircularArray(){delete[] array;}
    
    void resize() {
        if(capacity == 0){
            capacity = 100;
            T* temp = new T[capacity];
            array = temp;
        }else{
            T* temp = new T[capacity*2];
            int j=0;
            for (int i = l; i < l+sz; ++i) {
                temp[j] = array[i%capacity];
                j++;
            }
            l=0;r=sz-1;
            delete[] array;
            array = temp;
            capacity*=2;
        }
    }
    
    void push_front(T data){   
        if(sz+1>capacity) resize();
        l = prev(l);
        array[l] = data;
        sz++;
    }

    void push_back(T data){
        if(sz+1>capacity) resize();
        r = next(r);
        array[r] = data;
        sz++;
    }
    
    void insert(T data, int pos){
        T* temp = new T[sz+1];
        int j=0;
        temp[pos]=data;
        for (int i = l; i < l+sz; ++i) {
            if(j==pos) j++;
            temp[j] = array[i%capacity];
            j++;
        }
        l=0;r=sz;
        delete[] array;
        array=temp;
        capacity=sz+1;
        sz++;
    }

    T pop_front(){
        T aux= array[l];
        sz--;
        l = next(l);
        if(sz==0) resize();
        return aux;
    }
    T pop_back(){
        T aux= array[r];
        sz--;
        r = prev(r);
        if(sz==0) resize();
        return aux;
    }

    bool is_full(){return sz==capacity;}
    bool is_empty(){return sz==0;}
    
    void clear(){
        delete []array;
        sz=0,capacity=0,l=0,r=-1;
        array  = new T[0];
    }   

    int size(){return sz;}
    
    T& operator[](int index) {
        T real_pos = (l + index)%capacity;
        return array[real_pos];
    }

    void swap(T *xp, T *yp){ 
            T temp = *xp; 
            *xp = *yp; 
            *yp = temp; 
    } 
    void sort(){
        for (int i = 0; i < sz; i++){    
            for (int j = 0; j < sz-i-1; j++){ 
                if ((*this)[j] > (*this)[j+1])  swap(&(*this)[j], &(*this)[j+1]); 
            }
        }
    }
    bool is_sorted(){
        for(int i=0;i+1<sz;i++){
            if((*this)[i]>(*this)[i+1]) return 0;
        }
        return 1;
    }
    
    void reverse(){
        int start=0,end=sz-1;
        while (start < end){
            T temp = (*this)[start];
            (*this)[start] = (*this)[end];
            (*this)[end] = temp;
            start++;
            end--;
        }
    }
    
    string to_string(string sep=" ");

private:
    int next(int);
    int prev(int);
};

template <class T>
int CircularArray<T>::prev(int index){return (index == 0) ? capacity - 1 : index - 1;}

template <class T>
int CircularArray<T>::next(int index){return (index + 1) % capacity;}

template <class T>
string CircularArray<T>::to_string(string sep){
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}
