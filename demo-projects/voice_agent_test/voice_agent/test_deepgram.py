#!/usr/bin/env python3
"""Test Deepgram API structure"""
from deepgram import DeepgramClient
import inspect

client = DeepgramClient(api_key='test')
print('transcribe_file signature:')
print(inspect.signature(client.listen.v1.media.transcribe_file))


