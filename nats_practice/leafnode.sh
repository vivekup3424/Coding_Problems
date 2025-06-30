#!/usr/bin/sh
set -eou pipefail

# a service connected to the main server
# another leaf node is connected to the main server
# clients connect to the leaf node and then interact
# with the service
#
NATS_MAIN_URL="nats://0.0.0.0:4222"
NATS_LEAF_URL="nats://0.0.0.0:4223"

nats context save main \
	--server "$NATS_MAIN_URL" \
nats context save leaf \
	--server "$NATS_LEAF_URL"

echo 'Creating the main server conf...'
cat <<- EOF > main.conf
port: 4222
leafnodes: {
	port : 7422
}
EOF

echo 'Creating the leaf node conf...'
cat <<- EOF > leaf.conf
port: 4223
leafnodes : {
	remotes: [
		{url: "nats-leaf://0.0.0.0:7422"}
	]
}
EOF

nats-server -c main.conf 2> /dev/null &
MAIN_PID=$!

sleep 1

nats-server -c leaf.conf 2> /dev/null &
LEAF_PID=$!

sleep 1

nats --context main reply 'greet' 'hello from main' &
SERVICE_PID=$!

sleep 1

nats --context leaf request 'greet' ''

nats --context leaf reply 'greet' 'hello from leaf' &
SERVICE2_PID=$!

nats --context leaf request 'greet' ''
nats --context leaf request 'greet' ''
nats --context leaf request 'greet' ''

kill $SERVICE2_PID
nats --context leaf request 'greet' ''

kill $SERVICE_PID
kill $LEAF_PID
kill $MAIN_PID
