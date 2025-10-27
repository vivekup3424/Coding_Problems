from livekit import api
import asyncio

async def main():
    lkapi = api.LiveKitAPI("http://localhost:7880", "devKey", "secret")
    room_info = await lkapi.room.create_room(api.CreateRoomRequest(name="my-room"))
    print("room_info:", room_info)
    results = await lkapi.room.list_rooms(api.ListRoomsRequest)
    print("results:", results)
    await lkapi.aclose()

asyncio.run(main())