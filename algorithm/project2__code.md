<code>

    #include<stdio.h>
    #include<sys/time.h>
    #include<time.h>

    int count_mul=0;
    int count_add=0;

    void standard(int num){
            int arr1[num][num], arr2[num][num], arr[num][num];
            int i, j, t;
            for(i=0; i<num; i++)
                    for(j=0; j<num; j++){
                            arr1[i][j]=rand()%num;			// 행렬을 랜덤으로 채운 뒤 시작하였습니다.
                            arr2[i][j]=rand()%num;
                    }
            for(i=0; i<num; i++){
                    for(j=0; j<num; j++) {
                            arr[i][j]=0;
                            for(t=0; t<num; t++){
                                    arr[i][j]+=arr1[i][t]*arr2[t][j];	// 기본적인 행렬 곱 연산입니다.
                                    count_mul++; count_add++;	// 곱셈보다 덧셈이 1회 적으므로
                            }
                            count_add--;				// 덧셈에서 1회 감소시켰습니다.
                    }
            }
    }

    int strassen(int num, int arr1[num][num], int arr2[num][num], int arr[num][num]){
            int i=0, j=0;
            int m1[num][num], m2[num][num], m3[num][num], m4[num][num], m5[num][num], m6[num][num], m7[num][num];							// 7개의 임시 배열입니다.
            int temp1[num][num], temp2[num][num];		// 행렬간의 연산을 위한 임시 행렬입니다.
            int sm1, sm2, sm3, sm4, sm5, sm6, sm7;		// 7개의 임시 값입니다.

            if(num<=2){						// 2X2행렬인 경우 행렬간 연산이 아닌
                    sm1=(arr1[0][0]+arr1[1][1])*(arr2[0][0]+arr2[1][1]);	// 값간의 연산이므로 if로 분기시켰습니다.
                    sm2=(arr1[1][0]+arr1[1][1])*arr2[0][0];
                    sm3=arr1[0][0]*(arr2[0][1]-arr2[1][1]);
                    sm4=arr1[1][1]*(arr2[1][0]-arr2[0][0]);
                    sm5=(arr1[0][0]+arr1[0][1])*arr2[1][1];
                    sm6=(arr1[1][0]-arr1[0][0])*(arr2[0][0]+arr2[0][1]);
                    sm7=(arr1[0][1]-arr1[1][1])*(arr2[1][0]+arr2[1][1]);
                    arr[0][0]=sm1+sm4-sm5+sm7;
                    arr[0][1]=sm3+sm5;
                    arr[1][0]=sm2+sm4;
                    arr[1][1]=sm1+sm3-sm2+sm6;
                    count_add+=18;
                    count_mul+=7;
            }
            else{					//그 외에는 행렬간의 연산이 필요하므로,
                    for(i=0; i<num/2; i++)		//행렬과 그에 대한 임시 행렬을 이용해
                            for(j=0; j<num/2; j++)	//원하는 결과를 얻었습니다.
                                    {temp1[i][j]=arr1[i][j]+arr1[i+num/2][j+num/2]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i][j]+arr2[i+num/2][j+num/2]; count_add++;}
                    strassen(num/2, temp1, temp2, m1);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i+num/2][j]+arr1[i+num/2][j+num/2]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i][j];}
                    strassen(num/2, temp1, temp2, m2);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i][j];}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i][j+num/2]-arr2[i+num/2][j+num/2]; count_add++;}
                    strassen(num/2, temp1, temp2, m3);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i+num/2][j+num/2];}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i+num/2][j]-arr2[i][j]; count_add++;}
                    strassen(num/2, temp1, temp2, m4);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i][j]+arr1[i][j+num/2]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i+num/2][j+num/2];}
                    strassen(num/2, temp1, temp2, m5);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i+num/2][j]-arr1[i][j]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i][j]+arr2[i][j+num/2]; count_add++;}
                    strassen(num/2, temp1, temp2, m6);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp1[i][j]=arr1[i][j+num/2]-arr1[i+num/2][j+num/2]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {temp2[i][j]=arr2[i+num/2][j]+arr2[i+num/2][j+num/2]; count_add++;}
                    strassen(num/2, temp1, temp2, m7);

                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {arr[i][j]=m1[i][j]+m4[i][j]-m5[i][j]+m7[i][j]; count_add+=3;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {arr[i][j+num/2]=m3[i][j]+m5[i][j]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {arr[i+num/2][j]=m2[i][j]+m4[i][j]; count_add++;}
                    for(i=0; i<num/2; i++)
                            for(j=0; j<num/2; j++)
                                    {arr[i+num/2][j+num/2]=m1[i][j]+m3[i][j]-m2[i][j]+m6[i][j]; count_add+=3;}
            }

            return 0;
    }

    int main(){
            int k=0;
            int i=0, a=0, b=0, t=0, tmp=0, num=1;
            int standard_mul[6]; int standard_add[6];	//파일 출력을 위한 결과 저장 배열입니다.
            int strassen_mul[6]; int strassen_add[6];		//파일 출력을 위한 결과 저장 배열입니다.
            struct timeval start_point, end_point;		//시간 계산을 위한 구조체 선언입니다.
            double operating_time;				//시간 정보를 기록하는 변수입니다.
            double standard_time[6];			//시간 결과를 저장하는 배열입니다.
            double strassen_time[6];				//시간 결과를 저장하는 배열입니다.
            double start, end;
            struct timeval {long tv_sec; long tv_usec;};	//시간 계산에 사용되는 구조체입니다.

            printf("행렬의 크기. (2^k)에서 k를 입력");
            scanf("%d", &k);
            for(i=0; i<7; i++){
                    num=1;
                    for(t=0; t<k-3+i; t++) num*=2;
                    int arr1[num][num], arr2[num][num], arr[num][num];

                    count_mul=0; count_add=0; operating_time=0;
                    printf("---------------------------------------------------------\n");
                    printf("%d..\n", num);

                    printf("standard start..\n");
                    gettimeofday(&start_point, NULL);
                    standard(num);		//스탠다드의 경우 행렬 크기만 입력하였습니다.
                    gettimeofday(&end_point, NULL);
                    standard_mul[i]=count_mul;
                    standard_add[i]=count_add;
              // 마이크로초 단위를 표현하기 위해 다음과 같은 코드를 이용하였습니다
    operating_time=(double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
                    printf("mul: %d add: %d time: %f\n", count_mul, count_add, operating_time);

                    standard_time[i]=operating_time;
                    if(i==0) start=standard_time[i];	// 배열 첫, 마지막 원소에서 에러가 발생하여 
                    if(i==6) end=standard_time[i];	// 다음과 같이 조정하였습니다.
                    count_mul=0; count_add=0; operating_time=0;
                    printf("strassen start..\n");
                    gettimeofday(&start_point, NULL);

                    for(a=0; a<num; a++)
                            for(b=0; b<num; b++)
                                    {arr1[a][b]=rand()%num; arr2[a][b]=rand()%num;}
                    strassen(num, arr1, arr2, arr);	//쉬트라센은 배열의 크기, 대상 배열 2개, 목적 배열 입력입니다
                    gettimeofday(&end_point, NULL);
                    strassen_mul[i]=count_mul;
                    strassen_add[i]=count_add;

                    operating_time=(double)(end_point.tv_sec)+(double)(end_point.tv_usec)/1000000.0-(double)(start_point.tv_sec)-(double)(start_point.tv_usec)/1000000.0;
                    printf("mul: %d add: %d time: %f\n\n", count_mul, count_add, operating_time);
                    strassen_time[i]=operating_time;
            }
            printf("시간 단위: 마이크로 초\n");

            FILE *output;			//파일 출력 과정입니다.
            output=fopen("output2.txt", "w");
            for(i=0; i<7; i++){
                    fprintf(output, "=========================================\n");
                    if(0<=i && i<3) fprintf(output, "2^(k%d)        standard        strassen\n", i-3);
                    else if(i==3)   fprintf(output, "2^k            standard        strassen\n");
                    else            fprintf(output, "2^(k+%d)       standard        strassen\n", i-3);
                    fprintf(output, "-----------------------------------------\n");
                    fprintf(output, "mul            %d              %d\n", standard_mul[i], strassen_mul[i]);
                    fprintf(output, "add/sub        %d              %d\n", standard_add[i], strassen_add[i]);
                    if(i==0)        fprintf(output, "time           %f              %f\n", start, strassen_time[i]);
                    else if(i==6)   fprintf(output, "time           %f              %f\n", end, strassen_time[i]);
                    else fprintf(output,"time               %f              %f\n",standard_time[i],strassen_time[i]);
            }
            fclose(output);
            return 0;
    }

</code>
