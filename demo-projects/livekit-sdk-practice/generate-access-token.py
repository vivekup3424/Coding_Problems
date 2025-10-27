from livekit import api
import os

token = api.AccessToken() \
    .with_identity("python-bot") \
    .with_name("Python Bot") \
    .with_grants(api.VideoGrants(
        room_join=True,
        room="my-room"
    ))