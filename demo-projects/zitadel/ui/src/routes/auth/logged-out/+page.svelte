<script lang="ts">
    import { onMount } from "svelte";
    import { goto } from "$app/navigation";
    import { browser } from "$app/environment";
    import { clearAuthState, clearTokens, clearUserInfo } from "$lib";

    onMount(() => {
        if (!browser) return;

        // Ensure all auth data is cleared
        clearAuthState();
        clearTokens();
        clearUserInfo();

        // Redirect to home page after 3 seconds
        setTimeout(() => {
            goto("/");
        }, 3000);
    });
</script>

<div class="logout-container">
    <div class="logout-card">
        <div class="logout-content">
            <h2>✅ Logged Out Successfully</h2>
            <p>You have been successfully logged out of your account.</p>
            <p class="redirect-info">
                Redirecting to home page in 3 seconds...
            </p>
            <a href="/" class="home-link">Go to Home Page</a>
        </div>
    </div>
</div>

<style>
    .logout-container {
        display: flex;
        justify-content: center;
        align-items: center;
        min-height: 100vh;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
            sans-serif;
    }

    .logout-card {
        background: white;
        padding: 3rem;
        border-radius: 12px;
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
        max-width: 400px;
        width: 100%;
        margin: 1rem;
        text-align: center;
    }

    .logout-content h2 {
        color: #28a745;
        margin-bottom: 1rem;
    }

    .logout-content p {
        color: #666;
        margin-bottom: 1rem;
        line-height: 1.5;
    }

    .redirect-info {
        font-size: 0.9rem;
        font-style: italic;
        color: #888;
    }

    .home-link {
        display: inline-block;
        margin-top: 1.5rem;
        padding: 0.75rem 1.5rem;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
        text-decoration: none;
        border-radius: 8px;
        transition: transform 0.2s ease;
    }

    .home-link:hover {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.2);
    }
</style>
