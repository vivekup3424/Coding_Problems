import { Ollama } from "ollama";
const ollama = new Ollama({ host: "http://172.24.128.1:11434" });
const modelName = "qwen2.5:7b";
(async () => {
    const message = { role: 'user', content: 'Why is the sky blue?' }
    const response = await ollama.chat({ model:modelName, messages: [message], stream: true })
    for await (const part of response) {
        process.stdout.write(part.message.content)
    }
})()
