export interface SmsSender {
  send(to: string, message: string): Promise<void>;
}

// POC only: prints messages to the server log instead of sending an SMS.
export class ConsoleSmsSender implements SmsSender {
  async send(to: string, message: string): Promise<void> {
    console.log(`[sms] to ${to}: ${message}`);
  }
}
