import { ServiceBroker, Context } from "moleculer";

export async function getSiteId(broker: ServiceBroker) {
  let node_config: any;
  try {
    node_config = await broker.call("v1.site_manager.GetNodes");
  } catch (err) {
    console.log("failed to getsite id", err);
  }
  console.log("node config", node_config);
  if (node_config?.success) {
    return node_config?.nodesInfo?.siteId;
    // let siteId:any = "Keus-199786d6-cf1f-47a7-87d9-af7f2a3ab9b0"
    // return siteId;
  } else {
    return null;
  }
}


export const sendLiveEvent = async (ctx: Context, type: string, data: any): Promise<any> => {
  ctx.broker.call("molecular_nats_gateway.PublishEvent", {
    rpcSuffix: 'LIVE-EVENTS',
    data: {
      type: type,
      data: data
    }
  });
}