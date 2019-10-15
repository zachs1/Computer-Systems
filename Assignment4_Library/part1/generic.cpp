// filename: generic.cpp
// compile with: g++ -g -c generic.cpp
// investigate with: objdump -t generic.o
template <class Datatype>

double add_generic(Datatype a, Datatype b){
	return a+b;
}


int main(){
    
    add_generic(1,1);
    add_generic(2.0f,2.0f);
    add_generic(3L,3L);
    add_generic(false,true);


    return 0;
}
