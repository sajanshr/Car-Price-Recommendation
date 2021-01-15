#ifndef CAR_H
#define CAR_H
typedef struct{
	char *make;
	char *model;
	double price;
	
}CAR;

typedef struct BstNode bstNode;
struct BstNode{
	CAR *car;
	bstNode *left;
	bstNode *right;
	
};


#endif //CAR_H