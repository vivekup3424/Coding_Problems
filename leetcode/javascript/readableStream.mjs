import { ReadableStream } from "node:stream/web";

import { setInterval as every } from "node:timers/promises";

import { performance } from "node:perf_hooks";

const SECOND = 1000;

const stream = new ReadableStream({
  async start(controller) {
    for await (const _ of every(SECOND)) controller.enqueue(performance.now());
  },
});

for await (const value of stream) console.log(value);
