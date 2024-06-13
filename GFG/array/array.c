#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void input_array(float *arr,int length) //manually enter input in a given array
{
    float num;
    int counter = 0;
    while (counter!=length)
    {
        scanf("%f",arr+counter);
        counter++;
    }
}
void transverse_array(float arr[],int no_elements)
{
    for (int i = 0; i < no_elements; i++)
    {
        printf("%0.2f ",*(arr+i));
    }
    printf("\n");
}
void insert_array(float arr[],int no_elements,int position,float element)
{
    if (position > MAX)
    {
        printf("Out of bound position,insertion not possible\n");
        exit(0);
    }
    else if(no_elements >= MAX)
    {
        printf("Array is full,hence insertion not possible.\n");
        exit(0);
    }
    else
    {
        for (int i = no_elements-1; i >=position-1; i--)
        {
            arr[i+1] = arr[i];
        }
        arr[position-1] = element;
        
    }
}
void search_array(float arr[],int no_elements,float element)
{
    if (no_elements == 0)
    {
        printf("Emty array, no element found.\n");
        exit(1);
    }
    printf("The position of %0.2f in array are: \n",element);
    for (int i = 0; i < no_elements; i++)
    {
        if (arr[i] ==element)
        {
            printf("%d ",i+1);
        }
    }
    printf("\n");
}
float delete_array(float arr[],int no_elements,int position)
{
    if (no_elements <= 0)
    {
        printf("Array is empty.\n");
        exit(1);
    }
    else if(position > no_elements || (position<1)) //position is not index here
    {
        printf("Out of bound.\nThese many elements are not in the array\n");
        exit(1);
    }
    int deleted = arr[position-1];
    for (int i = position-1; i < no_elements-1; i++)
    {
        arr[i] = arr[i+1];
    }
    no_elements--;  //reducing the total no of characters
    return deleted;
}
float delete_last_element(float arr[],int no_elements)
{
    float num = arr[no_elements-1];
    no_elements--;
    return num;
}
float delete_value(float arr[],int no_elments,float value)  //delete a given value from array
{
    ;
}
float rotate_array(float arr[],int no_elements,int no_rotations)
{
    if(no_elements == 0)
    {
        printf("Array is empty, so rotation not possible\n");
        exit(0);
    }
    if(no_rotations>no_elements)
    {
        printf("Out of Bounds,since no. of rotation is more"); 
        printf("than no. of elements\n");
        exit(0);
    }
    /*i am doing left rotations*/
    float arr1[no_elements];
    for (int i =0; i <no_elements; i++)
    {
        if (i<no_rotations)
        {
            arr1[i+no_elements-no_rotations] = arr[i]; 
        }
        else
        {
            arr1[i-no_rotations] = arr[i];
        }
    }
    for (int i = 0; i < no_elements; i++)
    {
        arr[i] = arr1[i];
    }
    return 0;
}


int main()
{
    float arr[100];
    int length;
    printf("Enter the length of array: ");
    scanf("%d",&length);
    printf("Enter the elements of array: \n");
    input_array(arr,length);
    printf("\n*************\n");
    printf("The given array is: \n");
    transverse_array(arr,length);

}


/*Advantages of using arrays: 

    Arrays allow random access to elements. This makes accessing elements by position faster.
    Arrays have better cache locality that makes a pretty big difference in performance.
    Arrays represent multiple data items of the same type using a single name.*/

/*Disadvantages of using arrays: 
You can’t change the size i.e. once you have declared the array you can’t 
change its size because of static memory allocation. Here Insertion(s) and deletion(s) are difficult 
as the elements are stored in consecutive memory locations and the shifting operation is costly too.
*/