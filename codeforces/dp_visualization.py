import matplotlib.pyplot as plt
import numpy as np

def visualize_dp(n, a, b, c):
    dp = np.zeros((n + 1, n + 1))

    for i in range(n, -1, -1):
        if i + a <= n:
            dp[i, i + a] = dp[i + a, i + a] + 1
        if i + b <= n:
            dp[i, i + b] = dp[i + b, i + b] + 1
        if i + c <= n:
            dp[i, i + c] = dp[i + c, i + c] + 1

    fig, ax = plt.subplots()
    cax = ax.matshow(dp, cmap='coolwarm')
    fig.colorbar(cax)

    plt.xlabel('State')
    plt.ylabel('Transition')
    plt.title(f'DP Table Visualization for n={n}, a={a}, b={b}, c={c}')

    plt.show()

n = 10  # Adjust the size for visualization purposes
a = 2
b = 3
c = 4

visualize_dp(n, a, b, c)
