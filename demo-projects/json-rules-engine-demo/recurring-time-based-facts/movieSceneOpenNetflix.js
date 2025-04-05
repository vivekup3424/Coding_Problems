const rule10 = {
  name: "NetflixAndChill",
  description:"If Movie scene has started between 10:00 and 18:00, open netflix, and then after 5 seconds execute the relax scene, and then after 5 seconds turn off everything",
  conditionSets: [
    {
      name: "Netflix Starter",
      conditions: [
        {
          name: "Movie scene",
          factName: "mainhub-current-scene-state",
          operation: "equal",
          factValue: "3PsWpGjXvC-185",
          serviceId: "1.0.0.kiotp.plugins.general.hubbridge",
          factStateAction: "GetCurrentScene",
          params:{
            "id" : "3PsWpGjXvC-185",
          }
        },
      ],
    },
    {
        name: "Daily time check 1",
        conditions: [
          {
            factName: "time",
            operation: "greaterThanInclusive",
            factValue: 1000,
            serviceId: "1.0.0.kiotp.plugins.general.rulesengine", //service from which we will get the current fact's value
            factStateAction: "CurrentTime", //returns time in 24 hours format
          },
        ],
      },
      {
        name: "daily time check 2",
        conditions: [
          {
            factName: "time",
            operation: "lessThanInclusive",
            factValue: 1800,
            serviceId: "1.0.0.kiotp.plugins.general.rulesengine", //service from which we will get the current fact's value
            factStateAction: "CurrentTime", //returns time in 24 hours format
          },
        ],
      },
  ],
  event: {
    type: "JustChillGuyzzz",
    params: [
      {
        order: 0,
        routines: [
          {
            serviceId: "1.0.0.kiotp.plugins.core.deepmedia.tv.appletv",
            executionName: "Start Netflix",
            moleculerEvent: "p1.trigger-deepmedia-scene-state-change",
            executionStrategy: "durable",
            customExecutionData: {
                "sceneId": "67b457a972cdc09958ef364b"
            },
          },
        ],
      },
      {
        order: 1,
        delay: 5,
      },
      {
        order: 2,
        routines: [
          {
            serviceId: "1.0.0.kiotp.plugins.general.hubbridge",
            executionName: "Start Relax Scene",
            moleculerEvent: "p1.trigger-mainhub-scene-state-change",
            executionStrategy: "durable",
            customExecutionData: {
                "sceneId": "3PsWpGjXvC-152"
            },
          },
        ],
      },
      {
        order: 3,
        delay: 5,
      },{
        order: 4,
        routines: [
          {
            serviceId: "1.0.0.kiotp.plugins.general.hubbridge",
            executionName: "All Off Scene",
            moleculerEvent: "p1.trigger-mainhub-scene-state-change",
            executionStrategy: "durable",
            customExecutionData: {
                "sceneId": "3PsWpGjXvC-153"
            },
          },
          {
            serviceId: "1.0.0.kiotp.plugins.general.hubbridge",
            executionName: "All Off Scene",
            moleculerEvent: "p1.trigger-mainhub-scene-state-change",
            executionStrategy: "durable",
            customExecutionData: {
                "sceneId": "3PsWpGjXvC-156"
            },
          },

        ],
      },
    ],
  },
  enabled: true,
  priority: 5,
};
