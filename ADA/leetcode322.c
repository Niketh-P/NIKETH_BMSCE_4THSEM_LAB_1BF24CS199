#include <stdlib.h>

int coinChange(int* coins, int coinsSize, int amount) {

    if (amount == 0) return 0;
    

    int* dp = (int*)malloc((amount + 1) * sizeof(int));

    int max_val = amount + 1;
    dp[0] = 0;
    for (int i = 1; i <= amount; i++) {
        dp[i] = max_val;
    }
    

    for (int i = 1; i <= amount; i++) {
        for (int j = 0; j < coinsSize; j++) {

            if (coins[j] <= i) {

                if (dp[i - coins[j]] + 1 < dp[i]) {
                    dp[i] = dp[i - coins[j]] + 1;
                }
            }
        }
    }
    

    int min_coins = (dp[amount] > amount) ? -1 : dp[amount];
    
    
    free(dp);
    
    return min_coins;
}
