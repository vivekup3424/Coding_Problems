import { ElevenLabsClient, play } from '@elevenlabs/elevenlabs-js';

const elevenlabs = new ElevenLabsClient({
    apiKey : "sk_023ab3f6ae7368129c95670773d4314ddf59b496c712c1aa"
});
const audio = await elevenlabs.textToSpeech.convert('JBFqnCBsd6RMkjVDRZzb', {
  text: 'This will be a placeholder for the text',
  modelId: 'eleven_multilingual_v2',
  outputFormat: 'mp3_44100_128',
});

await play(audio);

