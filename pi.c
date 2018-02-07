#include <stdio.h>

#define KETA 500 + 1 + KETAp  /*小数点以下の桁数 + 整数部分 + 計算用*/
#define KETAp 3 /* 大きいほど正確に計算する */
#define N 360   /* 大きいほど精度を良くする */
#define ENTER 50 /* 改行までの文字数 */
#define SPACE 10 /* 空白を入れる間隔 */

void add(int x[], int y[]){
    int carry = 0, i, sum;
  
    for(i = KETA - 1; i >= 0; i--){
        sum = x[i] + y[i] + carry;
        carry = sum / 10;
        x[i] = sum % 10;
    }
}

void sub(int x[], int y[]){
    int i;
  
    for(i = KETA - 1; i >= 0; i--){
        if(x[i] - y[i] < 0){
            x[i - 1]--;
            x[i] += 10;
        }
        x[i] = x[i] - y[i];
    }
}

void mul(int x[], int n){
    int carry, i, j;
  
    for(i = KETA - 1; i >= 0; i--){
        x[i] *= n;
    }
    for(i = KETA - 1; i >= 0; i--){
        carry = x[i];
        x[i] = 0;
        for(j = i; carry != 0; j--){
            x[j] += carry % 10;
            carry /= 10;
        }
    }
}

void div(int x[], int n){
    int m = 0, i;
  
    for(i = 0; i < KETA; i++){
        m *= 10;
        m += x[i];
        x[i] = m / n;
        m -= n * x[i];
    }
}

int main(void)
{
    int a[KETA], b[KETA], t[KETA], n, i;

  

    /* ひとつめのシグマの計算 */

    for(i = 0; i < KETA; i++){
        a[i] = 0;
        t[i] = 0;
    }
    t[1] = 2;

    add(a, t);
  
    for(n = 1; n <= N; n++){
        mul(t, 2 * n - 1);

        div(t, (2 * n + 1) * 25);
    
        if(n % 2 == 0){
            add(a, t);
        }
        else{
        sub(a, t);
        }
    }

    mul(a, 4);

  

    /* 2つめのシグマの計算 */

    for(i = 0; i < KETA; i++){
        b[i] = 0;
        t[i] = 0;
    }
    t[0] = 1;

    div(t, 239);

    add(b, t);

    for(n = 1; n <= N; n++){
        mul(t, 2 * n - 1);

        div(t, (2 * n + 1) * 57121);

        if(n % 2 == 0){
            add(b, t);
        }
        else{
            sub(b, t);
        }
    }

    /* (a - b) * 4 */

    sub(a, b);

    mul(a, 4);

    /* 出力 */

    printf("\n \x1b[36m\x1b[1m円周率PI\x1b[0m = \x1b[1m%d.\x1b[0m", a[0]);
    for(i = 1; i < KETA - KETAp; i++){
        if((i - 1) % ENTER == 0 && i >= 21 && i + ENTER > KETA){
            printf(" \x1b[33m\x1b[1m*%3d-%3d桁*\x1b[0m  ", i, KETA - 1);
        }
        else if((i - 1) % ENTER == 0 && i >= 21){
            printf(" \x1b[33m\x1b[1m*%3d-%3d桁*\x1b[0m  ", i, i + ENTER - 1);
        }
        printf("\x1b[1m%d\x1b[0m", a[i]);
        if(i % ENTER == 0){
            printf("\n");
        }
        else if(i % SPACE == 0){
            printf(" ");
        }
    }
    if((i - 1) % ENTER != 0){
        printf("\n");
    }
    printf("\n");

    return 0;
}
