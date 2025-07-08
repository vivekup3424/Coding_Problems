from openai import OpenAI

client = OpenAI(
    base_url="http://localhost:8880/v1", api_key="not-needed"
)

value = input("Please enter what should I speak")
with client.audio.speech.with_streaming_response.create(
    model="kokoro",
    voice="af_sky+af_bella", #single or multiple voicepack combo
    input=value
  ) as response:
      response.stream_to_file("output.mp3")
