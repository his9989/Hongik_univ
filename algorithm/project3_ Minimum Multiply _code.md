<code>

    #include<stdio.h>

    int order(int num, int i, int j, int (*P)[num + 1]){		// 정렬된 행렬 곱을 출력하는 함수
            if(i == j)
                    printf("A%d", i);
            else{
                    int k = P[i][j];
                    printf("(");
                    order(num, i, k, P);
                    order(num, k + 1, j, P);
                    printf(")");
            }
    }

    int mimmul(int num, int d_tmp[num], int (*P)[num+1]){		// 행렬 곱의 M, P행렬 구하는 함수입니다.
            int i=0, j=0, k=1, diagonal=0;
            int minimum=0, temp=0, count=0;
            int M[num+1][num+1];
            int d[num];

            for(i=0; i<=num; i++){					// P, M 행렬을 0으로 초기화
                    d[i]=d_tmp[i];
                    for(j=0; j<=num; j++)
                            {P[i][j]=0; M[i][j]=0;}
            }

            for(diagonal=1; diagonal<=num-1; diagonal++)		// M, P 구하기 위해 최솟값 판별 
                    for(i=1; i<=num-diagonal; i++){
                            j=i+diagonal;
                            count=0; temp=0; minimum=0;
                            for(k=i; k<=j-1; k++){
                                    temp=M[i][k]+M[k+1][j]+d[i-1]*d[i]*d[j];
                                    if(count==0){minimum=temp; P[i][j]=k;}
                                    if(minimum>temp) {minimum=temp; P[i][j]=k;}
                                    count++;}
                            M[i][j]=minimum;
                    }

            for(i=1; i<=num; i++){				//M 출력
                    for(j=1; j<=num; j++)
                            printf("%d      ", M[i][j]);
                    printf("\n");}
            printf("\n");

            for(i=1; i<=num; i++){				//P 출력
                    for(j=1; j<=num; j++)
                            printf("%d      ", P[i][j]);
                    printf("\n");}
    }

    int main(){
            int i=0, j=0, num=0;
            printf("행렬의 개수 입력: ");
            scanf("%d", &num);
            int mat_size[num];
            int tmp, result;
            int P[num+1][num+1];
            for(i=0; i<=num; i++){						// 행렬 크기 입력
                    printf("행렬 크기 입력: ");
                    scanf("%d", &tmp);
                    mat_size[i]=tmp;}
            mimmul(num, mat_size, P);
            order(num, 1, num, P);
            printf("\n");
    }

</code>
