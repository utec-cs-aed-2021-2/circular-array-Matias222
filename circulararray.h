#include <iostream>

using namespace std;


template <class T>
class CircularArray{
    private:
        T *array;
        int capacity,sz;
        int back, front;

    public:
        CircularArray(){
            capacity=1,sz=0,back=0,front=1;
            array  = new T[capacity];
        }
        CircularArray(int _capacity){
            sz = 0,capacity=_capacity,back=0,front=0;
            array = new T[capacity];
        }
        T &operator[](int ind){return array[(ind+back)%capacity];}

        void push_front(T data){
            if(sz+1>capacity) resize();
            if(back>0){
                array[back-1]=data;
                back--;
            }else{
                T temp=array[0];
                for(int i=1;i<sz+1;i++){
                    T temp1=array[i];
                    array[i]=temp;
                    temp=temp1;
                }
                array[0]=data;
                front++;
            }
            sz++;
        }
        void push_back(T data){    
            if(sz+1>capacity){resize();}
            array[front%capacity]=data;
            front++;sz++;
        }

        int size(){return sz;}
        
        void insert(T data, int pos){
            if(sz+1>capacity) resize();
            else if(sz==0) sz=1;
            T temp=array[(pos+back)%capacity];
            array[pos]=data;
            for(int i=pos+1;i<sz+1;i++){
                T temp1=array[(i+back)%capacity];
                array[(i+back)%capacity]=temp;
                temp=temp1;
            }
            sz++;front++;
        }
        virtual ~CircularArray();
        T pop_front(){
            T temp=array[back];
            sz--;back++;
            return temp;
        }
        T pop_back(){
            T temp=array[front%capacity];
            sz--;front--;
            return temp;
        }
        bool is_full(){return sz==capacity;}
        bool is_empty(){ return sz==0;}
        void clear(){
            delete []array;
            sz=0;capacity=1;
            array  = new T[1];
        }          
        void swap(T *xp, T *yp){ 
            T temp = *xp; 
            *xp = *yp; 
            *yp = temp; 
        } 
        void sort(){
            int i, j; 
            for (i = 0; i < sz-1; i++){    
                for (j = 0; j < sz-i-1; j++){ 
                    if (array[(j+back)%capacity] > array[(j+back+1)%capacity])  swap(&array[(j+back)%capacity], &array[(back+j+1)%capacity]); 
                }
            }
        }
        bool is_sorted(){
            for(int i=0;i+1<sz;i++){
                if(array[(back+i)%capacity]>array[(back+i+1)%capacity]) return 0;
            }
            return 1;
        }
        void reverse(){
            int start=back,end=front-1;
            while (start < end){
                T temp = array[start%capacity];
                array[start%capacity] = array[end%capacity];
                array[end%capacity] = temp;
                start++;
                end--;
            }
        }
        string to_string(string sep=" ");
        void resize(){
            T* w  = new T[capacity * 2];
            int  j=0;
            for(int i = back ; i<front ;i++) w[j] = array[i%capacity],j++;
            delete [] array; 
            array = w; 
            capacity *= 2; 
            back=0,front=sz;
        }
    private:
        int next(int);
        int prev(int);
};

template <class T>
CircularArray<T>::~CircularArray(){delete[] array;}

template <class T>
int CircularArray<T>::prev(int index){
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index){
    return (index + 1) % capacity;
}

template <class T>
string CircularArray<T>::to_string(string sep){
    string result = ""; 
    for (int i = 0; i < size(); i++)
        result += std::to_string((*this)[i]) + sep;
    return result;    
}


