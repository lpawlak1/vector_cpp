#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "list.hpp"
#include "array_container.hpp"
#include "link_vector.hpp"

template<typename T> class vector : public list<T>, public array_container<T>{
public:
//own
    vector();
    vector(int initial_size);
    vector(int initial_size,float load_factor);
    vector(float load_factor);
    ~vector(){this -> clear();};

//list
    void insert(int index, T value) override;
    void push_back(T value) override;
    void push_front(T value) override ;
    T pop_front() override;
    T pop_back() override;
    T pop(int index) override;
    T operator[](int index) override;
//container
    bool clear() override;
protected:
//array_container
    T* rewrite_append(T value) override;
    T* rewrite(int size, int first_index) override;
};

//* private
template<typename T> T* vector<T>::rewrite_append(T a)
{
    int* tab =  this -> rewrite(array_container<T>::container_size_*2,0);
    this -> push_back(a);
    return tab;
}

template<typename T> T* vector<T>::rewrite(int new_size, int first_index){
    int* ret = new int[new_size];
    int j = 0;
    for (int i = first_index;i < new_size && i < container::size_;i++){
        ret[j] = array_container<T>::tab_[i];
        j+=1;
    }
    array_container<T>::container_size_ = new_size;
    container::size_ = j;
    delete [] array_container<T>::tab_;
    return ret;
}

//* public
template<typename T> vector<T>::vector(){
}
template<typename T> vector<T>::vector(int initial_size) : array_container<T>::array_container(initial_size){}
template<typename T> vector<T>::vector(int initial_size,float load_factor) : array_container<T>::array_container(initial_size,load_factor){}
template<typename T> vector<T>::vector(float load_factor) : array_container<T>::array_container(load_factor){}

template<typename T> T vector<T>::operator[](int index) {
    if (index >=0 && index <= container::size_){
        return array_container<T>::tab_[index];
    }
    else{
        throw 123;
    }
}
template<typename T> void vector<T>::push_back(T value){
    //todo load factor
    if (array_container<T>::container_size_ > container::size_)
    {
        array_container<T>::tab_[container::size_] = value;
        container::size_ += 1;
        return;
    }
    array_container<T>::tab_ = rewrite_append(value);
}

template<typename T> void vector<T>::push_front(T value){
    return insert(0,value);
}

template<typename T> void vector<T>::insert(int index,T value){
    if (index >= 0 && index < container::size_){
        int i = index;
        int temp = value;
        int temp2;
        while(i<container::size_){
            temp2 = array_container<T>::tab_[i];
            array_container<T>::tab_[i] = temp;
            temp = temp2;
            i+=1;
        }
        push_back(temp);
    }
    else if (index == 0 && container::size_ == 0){
        push_back(value);
    }
}

template<typename T> T vector<T>::pop(int index){
    int ret = -1;
    if (index >= 0 && index < container::size_){
        ret = array_container<T>::tab_[index];
        int i = index;
        while(i<container::size_-1){
            array_container<T>::tab_[i] = array_container<T>::tab_[i+1];
            i+=1;
        }
        container::size_--;
    }
    return ret;
}

template<typename T> T vector<T>::pop_back(){
    return pop(container::size_-1);
}

template<typename T> T vector<T>::pop_front(){
    return pop(0);
}

template<typename T> bool vector<T>::clear(){
    delete [] array_container<T>::tab_;
    array_container<T>::tab_ = new T[array_container<T>::initial_size_];
    container::size_ = 0;
    return 1;
}

#endif