<script lang="ts">
    import {
        generatePKCE,
        storeAuthState,
        generateAuthorizationUrl,
        isAuthenticated,
        getUserInfoFromStorage,
        logout,
        getTokens,
        storeTokensInSession,
        testProtectedAPI,
        getUserDashboard,
        updateSite,
        type UserInfo,
    } from "$lib";
    import { onMount } from "svelte";
    import { browser } from "$app/environment";

    let isLoggedIn = $state(false);
    let userInfo: UserInfo | null = $state(null);
    let isLoading = $state(false);
    let error = $state("");
    let apiTestResult = $state("");
    let isTestingAPI = $state(false);

    // Site update states
    let isSiteUpdateExpanded = $state(false);
    let siteId = $state("f2fc3b580000000000000000");
    let siteAddress = $state("updated");
    let isUpdatingSite = $state(false);
    let siteUpdateResult = $state("");

    onMount(() => {
        if (browser) {
            checkAuthStatus();
            // Store tokens in server session if authenticated
            if (isAuthenticated()) {
                const tokens = getTokens();
                const userInfo = getUserInfoFromStorage();
                // if (tokens && userInfo) {
                //     storeTokensInSession(tokens, userInfo).catch(console.error);
                // }
            }
        }
    });

    function checkAuthStatus() {
        isLoggedIn = isAuthenticated();
        if (isLoggedIn) {
            userInfo = getUserInfoFromStorage();
        }
    }

    async function handleLogin() {
        try {
            isLoading = true;
            error = "";

            // Generate PKCE parameters
            const authState = await generatePKCE();

            // Store auth state for callback
            storeAuthState(authState);

            // Generate authorization URL
            const authUrl = generateAuthorizationUrl(authState);

            // Redirect to Zitadel
            window.location.href = authUrl;
        } catch (err) {
            error = err instanceof Error ? err.message : "Login failed";
            isLoading = false;
        }
    }

    function handleLogout() {
        const tokens = getTokens();
        logout(tokens?.id_token);
    }

    async function testAPI() {
        try {
            isTestingAPI = true;
            apiTestResult = "";
            error = "";

            const result = await testProtectedAPI();
            apiTestResult = JSON.stringify(result, null, 2);
        } catch (err) {
            error = err instanceof Error ? err.message : "API test failed";
            apiTestResult = "";
        } finally {
            isTestingAPI = false;
        }
    }

    async function testDashboardAPI() {
        try {
            isTestingAPI = true;
            apiTestResult = "";
            error = "";

            const result = await getUserDashboard();
            apiTestResult = JSON.stringify(result, null, 2);
        } catch (err) {
            error =
                err instanceof Error
                    ? err.message
                    : "Dashboard API test failed";
            apiTestResult = "";
        } finally {
            isTestingAPI = false;
        }
    }

    async function handleSiteUpdate() {
        try {
            isUpdatingSite = true;
            siteUpdateResult = "";
            error = "";

            if (!siteId.trim()) {
                throw new Error("Site ID is required");
            }

            if (!siteAddress.trim()) {
                throw new Error("Site address is required");
            }

            const result = await updateSite(siteId.trim(), siteAddress.trim());
            siteUpdateResult = JSON.stringify(result, null, 2);
        } catch (err) {
            error = err instanceof Error ? err.message : "Site update failed";
            siteUpdateResult = "";
        } finally {
            isUpdatingSite = false;
        }
    }

    function toggleSiteUpdate() {
        isSiteUpdateExpanded = !isSiteUpdateExpanded;
        if (!isSiteUpdateExpanded) {
            siteUpdateResult = "";
            error = "";
        }
    }
</script>

<div class="container">
    <div class="auth-card">
        <h1>Welcome to Zitadel Auth Demo</h1>

        {#if error}
            <div class="error">
                <p>❌ {error}</p>
            </div>
        {/if}

        {#if isLoading}
            <div class="loading">
                <p>🔄 Redirecting to login...</p>
            </div>
        {:else if isLoggedIn && userInfo}
            <div class="user-info">
                <h2>Welcome back!</h2>
                <div class="user-details">
                    {#if userInfo.picture}
                        <img
                            src={userInfo.picture}
                            alt="Profile"
                            class="profile-picture"
                        />
                    {/if}
                    <div class="details">
                        <p>
                            <strong>Name:</strong>
                            {userInfo.name ||
                                userInfo.preferred_username ||
                                "N/A"}
                        </p>
                        <p><strong>Email:</strong> {userInfo.email || "N/A"}</p>
                        <p>
                            <strong>Email Verified:</strong>
                            {userInfo.email_verified ? "✅" : "❌"}
                        </p>
                        <p><strong>User ID:</strong> {userInfo.sub}</p>
                    </div>
                </div>
                <button class="logout-btn" onclick={handleLogout}>
                    Logout
                </button>

                <div class="api-test-section">
                    <h3>🔐 Test Protected APIs</h3>
                    <div class="api-buttons">
                        <button
                            class="api-btn test-btn"
                            onclick={testAPI}
                            disabled={isTestingAPI}
                        >
                            {isTestingAPI ? "Testing..." : "Test API"}
                        </button>
                        <button
                            class="api-btn dashboard-btn"
                            onclick={testDashboardAPI}
                            disabled={isTestingAPI}
                        >
                            {isTestingAPI ? "Loading..." : "Get Dashboard"}
                        </button>
                    </div>
                </div>

                <div class="site-update-section">
                    <div
                        class="collapsible-header"
                        onclick={toggleSiteUpdate}
                        onkeydown={(e) =>
                            e.key === "Enter" || e.key === " "
                                ? toggleSiteUpdate()
                                : null}
                        role="button"
                        tabindex="0"
                        aria-expanded={isSiteUpdateExpanded}
                        aria-controls="site-update-content"
                    >
                        <h3>🏢 Site Management</h3>
                        <span
                            class="toggle-icon"
                            class:expanded={isSiteUpdateExpanded}
                        >
                            ▼
                        </span>
                    </div>

                    {#if isSiteUpdateExpanded}
                        <div
                            class="site-update-content"
                            id="site-update-content"
                        >
                            <p class="section-description">
                                Update site information using the authenticated
                                API endpoint
                            </p>

                            <div class="form-group">
                                <label for="siteId">Site ID:</label>
                                <input
                                    id="siteId"
                                    type="text"
                                    bind:value={siteId}
                                    placeholder="Enter site ID"
                                    disabled={isUpdatingSite}
                                />
                            </div>

                            <div class="form-group">
                                <label for="siteAddress">Address:</label>
                                <input
                                    id="siteAddress"
                                    type="text"
                                    bind:value={siteAddress}
                                    placeholder="Enter new address"
                                    disabled={isUpdatingSite}
                                />
                            </div>

                            <button
                                class="api-btn update-site-btn"
                                onclick={handleSiteUpdate}
                                disabled={isUpdatingSite ||
                                    !siteId.trim() ||
                                    !siteAddress.trim()}
                            >
                                {isUpdatingSite ? "Updating..." : "Update Site"}
                            </button>
                        </div>
                    {/if}
                </div>
            </div>
        {:else}
            <div class="login-section">
                <p>Please login to access your account</p>
                <button class="login-btn" onclick={handleLogin}>
                    Login with Zitadel
                </button>
            </div>
        {/if}

        {#if apiTestResult || siteUpdateResult}
            <div class="api-result">
                {#if apiTestResult}
                    <h3>📊 API Response</h3>
                    <pre class="api-response">{apiTestResult}</pre>
                    <button
                        class="clear-btn"
                        onclick={() => {
                            apiTestResult = "";
                        }}
                    >
                        Clear API Result
                    </button>
                {/if}

                {#if siteUpdateResult}
                    <h3>🏢 Site Update Response</h3>
                    <pre class="api-response">{siteUpdateResult}</pre>
                    <button
                        class="clear-btn"
                        onclick={() => {
                            siteUpdateResult = "";
                        }}
                    >
                        Clear Site Result
                    </button>
                {/if}
            </div>
        {/if}

        <div class="info-section">
            <h3>About this demo</h3>
            <p>
                This demonstration shows how to implement OAuth 2.0 with PKCE
                (Proof Key for Code Exchange) using Zitadel as the identity
                provider.
            </p>
            <ul>
                <li>✅ Secure PKCE flow implementation</li>
                <li>✅ Token exchange and validation</li>
                <li>✅ User info retrieval</li>
                <li>✅ Proper logout handling</li>
                <li>✅ Token refresh functionality</li>
            </ul>

            {#if isLoggedIn}
                <div class="demo-link">
                    <a href="/demo" class="demo-btn"
                        >🔍 View Authentication Details</a
                    >
                </div>
            {/if}

            <div class="demo-link">
                <a href="/token-generator" class="demo-btn token-btn"
                    >🔐 Token Generator</a
                >
            </div>
        </div>
    </div>
</div>

<style>
    .container {
        display: flex;
        justify-content: center;
        align-items: center;
        min-height: 100vh;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
            sans-serif;
    }

    .auth-card {
        background: white;
        padding: 2rem;
        border-radius: 12px;
        box-shadow: 0 20px 40px rgba(0, 0, 0, 0.1);
        max-width: 500px;
        width: 100%;
        margin: 1rem;
    }

    h1 {
        color: #333;
        text-align: center;
        margin-bottom: 2rem;
        font-size: 1.8rem;
    }

    .error {
        background: #fee;
        border: 1px solid #fcc;
        padding: 1rem;
        border-radius: 8px;
        margin-bottom: 1rem;
        color: #c33;
    }

    .loading {
        text-align: center;
        padding: 2rem;
        color: #666;
    }

    .user-info {
        text-align: center;
    }

    .user-info h2 {
        color: #333;
        margin-bottom: 1.5rem;
    }

    .user-details {
        display: flex;
        align-items: center;
        gap: 1rem;
        margin-bottom: 2rem;
        text-align: left;
    }

    .profile-picture {
        width: 80px;
        height: 80px;
        border-radius: 50%;
        object-fit: cover;
    }

    .details p {
        margin: 0.5rem 0;
        color: #555;
    }

    .login-section {
        text-align: center;
        padding: 2rem 0;
    }

    .login-section p {
        color: #666;
        margin-bottom: 1.5rem;
    }

    .login-btn,
    .logout-btn {
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
        border: none;
        padding: 1rem 2rem;
        border-radius: 8px;
        font-size: 1rem;
        cursor: pointer;
        transition: transform 0.2s ease;
    }

    .login-btn:hover,
    .logout-btn:hover {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.2);
    }

    .logout-btn {
        background: #dc3545;
    }

    .logout-btn:hover {
        background: #c82333;
    }

    .api-test-section {
        margin-top: 2rem;
        padding: 1.5rem;
        background: #f8f9fa;
        border-radius: 8px;
        border: 1px solid #e9ecef;
    }

    .api-test-section h3 {
        margin: 0 0 1rem 0;
        color: #495057;
        font-size: 1.1rem;
    }

    .api-buttons {
        display: flex;
        gap: 1rem;
        flex-wrap: wrap;
    }

    .api-btn {
        padding: 0.75rem 1.5rem;
        border: none;
        border-radius: 6px;
        font-size: 0.9rem;
        font-weight: 500;
        cursor: pointer;
        transition: all 0.2s ease;
        color: white;
    }

    .api-btn:disabled {
        opacity: 0.6;
        cursor: not-allowed;
    }

    .test-btn {
        background: #28a745;
    }

    .test-btn:hover:not(:disabled) {
        background: #218838;
        transform: translateY(-1px);
    }

    .dashboard-btn {
        background: #17a2b8;
    }

    .dashboard-btn:hover:not(:disabled) {
        background: #138496;
        transform: translateY(-1px);
    }

    .api-result {
        margin-top: 2rem;
        padding: 1.5rem;
        background: #f8f9fa;
        border-radius: 8px;
        border: 1px solid #e9ecef;
    }

    .api-result h3 {
        margin: 0 0 1rem 0;
        color: #495057;
        font-size: 1.1rem;
    }

    .api-response {
        background: #2d3748;
        color: #e2e8f0;
        padding: 1rem;
        border-radius: 6px;
        font-family: "Monaco", "Menlo", "Consolas", monospace;
        font-size: 0.85rem;
        line-height: 1.5;
        overflow-x: auto;
        white-space: pre-wrap;
        word-wrap: break-word;
        margin: 0 0 1rem 0;
    }

    .clear-btn {
        background: #6c757d;
        color: white;
        border: none;
        padding: 0.5rem 1rem;
        border-radius: 4px;
        font-size: 0.85rem;
        cursor: pointer;
        transition: background 0.2s ease;
    }

    .clear-btn:hover {
        background: #5a6268;
    }

    .demo-btn {
        display: inline-block;
        background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
        color: white;
        text-decoration: none;
        padding: 0.75rem 1.5rem;
        border-radius: 8px;
        font-weight: 500;
        transition: transform 0.2s ease;
        margin: 0.5rem;
    }

    .demo-btn:hover {
        transform: translateY(-2px);
        box-shadow: 0 4px 12px rgba(0, 0, 0, 0.2);
    }

    .token-btn {
        background: linear-gradient(135deg, #10b981 0%, #059669 100%);
    }

    .demo-link {
        text-align: center;
        margin-top: 1rem;
    }

    .site-update-section {
        margin-top: 2rem;
        border: 1px solid #e9ecef;
        border-radius: 8px;
        overflow: hidden;
    }

    .collapsible-header {
        display: flex;
        justify-content: space-between;
        align-items: center;
        padding: 1rem 1.5rem;
        background: #f8f9fa;
        cursor: pointer;
        transition: background-color 0.2s ease;
        border-bottom: 1px solid #e9ecef;
    }

    .collapsible-header:hover {
        background: #e9ecef;
    }

    .collapsible-header h3 {
        margin: 0;
        color: #495057;
        font-size: 1.1rem;
    }

    .toggle-icon {
        font-size: 0.8rem;
        color: #6c757d;
        transition: transform 0.2s ease;
    }

    .toggle-icon.expanded {
        transform: rotate(180deg);
    }

    .site-update-content {
        padding: 1.5rem;
        background: white;
    }

    .section-description {
        color: #6c757d;
        font-size: 0.9rem;
        margin: 0 0 1.5rem 0;
        font-style: italic;
    }

    .form-group {
        margin-bottom: 1rem;
    }

    .form-group label {
        display: block;
        margin-bottom: 0.5rem;
        color: #495057;
        font-weight: 500;
        font-size: 0.9rem;
    }

    .form-group input {
        width: 100%;
        padding: 0.75rem;
        border: 1px solid #ced4da;
        border-radius: 4px;
        font-size: 0.9rem;
        transition:
            border-color 0.2s ease,
            box-shadow 0.2s ease;
        box-sizing: border-box;
    }

    .form-group input:focus {
        outline: none;
        border-color: #667eea;
        box-shadow: 0 0 0 2px rgba(102, 126, 234, 0.25);
    }

    .form-group input:disabled {
        background-color: #f8f9fa;
        color: #6c757d;
        cursor: not-allowed;
    }

    .update-site-btn {
        background: #fd7e14;
        margin-top: 0.5rem;
    }

    .update-site-btn:hover:not(:disabled) {
        background: #e8670e;
        transform: translateY(-1px);
    }
</style>
