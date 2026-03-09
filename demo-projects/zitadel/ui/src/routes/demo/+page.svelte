<script lang="ts">
    import { onMount } from "svelte";
    import { browser } from "$app/environment";
    import {
        isAuthenticated,
        getTokens,
        getUserInfoFromStorage,
        getTokenExpirationInfo,
        ensureValidTokens,
        getUserInfo,
        storeUserInfo,
        type TokenResponse,
        type UserInfo,
    } from "$lib";
    import { goto } from "$app/navigation";

    let isLoggedIn = $state(false);
    let tokens: TokenResponse | null = $state(null);
    let userInfo: UserInfo | null = $state(null);
    let tokenInfo = $state<any>(null);
    let isRefreshing = $state(false);
    let error = $state("");

    onMount(() => {
        if (browser) {
            checkStatus();
        }
    });

    async function checkStatus() {
        isLoggedIn = isAuthenticated();
        tokens = getTokens();
        userInfo = getUserInfoFromStorage();

        if (tokens) {
            tokenInfo = {
                accessToken: getTokenExpirationInfo(tokens.access_token),
                idToken: getTokenExpirationInfo(tokens.id_token),
                refreshToken: tokens.refresh_token
                    ? getTokenExpirationInfo(tokens.refresh_token)
                    : null,
            };
        }
    }

    async function handleRefreshTokens() {
        if (!tokens) return;

        try {
            isRefreshing = true;
            error = "";

            const newTokens = await ensureValidTokens();
            if (newTokens) {
                tokens = newTokens;
                // Refresh user info with new token
                const newUserInfo = await getUserInfo(newTokens.access_token);
                storeUserInfo(newUserInfo);
                userInfo = newUserInfo;

                // Update token info
                tokenInfo = {
                    accessToken: getTokenExpirationInfo(newTokens.access_token),
                    idToken: getTokenExpirationInfo(newTokens.id_token),
                    refreshToken: newTokens.refresh_token
                        ? getTokenExpirationInfo(newTokens.refresh_token)
                        : null,
                };

                isLoggedIn = true;
            } else {
                isLoggedIn = false;
                tokens = null;
                userInfo = null;
                tokenInfo = null;
            }
        } catch (err) {
            error =
                err instanceof Error ? err.message : "Failed to refresh tokens";
        } finally {
            isRefreshing = false;
        }
    }

    function formatTimestamp(timestamp: number): string {
        return new Date(timestamp * 1000).toLocaleString();
    }

    function goHome() {
        goto("/");
    }
</script>

<div class="demo-container">
    <div class="demo-card">
        <h1>🔐 Authentication Demo</h1>

        {#if error}
            <div class="error">
                <p>❌ {error}</p>
            </div>
        {/if}

        <div class="status-section">
            <h2>Authentication Status</h2>
            <div class="status-item">
                <span class="label">Status:</span>
                <span class="value {isLoggedIn ? 'success' : 'error'}">
                    {isLoggedIn ? "✅ Authenticated" : "❌ Not Authenticated"}
                </span>
            </div>
        </div>

        {#if isLoggedIn && userInfo}
            <div class="user-section">
                <h2>User Information</h2>
                <div class="user-details">
                    <div class="detail-row">
                        <span class="label">User ID:</span>
                        <span class="value">{userInfo.sub}</span>
                    </div>
                    <div class="detail-row">
                        <span class="label">Email:</span>
                        <span class="value">{userInfo.email || "N/A"}</span>
                    </div>
                    <div class="detail-row">
                        <span class="label">Name:</span>
                        <span class="value"
                            >{userInfo.name ||
                                userInfo.preferred_username ||
                                "N/A"}</span
                        >
                    </div>
                    <div class="detail-row">
                        <span class="label">Email Verified:</span>
                        <span class="value"
                            >{userInfo.email_verified
                                ? "✅ Yes"
                                : "❌ No"}</span
                        >
                    </div>
                </div>
            </div>
        {/if}

        {#if tokens && tokenInfo}
            <div class="token-section">
                <h2>Token Information</h2>

                <div class="token-details">
                    <h3>Access Token</h3>
                    <div class="detail-row">
                        <span class="label">Expires at:</span>
                        <span class="value"
                            >{formatTimestamp(tokenInfo.accessToken.exp)}</span
                        >
                    </div>
                    <div class="detail-row">
                        <span class="label">Status:</span>
                        <span
                            class="value {tokenInfo.accessToken.isExpired
                                ? 'error'
                                : 'success'}"
                        >
                            {tokenInfo.accessToken.isExpired
                                ? "❌ Expired"
                                : "✅ Valid"}
                        </span>
                    </div>
                </div>

                <div class="token-details">
                    <h3>ID Token</h3>
                    <div class="detail-row">
                        <span class="label">Expires at:</span>
                        <span class="value"
                            >{formatTimestamp(tokenInfo.idToken.exp)}</span
                        >
                    </div>
                    <div class="detail-row">
                        <span class="label">Status:</span>
                        <span
                            class="value {tokenInfo.idToken.isExpired
                                ? 'error'
                                : 'success'}"
                        >
                            {tokenInfo.idToken.isExpired
                                ? "❌ Expired"
                                : "✅ Valid"}
                        </span>
                    </div>
                </div>

                {#if tokenInfo.refreshToken}
                    <div class="token-details">
                        <h3>Refresh Token</h3>
                        <div class="detail-row">
                            <span class="label">Expires at:</span>
                            <span class="value"
                                >{formatTimestamp(
                                    tokenInfo.refreshToken.exp,
                                )}</span
                            >
                        </div>
                        <div class="detail-row">
                            <span class="label">Status:</span>
                            <span
                                class="value {tokenInfo.refreshToken.isExpired
                                    ? 'error'
                                    : 'success'}"
                            >
                                {tokenInfo.refreshToken.isExpired
                                    ? "❌ Expired"
                                    : "✅ Valid"}
                            </span>
                        </div>
                    </div>
                {/if}
            </div>

            <div class="actions">
                <button
                    class="refresh-btn"
                    onclick={handleRefreshTokens}
                    disabled={isRefreshing}
                >
                    {isRefreshing ? "🔄 Refreshing..." : "🔄 Refresh Tokens"}
                </button>
            </div>
        {/if}

        <div class="navigation">
            <button class="home-btn" onclick={goHome}> 🏠 Back to Home </button>
        </div>
    </div>
</div>

<style>
    .demo-container {
        display: flex;
        justify-content: center;
        align-items: flex-start;
        min-height: 100vh;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
            sans-serif;
        padding: 2rem 0;
    }

    .demo-card {
        background: white;
        padding: 2rem;
        border-radius: 12px;
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
        max-width: 800px;
        width: 100%;
        margin: 1rem;
    }

    h1 {
        color: #333;
        text-align: center;
        margin-bottom: 2rem;
        font-size: 2rem;
    }

    h2 {
        color: #333;
        margin-bottom: 1rem;
        font-size: 1.3rem;
        border-bottom: 2px solid #eee;
        padding-bottom: 0.5rem;
    }

    h3 {
        color: #555;
        margin-bottom: 0.5rem;
        font-size: 1.1rem;
    }

    .error {
        background: #fee;
        border: 1px solid #fcc;
        padding: 1rem;
        border-radius: 8px;
        margin-bottom: 1rem;
        color: #c33;
    }

    .status-section,
    .user-section,
    .token-section {
        margin-bottom: 2rem;
    }

    .status-item,
    .detail-row {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 0.5rem 0;
        border-bottom: 1px solid #f0f0f0;
    }

    .status-item:last-child,
    .detail-row:last-child {
        border-bottom: none;
    }

    .label {
        font-weight: 600;
        color: #555;
    }

    .value {
        font-family: "Monaco", "Menlo", "Ubuntu Mono", monospace;
        font-size: 0.9rem;
    }

    .value.success {
        color: #28a745;
    }

    .value.error {
        color: #dc3545;
    }

    .user-details,
    .token-details {
        background: #f8f9fa;
        padding: 1rem;
        border-radius: 8px;
        margin-bottom: 1rem;
    }

    .actions {
        display: flex;
        gap: 1rem;
        margin-bottom: 2rem;
    }

    .refresh-btn,
    .home-btn {
        padding: 0.75rem 1.5rem;
        border: none;
        border-radius: 8px;
        font-size: 1rem;
        cursor: pointer;
        transition: transform 0.2s ease;
    }

    .refresh-btn {
        background: #28a745;
        color: white;
    }

    .refresh-btn:hover:not(:disabled) {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.2);
    }

    .refresh-btn:disabled {
        background: #6c757d;
        cursor: not-allowed;
    }

    .home-btn {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
    }

    .home-btn:hover {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.2);
    }

    .navigation {
        text-align: center;
        padding-top: 2rem;
        border-top: 1px solid #eee;
    }
</style>
