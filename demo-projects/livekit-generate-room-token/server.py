# server.py
import os
from livekit import api
from flask import Flask

app = Flask(__name__)

@app.route('/getToken')
def getToken():
  token = api.AccessToken("APIEeDkRRrjEn5J", "IAhfcCHMaQyruClhLAthMPKySK1qdVbNzYVYa7GKYcW") \
    .with_identity("identity") \
    .with_name("my name") \
    .with_grants(api.VideoGrants(
        room_join=True,
        room="my-room",
    ))
  return token.to_jwt()

if __name__ == "__main__":
    app.run(debug=True)