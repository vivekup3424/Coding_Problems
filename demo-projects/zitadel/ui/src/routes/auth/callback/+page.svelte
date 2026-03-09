<script lang="ts">
    import { onMount } from "svelte";
    import { goto } from "$app/navigation";
    import { browser } from "$app/environment";
    import {
        getAuthState,
        clearAuthState,
        exchangeCodeForTokens,
        storeTokens,
        getUserInfo,
        storeUserInfo,
        type TokenResponse,
        type UserInfo,
    } from "$lib";

    let isLoading = $state(true);
    let error = $state("");
    let status = $state("Processing login...");

    onMount(async () => {
        if (!browser) return;

        try {
            // Extract code and state from URL
            const urlParams = new URLSearchParams(window.location.search);
            const code = urlParams.get("code");
            const state = urlParams.get("state");
            const error_param = urlParams.get("error");
            const error_description = urlParams.get("error_description");

            // Handle authorization errors
            if (error_param) {
                throw new Error(
                    `Authorization failed: ${error_param} - ${error_description || "Unknown error"}`,
                );
            }

            // Validate required parameters
            if (!code) {
                throw new Error("No authorization code received");
            }

            if (!state) {
                throw new Error("No state parameter received");
            }

            status = "Validating authorization...";

            // Retrieve stored auth state
            const authState = getAuthState();
            if (!authState) {
                throw new Error(
                    "No auth state found. Please try logging in again.",
                );
            }

            // Validate state parameter (CSRF protection)
            if (state !== authState.state) {
                throw new Error(
                    "Invalid state parameter. Possible CSRF attack.",
                );
            }

            status = "Exchanging code for tokens...";

            // Exchange authorization code for tokens
            const tokens: TokenResponse = await exchangeCodeForTokens(
                code,
                authState.codeVerifier,
            );

            // Store tokens
            storeTokens(tokens);

            status = "Fetching user information...";

            // Get user info
            const userInfo: UserInfo = await getUserInfo(tokens.access_token);

            // Store user info
            storeUserInfo(userInfo);

            // Clean up auth state
            clearAuthState();

            status = "Login successful! Redirecting...";

            // Redirect to home page
            setTimeout(() => {
                goto("/");
            }, 1000);
        } catch (err) {
            console.error("Login callback error:", err);
            error = err instanceof Error ? err.message : "Login failed";
            isLoading = false;

            // Clean up auth state on error
            clearAuthState();

            // Redirect to home page after showing error
            // setTimeout(() => {
            //     goto("/");
            // }, 3000);
        }
    });
</script>

<div class="callback-container">
    <div class="callback-card">
        {#if isLoading}
            <div class="loading">
                <div class="spinner"></div>
                <h2>Completing Login</h2>
                <p>{status}</p>
            </div>
        {:else if error}
            <div class="error">
                <h2>❌ Login Failed</h2>
                <p>{error}</p>
                <p class="redirect-info">Redirecting to home page...</p>
            </div>
        {/if}
    </div>
</div>

<style>
    .callback-container {
        display: flex;
        justify-content: center;
        align-items: center;
        min-height: 100vh;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
            sans-serif;
    }

    .callback-card {
        background: white;
        padding: 3rem;
        border-radius: 12px;
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
        max-width: 400px;
        width: 100%;
        margin: 1rem;
        text-align: center;
    }

    .loading {
        color: #333;
    }

    .loading h2 {
        margin-bottom: 1rem;
        color: #333;
    }

    .loading p {
        color: #666;
        margin-bottom: 2rem;
    }

    .spinner {
        width: 40px;
        height: 40px;
        border: 4px solid #f3f3f3;
        border-top: 4px solid #667eea;
        border-radius: 50%;
        animation: spin 1s linear infinite;
        margin: 0 auto 2rem;
    }

    @keyframes spin {
        0% {
            transform: rotate(0deg);
        }
        100% {
            transform: rotate(360deg);
        }
    }

    .error {
        color: #c33;
    }

    .error h2 {
        margin-bottom: 1rem;
    }

    .error p {
        margin-bottom: 1rem;
        line-height: 1.5;
    }

    .redirect-info {
        color: #666;
        font-size: 0.9rem;
        font-style: italic;
    }
</style>
