#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <limits.h>

//後々使うmax関数の定義
int max(int x, int y, int z)
{

    int m = x;
    if (y > m) m = y;

    if (z > m) m = z;

    return m;

}

//文字を比較するために数値に変換する
int suuti(int x)
{
    //塩基配列を入力（本当はテキストから取得したかった）
    char rna[] = "GGGAAACCCAACGGGAACCGACCGAUUUGACCGGAACCGGGUUGACUUGACCGUACCG"; 
    int y = rna[x] - '0'; 
    return y;
}

//後々使うδ(i,j)の作成
int delta(int a, int b)
{
    int z = suuti(a) - suuti(b);
    int d = abs(z);
    if (d == 20 || d == 4 || d == 14)

    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}

int main()
{
    //塩基配列を入力（本当はテキストから取得したかった）
    char rna[] = "GGGAAACCCAACGGGAACCGACCGAUUUGACCGGAACCGGGUUGACUUGACCGUACCG";

    //RNAの表示
    printf("RNA:%s\n", rna);

    //長さの取得
    int n = strlen(rna);

    //最後に表示するmax
    int ma = 0;

    //ガンマの配列作成
    int g[n][n];
    int i,j;

    //配列の初期化
    for (i=0; i < n; i++)
    {
        for (j=0; j < n; j++)
        {
            g[i][j] = 0;
        }
    }

    //Nussinovアルゴリズム
    //対角線で更新していくために３重ループ
    for(int k = 1; k < n; k++)
    {
        for (i=0; i < n; i++)
        {
            for (j=k; j < n; j++)
            {
                if(j > i)
                {
                    if(j - i == k)
                    {
                        int t = g[i+1][j-1] + delta(i, j);
                        g[i][j] = max(g[i+1][j], g[i][j-1], t);
                    }

                }
                
            }
        
        }

    }
    //最大値の表示
    printf("Max:%d\n", g[0][n-1]);

    //tracebackアルゴリズム
    int k = 0;
    int l = n-1;
    while(k < l)
    {

        if(g[k][l] == g[k+1][l])
        {
            printf("(%d,%d)\n",k + 1,l + 1);
            k++;
        }

        else if(g[k][l] == g[k][l-1])
        {
            printf("(%d,%d)\n",k + 1,l + 1);
            l--;
        }

        else
        {
            printf("(%d,%d)\n",k + 1,l + 1);
            k++;
            l--;
        }

    }

}