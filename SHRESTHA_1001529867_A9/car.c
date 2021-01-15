#include "car.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


long answer = -1;
bstNode * answer_node = NULL;

void printMenu()
{
	printf("\n1. Suggest Vehicle\n");
	printf("2. Add Model to Catalog\n");
	printf("3. View Catalog\n");
	printf("4. Exit\n");
}

bstNode *createCarNode(CAR * newcar){
	bstNode *newNode = calloc(1,sizeof(bstNode));
	newNode->car = newcar;
	newNode->left = newNode->right = NULL;
	return newNode;
}

bstNode *insertCarNode(bstNode *rootptr, CAR *car)
{
	if(rootptr == NULL){
		rootptr = createCarNode(car); 
	}
	else if(car->price <= rootptr->car->price){
		rootptr->left = insertCarNode(rootptr->left, car);
	}
	else{
		rootptr->right = insertCarNode(rootptr->right, car);
	}
	return rootptr;
	
}

CAR *createCar()
{
	char buffer[128]={0};
	CAR * car = calloc(1, sizeof(CAR));
	printf("Enter Make: ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	car->make = strdup(buffer);
	printf("Enter Model: ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	car->model = strdup(buffer);
	printf("Enter Price: ");
	fgets(buffer, 128, stdin);
	buffer[strlen(buffer)-1] = 0;
	car->price = atof(buffer);
	return car;
	
	
	
	
}

void decendingOrder(bstNode * root){
	if(root == NULL){
		return;
	}
	decendingOrder(root->right);
	printf("%15s %15s %15.2f\n", root->car->make, root->car->model, root->car->price);
	decendingOrder(root->left);
}
//Function to find Node with maximum value in a BST
bstNode *FindMax(bstNode* root) {
	if(root == NULL) return NULL;
	while(root->right != NULL)
		root = root->right;
	return root;
}

//Function to find Inorder Predesesor in a BST
bstNode *getPredecessor(bstNode* root, bstNode *current) {
	
	if(current == NULL) return NULL;
	if(current->left != NULL) {  //Case 1: Node has left subtree
		return FindMax(current->left); 
	}
	else {   //Case 2: No left subtree
		bstNode* predecessor = NULL;
		bstNode* ancestor = root;
		while(ancestor != current) {
			if(current->car->price > ancestor->car->price) {
				predecessor = ancestor; // 
				ancestor = ancestor->right;
			}
			else
				ancestor = ancestor->left;
		}
		return predecessor;
	}
}

void *suggest(bstNode *root, long budget)
{
	if(root->car->price <= budget)
	{
		if(root->car->price > answer)
		{
			answer = root->car->price;
			answer_node = root;
		}
	}
	if(root->left != NULL)
	{
		suggest(root->left, budget);
	}
	if(root->right != NULL)
	{
		suggest(root->right, budget);
	}
	return 0;
}
void release_tree(bstNode *node) {
	if (node != NULL) {
		free(node->car->make);
		free(node->car->model);
		free(node->car);
		release_tree(node->left);
		release_tree(node->right);
		free(node);
	}
}


int main(int argc, char **argv)
{
		bstNode * root = NULL;
		bstNode * bestPrice = NULL;
		bstNode * nextBestPrice= NULL;
		CAR *car = NULL;
		int userInput = 0;
		long budget=0;
	if(argv[1] != NULL)
	{
		FILE *fp = fopen(argv[1], "r");
		char buffer[128] = {0};
		char *token = NULL;

		while(!feof(fp))
		{	
			CAR * car = calloc(1, sizeof(CAR));
			fgets(buffer, 128, fp);
			buffer[strlen(buffer)-1] = 0;
			token = strtok(buffer, ",");
			car->make = strdup(token);
			token = strtok(NULL, ",");
			car->model = strdup(token);
			token = strtok(NULL, ",");
			car->price = atof(token);
			root = insertCarNode(root, car);
			
			
		}
	}
		
		while(userInput!=4)
		{
			answer_node = NULL;
			answer = -1;
			printMenu();
			scanf("%d", &userInput);
			getchar();
			if(userInput==1){
				printf("ENTER BUDGET: ");
				scanf("%ld", &budget);
				getchar();
				suggest(root, budget);
				if(answer == -1)
				{
					printf("Error: No Car found.\n");
				}
				else
				{
					bestPrice = answer_node;
					printf("%15s %15s %15.2f\n", bestPrice->car->make, bestPrice->car->model, bestPrice->car->price);
					nextBestPrice = getPredecessor(root, bestPrice );
					if(nextBestPrice == NULL)
					{
						printf("Error: No Car found.\n");
					}
					else
					{
						printf("%15s %15s %15.2f\n", nextBestPrice->car->make, nextBestPrice->car->model, nextBestPrice->car->price);
					}
				}
				
			}
			else if(userInput==2){
				car = createCar();
				//newNode = createCarNode(car);
				root = insertCarNode(root, car);
				
			}
			else if(userInput==3){
				if(root==NULL){
					printf("Empty vehicle list!\n");
				}
				else{
					decendingOrder(root);
				}
				
			}
			else if(userInput ==4){
				release_tree(root);
				
				
				break;
			}
			
		}
	
	
	
	
	
	return 0;
	
}
