<code>

    #include<stdio.h>
    int compare=0;							//전역변수로 연산 횟수 파악
    int merge(int *data, int start, int mid, int end){
            int i=start;
            int j=mid+1;
            int k=start;
            int t=0;
            int count=0;						//합병과정의 연산 횟수 중간 단계

            int tmp[3000];
            while(i<=mid && j<=end){
                    if(data[i]<=data[j]){
                            tmp[k]=data[i]; i++;}
                    else{
                            tmp[k]=data[j]; j++;}
                    k++; count++;                          //크기 비교를 한 번 할때마다 count를 증가시켰습니다.
            }
            if(i>mid){
                    for(t=j; t<=end; t++)
                            {tmp[k]=data[t]; k++;}}
            else{
                    for(t=i; t<=mid; t++)
                            {tmp[k]=data[t]; k++;}}
            count++;                                                        
            //잔류 부분을 채워 넣을 것인지 말 것인지에 대한 비교회수 1을 추가하였습니다.
            return count;
    }

    int merge_sort(int *data, int start, int end){				//merge sort 함수
            if(start<end){
                    int mid=(start+end)/2;
                    merge_sort(data, start, mid);
                    merge_sort(data, mid+1, end);
                    compare+=merge(data, start, mid, end);			//합병과정의 카운트 파악
            }
            compare++;                                 //mid를 만드는 횟수에 대하여 비교 회수를 추가하였습니다.
            return compare;			    //결론적으로 compare값을 반환합니다.
    }

    int quick_sort(int *data, int start, int end){                          //퀵 정렬은 함수 한개로 만들었습니다.

            if(start>=end)
                    {return;}

            int pivot=start;
            int i=pivot+1;
            int j=end;


            while(i<=j){
                    while(i<=end && data[i]<=data[pivot])
                            {i++; if(data[i]<=data[pivot]) compare++;}   //피봇과 비교하는 횟수만큼 증가하였습니다.
                    while(j>start && data[j] >= data[pivot])
                            {j--; if(data[j]>=data[pivot]) compare++;}   //피봇과 비교하는 횟수만큼 증가하였습니다.
                    if(i>j){
                            temp=data[j];
                            data[j]=data[pivot];
                            data[pivot]=temp;
                    }else{
                            temp=data[i];
                            data[i]=data[j];
                            data[j]=temp;
                    }
                    compare++;					//마지막 단계의 비교 
            }
            quick_sort(data, start, j-1);
            quick_sort(data, j+1, end);

            return compare;
    }

    int merge_wor_sort(int *data, int start, int end){
          //merge sort worst case는 2M(n/2)+(n-1)이므로, 이를 수식으로 함수화하였습니다.
            if(start<end){
                    merge_sort(data, start, end/2);
                    merge_sort(data, start, end/2);
                    compare+=end-start-1;
            }
            compare++;
            return compare;
    }

    int main(){
            int i, j=0, k=0, t=0, tmp=0;
            int merge_val[10], quick_val[10], merge_avg[5], quick_avg[5];
            int merge_wor[5], quick_wor[5];
            int data[6];

            FILE *input=fopen("input1.txt", "rb");			//파일 입력 부분입니다.
            while(fscanf(input, "%d", &i) != EOF)
                    {data[j]=i; j++;}
            fclose(input);

            for(k=1; k<7; k++){
                    tmp=k-1;
                    merge_avg[tmp]=0;
                    quick_avg[tmp]=0;
                    printf("\ndata=[%d]\n", data[k]);
                    int sorted[data[k]];
                    for(i=0; i<data[k]; i++)
                            sorted[i]=i;

                    for(t=0; t<data[0]; t++){
                            int random[data[k]];
                            for(i=0; i<data[k]; i++) random[i]=rand()%data[k];
                            compare=0;
                            merge_val[t]=merge_sort(random, 0, data[k]);
                            compare=0;
                            quick_val[t]=quick_sort(random, 0, data[k]);
                            merge_avg[tmp]+=merge_val[t];
                            quick_avg[tmp]+=quick_val[t];
                            printf("\n%d..  merge: %d       quick: %d\n", t+1, merge_val[t], quick_val[t]);
                    }
                    int random[data[k]];
                    for(i=0; i<data[k]; i++) random[i]=rand()%data[k];
                    merge_avg[tmp]/=data[0];
                    quick_avg[tmp]/=data[0];
                    printf("merge sort avg: %d\n", merge_avg[tmp]);
                    printf("quick sort avg: %d\n", quick_avg[tmp]);
                    quick_wor[tmp]=quick_sort(sorted, 0, data[k]);      
        //quick sort worst case는 정렬된 경우 이므로 다음과 같이 정렬된 배열을 입력으로 넣었습니다.
                    compare=0;
                    merge_wor[tmp]=merge_wor_sort(random, 0, data[k]);
                    printf("merge sort wor: %d\n", merge_wor[tmp]);
                    printf("quick sort wor: %d\n", quick_wor[tmp]);
            }

            FILE *output;						// 파일 출력부분입니다.
            output=fopen("output1.txt", "w");
            fputs(" rand_merge      worst_merge     rand_quick      worst_quick\n", output);
            fprintf(output, "===================================================================\n");
            for(k=2; k<8; k++){
                    tmp=k-1;
                    fprintf(output, "%d :   %d              %d              %d              %d\n", data[tmp], merge_avg[tmp-1], merge_wor[tmp-1], quick_avg[tmp-1], quick_wor[tmp-1]);}
            fclose(output);

            return 0;
    }

</code>
