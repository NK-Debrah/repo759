#include <cstdio>
#include <cstdlib>
#include <iostream>



int main(int argc, char *argv[]){
	if (argc < 2) {
        	std::cout << "Usage: task 6  N\n";
        	return 1;
    	}
	int N = std::atoi(argv[1]);
	for(int i = 0; i <= N; i++){
		 printf("%d ", i);
	}
	printf("\n");
	for(int i = N; i >= 0; i--){
    		std::cout<< i << " ";
	}
	std::cout<< "\n";
	return 0;
}
