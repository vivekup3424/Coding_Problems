#!/usr/bin/env bash
#
# Walks through the auth flows against a running server, one request at a time.
#
# Usage:
#   scripts/auth-flow.sh phone [+919876543210]   # phone OTP: send, verify, /api/me, sign out
#   scripts/auth-flow.sh me                      # /api/me with the saved session cookie
#
# Env:
#   BASE_URL  server address            (default http://localhost:6969)
#   ORIGIN    Origin header to send     (default http://localhost:5173, must be in TRUSTED_ORIGINS)
#   OTP       skip the prompt and use this code
#
# The session cookie is kept in .auth-cookies.txt so later commands reuse it.
#
# Google sign-in can't be scripted with curl: better-auth checks a signed "state"
# cookie on the callback, so the flow has to start and finish in the same browser.

set -euo pipefail

BASE_URL="${BASE_URL:-http://localhost:6969}"
ORIGIN="${ORIGIN:-http://localhost:5173}"
COOKIE_JAR="${COOKIE_JAR:-.auth-cookies.txt}"

# Prints the request, sends it with the cookie jar, prints status + JSON body.
# better-auth rejects state-changing requests without an Origin header, so it is always sent.
request() {
  local method="$1" path="$2" body="${3:-}"
  echo "→ $method $path ${body:+$body}" >&2

  local args=(-sS -X "$method" "$BASE_URL$path"
    -H "Origin: $ORIGIN"
    -b "$COOKIE_JAR" -c "$COOKIE_JAR"
    -w $'\n%{http_code}')
  [[ -n "$body" ]] && args+=(-H "Content-Type: application/json" -d "$body")

  local response status
  response="$(curl "${args[@]}")"
  status="${response##*$'\n'}"
  response="${response%$'\n'*}"

  echo "← $status" >&2
  echo "$response" | jq . >&2 2>/dev/null || echo "$response" >&2
  echo >&2

  LAST_STATUS="$status"
  LAST_BODY="$response"
}

expect_status() {
  if [[ "$LAST_STATUS" != "$1" ]]; then
    echo "✗ expected $1, got $LAST_STATUS" >&2
    exit 1
  fi
}

step() { echo "=== $*" >&2; }

phone_flow() {
  local phone="${1:-+919876543210}"
  : > "$COOKIE_JAR"

  step "1. Health check"
  request GET /health
  expect_status 200

  step "2. Send OTP to $phone"
  request POST /api/auth/phone-number/send-otp "{\"phoneNumber\":\"$phone\"}"
  expect_status 200

  local code="${OTP:-}"
  if [[ -z "$code" ]]; then
    # ConsoleSmsSender prints: [sms] to +91…: Your verification code is 123456
    read -rp "Enter the OTP from the server log: " code
  fi

  step "3. Verify OTP (signs in, creates the user on first login)"
  request POST /api/auth/phone-number/verify "{\"phoneNumber\":\"$phone\",\"code\":\"$code\"}"
  expect_status 200

  step "4. Read the session through our own protected route"
  request GET /api/me
  expect_status 200

  step "5. Sign out"
  request POST /api/auth/sign-out '{}'
  expect_status 200

  step "6. /api/me after sign-out should be 401"
  request GET /api/me
  expect_status 401

  echo "✓ phone OTP flow passed" >&2
}

case "${1:-}" in
  phone) phone_flow "${2:-}" ;;
  me) request GET /api/me ;;
  *)
    sed -n '3,17p' "$0" | sed 's/^# \{0,1\}//'
    exit 1
    ;;
esac
