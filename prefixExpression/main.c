#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Bekir KURT
// Prefix ifadelerin degerini hesaplama kuyruk yapisi ile
// - + * 9 + 2 8 * + 4 8 6 3 ornek ifade

typedef struct node{
    char ifade[16];
    struct node *link;
} NODE;

typedef struct queue{
    NODE *front;
    NODE *rear;
    int count;
} QUEUE;

QUEUE* CreateQueue(){
    QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
    return q;
}

void Enqueue(QUEUE *q, char* datain){
    NODE *newNode = (NODE*)malloc(sizeof(NODE));
    strcpy(newNode->ifade, datain);
    newNode->link = NULL;
    if (q->front == NULL){
        q->front = newNode;
    }
    else{
        q->rear->link = newNode;
    }

    q->rear = newNode;
    q->count++;
}

void Dequeue(QUEUE *q, char *cikar){

    NODE *temp = q->front;
    strcpy(cikar, q->front->ifade);
    if (q->count == 1){
        q->rear = NULL;
    }

    q->front = q->front->link;
    q->count--;
    free(temp);
}

int QueueCount(QUEUE *q){
    return q->count;
}

void Display(QUEUE *q){

    NODE *position = q->front;
    printf("\n");
    printf("ifade: ");

    while (position != NULL){
        printf("%s ", position->ifade);
        position = position->link;
    }
}

void DestroyQueue(QUEUE *q){
    NODE *temp;

    while (q->front != NULL){
        temp = q->front;
        q->front = q->front->link;
        free(temp);
    }
    free(q);
}

int hesapla(char a, int b, int c){

    if(a == '+')
        return (b+c);
    else if(a == '-')
        return (b-c);
    else if(a == '*')
        return (b*c);
    else if(a == '/')
        return (b/c);
    else
        return 0;
}
void stringcopy(char data1[],char* datapointer){

    int i=0;
    while(*datapointer!='\0')
    {
        data1[i]=*datapointer;
        datapointer++;
        i++;
    }
    data1[i]='\0';
}

int ifadeyihesapla(QUEUE *q){

    char ifade[16], data1[16],data2[16],temp_opr, temp_op1, temp_op2, *datapointer;
    int i, operand1, operand2, value;
    while ((QueueCount(q)!=1)){
        Dequeue(q, ifade);
        temp_opr=ifade[0];

        if(ispunct(temp_opr)){
            datapointer=q->front->ifade;
            temp_op1=*datapointer;
            stringcopy(data1,datapointer);
            datapointer=q->front->link->ifade;
            temp_op2=*datapointer;
            stringcopy(data2,datapointer);

            if(!ispunct(temp_op1)&&!ispunct(temp_op2)){

                operand1 = atoi (data1);
                operand2 = atoi (data2);
                Dequeue( q, data1);
                Dequeue( q, data2);
                value = hesapla(temp_opr,operand1, operand2);
                printf(" \n\nHesaplanan islem : %d %c %d = %d\n",operand1,temp_opr,operand2,value);
                sprintf(ifade,"%d",value);
                datapointer=ifade;

                Enqueue(q, datapointer);
                Display(q);
            }
            else{
                datapointer=ifade;
                Enqueue(q, datapointer);
                Display(q);
            }
        }
        else{
            datapointer=ifade;
            Enqueue(q, datapointer);
            Display(q);
        }
    }

    Dequeue(q, ifade);

    return atoi(ifade);
}

int main(){

    char ifade[128];
    printf("prefix ifadeyi giriniz (aralarina bosluk birakiniz) :");
    gets(ifade);

    char *token;
    int son_deger;
    QUEUE *q = CreateQueue();

    token = ifade;

    while ((token = strtok(token, " "))){
        Enqueue(q, token);
        token = NULL;
    }

    son_deger=ifadeyihesapla(q);
    printf("\n\nifadenin sonucu : %d", son_deger);

    DestroyQueue(q);

    return 0;
}
