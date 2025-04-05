import { Service, Errors } from "moleculer";
const fibonacci = (num) => {
  if (num == 1 || num == 0) {
    return 1;
  } else {
    return fibonacci(num - 1) + fibonacci(num - 2);
  }
};
const factorial = (num) => {
  if (num == 0 || num == 1) {
    return 1;
  } else {
    return num * factorial(num - 1);
  }
};

export class Math extends Service {
  constructor(broker) {
    super(broker);
    this.parseServiceSchema({
      name: "math",
      actions: {
        fact: {
          retryPolicy: {
            retries: 3,
            delay: 500,
            enabled: true,
          },
          handler(ctx) {
            const { num } = ctx.params;
            broker.logger.info("Trying it again");
            if (num >= 0 && num < 10) {
              return { success: true, data: factorial(num) };
            } else {
              throw new Errors.MoleculerRetryableError(
                "Invalid Number, Retrying..."
              );
            }
          },
        },
      },
      events: {
        "calculate.fibonacci": {
          handler(ctx) {
            const { num } = ctx.params;
            if (num >= 0 && num < 10) {
              return { success: true, data: fibonacci(num) };
            } else {
              throw new Errors.MoleculerRetryableError(
                "Invalid Number, Retrying..."
              );
            }
          },
        },
      },
      channels: {
        "p2.calculate.fibonacci": {
          maxRetries: 5,
          context: true,
          handler(ctx) {
            const { num } = ctx.params;
            if (num >= 0 && num < 10) {
              return { success: true, data: fibonacci(num) };
            } else {
              throw new Errors.MoleculerRetryableError(
                "Invalid Number, Retrying..."
              );
            }
          },
        },
      },
    });
  }
}
