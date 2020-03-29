#include <iostream>

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

void print_array(int input[], int n){
	for(int i=0; i<n; i++){
		std::cout << input[i] << ' ';
	}
	std::cout << std::endl;
}

void cartisanProduct(int toSort[], int a[], int b[], int n){
	//std::cout << "Start";
	int index = 1;
	for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) {
        	toSort[index] = a[i]+b[j];
                index++;
		}
}

void swap(int toSort[], int n1, int n2){
	int temp = toSort[n1];
	toSort[n1] = toSort[n2];
	toSort[n2] = temp;
}

void maxheapify(int toSort[], int node, int length){
	//std::cout << "node: " << node << std::endl;
	//std::cout << "length: " << length << std::endl;
	int leftChild = 2*node;
  	int rightChild = 2*node + 1;
  	
  	if (rightChild<=length && toSort[leftChild] <= toSort[rightChild]){
  		//std::cout << "1st loop for right "<< std::endl;
  		if (toSort[rightChild] > toSort[node]){
  			//std::cout << "node: " << node << std::endl;
  			//std::cout << "rightChild: " << rightChild << std::endl;
 			swap(toSort, rightChild, node);
 			maxheapify(toSort, rightChild, length);
		}
	}
	if (rightChild<=length){
		if (leftChild<=length && toSort[leftChild] > toSort[rightChild]){
		//std::cout << "1st loop for left "<< std::endl;
		if (toSort[leftChild] > toSort[node]){
			//std::cout << "node: " << node << std::endl;
  			//std::cout << "leftChild: " << leftChild << std::endl;
 			swap(toSort, leftChild, node);
 			maxheapify(toSort, leftChild, length);
			}
		}
	}else if(rightChild>length){
		if (leftChild<=length){
		//std::cout << "1st loop for left "<< std::endl;
		if (toSort[leftChild] > toSort[node]){
			//std::cout << "node: " << node << std::endl;
  			//std::cout << "leftChild: " << leftChild << std::endl;
 			swap(toSort, leftChild, node);
 			maxheapify(toSort, leftChild, length);
			}
		}
	}
		
}

void buildMaxheap(int toSort[], int length){
	int start = (int)(length-1)/2;
	//std::cout << "start: " << start << std::endl;
	for(int i=start; i>=1; i--){
		//std::cout << "i = " << i << std::endl;
		maxheapify(toSort, i, length-1);
	}
}

void heapSort(int toSort[], int length){
	buildMaxheap(toSort, length);
	int size = length-1;
	//std::cout << "len: " << length << std::endl;
	for (int i=length-1; i>1; i--){
		//std::cout << "i = " << i <<std::endl;
		size--;
		//std::cout << "size = " << size <<std::endl;
		swap(toSort, 1, i);
		maxheapify(toSort, 1, size);		
		//print_array(toSort, length);
	}
}

void printNode(int toSort[], int node){
	int leftChild = 2*node;
  	int rightChild = 2*node + 1;
  	
	std::cout << ' ' << toSort[node] << std::endl;
	std::cout << toSort[leftChild] << ' ' << toSort[rightChild];
}

