#include <stdio.h>
#define N 5
int Rear = -1;
int Front = -1;
int q[N];

void enqueue(int x)
{
    if (Rear == N - 1)
    {
        printf("overflow\n");
    }
    else if (Front == -1 && Rear == -1)
    {
        Front = Rear = 0;
        q[Rear] = x;
    }
    else
    {
        Rear++;
        q[Rear] = x;
    }
}

void dequeue()
{
    if (Front == -1 && Rear == -1)
    {
        printf("underflow");
    }
    else if (Front = Rear)
    {
        Front = Rear = -1;
    }
    else
    {
        printf("dequeue element is %d", q[Front]);
        Front++;
    }
}
void display()
{
    if (Front == -1 && Rear == -1)
    {
        printf("empty");
    }
    else
    {
        for (int i = Front; i < Rear + 1; i++)
        {
            printf("%d\n", q[i]);
        }
    }
}
int main()
{
    int p;
    p = 5;
    enqueue(p);
    display();
}