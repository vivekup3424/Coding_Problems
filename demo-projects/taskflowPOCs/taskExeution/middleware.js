import { Middleware as channelsmiddleware } from "@moleculer/channels";

export const getchannelsmiddleware = ({
	streamname = "kiotp-default",
	namespace,
	subjects = [`p1.>`, `p2.>`, `default.>`],
	debug = false,
}) => {
	subjects = subjects.map(subject => `${namespace}.${subject}`);
	console.log("~~~~~~~~~~~~~subjects", subjects);
	//@ts-ignore
	return channelsmiddleware({
		adapter: {
			type: "nats",
			//@ts-ignore
			options: {
				nats: {
					url: "nats://localhost:4222",
					connectionoptions: {
						// token: "keus-iot-platform",
						debug: debug
					},
					streamconfig: {
						name: streamname,
						subjects: subjects
					},
					consumeroptions: {
						config: {
							deliver_policy: "new",
							ack_policy: "explicit",
							max_ack_pending: 1
						}
					},
					maxinFlight: 10,
					maxRetries: 3,
					deadLettering: {
						enabled: false,
						queuename: "dead_letter_reg"
					}
				},
			}
		},
		context: true,
	})
}
