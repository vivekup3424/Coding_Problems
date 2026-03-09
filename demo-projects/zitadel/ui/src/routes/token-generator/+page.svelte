<script lang="ts">
    import { browser } from "$app/environment";
    import { onMount } from "svelte";

    let siteId = $state("");
    let generatedToken = $state("");
    let pastedToken = $state("");
    let tokenData = $state<any>(null);
    let validationResult = $state<any>(null);
    let decodeResult = $state<any>(null);
    let isGenerating = $state(false);
    let isValidating = $state(false);
    let isDecoding = $state(false);
    let error = $state("");
    let validationError = $state("");
    let decodeError = $state("");

    // Server configuration
    // const SERVER_URL = "http://localhost:3005"; // Introspect-su server port
    // const INTROSPECT_URL = "http://localhost:8080"; // Introspect-su server port
    const INTROSPECT_URL = "http://heimdall.keus.in"; // Introspect-su server port

    async function generateToken() {
        if (!siteId.trim()) {
            error = "Site ID is required";
            return;
        }

        isGenerating = true;
        error = "";
        generatedToken = "";
        tokenData = null;
        validationResult = null;
        decodeResult = null;
        validationError = "";
        decodeError = "";

        try {
            const response = await fetch(
                `${INTROSPECT_URL}/api/generate-token`,
                {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json",
                    },
                    body: JSON.stringify({ site_id: siteId.trim() }),
                },
            );

            const data = await response.json();

            if (response.ok) {
                tokenData = data.data;
                generatedToken = data.data.access_token;
                error = "";
            } else {
                error = data.message || "Failed to generate token";
            }
        } catch (err) {
            error =
                "Network error: " +
                (err instanceof Error ? err.message : String(err));
        } finally {
            isGenerating = false;
        }
    }

    async function validateToken() {
        const tokenToValidate = pastedToken.trim() || generatedToken;

        if (!tokenToValidate) {
            validationError =
                "No token to validate. Please generate a token or paste one below.";
            return;
        }

        isValidating = true;
        validationError = "";
        validationResult = null;

        try {
            const response = await fetch(
                `${INTROSPECT_URL}/api/validate-token`,
                {
                    method: "POST",
                    headers: {
                        "Content-Type": "application/json",
                    },
                    body: JSON.stringify({ token: tokenToValidate }),
                },
            );

            const data = await response.json();

            if (response.ok) {
                validationResult = data.data;
                validationError = "";
            } else {
                validationError = data.message || "Failed to validate token";
            }
        } catch (err) {
            validationError =
                "Network error: " +
                (err instanceof Error ? err.message : String(err));
        } finally {
            isValidating = false;
        }
    }

    async function decodeToken() {
        const tokenToDecode = pastedToken.trim() || generatedToken;

        if (!tokenToDecode) {
            decodeError =
                "No token to decode. Please generate a token or paste one below.";
            return;
        }

        isDecoding = true;
        decodeError = "";
        decodeResult = null;

        try {
            const response = await fetch(`${INTROSPECT_URL}/api/decode-token`, {
                method: "POST",
                headers: {
                    "Content-Type": "application/json",
                },
                body: JSON.stringify({ token: tokenToDecode }),
            });

            const data = await response.json();

            if (response.ok) {
                decodeResult = data.data;
                decodeError = "";
            } else {
                decodeError = data.message || "Failed to decode token";
            }
        } catch (err) {
            decodeError =
                "Network error: " +
                (err instanceof Error ? err.message : String(err));
        } finally {
            isDecoding = false;
        }
    }

    function copyToClipboard() {
        const tokenToCopy = pastedToken.trim() || generatedToken;
        if (browser && tokenToCopy) {
            navigator.clipboard.writeText(tokenToCopy);
        }
    }

    function clearAll() {
        siteId = "";
        generatedToken = "";
        pastedToken = "";
        tokenData = null;
        validationResult = null;
        decodeResult = null;
        error = "";
        validationError = "";
        decodeError = "";
    }
</script>

<div class="container">
    <h1>🔐 Token Generator</h1>
    <p class="subtitle">Generate and validate Zitadel tokens with site ID</p>

    <div class="card">
        <h2>Generate Token</h2>

        <div class="input-group">
            <label for="siteId">Site ID:</label>
            <input
                id="siteId"
                type="text"
                bind:value={siteId}
                placeholder="Enter site ID (e.g., site-123)"
                class="input-field"
            />
        </div>

        <button
            onclick={generateToken}
            disabled={isGenerating || !siteId.trim()}
            class="btn btn-primary"
        >
            {isGenerating ? "Generating..." : "Generate Token"}
        </button>

        {#if error}
            <div class="error">{error}</div>
        {/if}
    </div>

    {#if tokenData}
        <div class="card">
            <h2>Generated Token</h2>

            <div class="token-info">
                <div class="info-row">
                    <span class="label">Site ID:</span>
                    <span class="value">{tokenData.site_id}</span>
                </div>
                <div class="info-row">
                    <span class="label">Token Type:</span>
                    <span class="value">{tokenData.token_type}</span>
                </div>
                <div class="info-row">
                    <span class="label">Expires In:</span>
                    <span class="value">{tokenData.expires_in} seconds</span>
                </div>
                <div class="info-row">
                    <span class="label">Scope:</span>
                    <span class="value">{tokenData.scope}</span>
                </div>
                <div class="info-row">
                    <span class="label">Generated At:</span>
                    <span class="value"
                        >{new Date(
                            tokenData.generated_at,
                        ).toLocaleString()}</span
                    >
                </div>
            </div>

            <div class="token-display">
                <label for="token">Access Token:</label>
                <textarea
                    id="token"
                    readonly
                    value={generatedToken}
                    class="token-textarea"
                ></textarea>
                <button onclick={copyToClipboard} class="btn btn-secondary">
                    Copy Token
                </button>
            </div>
        </div>
    {/if}

    {#if validationResult}
        <div class="card">
            <h2>Validation Result</h2>

            <div class="current-token-info">
                <h3>📋 Validated Token Source</h3>
                <p>
                    <strong>Source:</strong>
                    {pastedToken.trim() ? "Pasted token" : "Generated token"}
                </p>
                {#if pastedToken.trim()}
                    <p>
                        <strong>Token Preview:</strong>
                        {pastedToken.trim().slice(0, 20)}...{pastedToken
                            .trim()
                            .slice(-10)}
                    </p>
                {:else if tokenData?.site_id}
                    <p>
                        <strong>Generated Site ID:</strong>
                        {tokenData.site_id}
                    </p>
                {/if}
            </div>

            <div class="validation-status">
                <span
                    class="status {validationResult.active
                        ? 'active'
                        : 'inactive'}"
                >
                    {validationResult.active
                        ? "✅ Token is Valid"
                        : "❌ Token is Invalid"}
                </span>
            </div>

            {#if validationResult.site_id}
                <div class="site-id-info">
                    <h3>🏷️ Site ID Information</h3>
                    <div class="info-row">
                        <span class="label">Site ID:</span>
                        <span class="value site-id-value"
                            >{validationResult.site_id}</span
                        >
                    </div>
                    <div class="success-message">
                        ✅ Site ID successfully embedded and retrieved from
                        token!
                    </div>
                </div>
            {:else}
                <div class="site-id-warning">
                    ⚠️ No site ID found in validated token
                </div>
            {/if}

            <div class="validation-details">
                <h3>Full Validation Details</h3>
                <pre>{JSON.stringify(validationResult, null, 2)}</pre>
            </div>
        </div>
    {/if}

    {#if decodeResult}
        <div class="card">
            <h2>Token Decode Result</h2>

            <div class="current-token-info">
                <h3>📋 Decoded Token Source</h3>
                <p>
                    <strong>Source:</strong>
                    {pastedToken.trim() ? "Pasted token" : "Generated token"}
                </p>
                {#if pastedToken.trim()}
                    <p>
                        <strong>Token Preview:</strong>
                        {pastedToken.trim().slice(0, 20)}...{pastedToken
                            .trim()
                            .slice(-10)}
                    </p>
                {:else if tokenData?.site_id}
                    <p>
                        <strong>Generated Site ID:</strong>
                        {tokenData.site_id}
                    </p>
                {/if}
            </div>

            {#if decodeResult.site_id}
                <div class="site-id-info">
                    <h3>🏷️ Site ID Found in Token</h3>
                    <div class="info-row">
                        <span class="label">Site ID:</span>
                        <span class="value site-id-value"
                            >{decodeResult.site_id}</span
                        >
                    </div>
                    <div class="success-message">
                        ✅ Site ID successfully embedded in JWT token!
                    </div>
                </div>
            {:else}
                <div class="site-id-warning">
                    ⚠️ No site ID found in decoded token
                </div>
            {/if}

            <div class="token-info">
                <div class="info-row">
                    <span class="label">Has Site ID:</span>
                    <span class="value"
                        >{decodeResult.has_site_id ? "Yes" : "No"}</span
                    >
                </div>
                <div class="info-row">
                    <span class="label">Token Type:</span>
                    <span class="value">{decodeResult.token_type}</span>
                </div>
                <div class="info-row">
                    <span class="label">Subject:</span>
                    <span class="value">{decodeResult.subject}</span>
                </div>
                <div class="info-row">
                    <span class="label">Issuer:</span>
                    <span class="value">{decodeResult.issuer}</span>
                </div>
                <div class="info-row">
                    <span class="label">Issued At:</span>
                    <span class="value">{decodeResult.issued_at || "N/A"}</span>
                </div>
                <div class="info-row">
                    <span class="label">Expires At:</span>
                    <span class="value">{decodeResult.expires_at || "N/A"}</span
                    >
                </div>
            </div>

            <div class="validation-details">
                <h3>Full Decoded Token</h3>
                <pre>{JSON.stringify(decodeResult.decoded_token, null, 2)}</pre>
            </div>
        </div>
    {/if}

    <div class="card">
        <h2>🔄 Or Validate Existing Token</h2>
        <p class="subtitle-small">Paste any token to validate or decode it</p>

        <div class="input-group">
            <label for="pastedToken">Token to Validate:</label>
            <textarea
                id="pastedToken"
                bind:value={pastedToken}
                placeholder="Paste your access token here..."
                class="token-textarea"
                rows="4"
            ></textarea>
        </div>

        <div class="action-buttons">
            <button
                onclick={validateToken}
                disabled={isValidating ||
                    (!pastedToken.trim() && !generatedToken)}
                class="btn btn-success"
            >
                {isValidating ? "Validating..." : "Validate Token"}
            </button>
            <button
                onclick={decodeToken}
                disabled={isDecoding ||
                    (!pastedToken.trim() && !generatedToken)}
                class="btn btn-info"
            >
                {isDecoding ? "Decoding..." : "Decode Token"}
            </button>
            <button onclick={clearAll} class="btn btn-outline">
                Clear All
            </button>
        </div>

        {#if pastedToken.trim()}
            <div class="current-token-info">
                <h3>📋 Current Token Source</h3>
                <p><strong>Using:</strong> Pasted token</p>
                <p>
                    <strong>Length:</strong>
                    {pastedToken.trim().length} characters
                </p>
                <p>
                    <strong>Preview:</strong>
                    {pastedToken.trim().slice(0, 20)}...{pastedToken
                        .trim()
                        .slice(-10)}
                </p>
            </div>
        {:else if generatedToken}
            <div class="current-token-info">
                <h3>📋 Current Token Source</h3>
                <p><strong>Using:</strong> Generated token</p>
                <p><strong>Site ID:</strong> {tokenData?.site_id || "N/A"}</p>
            </div>
        {:else}
            <div class="no-token-info">
                <p>
                    ℹ️ Generate a token above or paste an existing token to
                    validate
                </p>
            </div>
        {/if}

        {#if validationError}
            <div class="error">{validationError}</div>
        {/if}

        {#if decodeError}
            <div class="error">{decodeError}</div>
        {/if}
    </div>

    <div class="navigation">
        <a href="/" class="btn btn-outline">← Back to Home</a>
    </div>
</div>

<style>
    .container {
        max-width: 800px;
        margin: 0 auto;
        padding: 2rem;
        font-family: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto,
            sans-serif;
    }

    h1 {
        color: #2563eb;
        margin-bottom: 0.5rem;
    }

    .subtitle {
        color: #6b7280;
        margin-bottom: 2rem;
    }

    .card {
        background: white;
        border-radius: 8px;
        box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
        padding: 1.5rem;
        margin-bottom: 1.5rem;
    }

    .card h2 {
        color: #374151;
        margin-bottom: 1rem;
    }

    .input-group {
        margin-bottom: 1rem;
    }

    .input-group label {
        display: block;
        margin-bottom: 0.5rem;
        color: #374151;
        font-weight: 500;
    }

    .input-field {
        width: 100%;
        padding: 0.75rem;
        border: 1px solid #d1d5db;
        border-radius: 4px;
        font-size: 1rem;
        transition: border-color 0.2s;
    }

    .input-field:focus {
        outline: none;
        border-color: #2563eb;
        box-shadow: 0 0 0 2px rgba(37, 99, 235, 0.1);
    }

    .btn {
        padding: 0.75rem 1.5rem;
        border: none;
        border-radius: 4px;
        font-size: 1rem;
        font-weight: 500;
        cursor: pointer;
        transition: all 0.2s;
        text-decoration: none;
        display: inline-block;
        text-align: center;
    }

    .btn:disabled {
        opacity: 0.6;
        cursor: not-allowed;
    }

    .btn-primary {
        background-color: #2563eb;
        color: white;
    }

    .btn-primary:hover:not(:disabled) {
        background-color: #1d4ed8;
    }

    .btn-secondary {
        background-color: #6b7280;
        color: white;
        margin-top: 0.5rem;
    }

    .btn-secondary:hover {
        background-color: #4b5563;
    }

    .btn-success {
        background-color: #10b981;
        color: white;
    }

    .btn-success:hover:not(:disabled) {
        background-color: #059669;
    }

    .btn-info {
        background-color: #3b82f6;
        color: white;
    }

    .btn-info:hover:not(:disabled) {
        background-color: #2563eb;
    }

    .btn-outline {
        background-color: transparent;
        color: #6b7280;
        border: 1px solid #d1d5db;
    }

    .btn-outline:hover {
        background-color: #f9fafb;
        border-color: #9ca3af;
    }

    .error {
        background-color: #fef2f2;
        color: #dc2626;
        padding: 0.75rem;
        border-radius: 4px;
        margin-top: 1rem;
        border-left: 4px solid #dc2626;
    }

    .token-info {
        margin-bottom: 1rem;
    }

    .info-row {
        display: flex;
        margin-bottom: 0.5rem;
    }

    .info-row .label {
        font-weight: 500;
        color: #374151;
        min-width: 120px;
    }

    .info-row .value {
        color: #6b7280;
        word-break: break-word;
    }

    .token-display {
        margin-bottom: 1rem;
    }

    .token-display label {
        display: block;
        margin-bottom: 0.5rem;
        color: #374151;
        font-weight: 500;
    }

    .token-textarea {
        width: 100%;
        height: 120px;
        padding: 0.75rem;
        border: 1px solid #d1d5db;
        border-radius: 4px;
        font-family: "Monaco", "Consolas", monospace;
        font-size: 0.875rem;
        resize: vertical;
    }

    .action-buttons {
        display: flex;
        gap: 1rem;
        margin-bottom: 1rem;
    }

    .validation-status {
        margin-bottom: 1rem;
    }

    .status {
        padding: 0.75rem 1rem;
        border-radius: 4px;
        font-weight: 500;
        display: inline-block;
    }

    .status.active {
        background-color: #d1fae5;
        color: #065f46;
    }

    .status.inactive {
        background-color: #fef2f2;
        color: #991b1b;
    }

    .validation-details {
        background-color: #f9fafb;
        border: 1px solid #e5e7eb;
        border-radius: 4px;
        padding: 1rem;
    }

    .validation-details h3 {
        margin-top: 0;
        margin-bottom: 0.5rem;
        color: #374151;
        font-size: 1rem;
    }

    .validation-details pre {
        margin: 0;
        font-family: "Monaco", "Consolas", monospace;
        font-size: 0.875rem;
        color: #374151;
        white-space: pre-wrap;
        word-wrap: break-word;
    }

    .site-id-info {
        background-color: #f0fdf4;
        border: 1px solid #bbf7d0;
        border-radius: 4px;
        padding: 1rem;
        margin-bottom: 1rem;
    }

    .site-id-info h3 {
        margin-top: 0;
        margin-bottom: 0.75rem;
        color: #166534;
        font-size: 1.1rem;
    }

    .site-id-value {
        font-family: "Monaco", "Consolas", monospace;
        background-color: #dcfce7;
        padding: 0.25rem 0.5rem;
        border-radius: 4px;
        font-weight: 600;
        color: #166534;
    }

    .success-message {
        margin-top: 0.75rem;
        padding: 0.5rem;
        background-color: #dcfce7;
        color: #166534;
        border-radius: 4px;
        font-weight: 500;
    }

    .site-id-warning {
        background-color: #fef3c7;
        color: #92400e;
        padding: 0.75rem;
        border-radius: 4px;
        margin-bottom: 1rem;
        border-left: 4px solid #f59e0b;
    }

    .navigation {
        text-align: center;
        margin-top: 2rem;
    }

    .subtitle-small {
        color: #6b7280;
        margin-bottom: 1rem;
        font-size: 0.9rem;
    }

    .current-token-info {
        background-color: #f0f9ff;
        border: 1px solid #bae6fd;
        border-radius: 4px;
        padding: 1rem;
        margin-bottom: 1rem;
    }

    .current-token-info h3 {
        margin-top: 0;
        margin-bottom: 0.5rem;
        color: #0369a1;
        font-size: 1rem;
    }

    .current-token-info p {
        margin: 0.25rem 0;
        color: #0369a1;
        font-size: 0.9rem;
    }

    .no-token-info {
        background-color: #f9fafb;
        border: 1px solid #e5e7eb;
        border-radius: 4px;
        padding: 1rem;
        margin-bottom: 1rem;
        text-align: center;
    }

    .no-token-info p {
        margin: 0;
        color: #6b7280;
        font-style: italic;
    }

    @media (max-width: 640px) {
        .container {
            padding: 1rem;
        }

        .action-buttons {
            flex-direction: column;
        }

        .info-row {
            flex-direction: column;
        }

        .info-row .label {
            min-width: auto;
            margin-bottom: 0.25rem;
        }
    }
</style>
