<code>

    #include<stdio.h>
    #include<stdlib.h>

    int count=0;    // solution 갯수
    int mim=0;      // 최소한의 color 수
    int size=0;     // 입력받을 행렬의 크기

    void m_coloring(int i, int *vcolor, int (*W)[size]){
            int color;
            int j=0;
            if(promising(i, vcolor, W)){
                    if(i==size){                                                    
        // i==size에 도달, 즉, 전체 노드의 색을 모두 비교했을때, promising 조건을 만족하는 경우 출력!
                            count++;
                            if(count==1) printf("minimum m: %d\n", mim);
              // 1st의 경우에만 mim의 색깔 수 를 출력
                            printf("%d번째 방법: ", count);
                            for(j=1; j<=size; j++) printf("%d ", vcolor[j]);        
              // vcolor행렬에 저장해둔, 색깔의 배열을 출력
                            printf("\n");}

                    else{ 
        // promising 조건을 만족하면서 모든 노드의 색깔을 비교할 수 있을 때 까지 비교해나가는 과정
                            for(color=1; color<=3; color++){
                                    vcolor[i+1]=color;
                                    m_coloring(i+1, vcolor, W);}
                    }
            }
    }

    int promising(int i, int *vcolor, int (*W)[size]){
            int j=1;
            int check=1;
            while(j<i && check){
                    if(W[i][j]==1 && vcolor[i]==vcolor[j]) check=0;
              // 이전의 색깔과 같은 경우, 조건을 만족할 수 없음을 의미한다.
                    j++;}
            return check;
    }

    int main() {
            int i, j;
            printf("input size: ");
            scanf("%d", &size);

            int vcolor[size];
            int W[size][size];

            for(i=1; i<=size; i++){
                    printf("%d번째 row: ", i);
                    for(j=1; j<=size; j++)
                            scanf("%d", &W[i][j]);}
            printf("\n");

            for(i=0; i<=size; i++) vcolor[i]=-1;

            count=0;

            for(mim=3; mim<=size; mim++){
                    m_coloring(0, vcolor, W);
                    if(vcolor[size]!=-1) break;}

            printf("총 가짓 수 : %d\n", count);
    }

</code>
