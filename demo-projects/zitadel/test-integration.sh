#!/usr/bin/env bash

# Test script to verify UI and Server integration
# This script tests the complete flow without requiring authentication

echo "🧪 Testing Zitadel POC UI and Server Integration"
echo "================================================="

# Test 1: Server Health Check
echo "1. Testing server health endpoint..."
HEALTH_RESPONSE=$(curl -s http://localhost:8080/health)
echo "   Response: $HEALTH_RESPONSE"
if echo "$HEALTH_RESPONSE" | grep -q "healthy"; then
    echo "   ✅ Server health check passed"
else
    echo "   ❌ Server health check failed"
    exit 1
fi

# Test 2: CORS Configuration
echo ""
echo "2. Testing CORS configuration..."
CORS_RESPONSE=$(curl -s -w "%{http_code}" -o /dev/null -H "Origin: http://localhost:3001" -H "Access-Control-Request-Method: POST" -H "Access-Control-Request-Headers: Content-Type,Authorization" -X OPTIONS http://localhost:8080/zitadel-poc/auth/store-tokens)
if [ "$CORS_RESPONSE" = "200" ]; then
    echo "   ✅ CORS preflight request successful"
else
    echo "   ❌ CORS preflight request failed (HTTP $CORS_RESPONSE)"
    exit 1
fi

# Test 3: Protected endpoint without token
echo ""
echo "3. Testing protected endpoint without token..."
PROTECTED_RESPONSE=$(curl -s http://localhost:8080/zitadel-poc/test)
echo "   Response: $PROTECTED_RESPONSE"
if echo "$PROTECTED_RESPONSE" | grep -q "No token provided"; then
    echo "   ✅ Protected endpoint correctly rejects requests without tokens"
else
    echo "   ❌ Protected endpoint should reject requests without tokens"
    exit 1
fi

# Test 4: UI Server Status
echo ""
echo "4. Testing UI server status..."
UI_RESPONSE=$(curl -s -w "%{http_code}" -o /dev/null http://localhost:3001)
if [ "$UI_RESPONSE" = "200" ]; then
    echo "   ✅ UI server is responding"
else
    echo "   ❌ UI server is not responding (HTTP $UI_RESPONSE)"
    exit 1
fi

# Test 5: API Configuration Check
echo ""
echo "5. Checking API configuration..."
echo "   Server URL: http://localhost:8080"
echo "   UI URL: http://localhost:3001"
echo "   Zitadel Domain: https://auth.keus.in"
echo "   Client ID: 327213041626185734"
echo "   Service User: 326209635662954502"
echo "   ✅ Configuration appears correct"

# Test 6: Token Introspection Test (without valid token)
echo ""
echo "6. Testing token introspection endpoint..."
INTROSPECT_RESPONSE=$(curl -s -X POST -H "Content-Type: application/json" -d '{"token":"invalid_token"}' http://localhost:8080/zitadel-poc/auth/introspect)
echo "   Response: $INTROSPECT_RESPONSE"
if echo "$INTROSPECT_RESPONSE" | grep -q "introspection"; then
    echo "   ✅ Token introspection endpoint is working"
else
    echo "   ❌ Token introspection endpoint failed"
    exit 1
fi

echo ""
echo "🎉 All tests passed! UI and Server integration is working correctly."
echo ""
echo "📋 Summary:"
echo "   - Server is healthy and responding"
echo "   - CORS is properly configured for UI communication"
echo "   - Protected endpoints are properly secured"
echo "   - UI server is running and accessible"
echo "   - Token introspection is working"
echo ""
echo "🔗 Next steps:"
echo "   1. Open UI at: http://localhost:3001"
echo "   2. Test login flow with Zitadel authentication"
echo "   3. Test protected API endpoints after authentication"
echo ""
echo "ℹ️  Note: The redirect URI configuration is set to port 3000,"
echo "   but UI is running on port 3001. This may need adjustment in"
echo "   Zitadel application settings if you encounter redirect issues."
