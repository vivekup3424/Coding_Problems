from flask import Flask, request, jsonify
import json
import datetime

app = Flask(__name__)

@app.route('/webhook', methods=['POST'])
def webhook():
    """
    Webhook endpoint to receive logs from Fluentd
    """
    try:
        data = request.get_json()
        
        received_at = datetime.datetime.now().isoformat()
        
        print(f"[{received_at}] Received webhook data:")
        print(json.dumps(data, indent=2))
        
        return jsonify({
            "status": "success",
            "message": "Webhook received successfully",
            "received_at": received_at
        }), 200
        
    except Exception as e:
        print(f"Error processing webhook: {str(e)}")
        return jsonify({
            "status": "error",
            "message": str(e)
        }), 500

if __name__ == '__main__':
    print("Starting webhook server on port 3000...")
    app.run(host='0.0.0.0', port=3000, debug=True)
